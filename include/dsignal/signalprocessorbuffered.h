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

class DSIGNAL_EXPORT SignalProcessorBuffered: public SignalProcessor {
public:
    SignalProcessorBuffered(size_t max_size=1024);
    SignalProcessorBuffered(const SignalProcessorBuffered &s);
    void push(double value) override;
    double pop() override;

    bool has() override;
    void reset() override;

    SignalProcessorBuffered *clone() const override;

    virtual size_t size();
    virtual size_t maxSize();

protected:
    const std::deque<double>& data();

private:
    std::deque<double> m_buffer;
    size_t m_max_size;
};

}

#endif // DSIGNAL_SIGNALPROCESSORBUFFERED_H
