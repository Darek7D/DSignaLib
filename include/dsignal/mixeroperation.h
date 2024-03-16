#pragma once

#include "dsignal_export.h"

namespace dsignal {

class DSIGNAL_EXPORT MixerOperation
{
public:
    virtual ~MixerOperation() {}
    virtual double operate(const double a, const double b) = 0;
};

}

