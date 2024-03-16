#include <dsignal/dcmeanremoval.h>
#include <stdexcept>
#include <cmath>
#include <cfenv>

namespace dsignal {

#ifdef USE_FENV_ACCESS
#pragma STDC FENV_ACCESS ON
#endif

DcMeanRemoval::DcMeanRemoval(size_t mean_samples, size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_mean_samples(mean_samples),
    m_current_sum(0)
{

}

void DcMeanRemoval::push(double value)
{
#ifdef USE_FENV_ACCESS
    std::feclearexcept(FE_ALL_EXCEPT);
#endif

    // Keep no more than m_mean_samples samples
    if (m_mean_buffer.size()>=m_mean_samples) {
        m_current_sum-=m_mean_buffer.front();
        m_mean_buffer.pop_front();
    }

    // Compute a sum and remember the new value
    m_current_sum+=value;
    m_mean_buffer.push_back(value);

    // Compute arithmetic mean value
    double mean = m_current_sum/(double)m_mean_buffer.size();

    // Store new value in buffer
    SignalProcessorBuffered::push(value-mean);

#ifdef USE_FENV_ACCESS
    // Check computation errors
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

void DcMeanRemoval::reset()
{
    SignalProcessorBuffered::reset();
    m_current_sum = 0;
    m_mean_buffer.clear();
}

DcMeanRemoval *DcMeanRemoval::clone() const
{
    return new DcMeanRemoval( *this );
}

}
