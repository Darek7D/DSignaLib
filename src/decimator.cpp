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

#include <dsignal/decimator.h>
#include <stdexcept>

namespace dsignal {

Decimator::Decimator(int factor, size_t max_size, bool throw_overflow):
    SignalProcessorBuffered(max_size, throw_overflow),
    m_factor(factor),
    m_counter(0)
{
    if (m_factor<=0)
        throw std::invalid_argument("Wrong value of the factor! The factor must be greater than 0.");
}

Decimator::Decimator(const Decimator &s):
    SignalProcessorBuffered(s),
    m_factor(s.m_factor)
{

}

void Decimator::push(double value)
{
    if (m_counter%m_factor==0)
        SignalProcessorBuffered::push(value);
    m_counter++;
}

void Decimator::reset()
{
    SignalProcessorBuffered::reset();
    m_counter=0;
}

Decimator *Decimator::clone() const
{
    return new Decimator( *this );
}

}
