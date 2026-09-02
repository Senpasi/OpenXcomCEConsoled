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
#include "MiniBaseView.h"
#include <cmath>
#include "../Engine/SurfaceSet.h"
#include "../Engine/Action.h"
#include "../Savegame/Base.h"
#include "../Savegame/BaseFacility.h"
#include "../Mod/RuleBaseFacility.h"

namespace OpenXcom
{

/**
 * Sets up a mini base view with the specified size and position.
 * @param width Width in pixels.
 * @param height Height in pixels.
 * @param x X position in pixels.
 * @param y Y position in pixels.
 */
MiniBaseView::MiniBaseView(int width, int height, int x, int y) : InteractiveSurface(width, height, x, y), _bases(0), _texture(0), _base(0), _hoverBase(0), _page(0), _hoverZone(ZONE_NONE), _red(0), _green(0), _blue(0)
{
}

/**
 *
 */
MiniBaseView::~MiniBaseView()
{
}

/**
 * Changes the current list of bases to display.
 * @param bases Pointer to base list to display.
 */
void MiniBaseView::setBases(std::vector<Base*> *bases)
{
	_bases = bases;
	_redraw = true;
}

/**
 * Changes the texture to use for drawing
 * the various base elements.
 * @param texture Pointer to SurfaceSet to use.
 */
void MiniBaseView::setTexture(SurfaceSet *texture)
{
	_texture = texture;
}

/**
 * Returns the base the mouse cursor is currently over.
 * @return ID of the base.
 */
size_t MiniBaseView::getHoveredBase() const
{
	return _hoverBase;
}

/**
 * Changes the base that is currently selected on
 * the mini base view.
 * @param base ID of base.
 */
void MiniBaseView::setSelectedBase(size_t base)
{
	_base = base;

	const size_t numBases = _bases ? _bases->size() : 0;
	if (numBases > VISIBLE_BASES && base < numBases)
	{
		if (base < _page)
			_page = base;
		else if (base >= _page + VISIBLE_BASES)
			_page = base - VISIBLE_BASES + 1;
	}
	if (_page > numBases)
		_page = 0;

	_redraw = true;
}

/**
 * Draws the view of all the bases with facilities
 * in varying colors.
 */
void MiniBaseView::draw()
{
	Surface::draw();

	const size_t numBases = _bases ? _bases->size() : 0;

	if (numBases <= VISIBLE_BASES)
		_page = 0;
	else if (_page + VISIBLE_BASES > numBases)
		_page = numBases - VISIBLE_BASES;

	const bool canLeft  = _page > 0;
	const bool canRight = _page + VISIBLE_BASES < numBases;

	drawArrow(0, true, canLeft);
	drawArrow(VISIBLE_BASES + 1, false, canRight);

	for (int j = 0; j < VISIBLE_BASES; ++j)
	{
		const size_t baseIndex = _page + j;
		const int x = (j + 1) * (MINI_SIZE + 2);

		if (baseIndex == _base)
		{
			SDL_Rect r;
			r.x = x;
			r.y = 0;
			r.w = MINI_SIZE + 2;
			r.h = MINI_SIZE + 2;
			drawRect(&r, 1);
		}
		_texture->getFrame(41)->blitNShade(this, x, 0);

		if (baseIndex < numBases)
		{
			SDL_Rect r;
			lock();
			for (const auto* fac : *_bases->at(baseIndex)->getFacilities())
			{
				int color;
				if (fac->getDisabled())
					color = _blue;
				else if (fac->getBuildTime() == 0)
					color = _green;
				else
					color = _red;

				r.x = x + 2 + fac->getX() * 2;
				r.y = 2 + fac->getY() * 2;
				r.w = fac->getRules()->getSizeX() * 2;
				r.h = fac->getRules()->getSizeY() * 2;
				drawRect(&r, color + 3);
				r.x++;
				r.y++;
				r.w--;
				r.h--;
				drawRect(&r, color + 5);
				r.x--;
				r.y--;
				drawRect(&r, color + 2);
				r.x++;
				r.y++;
				r.w--;
				r.h--;
				drawRect(&r, color + 3);
				r.x--;
				r.y--;
				setPixel(r.x, r.y, color + 1);
			}
			unlock();
		}
	}
}

/**
 * Draw pagination arrows to scroll through the list of bases.
 */
void MiniBaseView::drawArrow(int cell, bool left, bool enabled)
{
	if (!enabled)
		return;

	const Uint8 color = 1;
	const int cx0 = cell * (MINI_SIZE + 2);
	const int midY = MINI_SIZE / 2;

	for (int y = 0; y < MINI_SIZE; ++y)
	{
		const int t = (y > midY) ? (y - midY) : (midY - y);
		if (t > midY)
			continue;
		if (left)
		{
			const int rightEdge = cx0 + MINI_SIZE - 3;
			const int apex = cx0 + 3;
			const int leftBound = apex + (rightEdge - apex) * t / (midY + 1);
			for (int x = leftBound; x <= rightEdge; ++x)
				setPixel(x, y, color);
		}
		else
		{
			const int leftEdge = cx0 + 3;
			const int apex = cx0 + MINI_SIZE - 3;
			const int rightBound = apex - (apex - leftEdge) * t / (midY + 1);
			for (int x = leftEdge; x <= rightBound; ++x)
				setPixel(x, y, color);
		}
	}
}

/**
 * Selects the base the mouse is over.
 * @param action Pointer to an action.
 * @param state State that the action handlers belong to.
 */
void MiniBaseView::mouseOver(Action *action, State *state)
{
	const size_t numBases = _bases ? _bases->size() : 0;
	const int cell = (int)floor(action->getRelativeXMouse() / ((MINI_SIZE + 2) * action->getXScale()));

	if (cell == 0)
	{
		_hoverZone = ZONE_LEFT;
	}
	else if (cell >= 1 && cell <= VISIBLE_BASES)
	{
		const size_t baseIndex = _page + (cell - 1);
		if (baseIndex < numBases)
		{
			_hoverZone = ZONE_BASE;
			_hoverBase = baseIndex;
		}
		else
		{
			_hoverZone = ZONE_NONE;
			_hoverBase = numBases;
		}
	}
	else if (cell == VISIBLE_BASES + 1)
	{
		_hoverZone = ZONE_RIGHT;
	}
	else
	{
		_hoverZone = ZONE_NONE;
		_hoverBase = numBases;
	}

	InteractiveSurface::mouseOver(action, state);
}

void MiniBaseView::mouseClick(Action *action, State *state)
{
	if (_hoverZone == ZONE_LEFT)
	{
		pageLeft();
		return;
	}
	if (_hoverZone == ZONE_RIGHT)
	{
		pageRight();
		return;
	}
	InteractiveSurface::mouseClick(action, state);
}

void MiniBaseView::pageLeft()
{
	if (_page > 0)
	{
		--_page;
		_redraw = true;
	}
}
void MiniBaseView::pageRight()
{
	const size_t numBases = _bases ? _bases->size() : 0;
	if (_page + VISIBLE_BASES < numBases)
	{
		++_page;
		_redraw = true;
	}
}

void MiniBaseView::setColor(Uint8 color)
{
	_green = color;
}
void MiniBaseView::setSecondaryColor(Uint8 color)
{
	_red = color;
}
void MiniBaseView::setBorderColor(Uint8 color)
{
	_blue = color;
}

}
