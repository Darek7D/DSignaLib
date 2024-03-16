#pragma once

#include "sample.h"
#include "signalprocessor.h"
#include "signalvector.h"
#include "dsignal_export.h"
#include <string>
#include <vector>

namespace dsignal {

class DSIGNAL_EXPORT SignalSplitter: public SignalVector
{
public:
    SignalSplitter(std::string name="splitter");

    SignalSplitter& split(SignalVector &signal_vector_destination);
    void push(const Sample &sample) override;

private:
    std::vector<SignalVector*> m_destinations;
};

}

