#include <dsignal/signalvector.h>
#include <cassert>

namespace dsignal {

SignalVector::SignalVector():
    m_enabled(true)
{
}

SignalVector::SignalVector(size_t channels, const SignalProcessor &signal_processor, std::string name):
    m_name(name),
    m_enabled(true)
{
    for (size_t i=0; i<channels; i++)
        m_signals.push_back(signal_processor.clone());
}

SignalVector::SignalVector(const SignalVector &signal_vector)
{
    m_name = signal_vector.m_name;
    m_enabled = signal_vector.m_enabled;
    for (size_t i=0; i<signal_vector.channels(); i++)
        m_signals.push_back(signal_vector.m_signals.at(i)->clone());
}

SignalVector::~SignalVector()
{
    for (auto s: m_signals)
        delete s;
}

SignalVector & SignalVector::operator=(const SignalVector &signal_vector)
{
    if(this == &signal_vector)
        return *this;

    for (auto s: m_signals)
        delete s;

    m_name = signal_vector.m_name;
    m_enabled = signal_vector.m_enabled;

    for (size_t i=0; i<signal_vector.channels(); i++)
        m_signals.push_back(signal_vector.m_signals.at(i)->clone());

    return *this;
}

Sample SignalVector::pop()
{
    std::lock_guard<std::mutex> guard(m_mutex);

    Sample s(channels());
    for (size_t c=0; c<m_signals.size(); c++)
        s.set(c, m_signals.at(c)->pop());

    return s;
}

Sample SignalVector::value() const
{
    std::lock_guard<std::mutex> guard(m_mutex);

    Sample s(channels());
    for (size_t c=0; c<m_signals.size(); c++)
        s.set(c, m_signals.at(c)->value());

    return s;
}

Sample SignalVector::at(size_t n) const
{
    std::lock_guard<std::mutex> guard(m_mutex);
    Sample s(channels());
    for (size_t c=0; c<channels(); c++)
        s.set(c, m_signals.at(c)->at(n));
    return s;
}

bool SignalVector::has() const
{
    std::lock_guard<std::mutex> guard(m_mutex);

    if (m_signals.empty())
        return false;

    for (auto s: m_signals) {
        if (!s->has())
            return false;
    }

    return true;
}

void SignalVector::push(const Sample &sample)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if (m_enabled) {
        try {
            if (sample.channels()!=channels())
                throw std::runtime_error("Not compatible sample pushed (wrong number of channels)!");

            for (size_t c=0; c<channels(); c++)
                m_signals.at(c)->push(sample.get(c));
        } catch (std::exception &e) {
            std::string s;
            s = e.what();
            s += ". " + getName();
            throw std::runtime_error(s);
        }
    }
}

size_t SignalVector::size() const
{
    std::lock_guard<std::mutex> guard(m_mutex);
    size_t ret=0;
    for (auto s: m_signals) {
        if (s->size()>ret)
            ret = s->size();
    }
    return ret;
}

void SignalVector::reset()
{
    std::lock_guard<std::mutex> guard(m_mutex);

    for (auto s: m_signals)
        s->reset();
}

SignalVector *SignalVector::clone() const
{
    return new SignalVector(*this);
}

void SignalVector::enable(bool enable)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    m_enabled = enable;
}

bool SignalVector::enabled()
{
    return m_enabled;
}

size_t SignalVector::channels() const
{
    return m_signals.size();
}

void SignalVector::setName(const std::string &name)
{
    m_name = name;
}

std::string SignalVector::getName() const
{
    return m_name;
}

SignalProcessor *SignalVector::getSignalProcessor(size_t channel) const
{
    return m_signals.at(channel);
}

SignalVector &SignalVector::operator>>(SignalVector &output_signal)
{
    while (has())
        output_signal.push(pop());
    return output_signal;
}

Sample &SignalVector::operator>>(Sample &output_sample)
{
    if (has())
        output_sample = pop();
    return output_sample;
}

}
