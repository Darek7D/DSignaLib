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

#include <dsignal/filterfir.h>
#include <algorithm>
#include <stdexcept>
#include <cfenv>

#ifdef USE_FENV_ACCESS
#pragma STDC FENV_ACCESS ON
#endif

namespace dsignal {

FilterFir::FilterFir(int max_buffer_size):
    SignalProcessorBuffered(max_buffer_size)
{

}

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
#ifdef USE_FENV_ACCESS
    std::feclearexcept(FE_ALL_EXCEPT);
#endif

    double sum = 0.0;
    std::vector<double>::const_iterator a_it = m_a.begin();
    for (double v: m_filter_buffer) {
        sum += v*(*a_it);
        ++a_it;
    }
    SignalProcessorBuffered::push(sum);

#ifdef USE_FENV_ACCESS
    if(std::fetestexcept(FE_INVALID	  ))
        throw std::runtime_error("FilterFir::process(): FE_INVALID computation error!");
    if(std::fetestexcept(FE_DIVBYZERO ))
        throw std::runtime_error("FilterFir::process(): Divide by zero!");
    if(std::fetestexcept(FE_OVERFLOW  ))
        throw std::runtime_error("FilterFir::process(): Overflow computation error!");
    if(std::fetestexcept(FE_UNDERFLOW ))
        throw std::runtime_error("FilterFir::process(): Underflow computation error!");
#endif
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
