/*
 * Copyright (C) 2018 Tedtronix.
 * This file is part of DSignal.
 *
 * DSignal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DSignal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with DSignal.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <dsignal/signalprocessorbuffered.h>
#include <dsignal/signalvector.h>
#include <dsignal/signalflow.h>
#include <dsignal/signalflowsession.h>
#include <catch.hpp>
#include <memory>
#include <vector>
#include <iostream>

using namespace dsignal;

SCENARIO("Signal flow process", "[signalflow]")
{
    GIVEN("Source signal, flow and sample sample.") {
        SignalFlowSession s;

        // Create signal flow elements
        SignalFlow sig1(&s, SignalVector(4, SignalProcessorBuffered(), "Signal 1"));
        SignalFlow sig2(&s, SignalVector(4, SignalProcessorBuffered(), "Signal 2"));
        SignalFlow sig3(&s, SignalVector(4, SignalProcessorBuffered(), "Signal 3"));
        SignalFlow sig4(&s, SignalVector(4, SignalProcessorBuffered(), "Signal 4"));
        SignalFlow sig3a(&s,SignalVector(4, SignalProcessorBuffered(), "Signal 3a"));
        SignalFlow sig4a(&s,SignalVector(4, SignalProcessorBuffered(), "Signal 4a"));
        SignalFlow sig5(&s, SignalVector(4, SignalProcessorBuffered(), "Signal 5"));

        // Define a signal flow
        sig1 >> sig2.split(sig3)
                    .split(sig4) >> sig5;
        sig3 >> sig3a;
        sig4 >> sig4a;

        // Define inputs, outputs
        s.setInput(sig1);
        s.setOutput(sig5, 0);
        s.setOutput(sig3a, 1);
        s.setOutput(sig4a, 2);

        // Create sample
        Sample sample(4);
        sample.set(0, 10);
        sample.set(1, 11);
        sample.set(2, 12);
        sample.set(3, 13);

        WHEN("Push the sample") {
            s.input()->push(sample);
            s.process();
            THEN("Output signals have values") {
                REQUIRE(s.output(0)->pop().get(0)==10);
                REQUIRE(s.output(1)->pop().get(0)==10);
                REQUIRE(s.output(2)->pop().get(0)==10);
            }
        }

        WHEN("Push more samples") {
            for (int i=0; i<100; i++)
                s.input()->push(sample);
            s.process();
            THEN("Output signals have values") {
                REQUIRE(s.output(0)->size()==100);
                REQUIRE(s.output(1)->size()==100);
                REQUIRE(s.output(2)->size()==100);
                for (int i=0; i<100; i++) {
                    REQUIRE(s.output(0)->pop().get(0)==10);
                    REQUIRE(s.output(1)->pop().get(0)==10);
                    REQUIRE(s.output(2)->pop().get(0)==10);
                }
            }
        }

        WHEN("Push more samples when disabled") {
            s.enableOutputs(false);
            for (int i=0; i<100; i++)
                s.input()->push(sample);
            s.process();
            THEN("Output signals have no values") {
                REQUIRE(s.output(0)->size()==0);
                REQUIRE(s.output(1)->size()==0);
                REQUIRE(s.output(2)->size()==0);
            }
        }

        WHEN("Push more samples and reset") {
            s.enableOutputs(true);
            for (int i=0; i<100; i++)
                s.input()->push(sample);
            s.process();
            s.reset();
            THEN("Output signals have no values") {
                REQUIRE(s.output(0)->size()==0);
                REQUIRE(s.output(1)->size()==0);
                REQUIRE(s.output(2)->size()==0);
            }
        }
    }
}

SCENARIO("Signal flow disconnection", "[signalflow]")
{
    GIVEN("Two connected signals") {
        SignalFlowSession s;
        SignalFlow sig1(&s, SignalVector(4, SignalProcessorBuffered(), "Signal 1"));
        SignalFlow sig2a(&s, SignalVector(4, SignalProcessorBuffered(), "Signal 2A"));
        SignalFlow sig2b(&s, SignalVector(4, SignalProcessorBuffered(), "Signal 2B"));
        sig1 >> sig2a;
        sig1 >> sig2b;
        REQUIRE(s.connectedSignals(&sig1).size()==2);

        WHEN("sig2b is disconnected") {
            REQUIRE(s.disconnect(&sig1, &sig2a));
            THEN("There remains one connection in the list") {
                REQUIRE(s.connectedSignals(&sig1).size()==1);
            }
            AND_THEN("Disconnecting again returns false") {
                REQUIRE_FALSE(s.disconnect(&sig1, &sig2a));
            }
            AND_THEN("Disconnecting the sig2b returns true.") {
                REQUIRE(s.disconnect(&sig1, &sig2b));
            }
        }
    }
}

SCENARIO("Signal flow disconnection all", "[signalflow]")
{
    GIVEN("Two connected signals") {
        SignalFlowSession s;
        SignalFlow sig1(&s, SignalVector(4, SignalProcessorBuffered(), "Signal 1"));
        SignalFlow sig2a(&s, SignalVector(4, SignalProcessorBuffered(), "Signal 2A"));
        SignalFlow sig2b(&s, SignalVector(4, SignalProcessorBuffered(), "Signal 2B"));
        sig1 >> sig2a;
        sig1 >> sig2b;
        REQUIRE(s.connectedSignals(&sig1).size()==2);

        WHEN("All signals are disconnected") {
            REQUIRE(s.disconnect(&sig1));
            THEN("There are no connection in the list") {
                REQUIRE(s.connectedSignals(&sig1).size()==0);
            }
            AND_THEN("Second disconnection returns false") {
                REQUIRE_FALSE(s.disconnect(&sig1));
            }
        }
    }
}
