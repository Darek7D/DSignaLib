#include <dsignal/signalprocessorbuffered.h>
#include <stdexcept>

namespace dsignal {

SignalProcessorBuffered::SignalProcessorBuffered(size_t max_size, bool throw_overflow):
    m_max_size(max_size),
    m_throw_overflow(throw_overflow)
{
}

void SignalProcessorBuffered::push(double value)
{
    if (m_buffer.size()>=m_max_size) {
        if (m_throw_overflow)
            throw std::overflow_error("Max size reached!");
        return;
    }

    m_buffer.push_back(value);
}

double SignalProcessorBuffered::pop()
{
    double val = value();
    m_buffer.pop_front();
    return val;
}

double SignalProcessorBuffered::value() const
{
    if (m_buffer.empty())
        throw std::out_of_range("No data in buffer!");
    return m_buffer.front();
}

double& SignalProcessorBuffered::at(size_t n)
{
    return m_buffer.at(n);
}

const double& SignalProcessorBuffered::at(size_t n) const
{
    return m_buffer.at(n);
}

bool SignalProcessorBuffered::has() const
{
    return !m_buffer.empty();
}

const std::deque<double> &SignalProcessorBuffered::data()
{
    return m_buffer;
}

void SignalProcessorBuffered::reset()
{
    std::deque<double> empty;
    std::swap(m_buffer, empty);
}

SignalProcessorBuffered *SignalProcessorBuffered::clone() const
{
    return new SignalProcessorBuffered( *this );
}

size_t SignalProcessorBuffered::size() const
{
    return m_buffer.size();
}

size_t SignalProcessorBuffered::maxSize() const
{
    return m_max_size;
}

}
