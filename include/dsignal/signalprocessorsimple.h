#pragma once

#include "dsignal_export.h"
#include "signalprocessor.h"

namespace dsignal {

class DSIGNAL_EXPORT SignalProcessorSimple: public SignalProcessor
{
public:
    SignalProcessorSimple();
    ~SignalProcessorSimple() override {}
    double pop() override;
    double value() const override;
    double& at(size_t n) override;
    const double& at(size_t n) const override;
    bool has() const override;
    void push(double value) override;
    size_t size() const override;
    void reset() override;
    SignalProcessorSimple *clone() const override;

protected:
    void checkHas() const;
    void checkRange(size_t n) const;

private:
    double m_value;
    bool m_has;
};

}

