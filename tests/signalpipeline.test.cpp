#include <catch.hpp>
#include <signalvector.h>
#include <signalprocessorbuffered.h>

using namespace dsignal;


TEST_CASE("signalpipeline testPipeline", "[signalpipeline]")
{
    SignalVector sig1(4, SignalProcessorBuffered(6), "sig1");
    SignalVector sig2(4, SignalProcessorBuffered(6), "sig2");

    Sample sin(4);
    sin.set(0, 10);
    sin.set(1, 11);
    sin.set(2, 12);
    sin.set(3, 13);

    Sample sout;

    sin >> sig1 >> sig2 >> sout;

    REQUIRE(sout.get(0)==10);
    REQUIRE(sout.get(1)==11);
    REQUIRE(sout.get(2)==12);
    REQUIRE(sout.get(3)==13);
}
