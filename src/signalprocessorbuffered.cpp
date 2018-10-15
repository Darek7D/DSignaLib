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

#include <dsignal/signalprocessorbuffered.h>
#include <stdexcept>

namespace dsignal {

SignalProcessorBuffered::SignalProcessorBuffered(size_t max_size, bool throw_overflow):
    m_max_size(max_size),
    m_throw_overflow(throw_overflow)
{
}

SignalProcessorBuffered::SignalProcessorBuffered(const SignalProcessorBuffered &s)
{
    m_buffer = s.m_buffer;
    m_max_size = s.m_max_size;
    m_throw_overflow = s.m_throw_overflow;
}

void SignalProcessorBuffered::push(double value)
{
    if (m_buffer.size()>=m_max_size) {
        if (m_throw_overflow)
            throw std::overflow_error("Max size reached!");
        return;
    }

    m_buffer.push_back(value);
}

double SignalProcessorBuffered::pop()
{
    if (m_buffer.empty())
        throw std::out_of_range("No data in buffer!");
    double val = m_buffer.front();
    m_buffer.pop_front();
    return val;
}

bool SignalProcessorBuffered::has()
{
    return !m_buffer.empty();
}

const std::deque<double> &SignalProcessorBuffered::data()
{
    return m_buffer;
}

void SignalProcessorBuffered::reset()
{
    std::deque<double> empty;
    std::swap(m_buffer, empty);
}

SignalProcessorBuffered *SignalProcessorBuffered::clone() const
{
    return new SignalProcessorBuffered( *this );
}

size_t SignalProcessorBuffered::size()
{
    return m_buffer.size();
}

size_t SignalProcessorBuffered::maxSize()
{
    return m_max_size;
}

}
