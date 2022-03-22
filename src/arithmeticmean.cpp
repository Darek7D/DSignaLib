/*
 * Copyright (C) 2018 Tedtronix.
 * This file is part of DSignal.
 *
 * DSignal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DSignal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with DSignal.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <dsignal/arithmeticmean.h>
#include <stdexcept>
#include <cmath>
#include <cfenv>

namespace dsignal {

#ifdef USE_FENV_ACCESS
#pragma STDC FENV_ACCESS ON
#endif

ArithmeticMean::ArithmeticMean(size_t mean_samples, size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_mean_samples(mean_samples),
    m_current_sum(0)
{

}

void ArithmeticMean::push(double value)
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
    SignalProcessorBuffered::push(mean);

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

void ArithmeticMean::reset()
{
    SignalProcessorBuffered::reset();
    m_current_sum = 0;
    m_mean_buffer.clear();
}

ArithmeticMean *ArithmeticMean::clone() const
{
    return new ArithmeticMean( *this );
}

}
