#pragma once

#include "signalprocessor.h"
#include "dsignal_export.h"
#include <deque>
#include <cstdlib>

namespace dsignal {

/**
 * The SignalProcessor with buffered data. You can push data until it
 * reaches the size of max_size. Than you can pop it at any time.
 * It works like a simple queue.
 * When you overflow the buffer, an the std::overflow_error will be thrown.
 */
class DSIGNAL_EXPORT SignalProcessorBuffered: public SignalProcessor {
public:
    /**
     * Constructs the SignalProcessorBuffered object.
     * \param max_size max size of the internal buffer.
     */
    SignalProcessorBuffered(size_t max_size=1024, bool throw_overflow=true);

    /**
     * @copydoc SignalProcessor::push()
     *
     * When you overflow the buffer, an the std::overflow_error will be thrown.
     */
    void push(double value) override;

    bool has() const override;

    /**
     * @copydoc SignalProcessor::pop()
     *
     * When you pop() an empty buffer, an the std::out_of_range will be thrown.
     */
    double pop() override;

    double value() const override;

    double& at(size_t n) override;

    const double& at(size_t n) const override;

    void reset() override;

    SignalProcessorBuffered *clone() const override;

    size_t size() const override;

    /**
     * The max size of the buffer.
     */
    virtual size_t maxSize() const;

protected:
    const std::deque<double>& data();

private:
    std::deque<double> m_buffer;
    size_t m_max_size;
    bool m_throw_overflow;
};

}

