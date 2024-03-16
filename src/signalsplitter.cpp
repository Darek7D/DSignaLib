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
