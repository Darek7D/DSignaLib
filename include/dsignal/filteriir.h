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

#ifndef DSIGNAL_FILTERIIR_H
#define DSIGNAL_FILTERIIR_H

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
    /**
     * Filter constructor.
     * \param b filter coefficient nominator
     * \param a filter coefficient denominator
     */
    FilterIir(const std::vector<double> &b,
              const std::vector<double> &a,
              int max_buffer_size=1024);
    FilterIir(const FilterIir &filter);

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

#endif // DSIGNAL_FILTERIIR_H
