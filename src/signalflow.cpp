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
    delete m_vector;
    m_vector = nullptr;
}

SignalFlow &SignalFlow::operator=(const SignalFlow &signal_flow)
{
    if(this == &signal_flow)
        return *this;

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
