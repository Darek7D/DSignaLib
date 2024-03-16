#pragma once

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
    SignalFlow(const SignalFlow& signal_flow);
    SignalFlow(SignalFlowSession *session, const SignalVector &signal_vector);
    virtual ~SignalFlow();

    virtual SignalFlow & operator=(const SignalFlow &signal_flow);
    virtual SignalFlow & operator>>(SignalFlow &output_flow);
    virtual SignalFlow & split(SignalFlow &output_flow);

    virtual SignalVector * vector();

private:
    SignalFlowSession *m_session;
    SignalVector *m_vector;

    friend class SignalFlowSession;
};

}

