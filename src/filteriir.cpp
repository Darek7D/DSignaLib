#include <dsignal/filteriir.h>
#include <stdexcept>
#include <cfenv>

#ifdef USE_FENV_ACCESS
#pragma STDC FENV_ACCESS ON
#endif

namespace dsignal {

FilterIir::FilterIir(size_t max_buffer_size, bool throw_overflow):
    SignalProcessorBuffered(max_buffer_size, throw_overflow)
{

}

FilterIir::FilterIir(const std::vector<double> &b,
                     const std::vector<double> &a,
                     size_t max_buffer_size, bool throw_overflow):
    SignalProcessorBuffered(max_buffer_size, throw_overflow),
    m_b(b),
    m_a(a)
{
    if (m_b.size()!=m_a.size())
        throw std::invalid_argument("The size of coefficients is different!");

    m_filter_buffer.resize(m_a.size(), 0);
    m_filter_feedback.resize(m_a.size(), 0);
}

void FilterIir::push(double value)
{
    m_filter_buffer.push_front(value);
    m_filter_buffer.pop_back();
    process();
}

void FilterIir::process()
{
#ifdef USE_FENV_ACCESS
    std::feclearexcept(FE_ALL_EXCEPT);
#endif
    double sum = 0.0;

    m_filter_feedback.pop_back();

    sum = m_filter_buffer[0] * m_b[0];
    for (size_t i=1; i<m_filter_buffer.size(); i++)
        sum += (m_filter_buffer[i] * m_b[i]) - (m_filter_feedback[i-1] * m_a[i]);

    m_filter_feedback.push_front(sum);

    SignalProcessorBuffered::push(sum);

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


void FilterIir::reset()
{
    SignalProcessorBuffered::reset();
    std::deque<double> empty1;
    std::swap(m_filter_buffer, empty1);
    std::deque<double> empty2;
    std::swap(m_filter_feedback, empty2);

    m_filter_buffer.resize(m_a.size(), 0);
    m_filter_feedback.resize(m_a.size(), 0);
}

FilterIir *FilterIir::clone() const
{
    return new FilterIir(*this);
}

}
