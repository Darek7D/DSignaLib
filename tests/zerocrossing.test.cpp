#include <dsignal/zerocrossing.h>
#include <catch.hpp>
#include <iostream>

using namespace dsignal;

SCENARIO("Zero-crossing push pop test - without zero crossing", "[zerocrossing]")
{
    GIVEN("ZeroCrossing empty buffer.") {
        ZeroCrossing z;

        REQUIRE(z.has()==false);

        WHEN("push some values") {
            z.push(100);
            z.push(50);
            z.push(40);
            z.push(80);

            THEN("it has some data") {
                REQUIRE(z.has()==true);
            }

            THEN("it has no zero-crossing on output") {
                REQUIRE(z.pop()==0);
                REQUIRE(z.pop()==0);
                REQUIRE(z.pop()==0);
                REQUIRE(z.pop()==0);
            }
        }
    }
}

SCENARIO("Zero-crossing push pop test - with one zero crossing", "[zerocrossing]")
{
    GIVEN("ZeroCrossing empty buffer.") {
        ZeroCrossing z;

        REQUIRE(z.has()==false);

        WHEN("push some values") {
            z.push(100);
            z.push(-10);
            z.push(-10);
            z.push(-20);

            THEN("it has some data") {
                REQUIRE(z.has()==true);
            }

            THEN("it has one zero-crossing on output") {
                REQUIRE(z.pop()==0);
                REQUIRE(z.pop()==1);
                REQUIRE(z.pop()==1);
                REQUIRE(z.pop()==1);
            }
        }
    }
}

SCENARIO("Zero-crossing push pop test - with multiple zero crossing", "[zerocrossing]")
{
    GIVEN("ZeroCrossing empty buffer.") {
        ZeroCrossing z;

        REQUIRE(z.has()==false);

        WHEN("push some values") {
            z.push(100);
            z.push(-10);
            z.push(1);
            z.push(-0.1);
            z.push(0.01);
            z.push(-0.0001);
            z.push(0.000001);
            z.push(0.000001);

            THEN("it has some data") {
                REQUIRE(z.has()==true);
            }

            THEN("it has multiple zero-crossing on output") {
                REQUIRE(z.pop()==0);
                REQUIRE(z.pop()==1);
                REQUIRE(z.pop()==2);
                REQUIRE(z.pop()==3);
                REQUIRE(z.pop()==4);
                REQUIRE(z.pop()==5);
                REQUIRE(z.pop()==6);
                REQUIRE(z.pop()==6);
            }
        }
    }
}
