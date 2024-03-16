#pragma once

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>
#include <cstdlib>

namespace dsignal {

class DSIGNAL_EXPORT Decimator: public SignalProcessorBuffered {
public:
    Decimator(int factor=1, size_t max_size=1024, bool throw_overflow=true);
    void push(double value) override;
    void reset() override;

    Decimator *clone() const override;

private:
    int m_factor;
    int m_counter;
};

}

