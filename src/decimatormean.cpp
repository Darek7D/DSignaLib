/*
 * Copyright (C) 2018 Tedtronix.
 * This file is part of DSignal.
 *
 * DSignal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DSignal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DSignal.  If not, see <http://www.gnu.org/licenses/>.
 */

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
