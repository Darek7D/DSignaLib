#include <QtTest>
#include <filteriir.h>

using namespace dsignal;

class FilterIirTest : public QObject
{
    Q_OBJECT

public:
    FilterIirTest();

private Q_SLOTS:
    void testPushPop();
};

FilterIirTest::FilterIirTest()
{
}

void FilterIirTest::testPushPop()
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

    qDebug() << iir.pop();
    qDebug() << iir.pop();
    qDebug() << iir.pop();
    qDebug() << iir.pop();
    qDebug() << iir.pop();
    qDebug() << iir.pop();

    /*QVERIFY(fir.pop()==5);
    QVERIFY(fir.pop()==5);
    QVERIFY(fir.pop()==10);
    QVERIFY(fir.pop()==10);*/
}


QTEST_APPLESS_MAIN(FilterIirTest)

#include "tst_filteriir.moc"
