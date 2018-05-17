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
    /**
     * Make a connection between two SignalFlow's.
     * All data from input SignalFlow will be transfered to output SignalFlow.
     */
    virtual void connect(SignalFlow* input, SignalFlow* output);

    /**
     * Declare the given SignalFlow as input. When you declare the input,
     * you can access it using the input() method.
     * The SignalFlow declaration doesn't affect the processing, it is only used
     * for easy identification by the library user.
     * \param sf SignalFlow object to declare.
     * \param id unique identification number for this input.
     */
    virtual void setInput(SignalFlow& sf, int id=0);

    /**
     * Declare the given SignalFlow as output. When you declare the output,
     * you can access it using the output() method.
     * The SignalFlow declaration doesn't affect the processing, it is only used
     * for easy identification by the library user.
     * \param sf SignalFlow object to declare.
     * \param id unique identification number for this output.
     */
    virtual void setOutput(SignalFlow& sf, int id=0);

    /**
     * Returns the SignalFlow object declared by setInput() method
     * \param id unique identification number defined by setInput() method.
     */
    virtual SignalFlow* input(int id) const;

    /**
     * Returns the SignalFlow object declared by setOutput() method
     * \param id unique identification number defined by setOutput() method.
     */
    virtual SignalFlow* output(int id) const;

    /**
     * \copybrief SignalFlowSession::input()
     */
    virtual SignalFlow* input() const;

    /**
     * \copybrief SignalFlowSession::output()
     */
    virtual SignalFlow* output() const;

    /**
     * Runs the processing of all buffered data in SignalFlow objects.
     */
    virtual void process();

    /**
     * Dump the graph of all connections in Graphvis format.
     */
    virtual std::string dumpGraph() const;

private:
    std::unordered_map<SignalFlow*, std::vector<SignalFlow*>> m_signal_connections;
    std::unordered_map<int, SignalFlow*> m_inputs;
    std::unordered_map<int, SignalFlow*> m_outputs;

    std::string makeDotSymbol(const SignalFlow* signalflow) const;
    std::string stripStrToDotSymbol(std::string s) const;
};

}

#endif // DSIGNAL_SIGNALFLOWSESSION_H
