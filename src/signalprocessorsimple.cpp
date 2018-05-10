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

#include <dsignal/signalprocessorsimple.h>
#include <stdexcept>

namespace dsignal {

SignalProcessorSimple::SignalProcessorSimple():
    m_value(0.0),
    m_has(false)
{

}

SignalProcessorSimple::SignalProcessorSimple(const SignalProcessorSimple &signal_processor_simple)
    : SignalProcessorSimple()
{

}

double SignalProcessorSimple::pop()
{
    m_has = false;
    return m_value;
}

bool SignalProcessorSimple::has()
{
    return m_has;
}

void SignalProcessorSimple::push(double value)
{
    m_value = value;
    m_has = true;
}

void SignalProcessorSimple::reset()
{
    m_has = false;
}

SignalProcessorSimple *SignalProcessorSimple::clone() const
{
    return new SignalProcessorSimple(*this);
}


}
