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

#ifndef DSIGNAL_SIGNALFLOWSESSION_H
#define DSIGNAL_SIGNALFLOWSESSION_H

#include "dsignal_export.h"
#include "sample.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

namespace dsignal {

class SignalFlow;

/**
 * The SignalFlowSession class stores a session for signal flow processing.
 * The designed signal flow process is stored in SignalFlowSession and processed
 * when process() method is used.
 *
 * Example:
 * \code
 * // Create session
 * SignalFlowSession s;
 *
 * // Create signal flow elements
 * SignalFlow sig1(s, 4, SignalProcessorBuffered(), "Signal 1");
 * SignalFlow sig2(s, 4, SignalProcessorBuffered(), "Signal 2");
 *
 * // Declare inputs/outputs
 * s.setInput(sig1);
 * s.setOutput(sig2);
 *
 * // Design signal flow process
 * sig1 >> sig2;
 *
 * // Create sample and push it to session
 * Sample sample(4);
 * s.input()->push(sample);
 *
 * // Process all sample through signal processors.
 * s.process();
 *
 * // Pop output sample
 * Sample out = s.output()->pop();
 * \endcode
 */
class DSIGNAL_EXPORT SignalFlowSession {
public:
    virtual void connect(SignalFlow* input, SignalFlow* output);

    virtual void setInput(SignalFlow& sf, int id=0);
    virtual void setOutput(SignalFlow& sf, int id=0);

    virtual SignalFlow* input(int id);
    virtual SignalFlow* output(int id);
    virtual SignalFlow* input();
    virtual SignalFlow* output();

    virtual void process();
    virtual std::string dumpGraph();

private:
    std::unordered_map<SignalFlow*, std::vector<SignalFlow*>> m_signal_connections;
    std::unordered_map<int, SignalFlow*> m_inputs;
    std::unordered_map<int, SignalFlow*> m_outputs;

    std::string stripStrToDot(std::string s);
};

}

#endif // DSIGNAL_SIGNALFLOWSESSION_H
