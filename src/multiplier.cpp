#include <dsignal/multiplier.h>
#include <stdexcept>

namespace dsignal {

Multiplier::Multiplier(double multiplier, size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_multiplier(multiplier)
{
}

void Multiplier::push(double value)
{
    SignalProcessorBuffered::push(value*m_multiplier);
}

Multiplier *Multiplier::clone() const
{
    return new Multiplier( *this );
}

}
