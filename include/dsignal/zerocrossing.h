#pragma once

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>

namespace dsignal {

/**
 * Minimum value in buffer since reset or construction.
 */
class DSIGNAL_EXPORT ZeroCrossing: public SignalProcessorBuffered {
public:
    ZeroCrossing(size_t max_size=1024, bool throw_overflow=true);
    void push(double value) override;
    void reset() override;
    ZeroCrossing *clone() const override;

private:
    double m_zero_crossing;
    double m_last_value;
    bool m_has_last_value;
};

}

