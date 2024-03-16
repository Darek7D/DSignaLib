#include <dsignal/decimator.h>
#include <catch.hpp>

using namespace dsignal;


SCENARIO("signal decimator should remove samples", "[signalprocessordecimator]")
{
    GIVEN("Decimator with factor 2") {
        Decimator sig(2);

        WHEN("push 7 samples") {
            sig.push(0);
            sig.push(1);
            sig.push(2);
            sig.push(3);
            sig.push(4);
            sig.push(5);
            sig.push(6);
            THEN("the size grows to 4") {
                REQUIRE(sig.size()==4);
                REQUIRE(sig.has());
            }

            THEN("poped values are equals to 0, 2, 4, 6") {
                REQUIRE(sig.pop()==0);
                REQUIRE(sig.pop()==2);
                REQUIRE(sig.pop()==4);
                REQUIRE(sig.pop()==6);
                AND_THEN("there is no more samples") {
                    REQUIRE(!sig.has());
                }
            }
        }
    }
}
