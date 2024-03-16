#include <dsignal/additionner.h>
#include <catch.hpp>

using namespace dsignal;

SCENARIO("addition push pop test", "[additionner]")
{
    GIVEN("A additionner with 2 factor") {
        Additionner m(2);

        REQUIRE(m.has()==false);

        WHEN("push two values") {
            m.push(1);
            m.push(10);

            THEN("it has some data") {
                REQUIRE(m.has()==true);
            }

            THEN("output values are summed") {
                REQUIRE(m.pop()==3);
                REQUIRE(m.pop()==12);
            }
        }
    }
}
