#include <QtTest>
#include <rms.h>
#include <limits>

using namespace dsignal;

class RmsTest: public QObject
{
    Q_OBJECT
public:
    RmsTest(){}

private Q_SLOTS:
    void testSameValues();
    void testNegativePositive();
    void testReset();
    void testOverflow();
};

void RmsTest::testSameValues()
{
    Rms rms(4);
    rms.push(10);
    rms.push(10);
    rms.push(10);
    rms.push(10);
    QVERIFY(rms.pop()==10);
}

void RmsTest::testNegativePositive()
{
    Rms rms(5);
    rms.push(-2);
    rms.push(5);
    rms.push(-8);
    rms.push(9);
    rms.push(-4);
    QVERIFY(rms.pop()>6.163 && rms.pop()<6.165);
}

void RmsTest::testReset()
{
    Rms rms(5);
    QVERIFY(rms.has()==false);
    rms.push(-2);
    QVERIFY(rms.has()==true);
    rms.push(5);
    rms.push(-8);
    rms.push(9);
    rms.push(-4);
    rms.reset();
    QVERIFY(rms.has()==false);
    QVERIFY(rms.pop()==0);
}

void RmsTest::testOverflow()
{
    bool exception = false;
    try {
        Rms rms(4);
        rms.push(std::numeric_limits<double>::max());
        rms.push(std::numeric_limits<double>::max());
        rms.push(std::numeric_limits<double>::max());
        rms.push(std::numeric_limits<double>::max());
    } catch (std::exception &e) {
        exception = true;
    }

    QVERIFY(exception);
}


QTEST_APPLESS_MAIN(RmsTest)

#include "tst_rms.moc"
