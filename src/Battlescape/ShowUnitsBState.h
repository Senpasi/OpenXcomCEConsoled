#pragma once
/*
 * Copyright 2010-2016 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "BattleState.h"
#include "Position.h"
#include <vector>

namespace OpenXcom
{

class BattlescapeGame;

/**
 * State for briefly showing a list of positions to the player.
 * The camera is centered on each position in turn for a couple
 * of seconds, then the camera returns to the selected unit.
 * Used, for example, to show resurrected units after a turn change.
 */
class ShowUnitsBState : public BattleState
{
private:
	std::vector<Position> _positions;
	size_t _index;
	int _ticks;
	int _ticksPerPosition;
public:
	/// Creates a new ShowUnitsBState class.
	ShowUnitsBState(BattlescapeGame *parent, std::vector<Position> positions, int durationMs = 2000);
	/// Cleans up the ShowUnitsBState.
	~ShowUnitsBState();
	/// Initializes the state.
	void init() override;
	/// Called when the state gets popped out.
	void deinit() override;
	/// Handles a cancels request (skips the showcase).
	void cancel() override;
	/// Runs state functionality every cycle.
	void think() override;
};

}
