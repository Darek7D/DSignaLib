#include <dsignal/signalprocessorsimple.h>
#include <stdexcept>

namespace dsignal {

SignalProcessorSimple::SignalProcessorSimple():
    m_value(0.0),
    m_has(false)
{

}

double SignalProcessorSimple::pop()
{
    m_has = false;
    return m_value;
}

double SignalProcessorSimple::value() const
{
    checkHas();
    return m_value;
}

double& SignalProcessorSimple::at(size_t n)
{
    checkHas();
    checkRange(n);
    return m_value;
}

const double& SignalProcessorSimple::at(size_t n) const
{
    checkHas();
    checkRange(n);
    return m_value;
}

bool SignalProcessorSimple::has() const
{
    return m_has;
}

void SignalProcessorSimple::push(double value)
{
    m_value = value;
    m_has = true;
}

size_t SignalProcessorSimple::size() const
{
    return has();
}

void SignalProcessorSimple::reset()
{
    m_has = false;
}

SignalProcessorSimple *SignalProcessorSimple::clone() const
{
    return new SignalProcessorSimple(*this);
}

void SignalProcessorSimple::checkHas() const
{
    if (!m_has)
        throw std::out_of_range("No data in buffer!");
}

void SignalProcessorSimple::checkRange(size_t n) const
{
    if (n!=0)
        throw std::out_of_range("The element is out of range!");
}

}
