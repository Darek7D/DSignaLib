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

#include <dsignal/additionner.h>
#include <stdexcept>
#include <cfenv>
#include <limits>
#include <cmath>

#ifdef USE_FENV_ACCESS
#pragma STDC FENV_ACCESS ON
#endif

namespace dsignal {

Additionner::Additionner(double addend, size_t max_size):
    SignalProcessorBuffered(max_size),
    m_addend(addend)
{

}

Additionner::Additionner(const Additionner &s):
    SignalProcessorBuffered(s),
    m_addend(s.m_addend)
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
