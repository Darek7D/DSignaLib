#include <dsignal/multiplier.h>
#include <catch.hpp>

using namespace dsignal;

SCENARIO("multiplier push pop test", "[multiplier]")
{
    GIVEN("A multiplier with 2.5 factor") {
        Multiplier m(2.5);

        REQUIRE(m.has()==false);

        WHEN("push two values") {
            m.push(1);
            m.push(10);

            THEN("it has some data") {
                REQUIRE(m.has()==true);
            }

            THEN("output values are multiplied") {
                REQUIRE(m.pop()==2.5);
                REQUIRE(m.pop()==25);
            }
        }
    }
}
