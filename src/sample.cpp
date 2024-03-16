#include <dsignal/sample.h>

namespace dsignal {

Sample::Sample(size_t channels)
{
    m_values.resize(channels, 0.0);
}

Sample::Sample(const std::vector<double> &values)
{
    m_values = values;
}

double Sample::get(size_t channel) const
{
    return m_values.at(channel);
}

void Sample::set(size_t channel, double value)
{
    m_values.at(channel) = value;
}

size_t Sample::channels() const
{
    return m_values.size();
}


}

