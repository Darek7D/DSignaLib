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

#include <dsignal/filteriir.h>
#include <catch.hpp>

using namespace dsignal;

TEST_CASE("filteriir testPushPop", "[filteriir]")
{
    std::vector<double> coef_a={1.0, 2, 4};
    std::vector<double> coef_b={1, 2, 4};
    FilterIir iir(coef_a, coef_b);
    iir.push(10);
    iir.push(10);
    iir.push(10);
    iir.push(10);
    iir.push(10);
    iir.push(10);

    /*Todo:
    qDebug() << iir.pop();
    qDebug() << iir.pop();
    qDebug() << iir.pop();
    qDebug() << iir.pop();
    qDebug() << iir.pop();
    qDebug() << iir.pop();*/

    /*QVERIFY(fir.pop()==5);
    QVERIFY(fir.pop()==5);
    QVERIFY(fir.pop()==10);
    QVERIFY(fir.pop()==10);*/
}
