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

#include <dsignal/min.h>
#include <limits>

namespace dsignal {

Min::Min(size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_min(std::numeric_limits<int>::max())
{

}

Min::Min(const Min &s):
    SignalProcessorBuffered(s),
    m_min(s.m_min)
{
}

void Min::push(double value)
{
    if (value<m_min)
        m_min = value;

    SignalProcessorBuffered::push(m_min);
}

void Min::reset()
{
    SignalProcessorBuffered::reset();
    m_min = std::numeric_limits<int>::max();
}

Min *Min::clone() const
{
    return new Min( *this );
}

}
