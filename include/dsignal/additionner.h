#pragma once

#include "signalprocessorbuffered.h"
#include "dsignal_export.h"
#include <deque>
#include <cstdlib>

namespace dsignal {

class DSIGNAL_EXPORT Additionner: public SignalProcessorBuffered {
public:
    Additionner(double addend=0, size_t max_size=1024, bool throw_overflow=true);
    void push(double value) override;

    Additionner *clone() const override;

private:
    double m_addend;
};

}

