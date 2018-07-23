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

#include <dsignal/min.h>
#include <catch.hpp>
#include <iostream>

using namespace dsignal;

SCENARIO("minumum push pop test", "[minumum]")
{
    GIVEN("Min with 4 as mean buffer.") {
        Min m;

        REQUIRE(m.has()==false);

        WHEN("push some values") {
            m.push(100);
            m.push(50);
            m.push(40);
            m.push(80);

            THEN("it has some data") {
                REQUIRE(m.has()==true);
            }

            THEN("it has minimum on output") {
                REQUIRE(m.pop()==100);
                REQUIRE(m.pop()==50);
                REQUIRE(m.pop()==40);
                REQUIRE(m.pop()==40);
            }
        }
    }
}
