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

#ifndef DSIGNAL_ZEROCROSSING_H
#define DSIGNAL_ZEROCROSSING_H

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>

namespace dsignal {

/**
 * Minimum value in buffer since reset or construction.
 */
class DSIGNAL_EXPORT ZeroCrossing: public SignalProcessorBuffered {
public:
    ZeroCrossing(size_t max_size=1024, bool throw_overflow=true);
    void push(double value) override;
    void reset() override;
    ZeroCrossing *clone() const override;

private:
    double m_zero_crossing;
    double m_last_value;
    bool m_has_last_value;
};

}

#endif // DSIGNAL_ZEROCROSSING_H
