#pragma once

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>

namespace dsignal {

/**
 * Maximum value in buffer since reset or construction.
 */
class DSIGNAL_EXPORT Max: public SignalProcessorBuffered {
public:
    Max(size_t max_size=1024, bool throw_overflow=true);
    void push(double value) override;
    void reset() override;
    Max *clone() const override;

private:
    double m_max;
};

}

