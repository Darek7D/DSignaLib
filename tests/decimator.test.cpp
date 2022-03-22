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

#include <dsignal/decimator.h>
#include <catch.hpp>

using namespace dsignal;


SCENARIO("signal decimator should remove samples", "[signalprocessordecimator]")
{
    GIVEN("Decimator with factor 2") {
        Decimator sig(2);

        WHEN("push 7 samples") {
            sig.push(0);
            sig.push(1);
            sig.push(2);
            sig.push(3);
            sig.push(4);
            sig.push(5);
            sig.push(6);
            THEN("the size grows to 4") {
                REQUIRE(sig.size()==4);
                REQUIRE(sig.has());
            }

            THEN("poped values are equals to 0, 2, 4, 6") {
                REQUIRE(sig.pop()==0);
                REQUIRE(sig.pop()==2);
                REQUIRE(sig.pop()==4);
                REQUIRE(sig.pop()==6);
                AND_THEN("there is no more samples") {
                    REQUIRE(!sig.has());
                }
            }
        }
    }
}
