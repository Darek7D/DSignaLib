#pragma once

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>
#include <cstdlib>

namespace dsignal {

class DSIGNAL_EXPORT DecimatorMean: public SignalProcessorBuffered {
public:
    DecimatorMean(size_t mean_samples=2, size_t max_size=1024, bool throw_overflow=true);
    void push(double value) override;
    void reset() override;
    DecimatorMean *clone() const override;

private:
    size_t m_mean_samples;
    double m_current_sum;
    size_t m_current_index;
    std::deque<double> m_mean_buffer;
};

}

