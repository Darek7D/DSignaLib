#include <dsignal/arithmeticmean.h>
#include <catch.hpp>
#include <iostream>

using namespace dsignal;

SCENARIO("arithmeticmean push pop test", "[arithmeticmean]")
{
    GIVEN("ArithmeticMean with 4 as mean buffer.") {
        ArithmeticMean m(4);

        REQUIRE(m.has()==false);

        WHEN("push some values") {
            m.push(1);
            m.push(2);
            m.push(3);
            m.push(4);

            THEN("it has some data") {
                REQUIRE(m.has()==true);
            }

            THEN("it has averaged output values") {
                REQUIRE(m.pop()==1);
                REQUIRE(m.pop()==1.5);
                REQUIRE(m.pop()==2.0);
                REQUIRE(m.pop()==2.5);
            }
        }
    }
}
