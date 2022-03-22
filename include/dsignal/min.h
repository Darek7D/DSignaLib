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

#ifndef DSIGNAL_MIN_H
#define DSIGNAL_MIN_H

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>

namespace dsignal {

/**
 * Minimum value in buffer since reset or construction.
 */
class DSIGNAL_EXPORT Min: public SignalProcessorBuffered {
public:
    Min(size_t max_size=1024, bool throw_overflow=true);
    void push(double value) override;
    void reset() override;
    Min *clone() const override;

private:
    double m_min;
};

}

#endif // DSIGNAL_MIN_H
