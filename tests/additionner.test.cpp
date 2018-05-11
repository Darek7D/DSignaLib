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

#include <dsignal/additionner.h>
#include <catch.hpp>

using namespace dsignal;

SCENARIO("addition push pop test", "[additionner]")
{
    GIVEN("A additionner with 2 factor") {
        Additionner m(2);

        REQUIRE(m.has()==false);

        WHEN("push two values") {
            m.push(1);
            m.push(10);

            THEN("it has some data") {
                REQUIRE(m.has()==true);
            }

            THEN("output values are summed") {
                REQUIRE(m.pop()==3);
                REQUIRE(m.pop()==12);
            }
        }
    }
}
