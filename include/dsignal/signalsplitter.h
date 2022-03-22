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

#ifndef DSIGNAL_SIGNALSPLITTER_H
#define DSIGNAL_SIGNALSPLITTER_H

#include "sample.h"
#include "signalprocessor.h"
#include "signalvector.h"
#include "dsignal_export.h"
#include <string>
#include <vector>

namespace dsignal {

class DSIGNAL_EXPORT SignalSplitter: public SignalVector
{
public:
    SignalSplitter(std::string name="splitter");

    SignalSplitter& split(SignalVector &signal_vector_destination);
    void push(const Sample &sample) override;

private:
    std::vector<SignalVector*> m_destinations;
};

}

#endif // DSIGNAL_SIGNALSPLITTER_H
