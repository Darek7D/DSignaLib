#pragma once

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>

namespace dsignal {

/**
 * Arithmetic mean
 */
class DSIGNAL_EXPORT ArithmeticMean: public SignalProcessorBuffered {
public:
    ArithmeticMean(size_t mean_samples=1, size_t max_size=1024, bool throw_overflow=true);
    void push(double value) override;
    void reset() override;
    ArithmeticMean *clone() const override;

private:
    size_t m_mean_samples;
    double m_current_sum;
    std::deque<double> m_mean_buffer;
};

}

