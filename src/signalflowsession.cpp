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
#include <stdexcept>
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

bool SignalFlowSession::disconnect(SignalFlow *input, SignalFlow *output)
{
    auto connection_item = m_signal_connections.find(input);
    if (connection_item == m_signal_connections.end()) {
        return false;
    }

    auto output_items = connection_item->second;
    auto size_before = output_items.size();

    output_items.erase(
        std::remove_if(output_items.begin(),
                       output_items.end(),
                       [output](SignalFlow * o) { return o == output; }),
        output_items.end());

    auto size_after = output_items.size();
    if (size_after==0) {
        m_signal_connections.erase(connection_item);
        return true;
    }

    if (size_after == size_before) {
        return false;
    }

    return true;
}

void SignalFlowSession::clearConnections()
{
    m_signal_connections.clear();
    m_inputs.clear();
    m_outputs.clear();
}

void SignalFlowSession::setInput(SignalFlow& sf, int id){
    m_inputs[id] = &sf;
}

void SignalFlowSession::setOutput(SignalFlow& sf, int id){
    m_outputs[id] = &sf;
}

SignalVector *SignalFlowSession::input(int id) const {
    return m_inputs.at(id)->m_vector;
}

SignalVector *SignalFlowSession::output(int id) const {
    return m_outputs.at(id)->m_vector;
}

void SignalFlowSession::process() {
    bool finished = false;
    while (!finished) {
        finished = true;
        for (auto pair: m_signal_connections) {
            while (pair.first->m_vector->has()) {
                // Pop the sample from input connection
                Sample s = pair.first->m_vector->pop();

                // And push it to output connections
                for (auto o: pair.second)
                    o->m_vector->push(s);

                // Inform that we havn't finished yet
                finished = false;
            }
        }
    }
}

void SignalFlowSession::reset()
{
    for (auto pair: m_signal_connections) {
        pair.first->vector()->reset();
        for (auto destination: pair.second) {
            destination->vector()->reset();
        }
    }
}

void SignalFlowSession::enableOutputs(bool enable)
{
    for (auto pair: m_outputs)
        pair.second->vector()->enable(enable);
}

void SignalFlowSession::enableInputs(bool enable)
{
    for (auto pair: m_inputs)
        pair.second->vector()->enable(enable);
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
               << stripStrToDotSymbol(o->m_vector->getName()) << ";" << std::endl;
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
        ss << "  " << makeDotSymbol(input.second);
        ss << " [shape=box, style=\"filled, rounded\", fillcolor=" << (input.second->m_vector->enabled()?"red":"gray") <<"];" << std::endl;
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
           << " [label=\"" << connection->m_vector->getName() << "\"];" << std::endl;
    }
    ss << "}" << std::endl;
    return ss.str();
}

std::vector<SignalFlow *> SignalFlowSession::connectedSignals(SignalFlow *source_signal_flow)
{
    auto connection_item = m_signal_connections.find(source_signal_flow);
    if (connection_item == m_signal_connections.end()) {
        return std::vector<SignalFlow *>();
    }

    return connection_item->second;
}

std::string SignalFlowSession::makeDotSymbol(const SignalFlow *signalflow) const
{
    std::string output = signalflow->m_vector->getName();
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
