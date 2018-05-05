#include <QtTest>
#include <filterfir.h>

using namespace dsignal;

class FilterFirTest : public QObject
{
    Q_OBJECT

public:
    FilterFirTest();

private Q_SLOTS:
    void testPushPop();
    void testClone();
};

FilterFirTest::FilterFirTest()
{
}

void FilterFirTest::testPushPop()
{
    std::vector<double> coef={0.5, 0, 0.5};
    FilterFir fir(coef);
    fir.push(10);
    fir.push(10);
    fir.push(10);
    fir.push(10);
    QVERIFY(fir.pop()==5);
    QVERIFY(fir.pop()==5);
    QVERIFY(fir.pop()==10);
    QVERIFY(fir.pop()==10);
}

void FilterFirTest::testClone()
{
    std::vector<double> coef={0.5, 0, 0.5};
    FilterFir fir(coef);
    fir.push(10);
    fir.push(10);
    fir.push(10);
    fir.push(10);

    FilterFir *fir2 = fir.clone();
    QVERIFY(fir2->pop()==5);
    QVERIFY(fir2->pop()==5);
    QVERIFY(fir2->pop()==10);
    QVERIFY(fir2->pop()==10);

    delete fir2;
}


QTEST_APPLESS_MAIN(FilterFirTest)

#include "tst_filterfir.moc"
