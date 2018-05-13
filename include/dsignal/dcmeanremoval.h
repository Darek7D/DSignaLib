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

#ifndef DSIGNAL_DCMEANREMOVAL_H
#define DSIGNAL_DCMEANREMOVAL_H

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>

namespace dsignal {

/**
 * DC offset mean removal signal processor.
 */
class DSIGNAL_EXPORT DcMeanRemoval: public SignalProcessorBuffered {
public:
    DcMeanRemoval(int mean_samples, size_t max_size=1024);
    DcMeanRemoval(const DcMeanRemoval &s);
    void push(double value) override;
    void reset() override;
    DcMeanRemoval *clone() const override;

private:
    int m_mean_samples;
    double m_current_sum;
    std::deque<double> m_mean_buffer;
};

}

#endif // DSIGNAL_DCMEANREMOVAL_H
