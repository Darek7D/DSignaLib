#include <dsignal/filterfir.h>
#include <algorithm>
#include <stdexcept>
#include <cfenv>

#ifdef USE_FENV_ACCESS
#pragma STDC FENV_ACCESS ON
#endif

namespace dsignal {

FilterFir::FilterFir(size_t max_buffer_size, bool throw_overflow):
    SignalProcessorBuffered(max_buffer_size, throw_overflow)
{

}

FilterFir::FilterFir(const std::vector<double> &a, size_t max_buffer_size, bool throw_overflow):
    SignalProcessorBuffered(max_buffer_size, throw_overflow),
    m_a(a)
{
}

void FilterFir::push(double value)
{
    m_filter_buffer.push_back(value);
    if (m_filter_buffer.size()>m_a.size())
        m_filter_buffer.pop_front();
    process();
}

void FilterFir::process()
{
#ifdef USE_FENV_ACCESS
    std::feclearexcept(FE_ALL_EXCEPT);
#endif

    double sum = 0.0;
    std::vector<double>::const_iterator a_it = m_a.begin();
    for (double v: m_filter_buffer) {
        sum += v*(*a_it);
        ++a_it;
    }
    SignalProcessorBuffered::push(sum);

#ifdef USE_FENV_ACCESS
    if(std::fetestexcept(FE_INVALID	  ))
        throw std::runtime_error("FilterFir::process(): FE_INVALID computation error!");
    if(std::fetestexcept(FE_DIVBYZERO ))
        throw std::runtime_error("FilterFir::process(): Divide by zero!");
    if(std::fetestexcept(FE_OVERFLOW  ))
        throw std::runtime_error("FilterFir::process(): Overflow computation error!");
    if(std::fetestexcept(FE_UNDERFLOW ))
        throw std::runtime_error("FilterFir::process(): Underflow computation error!");
#endif
}

void FilterFir::reset()
{
    SignalProcessorBuffered::reset();
    std::deque<double> empty;
    std::swap(m_filter_buffer, empty);
}

FilterFir *FilterFir::clone() const
{
    return new FilterFir(*this);
}

}
