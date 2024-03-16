#include <dsignal/min.h>
#include <limits>

namespace dsignal {

Min::Min(size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_min(std::numeric_limits<int>::max())
{

}

void Min::push(double value)
{
    if (value<m_min)
        m_min = value;

    SignalProcessorBuffered::push(m_min);
}

void Min::reset()
{
    SignalProcessorBuffered::reset();
    m_min = std::numeric_limits<int>::max();
}

Min *Min::clone() const
{
    return new Min( *this );
}

}
