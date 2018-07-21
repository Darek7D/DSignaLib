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

#include <dsignal/arithmeticmean.h>
#include <catch.hpp>
#include <iostream>

using namespace dsignal;

SCENARIO("arithmeticmean push pop test", "[arithmeticmean]")
{
    GIVEN("ArithmeticMean with 4 as mean buffer.") {
        ArithmeticMean m(4);

        REQUIRE(m.has()==false);

        WHEN("push some values") {
            m.push(1);
            m.push(2);
            m.push(3);
            m.push(4);

            THEN("it has some data") {
                REQUIRE(m.has()==true);
            }

            THEN("it has averaged output values") {
                REQUIRE(m.pop()==1);
                REQUIRE(m.pop()==1.5);
                REQUIRE(m.pop()==2.0);
                REQUIRE(m.pop()==2.5);
            }
        }
    }
}
