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

Rms::Rms(size_t dimension):
    SignalProcessorBuffered(dimension)
{

}

Rms::Rms(const Rms &rms):
    SignalProcessorBuffered(rms)
{
    m_current_rms=rms.m_current_rms;
    m_current_sum=rms.m_current_sum;
}

void Rms::push(double value)
{
#ifdef USE_FENV_ACCESS
    std::feclearexcept(FE_ALL_EXCEPT);
#endif

    if (size()>=maxSize())
        m_current_sum-=SignalProcessorBuffered::pop();

    double new_value = value*value;
    SignalProcessorBuffered::push(new_value);
    m_current_sum+=new_value;
    m_current_rms = sqrt(m_current_sum/size());

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

double Rms::pop()
{
    return m_current_rms;
}

void Rms::reset()
{
    SignalProcessorBuffered::reset();
    m_current_rms=0.0;
    m_current_sum=0.0;
}

Rms *Rms::clone() const
{
    return new Rms(*this);
}

}
