#include <QtTest>
#include <signalvector.h>
#include <signalprocessorbuffered.h>

using namespace dsignal;

class SignalVectorTest : public QObject
{
    Q_OBJECT

public:
    SignalVectorTest();

private Q_SLOTS:
    void testPushPop();
};

SignalVectorTest::SignalVectorTest()
{
}

void SignalVectorTest::testPushPop()
{
    SignalVector sig(4, SignalProcessorBuffered(6));
    QVERIFY(sig.has()==false);

    Sample s(4);
    s.set(0, 10);
    s.set(1, 11);
    s.set(2, 12);
    s.set(3, 13);

    sig.push(s);
    sig.push(s);

    Sample s1 = sig.pop();
    QVERIFY(s1.get(0)==10);
    QVERIFY(s1.get(1)==11);
    QVERIFY(s1.get(2)==12);
    QVERIFY(s1.get(3)==13);

    Sample s2 = sig.pop();
    QVERIFY(s2.get(0)==10);
    QVERIFY(s2.get(1)==11);
    QVERIFY(s2.get(2)==12);
    QVERIFY(s2.get(3)==13);
}


QTEST_APPLESS_MAIN(SignalVectorTest)

#include "tst_signalvector.moc"
