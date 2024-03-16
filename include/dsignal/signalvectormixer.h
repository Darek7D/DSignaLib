#pragma once

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

    virtual SignalVectorMixer & operator=(const SignalVectorMixer &signal_mixer);

    /**
     * Pushes a Sample to SignalVector. Each channel Sample channel will be splitted
     * and pushed separately to the internal SignalProcessor's.
     */
    void push(const Sample &sample) override;

    SignalVectorMixer* clone() const override;

    void setMixerMatrix(const SignalProcessorMixerMatrix &mixer_matrix);

protected:
    SignalProcessorMixerMatrix m_mixer_matrix;
    MixerOperation *m_mixer_operation;
    mutable std::mutex m_mixer_mutex;
};


}

