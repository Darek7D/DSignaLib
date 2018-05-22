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

#include <dsignal/signalvector.h>
#include <dsignal/signalvectormixer.h>
#include <dsignal/signalprocessorbuffered.h>
#include <dsignal/mixeroperationsubtract.h>
#include <catch.hpp>

using namespace dsignal;

SCENARIO("signalvectormixer push pop test", "[signalvectormixer]")
{
    SignalVector in(4, SignalProcessorBuffered());
    SignalVectorMixer mixer({{0,1}, {2,3}}, new MixerOperationSubtract());
    SignalVector out(2, SignalProcessorBuffered());

    Sample sample_in({1,2,3,4});
    Sample sample_out(2);

    sample_in >> in >> mixer >> out >> sample_out;

    REQUIRE(sample_out.get(0)==-1);
    REQUIRE(sample_out.get(1)==-1);
}
