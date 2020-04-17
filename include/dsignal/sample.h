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

#ifndef DSIGNAL_SAMPLE_H
#define DSIGNAL_SAMPLE_H

#include "dsignal_export.h"
#include <cstdlib>
#include <vector>

namespace dsignal {

class DSIGNAL_EXPORT Sample
{
public:
    Sample() = default;
    Sample(size_t channels);
    Sample(const std::vector<double> &values);
    virtual ~Sample() = default;

    virtual double get(size_t channel) const;
    virtual void set(size_t channel, double value);
    virtual size_t channels() const;

private:
    std::vector<double> m_values;
};

}

#endif // DSIGNAL_SAMPLE_H
