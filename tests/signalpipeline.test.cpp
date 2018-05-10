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
#include <catch.hpp>

using namespace dsignal;


TEST_CASE("signalpipeline testPipeline", "[signalpipeline]")
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

    REQUIRE(sout.get(0)==10);
    REQUIRE(sout.get(1)==11);
    REQUIRE(sout.get(2)==12);
    REQUIRE(sout.get(3)==13);
}
