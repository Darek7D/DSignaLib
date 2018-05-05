#include <QtTest>
#include <signalprocessorbuffered.h>

using namespace dsignal;

class SignalProcessorBufferedTest : public QObject
{
    Q_OBJECT

public:
    SignalProcessorBufferedTest();

private Q_SLOTS:
    void testPushPop();
    void testOverflow();
    void testUnderflow();
    void testClone();
};

SignalProcessorBufferedTest::SignalProcessorBufferedTest()
{
}

void SignalProcessorBufferedTest::testPushPop()
{
    SignalProcessorBuffered sig;
    QVERIFY(sig.has()==false);
    sig.push(1);
    sig.push(2);
    sig.push(3);

    QVERIFY(sig.size()==3);
    QVERIFY(sig.has());

    QVERIFY(sig.pop()==1);
    QVERIFY(sig.pop()==2);
    QVERIFY(sig.pop()==3);

    QVERIFY(sig.size()==0);
    QVERIFY(sig.has()==false);
}

void SignalProcessorBufferedTest::testOverflow()
{
    bool exception = false;
    SignalProcessorBuffered sig(4);
    try {
        sig.push(1);
        sig.push(2);
        sig.push(3);
        sig.push(4);
    } catch (std::exception &e) {
        exception = true;
    }
    QVERIFY(exception==false);

    exception = false;
    try {
        sig.push(5);
    } catch (std::exception &e) {
        exception = true;
    }
    QVERIFY(exception==true);
}

void SignalProcessorBufferedTest::testUnderflow()
{
    bool exception = false;
    SignalProcessorBuffered sig(4);
    try {
        sig.push(1);
        sig.push(2);
        sig.pop();
        sig.pop();
        sig.pop();
    } catch (std::exception &e) {
        exception = true;
    }
    QVERIFY(exception);
}

void SignalProcessorBufferedTest::testClone()
{
    SignalProcessorBuffered sig(4);
    sig.push(1);
    sig.push(2);

    SignalProcessorBuffered *sig2 = sig.clone();
    QVERIFY(sig2->maxSize()==4);
    QVERIFY(sig2->size()==2);
    QVERIFY(sig2->pop()==1);
    QVERIFY(sig2->pop()==2);

    delete sig2;
}

QTEST_APPLESS_MAIN(SignalProcessorBufferedTest)

#include "tst_signalprocessorbufferedtest.moc"
