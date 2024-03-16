#pragma once

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>

namespace dsignal {

/**
 * Minimum value in buffer since reset or construction.
 */
class DSIGNAL_EXPORT Min: public SignalProcessorBuffered {
public:
    Min(size_t max_size=1024, bool throw_overflow=true);
    void push(double value) override;
    void reset() override;
    Min *clone() const override;

private:
    double m_min;
};

}

