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

#include <dsignal/dcmeanremoval.h>
#include <catch.hpp>
#include <iostream>

using namespace dsignal;

SCENARIO("dcmeanremoval push pop test - same values", "[dcmeanremoval]")
{
    GIVEN("A DcMeanRemoval with mean of 4 samples") {
        DcMeanRemoval m(4);

        REQUIRE(m.has()==false);

        WHEN("push some values") {
            m.push(4);
            m.push(4);
            m.push(4);
            m.push(4);

            THEN("it has some data") {
                REQUIRE(m.has()==true);
            }

            THEN("output values have DC removed") {
                REQUIRE(m.pop()==0);
                REQUIRE(m.pop()==0);
                REQUIRE(m.pop()==0);
                REQUIRE(m.pop()==0);
            }
        }
    }
}

SCENARIO("dcmeanremoval push pop test - different values", "[dcmeanremoval]")
{
    GIVEN("A DcMeanRemoval with mean of 4 samples") {
        DcMeanRemoval m(2);
        m.push(4);
        REQUIRE(m.pop()==0);
        m.push(6);
        REQUIRE(m.pop()==1);
        m.push(8);
        REQUIRE(m.pop()==1);
    }
}
