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

#include <dsignal/signalvectormixer.h>
#include <dsignal/signalprocessorbuffered.h>
#include <cassert>

namespace dsignal {

SignalVectorMixer::SignalVectorMixer():
    m_mixer_operation(nullptr)
{
}

SignalVectorMixer::SignalVectorMixer(const SignalProcessorMixerMatrix &mixer_matrix,
                                     MixerOperation *mixer_operation,
                                     std::string name):
    SignalVector(mixer_matrix.size(), SignalProcessorBuffered(), name),
    m_mixer_matrix(mixer_matrix),
    m_mixer_operation(mixer_operation)
{

}

SignalVectorMixer::SignalVectorMixer(const SignalVectorMixer &signal_mixer):
    SignalVector(signal_mixer),
    m_mixer_matrix(signal_mixer.m_mixer_matrix),
    m_mixer_operation(signal_mixer.m_mixer_operation)
{

}

SignalVectorMixer & SignalVectorMixer::operator=(const SignalVectorMixer &signal_mixer)
{
    SignalVector::operator=(signal_mixer);
    m_mixer_matrix = signal_mixer.m_mixer_matrix;
    m_mixer_operation = signal_mixer.m_mixer_operation;
    return *this;
}

void SignalVectorMixer::push(const Sample &sample)
{
    if (enabled()) {
        std::lock_guard<std::mutex> guard(m_mixer_mutex);
        for (size_t i=0; i<m_mixer_matrix.size(); i++) {
            double result = m_mixer_operation->operate(sample.get(m_mixer_matrix[i].first),
                                                       sample.get(m_mixer_matrix[i].second));
            m_signals.at(i)->push(result);
        }
    }
}

SignalVectorMixer *SignalVectorMixer::clone() const
{
    return new SignalVectorMixer(*this);
}

void SignalVectorMixer::setMixerMatrix(const SignalProcessorMixerMatrix &mixer_matrix)
{
    m_mixer_matrix = mixer_matrix;
}

}
