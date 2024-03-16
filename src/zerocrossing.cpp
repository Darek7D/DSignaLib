#include <dsignal/zerocrossing.h>
#include <limits>
#include <cmath>

namespace dsignal {

ZeroCrossing::ZeroCrossing(size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_zero_crossing(0),
    m_last_value(0),
    m_has_last_value(false)
{

}

void ZeroCrossing::push(double value)
{
    if (std::signbit(m_last_value) != std::signbit(value) && m_has_last_value)
        m_zero_crossing+=1;
    m_has_last_value = true;
    m_last_value = value;
    SignalProcessorBuffered::push(m_zero_crossing);
}

void ZeroCrossing::reset()
{
    SignalProcessorBuffered::reset();
    m_zero_crossing = 0;
    m_has_last_value = false;
    m_last_value = 0;
}

ZeroCrossing *ZeroCrossing::clone() const
{
    return new ZeroCrossing( *this );
}

}
