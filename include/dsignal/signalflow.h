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

#ifndef DSIGNAL_SIGNALFLOW_H
#define DSIGNAL_SIGNALFLOW_H

#include "sample.h"
#include "signalvector.h"
#include "dsignal_export.h"
#include <string>
#include <iostream>

namespace dsignal {

class SignalFlowSession;

/**
 * The SignalFlow class allows to design the signal flow process before
 * processing anything, by using operator>> and split() method. The designed
 * signal flow process is stored in SignalFlowSession and processed when
 * SignalFlowSession::process() method is used.
 *
 * Signal flow define example:
 * \code
 * // Forwarding
 * SignalFlow s1(...);
 * SignalFlow s2(...);
 * SignalFlow s3(...);
 * s1 >> s2 >> s2;
 *
 * // Splitting
 * // Method #1
 * SignalFlow s1(...);
 * SignalFlow s2(...);
 * SignalFlow s3(...);
 * SignalFlow s4(...);
 * SignalFlow s5(...);
 * SignalFlow s6(...);
 *
 * s1 >> s2 >> s3.split(s4).split(s5);
 * // further processing
 * s4 >> s6;
 *
 * // Method #2
 * s1 >> s2 >> s3;
 * s3 >> s4;
 * s3 >> s5;
 * // further processing
 * s4 >> s6;
 *
 * \endcode
 */
class DSIGNAL_EXPORT SignalFlow {
public:
    SignalFlow();
    SignalFlow(SignalFlowSession *session, const SignalVector &signal_vector);
    virtual ~SignalFlow();

    virtual SignalFlow& operator>>(SignalFlow& output_flow);
    virtual SignalFlow& split(SignalFlow &output_flow);
    //virtual SignalVector vector();

private:
    SignalFlowSession *m_session;
    SignalVector *m_vector;

    friend class SignalFlowSession;
};

}

#endif // DSIGNAL_SIGNALFLOW_H
