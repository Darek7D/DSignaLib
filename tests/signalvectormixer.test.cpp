#include <dsignal/signalvector.h>
#include <dsignal/signalvectormixer.h>
#include <dsignal/signalprocessorbuffered.h>
#include <dsignal/mixeroperationsubtract.h>
#include <catch.hpp>

using namespace dsignal;

SCENARIO("signalvectormixer push pop test", "[signalvectormixer]")
{
    SignalVector in(4, SignalProcessorBuffered());
    SignalVectorMixer mixer({{0,1}, {2,3}}, new MixerOperationSubtract());
    SignalVector out(2, SignalProcessorBuffered());

    Sample sample_in({1,2,3,4});
    Sample sample_out(2);

    sample_in >> in >> mixer >> out >> sample_out;

    REQUIRE(sample_out.get(0)==-1);
    REQUIRE(sample_out.get(1)==-1);
}
