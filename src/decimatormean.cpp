#include <dsignal/decimatormean.h>
#include <stdexcept>
#include <cfenv>

namespace dsignal {

DecimatorMean::DecimatorMean(size_t mean_samples, size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_mean_samples(mean_samples),
    m_current_sum(0),
    m_current_index(0)
{
    if (m_mean_samples<=0)
        throw std::invalid_argument("Wrong value of the mean samples! Mean samples must be greater than 0.");
}

void DecimatorMean::push(double value)
{
#ifdef USE_FENV_ACCESS
    std::feclearexcept(FE_ALL_EXCEPT);
#endif
    m_current_sum+=value;
    m_current_index++;

    if (m_current_index>=m_mean_samples) {
        SignalProcessorBuffered::push(m_current_sum/static_cast<double>(m_current_index));
        m_current_sum=0;
        m_current_index=0;
    }
}

void DecimatorMean::reset()
{
    SignalProcessorBuffered::reset();
    m_current_index=0;
    m_current_sum=0;
}

DecimatorMean *DecimatorMean::clone() const
{
    return new DecimatorMean( *this );
}

}
