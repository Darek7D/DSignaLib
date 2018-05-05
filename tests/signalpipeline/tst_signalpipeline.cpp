#include <QtTest>
#include <signalvector.h>
#include <signalprocessorbuffered.h>

using namespace dsignal;

class SignalPipelineTest : public QObject
{
    Q_OBJECT

public:
    SignalPipelineTest();

private Q_SLOTS:
    void testPipeline();
};

SignalPipelineTest::SignalPipelineTest()
{
}

void SignalPipelineTest::testPipeline()
{
    SignalVector sig1(4, SignalProcessorBuffered(6), "sig1");
    SignalVector sig2(4, SignalProcessorBuffered(6), "sig2");

    Sample sin(4);
    sin.set(0, 10);
    sin.set(1, 11);
    sin.set(2, 12);
    sin.set(3, 13);

    Sample sout;

    sin >> sig1 >> sig2 >> sout;

    QVERIFY(sout.get(0)==10);
    QVERIFY(sout.get(1)==11);
    QVERIFY(sout.get(2)==12);
    QVERIFY(sout.get(3)==13);
}


QTEST_APPLESS_MAIN(SignalPipelineTest)

#include "tst_signalpipeline.moc"
