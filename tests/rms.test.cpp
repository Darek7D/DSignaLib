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

#include <dsignal/rms.h>
#include <limits>
#include <catch.hpp>

using namespace dsignal;

TEST_CASE("rms testSameValues", "[rms]")
{
    Rms rms(4);
    rms.push(10);
    rms.push(10);
    rms.push(10);
    rms.push(10);
    REQUIRE(rms.pop()==10);
}

TEST_CASE("rms testNegativePositive", "[rms]")
{
    Rms rms(5);
    rms.push(-2);
    rms.push(5);
    rms.push(-8);
    rms.push(9);
    rms.push(-4);
    REQUIRE((rms.pop()>6.163 && rms.pop()<6.165)==true);
}

TEST_CASE("rms testReset", "[rms]")
{
    Rms rms(5);
    REQUIRE(rms.has()==false);
    rms.push(-2);
    REQUIRE(rms.has()==true);
    rms.push(5);
    rms.push(-8);
    rms.push(9);
    rms.push(-4);
    rms.reset();
    REQUIRE(rms.has()==false);
    REQUIRE(rms.pop()==0);
}

TEST_CASE("rms testOverflow", "[rms]")
{
    bool exception = false;
    try {
        Rms rms(4);
        rms.push(std::numeric_limits<double>::max());
        rms.push(std::numeric_limits<double>::max());
        rms.push(std::numeric_limits<double>::max());
        rms.push(std::numeric_limits<double>::max());
    } catch (std::exception &e) {
        exception = true;
    }

    REQUIRE(exception);
}
