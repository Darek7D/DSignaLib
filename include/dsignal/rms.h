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

#ifndef DSIGNAL_RMS_H
#define DSIGNAL_RMS_H

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>
#include <vector>

namespace dsignal {
/**
 * RMS online processor.
 */
class DSIGNAL_EXPORT Rms: public SignalProcessorBuffered
{
public:
    /**
     * Constructs the RMS module
     * \param dimension number of samples to collect
     */
    Rms(size_t dimension=2, size_t max_size=1024);
    Rms(const Rms &rms);
    void push(double value) override;
    void reset() override;
    Rms *clone() const override;

private:
    std::deque<double> m_internal_buffer;
    double m_current_rms=0.0;
    double m_current_sum=0.0;
    size_t m_dimension;
};

}

#endif // DSIGNAL_RMS_H
