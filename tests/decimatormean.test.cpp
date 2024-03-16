#include <dsignal/decimatormean.h>
#include <catch.hpp>

using namespace dsignal;


SCENARIO("signal mean decimator should remove samples", "[decimatormean]")
{
    GIVEN("Decimator with factor 2") {
        DecimatorMean sig(2);

        WHEN("push 7 samples") {
            sig.push(0);
            sig.push(1);
            sig.push(2);
            sig.push(3);
            sig.push(4);
            sig.push(5);

            THEN("the size grows to 3") {
                REQUIRE(sig.size()==3);
                REQUIRE(sig.has());
            }

            THEN("poped values are equals to 0.5, 2.5, 4.5") {
                REQUIRE(sig.pop()==0.5);
                REQUIRE(sig.pop()==2.5);
                REQUIRE(sig.pop()==4.5);
                AND_THEN("there is no more samples") {
                    REQUIRE(!sig.has());
                }
            }
        }
    }
}
