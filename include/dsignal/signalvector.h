#pragma once

#include "sample.h"
#include "signalprocessor.h"
#include "dsignal_export.h"
#include <string>
#include <mutex>

namespace dsignal {

typedef std::vector<SignalProcessor*> TSignals;

/**
 * The SignalVector is a multichannel version of SignalProcessor.
 * It takes a Sample as an input and push every channel of Sample to
 * separate SignalProcessor. It doesn't collect any data itself.
 * Every pushed values are forwarded to provided SignalProcessor.
 *
 * \copydoc operator>>(SignalVector &output_signal)
 * \copydoc operator>>(Sample &output_sample)
 */
class DSIGNAL_EXPORT SignalVector
{
public:
    SignalVector();

    /**
     * Contructor of the SignalVector.
     * \param channels the number of channels - it is a number of SignalProcessors's
     *        which will be cloned.
     * \param signal_processor SignalProcessor prototype.
     * \param name optional name for easier identification (i.e. when
     *        generating SignalFlow graphs)
     */
    SignalVector(size_t channels, const SignalProcessor &signal_processor,
                 std::string name="");
    SignalVector(const SignalVector& signal_vector);
    virtual ~SignalVector();

    virtual SignalVector & operator=(const SignalVector &signal_vector);

    /**
     * Pops the values from underlying SignalProcessor's and return as a Sample.
     */
    virtual Sample pop();

    /**
     * Gets the current values from underlying SignalProcessor's and return as a Sample.
     */
    virtual Sample value() const;

    /**
     * Gets the values at the position 'n' from underlying SignalProcessor's and return as a Sample.
     */
    virtual Sample at(size_t n) const;

    /**
     * Checks if a SignalVector has a value, that you can pop().
     */
    virtual bool has() const;

    /**
     * Pushes a Sample to SignalVector. Each channel Sample channel will be splitted
     * and pushed separately to the internal SignalProcessor's.
     */
    virtual void push(const Sample &sample);

    /**
     * Returns the number of samples available to pop().
     */
    virtual size_t size() const;

    /**
     * Resets each SignalProcessor.
     */
    virtual void reset();

    /**
     * Clones the SignalVector object.
     */
    virtual SignalVector *clone() const;

    /**
     * Enables or disables the SignalVector. If disabled, any pushed Sample
     * will be ignored.
     */
    virtual void enable(bool enable=true);
    virtual bool enabled();

    /**
     * Returns the number of channels.
     */
    virtual size_t channels() const;

    /**
     * Sets the name of SignalVector.
     * The name can be used for easier identification (i.e. when generating
     * SignalFlow graphs)
     */
    virtual void setName(const std::string &name);

    /**
     * Returns the name of SignalVector.
     */
    virtual std::string getName() const;

    /**
     * Returns the internal SignalProcessor.
     */
    virtual SignalProcessor* getSignalProcessor(size_t channel) const;

    /**
     * Using operator>> you can pop() every data from one SignalVector
     * and push() it to another, example:
     * \code
     * SignalVector a(...), b(...);
     * // All buffer from 'a' will be transfered to 'b'
     * a >> b;
     * \endcode
     */
    virtual SignalVector& operator>>(SignalVector &output_signal);

    /**
     * Using operator>> with Sample, you can push it to the SignalVector, example:
     * \code
     * SignalVector vect(...);
     * Sample sample(...);
     * sample >> vect;
     * \endcode
     */
    virtual Sample& operator>>(Sample &output_sample);

protected:
    TSignals m_signals;

private:
    std::string m_name;
    mutable std::mutex m_mutex;
    bool m_enabled;
};

inline SignalVector& operator>>(const Sample &sample, SignalVector &signal)
{
    signal.push(sample);
    return signal;
}

}

