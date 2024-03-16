#pragma once

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>
#include <cstdlib>

namespace dsignal {

class DSIGNAL_EXPORT Multiplier: public SignalProcessorBuffered {
public:
    Multiplier(double multiplier=1, size_t max_size=1024, bool throw_overflow=true);
    void push(double value) override;

    Multiplier *clone() const override;

private:
    double m_multiplier;
};

}

