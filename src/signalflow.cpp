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

#include <dsignal/signalflow.h>
#include <dsignal/signalvector.h>
#include <dsignal/signalflowsession.h>
#include <cassert>

namespace dsignal {

SignalFlow::SignalFlow():
    m_session(nullptr),
    m_vector(nullptr)
{
}

SignalFlow::SignalFlow(SignalFlowSession *session, const SignalVector &signal_vector):
    m_session(session),
    m_vector(signal_vector.clone())
{
}

SignalFlow::SignalFlow(const SignalFlow &signal_flow):
    m_session(signal_flow.m_session),
    m_vector(signal_flow.m_vector->clone())
{
}

SignalFlow::~SignalFlow()
{
    if (m_vector!=nullptr)
        delete m_vector;
}

SignalFlow &SignalFlow::operator=(const SignalFlow &signal_flow)
{
    if(this == &signal_flow)
        return *this;

    if (m_vector!=nullptr)
        delete m_vector;

    m_session = signal_flow.m_session;
    m_vector = signal_flow.m_vector->clone();

    return *this;
}

SignalFlow& SignalFlow::operator>>(SignalFlow& output_flow) {
    if (m_session==nullptr)
        throw std::runtime_error("No SignalFlowSession defined!");

    if (m_vector==nullptr)
        throw std::runtime_error("No SignalVector defined!");

    m_session->connect(this, &output_flow);

    return output_flow;
}

SignalFlow& SignalFlow::split(SignalFlow &output_flow) {
    if (m_session==nullptr)
        throw std::runtime_error("No SignalFlowSession defined!");

    if (m_vector==nullptr)
        throw std::runtime_error("No SignalVector defined!");

    m_session->connect(this, &output_flow);

    return *this;
}

SignalVector* SignalFlow::vector()
{
    return m_vector;
}

}
