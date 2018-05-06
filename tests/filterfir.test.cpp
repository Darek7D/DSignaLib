#include <catch.hpp>
#include <filterfir.h>

using namespace dsignal;

TEST_CASE("filterfir testPushPop", "[filterfir]")
{
    std::vector<double> coef={0.5, 0, 0.5};
    FilterFir fir(coef);
    fir.push(10);
    fir.push(10);
    fir.push(10);
    fir.push(10);
    REQUIRE(fir.pop()==5);
    REQUIRE(fir.pop()==5);
    REQUIRE(fir.pop()==10);
    REQUIRE(fir.pop()==10);
}

TEST_CASE("filterfir testClone", "[filterfir]")
{
    std::vector<double> coef={0.5, 0, 0.5};
    FilterFir fir(coef);
    fir.push(10);
    fir.push(10);
    fir.push(10);
    fir.push(10);

    FilterFir *fir2 = fir.clone();
    REQUIRE(fir2->pop()==5);
    REQUIRE(fir2->pop()==5);
    REQUIRE(fir2->pop()==10);
    REQUIRE(fir2->pop()==10);

    delete fir2;
}
