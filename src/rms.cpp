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

#include <dsignal/rms.h>
#include <stdexcept>
#include <cmath>
#include <cfenv>

namespace dsignal {

#ifdef USE_FENV_ACCESS
#pragma STDC FENV_ACCESS ON
#endif

Rms::Rms(size_t dimension, size_t max_size):
    SignalProcessorBuffered(max_size),
    m_dimension(dimension)
{

}

Rms::Rms(const Rms &rms):
    SignalProcessorBuffered(rms)
{
    m_current_rms = rms.m_current_rms;
    m_current_sum = rms.m_current_sum;
    m_dimension = rms.m_dimension;
}

void Rms::push(double value)
{
    // Todo: change the internal buffer to circular buffer
#ifdef USE_FENV_ACCESS
    std::feclearexcept(FE_ALL_EXCEPT);
#endif
    if (m_internal_buffer.size()>=m_dimension) {
        m_current_sum-=m_internal_buffer.front();
        m_internal_buffer.pop_front();
    }

    double new_value = value*value;
    m_internal_buffer.push_back(new_value);
    m_current_sum+=new_value;
    m_current_rms = sqrt(m_current_sum/m_internal_buffer.size());

    SignalProcessorBuffered::push(m_current_rms);

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

void Rms::reset()
{
    SignalProcessorBuffered::reset();
    m_current_rms=0.0;
    m_current_sum=0.0;
    m_internal_buffer.clear();
}

Rms *Rms::clone() const
{
    return new Rms(*this);
}

}
