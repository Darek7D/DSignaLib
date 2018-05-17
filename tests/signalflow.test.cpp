/*
 * Copyright (C) 2018 Tedtronix.
 * This file is part of DSignal.
 *
 * DSignal is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DSignal is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
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
        SignalFlow sig1(&s, 4, SignalProcessorBuffered(), "Signal 1");
        SignalFlow sig2(&s, 4, SignalProcessorBuffered(), "Signal 2");
        SignalFlow sig3(&s, 4, SignalProcessorBuffered(), "Signal 3");
        SignalFlow sig4(&s, 4, SignalProcessorBuffered(), "Signal 4");
        SignalFlow sig3a(&s,4, SignalProcessorBuffered(), "Signal 3a");
        SignalFlow sig4a(&s,4, SignalProcessorBuffered(), "Signal 4a");
        SignalFlow sig5(&s, 4, SignalProcessorBuffered(), "Signal 5");

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

        std::cout << s.dumpGraph();

        REQUIRE(sig1.has() == false);
        REQUIRE(sig2.has() == false);
        REQUIRE(sig3.has() == false);
        REQUIRE(sig4.has() == false);
        REQUIRE(sig3a.has()== false);
        REQUIRE(sig4a.has()== false);
        REQUIRE(sig5.has() == false);

        WHEN("Push the sample") {
            s.input()->push(sample);
            s.process();
            THEN("Output signals have values") {
                REQUIRE(s.output(0)->pop().get(0)==10);
                REQUIRE(s.output(1)->pop().get(0)==10);
                REQUIRE(s.output(2)->pop().get(0)==10);

                REQUIRE(sig1.has() == false);
                REQUIRE(sig2.has() == false);
                REQUIRE(sig3.has() == false);
                REQUIRE(sig4.has() == false);
                REQUIRE(sig3a.has()== false);
                REQUIRE(sig4a.has()== false);
                REQUIRE(sig5.has() == false);
            }
        }
    }
}
