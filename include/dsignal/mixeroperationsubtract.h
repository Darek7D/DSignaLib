#pragma once

#include "dsignal_export.h"
#include "mixeroperation.h"

namespace dsignal {

class DSIGNAL_EXPORT MixerOperationSubtract: public MixerOperation
{
public:
    double operate(const double a, const double b) override;
};

}

