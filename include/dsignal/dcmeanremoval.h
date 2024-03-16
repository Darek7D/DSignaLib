#pragma once

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>

namespace dsignal {

/**
 * DC offset mean removal signal processor.
 *
 * This signal processor module, removes an offset from the signal.
 * Used method is to calculate the arithmetic mean from 'mean_samples' and
 * substract it from current pushed value.
 *
 * Example signal diagram:
 * \code
 * [values]^           |<--mean_samples-->|
 *         |           |                  |
 *         |~~samples~~~~~~~~~~~~~~~~~~~~~~
 *         |
 *         |---------------------------------> [samples]
 * \endcode
 */
class DSIGNAL_EXPORT DcMeanRemoval: public SignalProcessorBuffered {
public:
    DcMeanRemoval(size_t mean_samples=1, size_t max_size=1024, bool throw_overflow=true);
    void push(double value) override;
    void reset() override;
    DcMeanRemoval *clone() const override;

private:
    size_t m_mean_samples;
    double m_current_sum;
    std::deque<double> m_mean_buffer;
};

}

