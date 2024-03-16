#include <dsignal/rms.h>
#include <stdexcept>
#include <cmath>
#include <cfenv>

namespace dsignal {

#ifdef USE_FENV_ACCESS
#pragma STDC FENV_ACCESS ON
#endif

Rms::Rms(size_t dimension, size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_dimension(dimension)
{

}

void Rms::push(double value)
{
    // Todo: change the internal buffer to circular buffer
#ifdef USE_FENV_ACCESS
    std::feclearexcept(FE_ALL_EXCEPT);
#endif
    if (m_internal_buffer.size()>=m_dimension) {
        m_current_sum-=m_internal_buffer.front();
        m_internal_buffer.pop_front();
    }

    double new_value = value*value;
    m_internal_buffer.push_back(new_value);
    m_current_sum+=new_value;

    if (m_current_sum<0.0) {
        reset();
        m_current_rms = 0.0;
    } else {
        m_current_rms = sqrt(m_current_sum/m_internal_buffer.size());
    }

    SignalProcessorBuffered::push(m_current_rms);

#ifdef USE_FENV_ACCESS
    if(std::fetestexcept(FE_INVALID	  ))
        throw std::runtime_error("FE_INVALID computation error!");
    if(std::fetestexcept(FE_DIVBYZERO ))
        throw std::runtime_error("Divide by zero!");
    if(std::fetestexcept(FE_OVERFLOW  ))
        throw std::runtime_error("Overflow computation error!");
    if(std::fetestexcept(FE_UNDERFLOW ))
        throw std::runtime_error("Underflow computation error!");
#endif
}

void Rms::reset()
{
    SignalProcessorBuffered::reset();
    m_current_rms=0.0;
    m_current_sum=0.0;
    m_internal_buffer.clear();
}

Rms *Rms::clone() const
{
    return new Rms(*this);
}

}
