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
#include <catch.hpp>

using namespace dsignal;


TEST_CASE("signalprocessorbuffered testPushPop", "[signalprocessorbuffered]")
{
    SignalProcessorBuffered sig;
    REQUIRE(sig.has()==false);
    sig.push(1);
    sig.push(2);
    sig.push(3);

    REQUIRE(sig.size()==3);
    REQUIRE(sig.has());

    REQUIRE(sig.value()==1);
    REQUIRE(sig.pop()==1);

    REQUIRE(sig.value()==2);
    REQUIRE(sig.pop()==2);

    REQUIRE(sig.value()==3);
    REQUIRE(sig.pop()==3);

    REQUIRE(sig.size()==0);
    REQUIRE(sig.has()==false);
}

TEST_CASE("signalprocessorbuffered testOverflow", "[signalprocessorbuffered]")
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
    REQUIRE(exception==false);

    exception = false;
    try {
        sig.push(5);
    } catch (std::exception &e) {
        exception = true;
    }
    REQUIRE(exception==true);
}

TEST_CASE("signalprocessorbuffered testUnderflow", "[signalprocessorbuffered]")
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
    REQUIRE(exception);
}

TEST_CASE("signalprocessorbuffered testClone")
{
    SignalProcessorBuffered sig(4);
    sig.push(1);
    sig.push(2);

    SignalProcessorBuffered *sig2 = sig.clone();
    REQUIRE(sig2->maxSize()==4);
    REQUIRE(sig2->size()==2);
    REQUIRE(sig2->pop()==1);
    REQUIRE(sig2->pop()==2);

    delete sig2;
}
