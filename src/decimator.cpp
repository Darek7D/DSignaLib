#include <dsignal/decimator.h>
#include <stdexcept>

namespace dsignal {

Decimator::Decimator(int factor, size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_factor(factor),
    m_counter(0)
{
    if (m_factor<=0)
        throw std::invalid_argument("Wrong value of the factor! The factor must be greater than 0.");
}

void Decimator::push(double value)
{
    if (m_counter%m_factor==0)
        SignalProcessorBuffered::push(value);
    m_counter++;
}

void Decimator::reset()
{
    SignalProcessorBuffered::reset();
    m_counter=0;
}

Decimator *Decimator::clone() const
{
    return new Decimator( *this );
}

}
