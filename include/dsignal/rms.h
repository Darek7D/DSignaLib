#pragma once

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>
#include <vector>

namespace dsignal {
/**
 * RMS online processor.
 */
class DSIGNAL_EXPORT Rms: public SignalProcessorBuffered
{
public:
    /**
     * Constructs the RMS module
     * \param dimension number of samples to collect
     */
    Rms(size_t dimension=2, size_t max_size=1024, bool throw_overflow=true);
    void push(double value) override;
    void reset() override;
    Rms *clone() const override;

private:
    std::deque<double> m_internal_buffer;
    double m_current_rms=0.0;
    double m_current_sum=0.0;
    size_t m_dimension;
};

}

