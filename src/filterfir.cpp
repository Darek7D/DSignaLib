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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "filterfir.h"
#include <algorithm>
#include <stdexcept>
#include <cfenv>

#pragma STDC FENV_ACCESS ON

namespace dsignal {

FilterFir::FilterFir(const std::vector<double> &a, int max_buffer_size):
    SignalProcessorBuffered(max_buffer_size),
    m_a(a)
{
}

FilterFir::FilterFir(const FilterFir &filter):
    SignalProcessorBuffered(filter)
{
    m_filter_buffer = filter.m_filter_buffer;
    m_a = filter.m_a;
}

void FilterFir::push(double value)
{
    m_filter_buffer.push_back(value);
    if (m_filter_buffer.size()>m_a.size())
        m_filter_buffer.pop_front();
    process();
}

void FilterFir::process()
{
    std::feclearexcept(FE_ALL_EXCEPT);

    double sum = 0.0;
    std::vector<double>::const_iterator a_it = m_a.begin();
    for (double v: m_filter_buffer) {
        sum += v*(*a_it);
        ++a_it;
    }
    SignalProcessorBuffered::push(sum);

    if(std::fetestexcept(FE_INVALID	  ))
        throw std::runtime_error("FE_INVALID computation error!");
    if(std::fetestexcept(FE_DIVBYZERO ))
        throw std::runtime_error("Divide by zero!");
    if(std::fetestexcept(FE_OVERFLOW  ))
        throw std::runtime_error("Overflow computation error!");
    if(std::fetestexcept(FE_UNDERFLOW ))
        throw std::runtime_error("Underflow computation error!");
}

void FilterFir::reset()
{
    SignalProcessorBuffered::reset();
    std::deque<double> empty;
    std::swap(m_filter_buffer, empty);
}

FilterFir *FilterFir::clone() const
{
    return new FilterFir(*this);
}

}
