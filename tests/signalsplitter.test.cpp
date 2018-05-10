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
#include <dsignal/signalsplitter.h>
#include <catch.hpp>

using namespace dsignal;


TEST_CASE("signalsplitter testPipeline", "[signalsplitter]")
{
    SignalVector sig_source(4, SignalProcessorBuffered(6), "sig_source");

    SignalVector sig_1(4, SignalProcessorBuffered(6), "sig1");
    SignalVector sig_2(4, SignalProcessorBuffered(6), "sig2");
    SignalVector sig_3(4, SignalProcessorBuffered(6), "sig3");

    Sample sample1(4);
    sample1.set(0, 10);
    sample1.set(1, 11);
    sample1.set(2, 12);
    sample1.set(3, 13);

    SignalSplitter splitter;

    sample1 >> sig_source;
    sample1 >> sig_source;
    sample1 >> sig_source;
    sig_source >> splitter.split(sig_1).split(sig_2).split(sig_3);

    REQUIRE(splitter.has()==false);

    REQUIRE(sig_1.pop().get(0)==10);
    REQUIRE(sig_2.pop().get(1)==11);
    REQUIRE(sig_3.pop().get(2)==12);

    REQUIRE(sig_1.pop().get(3)==13);
    REQUIRE(sig_2.pop().get(0)==10);
    REQUIRE(sig_3.pop().get(1)==11);

    REQUIRE(sig_1.pop().get(2)==12);
    REQUIRE(sig_2.pop().get(3)==13);
    REQUIRE(sig_3.pop().get(0)==10);
}
