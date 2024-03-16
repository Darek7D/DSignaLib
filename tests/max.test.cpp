#include <dsignal/max.h>
#include <catch.hpp>
#include <iostream>

using namespace dsignal;

SCENARIO("maximum push pop test", "[maximum]")
{
    GIVEN("Max signal processor.") {
        Max m;

        REQUIRE(m.has()==false);

        WHEN("push some values") {
            m.push(10);
            m.push(50);
            m.push(60);
            m.push(30);

            THEN("it has some data") {
                REQUIRE(m.has()==true);
            }

            THEN("it has maximum on output") {
                REQUIRE(m.pop()==10);
                REQUIRE(m.pop()==50);
                REQUIRE(m.pop()==60);
                REQUIRE(m.pop()==60);
            }
        }
    }
}
