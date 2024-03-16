#include <dsignal/abs.h>
#include <catch.hpp>
#include <iostream>

using namespace dsignal;

SCENARIO("abs signal processor push pop test", "[abs]")
{
    GIVEN("Abs signal processor.") {
        Abs a;

        REQUIRE(a.has()==false);

        WHEN("push some values") {
            a.push(10);
            a.push(-50);
            a.push(60);
            a.push(-30);

            THEN("it has some data") {
                REQUIRE(a.has()==true);
            }

            THEN("it has absolute values on output") {
                REQUIRE(a.pop()==10);
                REQUIRE(a.pop()==50);
                REQUIRE(a.pop()==60);
                REQUIRE(a.pop()==30);
            }
        }
    }
}
