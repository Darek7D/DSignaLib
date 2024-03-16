#include <dsignal/additionner.h>
#include <stdexcept>
#include <cfenv>
#include <limits>
#include <cmath>

#ifdef USE_FENV_ACCESS
#pragma STDC FENV_ACCESS ON
#endif

namespace dsignal {

Additionner::Additionner(double addend, size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_addend(addend)
{

}

void Additionner::push(double value)
{
#ifdef USE_FENV_ACCESS
    std::feclearexcept(FE_ALL_EXCEPT);
#endif
    double new_value = value + m_addend;

#ifdef USE_FENV_ACCESS
    if(std::fetestexcept(FE_INVALID	  ))
        throw std::runtime_error("FE_INVALID computation error!");
    if(std::fetestexcept(FE_OVERFLOW  ))
        throw std::runtime_error("Overflow computation error!");
    if(std::fetestexcept(FE_UNDERFLOW ))
        throw std::runtime_error("Underflow computation error!");
#endif
    SignalProcessorBuffered::push(new_value);
}

Additionner *Additionner::clone() const
{
    return new Additionner( *this );
}

}
