/**
	Simple Sprite batch implementation using OpenGL.
	Copyright (C) 2019  Valdemar Lindberg

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
#ifndef SPRITEBATCH_SCENE_H_
#define SPRITEBATCH_SCENE_H_ 1
#include <sprite.h>

/**
 * 
 */
class Scene {
public:

	Scene(void);
	~Scene(void);

	virtual void init(void) = 0;

	virtual void releases(void) = 0;

	virtual void update(void) = 0;

	virtual void draw(float time) = 0;

	virtual void* getData(void);

	virtual SBSpriteBatch* getSpriteBatch(void);

	virtual const char* getName(void) const = 0;

protected:
	SBSpriteBatch* spriteBatch;
};

#endif
