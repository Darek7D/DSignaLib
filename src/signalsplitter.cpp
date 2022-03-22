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

#include <dsignal/signalsplitter.h>
#include <dsignal/signalprocessorsimple.h>
#include <cassert>
#include <iostream>

namespace dsignal {

SignalSplitter::SignalSplitter(std::string name):
    SignalVector(0, SignalProcessorSimple(), name)
{

}

SignalSplitter &SignalSplitter::split(SignalVector &signal_vector_destination)
{
    m_destinations.push_back(&signal_vector_destination);
    return *this;
}

void SignalSplitter::push(const Sample &sample)
{
    for (auto v: m_destinations)
        v->push(sample);
}

}
