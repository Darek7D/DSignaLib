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

#include <dsignal/filterfir.h>
#include <catch.hpp>

using namespace dsignal;

TEST_CASE("filterfir testPushPop", "[filterfir]")
{
    std::vector<double> coef={0.5, 0, 0.5};
    FilterFir fir(coef);
    fir.push(10);
    fir.push(10);
    fir.push(10);
    fir.push(10);
    REQUIRE(fir.pop()==5);
    REQUIRE(fir.pop()==5);
    REQUIRE(fir.pop()==10);
    REQUIRE(fir.pop()==10);
}

TEST_CASE("filterfir testClone", "[filterfir]")
{
    std::vector<double> coef={0.5, 0, 0.5};
    FilterFir fir(coef);
    fir.push(10);
    fir.push(10);
    fir.push(10);
    fir.push(10);

    FilterFir *fir2 = fir.clone();
    REQUIRE(fir2->pop()==5);
    REQUIRE(fir2->pop()==5);
    REQUIRE(fir2->pop()==10);
    REQUIRE(fir2->pop()==10);

    delete fir2;
}
