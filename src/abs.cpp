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

Abs::Abs(const Abs &s):
    SignalProcessorBuffered(s)
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
