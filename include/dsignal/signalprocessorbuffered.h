/*
 * Copyright (C) 2018 Tedtronix.
 * This file is part of DSignal.
 *
 * DSignal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DSignal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DSignal.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DSIGNAL_SIGNALPROCESSORBUFFERED_H
#define DSIGNAL_SIGNALPROCESSORBUFFERED_H

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
    SignalProcessorBuffered(const SignalProcessorBuffered &s);

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

#endif // DSIGNAL_SIGNALPROCESSORBUFFERED_H
