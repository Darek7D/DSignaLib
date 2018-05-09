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

#ifndef DSIGNAL_SIGNALVECTOR_H
#define DSIGNAL_SIGNALVECTOR_H

#include "sample.h"
#include "signalprocessor.h"
#include "dsignal_export.h"
#include <string>

namespace dsignal {

typedef std::vector<SignalProcessor*> TSignals;

class DSIGNAL_EXPORT SignalVector
{
public:
    SignalVector(size_t channels, const SignalProcessor &signal_processor, std::string name="signal");
    virtual ~SignalVector();

    virtual Sample pop();
    virtual bool has() const;
    virtual void push(const Sample &sample);
    virtual void reset();
    virtual size_t channels() const;
    virtual std::string getName() const;
    virtual SignalProcessor* getSignalProcessor(size_t channel);
    virtual SignalVector& operator>>(SignalVector& output_signal);
    virtual Sample& operator>>(Sample& output_sample);

protected:
    TSignals m_signals;
    std::string m_name;
};

inline SignalVector& operator>>(Sample& sample, SignalVector& signal)
{
    signal.push(sample);
    return signal;
}

}

#endif // DSIGNAL_SIGNALVECTOR_H
