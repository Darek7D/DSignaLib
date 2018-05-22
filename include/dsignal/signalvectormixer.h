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

#ifndef DSIGNAL_SIGNALVECTORMIXER_H
#define DSIGNAL_SIGNALVECTORMIXER_H

#include "sample.h"
#include "signalprocessor.h"
#include "signalvector.h"
#include <dsignal/mixeroperation.h>
#include "dsignal_export.h"
#include <string>
#include <vector>
#include <utility>
#include <mutex>

namespace dsignal {

typedef std::vector<std::pair<int, int> > SignalProcessorMixerMatrix;

class DSIGNAL_EXPORT SignalVectorMixer: public SignalVector
{
public:
    SignalVectorMixer();
    SignalVectorMixer(const SignalProcessorMixerMatrix &mixer_matrix,
                      MixerOperation* mixer_operation,
                      std::string name="");
    SignalVectorMixer(const SignalVectorMixer& signal_mixer);
    virtual ~SignalVectorMixer();

    virtual SignalVectorMixer & operator=(const SignalVectorMixer &signal_mixer);

    /**
     * Pushes a Sample to SignalVector. Each channel Sample channel will be splitted
     * and pushed separately to the internal SignalProcessor's.
     */
    virtual void push(const Sample &sample);

protected:
    SignalProcessorMixerMatrix m_mixer_matrix;
    MixerOperation *m_mixer_operation;
    mutable std::mutex m_mixer_mutex;

};


}

#endif // DSIGNAL_SIGNALVECTORMIXER_H
