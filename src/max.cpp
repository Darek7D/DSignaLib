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

#include <dsignal/max.h>
#include <limits>

namespace dsignal {

#ifdef USE_FENV_ACCESS
#pragma STDC FENV_ACCESS ON
#endif

Max::Max(size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_max(std::numeric_limits<int>::min())
{

}

Max::Max(const Max &s):
    SignalProcessorBuffered(s),
    m_max(s.m_max)
{
}

void Max::push(double value)
{
    if (value>m_max)
        m_max = value;

    SignalProcessorBuffered::push(m_max);
}

void Max::reset()
{
    SignalProcessorBuffered::reset();
    m_max = std::numeric_limits<int>::min();
}

Max *Max::clone() const
{
    return new Max( *this );
}

}
