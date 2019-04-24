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
#ifndef SPRITEBATCH_TESTSCENE_H_
#define SPRITEBATCH_TESTSCENE_H_ 1

#include "BenchmarkScene.h"

/**
 *
 */
class TestScene : public BenchmarkScene {
public:
	virtual float getTotalElapseTime(void);

	virtual void init(void);

	virtual void releases(void);

	virtual void update(void);

	virtual void draw(float time);

	virtual const char *getName(void) const;

private:
	SBTexture texture;
};

#endif