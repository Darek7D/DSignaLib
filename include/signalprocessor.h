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

#ifndef DSIGNAL_SIGNALPROCESSOR_H
#define DSIGNAL_SIGNALPROCESSOR_H

#include "dsignal_export.h"

namespace dsignal {

class DSIGNALIB_EXPORT SignalProcessor
{
public:
    virtual ~SignalProcessor() {}
    virtual double pop() = 0;
    virtual bool has() = 0;
    virtual void push(double value) = 0;
    virtual void reset() = 0;
    virtual SignalProcessor *clone() const = 0;
};

}

#endif // DSIGNAL_SIGNALPROCESSOR_H
