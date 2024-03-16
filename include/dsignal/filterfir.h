#pragma once

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>
#include <vector>

namespace dsignal {

/**
 * Filter FIR
 *
 * This implementation of FIR filter, filters the "online" signal according to
 * the provided parameters.
 */
class DSIGNAL_EXPORT FilterFir: public SignalProcessorBuffered
{
public:
    FilterFir(size_t max_buffer_size=1024, bool throw_overflow=true);
    FilterFir(const std::vector<double> &a, size_t max_buffer_size=1024,
              bool throw_overflow=true);

    void push(double value) override;
    void reset() override;
    FilterFir *clone() const override;

protected:
    virtual void process();

private:
    std::deque<double> m_filter_buffer;
    std::vector<double> m_a;
};

}

