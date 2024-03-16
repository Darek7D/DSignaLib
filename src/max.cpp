#include <dsignal/max.h>
#include <limits>

namespace dsignal {

#ifdef USE_FENV_ACCESS
#pragma STDC FENV_ACCESS ON
#endif

Max::Max(size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_max(std::numeric_limits<int>::min())
{

}

void Max::push(double value)
{
    if (value>m_max)
        m_max = value;

    SignalProcessorBuffered::push(m_max);
}

void Max::reset()
{
    SignalProcessorBuffered::reset();
    m_max = std::numeric_limits<int>::min();
}

Max *Max::clone() const
{
    return new Max( *this );
}

}
