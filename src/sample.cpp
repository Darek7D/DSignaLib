/*
 * Copyright (C) 2018 Tedtronix.
 * This file is part of DSignal.
 *
 * DSignal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DSignal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with DSignal.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <dsignal/sample.h>

namespace dsignal {

Sample::Sample(size_t channels)
{
    m_values.resize(channels, 0.0);
}

Sample::Sample(const std::vector<double> &values)
{
    m_values = values;
}

double Sample::get(size_t channel) const
{
    return m_values.at(channel);
}

void Sample::set(size_t channel, double value)
{
    m_values.at(channel) = value;
}

size_t Sample::channels() const
{
    return m_values.size();
}


}

