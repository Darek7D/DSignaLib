#pragma once

#include "dsignal_export.h"
#include <cstdlib>
#include <vector>

namespace dsignal {

class DSIGNAL_EXPORT Sample
{
public:
    Sample() = default;
    Sample(size_t channels);
    Sample(const std::vector<double> &values);
    virtual ~Sample() = default;

    virtual double get(size_t channel) const;
    virtual void set(size_t channel, double value);
    virtual size_t channels() const;

private:
    std::vector<double> m_values;
};

}

