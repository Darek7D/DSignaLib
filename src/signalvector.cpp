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
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <dsignal/signalvector.h>
#include <cassert>

namespace dsignal {

SignalVector::SignalVector(size_t channels, const SignalProcessor &signal_processor, std::string name):
    m_name(name)
{
    for (size_t i=0; i<channels; i++)
        m_signals.push_back(signal_processor.clone());
}

SignalVector::~SignalVector()
{
    for (auto s: m_signals)
        delete s;
}

Sample SignalVector::pop()
{
    Sample s(channels());
    for (size_t c=0; c<m_signals.size(); c++)
        s.set(c, m_signals.at(c)->pop());

    return s;
}

bool SignalVector::has() const
{
    for (auto s: m_signals)
        return s->has();
    return false;
}

void SignalVector::push(const Sample &sample)
{
    assert(sample.channels()==channels());
    for (size_t c=0; c<channels(); c++)
        m_signals.at(c)->push(sample.get(c));
}

void SignalVector::reset()
{
    for (auto s: m_signals)
        return s->reset();
}

size_t SignalVector::channels() const
{
    return m_signals.size();
}

std::string SignalVector::getName() const
{
    return m_name;
}

SignalProcessor *SignalVector::getSignalProcessor(size_t channel)
{
    return m_signals.at(channel);
}

SignalVector &SignalVector::operator>>(SignalVector &output_signal)
{
    while (has())
        output_signal.push(pop());
    return output_signal;
}

Sample &SignalVector::operator>>(Sample &output_sample)
{
    if (has())
        output_sample = pop();
    return output_sample;
}

}
