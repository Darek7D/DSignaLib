#include <dsignal/abs.h>
#include <cmath>

namespace dsignal {

#ifdef USE_FENV_ACCESS
#pragma STDC FENV_ACCESS ON
#endif

Abs::Abs(size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow)
{

}

void Abs::push(double value)
{
    SignalProcessorBuffered::push(fabs(value));
}

void Abs::reset()
{
    SignalProcessorBuffered::reset();
}

Abs *Abs::clone() const
{
    return new Abs( *this );
}

}
