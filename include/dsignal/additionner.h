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

#ifndef DSIGNAL_ADDITIONNER_H
#define DSIGNAL_ADDITIONNER_H

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>
#include <cstdlib>

namespace dsignal {

class DSIGNAL_EXPORT Additionner: public SignalProcessorBuffered {
public:
    Additionner(double addend=0, size_t max_size=1024);
    Additionner(const Additionner &s);
    void push(double value) override;

    Additionner *clone() const override;

private:
    double m_addend;
};

}

#endif // DSIGNAL_ADDITIONNER_H
