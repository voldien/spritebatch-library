/**
	Simple Sprite batch implementation using OpenGL.
	Copyright (C) 2017  Valdemar Lindberg

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */
#ifndef SPRITEBATCH_POLARROSESCENE_H_
#define SPRITEBATCH_POLARROSESCENE_H_ 1
#include "BenchmarkScene.h"

class PolarRoseScene : public BenchmarkScene {
public:
	float getTotalElapseTime(void) override;

	void init(void) override;

	void releases(void) override;

	void update(void) override;

	void draw(float time) override;

	const char *getName(void) const override;

public:
	SBTexture texture;
};

#endif