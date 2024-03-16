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
class DSIGNAL_EXPORT FilterIir: public SignalProcessorBuffered
{
public:
    FilterIir(size_t max_buffer_size=1024, bool throw_overflow=true);

    /**
     * Filter constructor.
     * \param b filter coefficient nominator
     * \param a filter coefficient denominator
     */
    FilterIir(const std::vector<double> &b,
              const std::vector<double> &a,
              size_t max_buffer_size=1024,
              bool throw_overflow=true);

    void push(double value) override;
    void reset() override;
    FilterIir *clone() const override;

protected:
    virtual void process();

private:
    std::deque<double> m_filter_buffer;
    std::deque<double> m_filter_feedback;
    std::vector<double> m_b;
    std::vector<double> m_a;
};

}

