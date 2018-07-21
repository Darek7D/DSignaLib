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

#ifndef DSIGNAL_DECIMATOR_H
#define DSIGNAL_DECIMATOR_H

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>
#include <cstdlib>

namespace dsignal {

class DSIGNAL_EXPORT DecimatorMean: public SignalProcessorBuffered {
public:
    DecimatorMean(int mean_samples=2, size_t max_size=1024);
    DecimatorMean(const DecimatorMean &s);
    void push(double value) override;
    void reset() override;
    DecimatorMean *clone() const override;

private:
    size_t m_mean_samples;
    double m_current_sum;
    size_t m_current_index;
    std::deque<double> m_mean_buffer;
};

}

#endif // DSIGNAL_DECIMATOR_H
