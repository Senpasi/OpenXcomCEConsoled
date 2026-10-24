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
#include "ShowUnitsBState.h"
#include "BattlescapeGame.h"
#include "BattlescapeState.h"
#include "Camera.h"
#include "Map.h"
#include "../Savegame/SavedBattleGame.h"
#include <algorithm>
#include <utility>

namespace OpenXcom
{

/**
 * Sets up a ShowUnitsBState.
 * @param parent Pointer to the Battlescape.
 * @param positions Positions to show, in order.
 * @param durationMs How long to hold the camera on each position.
 */
ShowUnitsBState::ShowUnitsBState(BattlescapeGame *parent, std::vector<Position> positions, int durationMs) :
	BattleState(parent), _positions(std::move(positions)), _index(0), _ticks(0)
{
	_ticksPerPosition = std::max(1, durationMs / BattlescapeState::DEFAULT_ANIM_SPEED);
}

/**
 * Deletes the ShowUnitsBState.
 */
ShowUnitsBState::~ShowUnitsBState()
{
}

/**
 * Initializes the state: centers the camera on the first position right away,
 * so the player sees it the moment the next turn screen is dismissed.
 */
void ShowUnitsBState::init()
{
	if (_positions.empty())
	{
		_parent->popState();
		return;
	}
	_parent->setStateInterval(BattlescapeState::DEFAULT_ANIM_SPEED);
	_parent->getMap()->getCamera()->centerOnPosition(_positions.front(), false);
}

/**
 * Ends the showcase: returns the camera to the selected unit (if any).
 */
void ShowUnitsBState::deinit()
{
	BattlescapeState *state = _parent->getSave()->getBattleState();
	if (state)
	{
		state->btnCenterClick(0);
	}
}

/**
 * The showcase can be skipped by the player (right-click).
 */
void ShowUnitsBState::cancel()
{
	_parent->popState();
}

/**
 * Runs state functionality every cycle.
 * Moves the camera to the next shown position when its time is up,
 * and ends the showcase when all positions have been shown.
 */
void ShowUnitsBState::think()
{
	if (_positions.empty())
	{
		_parent->popState();
		return;
	}
	if (++_ticks < _ticksPerPosition)
	{
		return;
	}
	_ticks = 0;
	if (++_index >= _positions.size())
	{
		_parent->popState();
		return;
	}
	_parent->getMap()->getCamera()->centerOnPosition(_positions[_index]);
}

}
