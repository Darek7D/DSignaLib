#include <dsignal/signalprocessorbuffered.h>
#include <catch.hpp>

using namespace dsignal;


TEST_CASE("signalprocessorbuffered testPushPop", "[signalprocessorbuffered]")
{
    SignalProcessorBuffered sig;
    REQUIRE(sig.has()==false);
    sig.push(1);
    sig.push(2);
    sig.push(3);

    REQUIRE(sig.size()==3);
    REQUIRE(sig.has());

    REQUIRE(sig.pop()==1);
    REQUIRE(sig.pop()==2);
    REQUIRE(sig.pop()==3);

    REQUIRE(sig.size()==0);
    REQUIRE(sig.has()==false);
}

TEST_CASE("signalprocessorbuffered testOverflow", "[signalprocessorbuffered]")
{
    bool exception = false;
    SignalProcessorBuffered sig(4);
    try {
        sig.push(1);
        sig.push(2);
        sig.push(3);
        sig.push(4);
    } catch (std::exception &e) {
        exception = true;
    }
    REQUIRE(exception==false);

    exception = false;
    try {
        sig.push(5);
    } catch (std::exception &e) {
        exception = true;
    }
    REQUIRE(exception==true);
}

TEST_CASE("signalprocessorbuffered testUnderflow", "[signalprocessorbuffered]")
{
    bool exception = false;
    SignalProcessorBuffered sig(4);
    try {
        sig.push(1);
        sig.push(2);
        sig.pop();
        sig.pop();
        sig.pop();
    } catch (std::exception &e) {
        exception = true;
    }
    REQUIRE(exception);
}

TEST_CASE("signalprocessorbuffered testClone")
{
    SignalProcessorBuffered sig(4);
    sig.push(1);
    sig.push(2);

    SignalProcessorBuffered *sig2 = sig.clone();
    REQUIRE(sig2->maxSize()==4);
    REQUIRE(sig2->size()==2);
    REQUIRE(sig2->pop()==1);
    REQUIRE(sig2->pop()==2);

    delete sig2;
}
