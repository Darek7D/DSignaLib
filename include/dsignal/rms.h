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

#ifndef DSIGNAL_RMS_H
#define DSIGNAL_RMS_H

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>
#include <vector>

namespace dsignal {

class DSIGNAL_EXPORT Rms: public SignalProcessorBuffered
{
public:
    Rms(size_t dimension=2);
    Rms(const Rms &rms);
    void push(double value) override;
    double pop() override;
    void reset() override;
    Rms *clone() const override;

private:
    double m_current_rms=0.0;
    double m_current_sum=0.0;
};

}

#endif // DSIGNAL_RMS_H
