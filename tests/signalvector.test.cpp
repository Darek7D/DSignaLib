#include <dsignal/signalvector.h>
#include <dsignal/signalprocessorbuffered.h>
#include <catch.hpp>

using namespace dsignal;

SCENARIO("signalvector push pop test", "[signalvector]")
{
    GIVEN("An empty 4-channel signal vector with buffered signal processor") {
        SignalVector sig(4, SignalProcessorBuffered());

        REQUIRE(sig.has()==false);

        WHEN("two init samples are pushed") {
            {
                Sample s(4);
                s.set(0, 10.);
                s.set(1, 11.);
                s.set(2, 12.);
                s.set(3, 13.);
                sig.push(s);
            }
            {
                Sample s(4);
                s.set(0, 20.);
                s.set(1, 21.);
                s.set(2, 22.);
                s.set(3, 23.);
                sig.push(s);
            }
            THEN("it has some data") {
                REQUIRE(sig.has()==true);
            }

            THEN("it has 2 samples") {
                REQUIRE(sig.size()==2);
            }

            THEN("samples at positions are equal to init samples") {
                {
                    Sample s = sig.at(0);
                    REQUIRE(s.get(0)==10.);
                    REQUIRE(s.get(1)==11.);
                    REQUIRE(s.get(2)==12.);
                    REQUIRE(s.get(3)==13.);
                }
                {
                    Sample s = sig.at(1);
                    REQUIRE(s.get(0)==20.);
                    REQUIRE(s.get(1)==21.);
                    REQUIRE(s.get(2)==22.);
                    REQUIRE(s.get(3)==23.);
                }
            }

            THEN("samples are equal to init samples") {

                Sample s1a = sig.value();
                REQUIRE(s1a.get(0)==10.);
                REQUIRE(s1a.get(1)==11.);
                REQUIRE(s1a.get(2)==12.);
                REQUIRE(s1a.get(3)==13.);

                Sample s1b = sig.pop();
                REQUIRE(s1b.get(0)==10.);
                REQUIRE(s1b.get(1)==11.);
                REQUIRE(s1b.get(2)==12.);
                REQUIRE(s1b.get(3)==13.);

                Sample s2a = sig.value();
                REQUIRE(s2a.get(0)==20.);
                REQUIRE(s2a.get(1)==21.);
                REQUIRE(s2a.get(2)==22.);
                REQUIRE(s2a.get(3)==23.);

                Sample s2b = sig.pop();
                REQUIRE(s2b.get(0)==20.);
                REQUIRE(s2b.get(1)==21.);
                REQUIRE(s2b.get(2)==22.);
                REQUIRE(s2b.get(3)==23.);
            }
        }
    }
}
