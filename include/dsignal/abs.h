#pragma once

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>

namespace dsignal {

/**
 * Transform values using absolute value/modulus function.
 */
class DSIGNAL_EXPORT Abs: public SignalProcessorBuffered {
public:
    Abs(size_t max_size=1024, bool throw_overflow=true);
    void push(double value) override;
    void reset() override;
    Abs *clone() const override;
};

}

