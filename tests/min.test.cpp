#include <dsignal/min.h>
#include <catch.hpp>
#include <iostream>

using namespace dsignal;

SCENARIO("minumum push pop test", "[minumum]")
{
    GIVEN("Min with 4 as mean buffer.") {
        Min m;

        REQUIRE(m.has()==false);

        WHEN("push some values") {
            m.push(100);
            m.push(50);
            m.push(40);
            m.push(80);

            THEN("it has some data") {
                REQUIRE(m.has()==true);
            }

            THEN("it has minimum on output") {
                REQUIRE(m.pop()==100);
                REQUIRE(m.pop()==50);
                REQUIRE(m.pop()==40);
                REQUIRE(m.pop()==40);
            }
        }
    }
}
