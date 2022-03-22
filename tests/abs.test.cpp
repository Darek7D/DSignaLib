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

#include <dsignal/abs.h>
#include <catch.hpp>
#include <iostream>

using namespace dsignal;

SCENARIO("abs signal processor push pop test", "[abs]")
{
    GIVEN("Abs signal processor.") {
        Abs a;

        REQUIRE(a.has()==false);

        WHEN("push some values") {
            a.push(10);
            a.push(-50);
            a.push(60);
            a.push(-30);

            THEN("it has some data") {
                REQUIRE(a.has()==true);
            }

            THEN("it has absolute values on output") {
                REQUIRE(a.pop()==10);
                REQUIRE(a.pop()==50);
                REQUIRE(a.pop()==60);
                REQUIRE(a.pop()==30);
            }
        }
    }
}
