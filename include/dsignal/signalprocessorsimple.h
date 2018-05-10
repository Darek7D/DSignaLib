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

#ifndef DSIGNAL_SIGNALPROCESSORSIMPLE_H
#define DSIGNAL_SIGNALPROCESSORSIMPLE_H

#include "dsignal_export.h"
#include "signalprocessor.h"

namespace dsignal {

class DSIGNAL_EXPORT SignalProcessorSimple: public SignalProcessor
{
public:
    SignalProcessorSimple();
    SignalProcessorSimple(const SignalProcessorSimple &signal_processor_simple);
    virtual ~SignalProcessorSimple() {}
    double pop() override;
    bool has() override;
    void push(double value) override;
    void reset() override;
    SignalProcessorSimple *clone() const override;

private:
    double m_value;
    bool m_has;
};

}

#endif // DSIGNAL_SIGNALPROCESSORSIMPLE_H
