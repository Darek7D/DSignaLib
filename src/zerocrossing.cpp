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

#include <dsignal/zerocrossing.h>
#include <limits>
#include <cmath>

namespace dsignal {

ZeroCrossing::ZeroCrossing(size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_zero_crossing(0),
    m_last_value(0),
    m_has_last_value(false)
{

}

ZeroCrossing::ZeroCrossing(const ZeroCrossing &s):
    SignalProcessorBuffered(s),
    m_zero_crossing(s.m_zero_crossing),
    m_last_value(s.m_last_value),
    m_has_last_value(s.m_has_last_value)
{
}

void ZeroCrossing::push(double value)
{
    if (std::signbit(m_last_value) != std::signbit(value) && m_has_last_value)
        m_zero_crossing+=1;
    m_has_last_value = true;
    m_last_value = value;
    SignalProcessorBuffered::push(m_zero_crossing);
}

void ZeroCrossing::reset()
{
    SignalProcessorBuffered::reset();
    m_zero_crossing = 0;
    m_has_last_value = false;
    m_last_value = 0;
}

ZeroCrossing *ZeroCrossing::clone() const
{
    return new ZeroCrossing( *this );
}

}
