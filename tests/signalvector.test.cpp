#include <dsignal/signalvector.h>
#include <dsignal/signalprocessorbuffered.h>
#include <catch.hpp>

using namespace dsignal;

TEST_CASE("signalvector testPushPop", "[signalvector]")
{
    SignalVector sig(4, SignalProcessorBuffered(6));
    REQUIRE(sig.has()==false);

    Sample s(4);
    s.set(0, 10);
    s.set(1, 11);
    s.set(2, 12);
    s.set(3, 13);

    sig.push(s);
    sig.push(s);

    Sample s1 = sig.pop();
    REQUIRE(s1.get(0)==10);
    REQUIRE(s1.get(1)==11);
    REQUIRE(s1.get(2)==12);
    REQUIRE(s1.get(3)==13);

    Sample s2 = sig.pop();
    REQUIRE(s2.get(0)==10);
    REQUIRE(s2.get(1)==11);
    REQUIRE(s2.get(2)==12);
    REQUIRE(s2.get(3)==13);
}
