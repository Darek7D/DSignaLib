#include <dsignal/dcmeanremoval.h>
#include <catch.hpp>
#include <iostream>

using namespace dsignal;

SCENARIO("dcmeanremoval push pop test - same values", "[dcmeanremoval]")
{
    GIVEN("A DcMeanRemoval with mean of 4 samples") {
        DcMeanRemoval m(4);

        REQUIRE(m.has()==false);

        WHEN("push some values") {
            m.push(4);
            m.push(4);
            m.push(4);
            m.push(4);

            THEN("it has some data") {
                REQUIRE(m.has()==true);
            }

            THEN("output values have DC removed") {
                REQUIRE(m.pop()==0);
                REQUIRE(m.pop()==0);
                REQUIRE(m.pop()==0);
                REQUIRE(m.pop()==0);
            }
        }
    }
}

SCENARIO("dcmeanremoval push pop test - different values", "[dcmeanremoval]")
{
    GIVEN("A DcMeanRemoval with mean of 4 samples") {
        DcMeanRemoval m(2);
        m.push(4);
        REQUIRE(m.pop()==0);
        m.push(6);
        REQUIRE(m.pop()==1);
        m.push(8);
        REQUIRE(m.pop()==1);
    }
}
