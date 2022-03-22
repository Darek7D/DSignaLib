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
#include <dsignal/signalsplitter.h>
#include <catch.hpp>

using namespace dsignal;

SCENARIO("signalsplitter split the signal", "[signalsplitter]")
{
    GIVEN("Source signal, three output signals, one sample and signal splitter") {
        SignalVector sig_source(4, SignalProcessorBuffered(6), "sig_source");
        SignalVector sig_1(4, SignalProcessorBuffered(6), "sig1");
        SignalVector sig_2(4, SignalProcessorBuffered(6), "sig2");
        SignalVector sig_3(4, SignalProcessorBuffered(6), "sig3");

        // Sample sample
        Sample sample1(4);
        sample1.set(0, 10);
        sample1.set(1, 11);
        sample1.set(2, 12);
        sample1.set(3, 13);

        SignalSplitter splitter;

        WHEN("add some samples to sig_source and split to signal outputs") {
            sample1 >> sig_source;
            sample1 >> sig_source;
            sample1 >> sig_source;

            // Push samples from sig_source to splitter
            sig_source >> splitter.split(sig_1).split(sig_2).split(sig_3);

            THEN("splitter have not data itself (it only forwards data)") {
                REQUIRE(splitter.has()==false);
            }

            THEN ("every output signal sample have the same data") {
                Sample sample_from_sig_1 = sig_1.pop();
                REQUIRE(sample_from_sig_1.get(0)==10);
                REQUIRE(sample_from_sig_1.get(1)==11);
                REQUIRE(sample_from_sig_1.get(2)==12);
                REQUIRE(sample_from_sig_1.get(3)==13);

                Sample sample_from_sig_2 = sig_2.pop();
                REQUIRE(sample_from_sig_2.get(0)==10);
                REQUIRE(sample_from_sig_2.get(1)==11);
                REQUIRE(sample_from_sig_2.get(2)==12);
                REQUIRE(sample_from_sig_2.get(3)==13);

                Sample sample_from_sig_3 = sig_3.pop();
                REQUIRE(sample_from_sig_3.get(0)==10);
                REQUIRE(sample_from_sig_3.get(1)==11);
                REQUIRE(sample_from_sig_3.get(2)==12);
                REQUIRE(sample_from_sig_3.get(3)==13);
            }
        }
    }
}
