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

#include <dsignal/signalvector.h>
#include <dsignal/signalprocessorbuffered.h>
#include <catch.hpp>

using namespace dsignal;

TEST_CASE("signalvector testPushPop", "[signalvector]")
{
    SignalVector sig(4, SignalProcessorBuffered(6));
    REQUIRE(sig.has()==false);

    Sample s(4);
    s.set(0, 10);
    s.set(1, 11);
    s.set(2, 12);
    s.set(3, 13);

    sig.push(s);
    sig.push(s);

    Sample s1 = sig.pop();
    REQUIRE(s1.get(0)==10);
    REQUIRE(s1.get(1)==11);
    REQUIRE(s1.get(2)==12);
    REQUIRE(s1.get(3)==13);

    Sample s2 = sig.pop();
    REQUIRE(s2.get(0)==10);
    REQUIRE(s2.get(1)==11);
    REQUIRE(s2.get(2)==12);
    REQUIRE(s2.get(3)==13);
}
