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

#include <dsignal/signalflowsession.h>
#include <dsignal/signalflow.h>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <sstream>
#include <cctype>
#include <string>

namespace dsignal {

void SignalFlowSession::connect(SignalFlow* input, SignalFlow* output) {
    m_signal_connections[input].push_back(output);
}

void SignalFlowSession::setInput(SignalFlow& sf, int id){
    m_inputs[id] = &sf;
}

void SignalFlowSession::setOutput(SignalFlow& sf, int id){
    m_outputs[id] = &sf;
}

SignalFlow* SignalFlowSession::input(int id) const {
    return m_inputs.at(id);
}

SignalFlow* SignalFlowSession::output(int id) const {
    return m_outputs.at(id);
}

SignalFlow *SignalFlowSession::input() const
{
    if (m_inputs.empty())
        throw std::runtime_error("No inputs defined!");
    return m_inputs.begin()->second;
}

SignalFlow *SignalFlowSession::output() const
{
    if (m_outputs.empty())
        throw std::runtime_error("No outputs defined!");
    return m_outputs.begin()->second;
}

void SignalFlowSession::process() {
    bool finished = false;
    while (finished==false) {
        finished = true;
        for (auto pair: m_signal_connections) {
            while (pair.first->has()) {
                // Pop the sample from input connection
                Sample s = pair.first->pop();

                // And push it to output connections
                for (auto o: pair.second)
                    o->push(s);

                // Inform that we havn't finished yet
                finished = false;
            }
        }
    }
}

std::string SignalFlowSession::dumpGraph() const
{
    std::stringstream ss;
    ss << "digraph SignalFlow {" << std::endl
       << "  node [shape=box];" << std::endl
       << "  rankdir=LR;" << std::endl << std::endl;

    for (auto connection: m_signal_connections) {
        for (auto o: connection.second) {
            ss << "  " << makeDotSymbol(connection.first) << "->"
               << stripStrToDotSymbol(o->getName()) << ";" << std::endl;
        }
    }
    ss << std::endl;

    // Input colors
    for (auto input: m_inputs) {
        ss << "  " << makeDotSymbol(input.second)
           << " [shape=box, style=\"filled, rounded\", fillcolor=green];" << std::endl;
    }

    // Output colors
    for (auto input: m_outputs) {
        ss << "  " << makeDotSymbol(input.second)
           << " [shape=box, style=\"filled, rounded\", fillcolor=red];" << std::endl;
    }

    // Labels
    std::unordered_set<SignalFlow*> m_all;
    for (auto connection: m_signal_connections) {
        m_all.insert(connection.first);
        for (auto o: connection.second) {
            m_all.insert(o);
        }
    }

    for (auto connection: m_all) {
        ss << "  " << makeDotSymbol(connection)
           << " [label=\"" << connection->getName() << "\"];" << std::endl;
    }
    ss << "}" << std::endl;
    return ss.str();
}

std::string SignalFlowSession::makeDotSymbol(const SignalFlow *signalflow) const
{
    std::string output = signalflow->getName();
    output = stripStrToDotSymbol(output);
    if (output.empty()) {
        output = std::to_string((size_t)signalflow);
    }
    return output;
}

std::string SignalFlowSession::stripStrToDotSymbol(std::string s) const
{
    s.erase(std::remove_if(s.begin(),
                           s.end(),
                           [](unsigned char x){return !isalnum(x);}),
                   s.end());

    return s;
}

}
