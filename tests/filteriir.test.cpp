#include <dsignal/filteriir.h>
#include <catch.hpp>

using namespace dsignal;

TEST_CASE("filteriir testPushPop", "[filteriir]")
{
    std::vector<double> coef_a={1.0, 2, 4};
    std::vector<double> coef_b={1, 2, 4};
    FilterIir iir(coef_a, coef_b);
    iir.push(10);
    iir.push(10);
    iir.push(10);
    iir.push(10);
    iir.push(10);
    iir.push(10);

    /*Todo:
    qDebug() << iir.pop();
    qDebug() << iir.pop();
    qDebug() << iir.pop();
    qDebug() << iir.pop();
    qDebug() << iir.pop();
    qDebug() << iir.pop();*/

    /*QVERIFY(fir.pop()==5);
    QVERIFY(fir.pop()==5);
    QVERIFY(fir.pop()==10);
    QVERIFY(fir.pop()==10);*/
}
