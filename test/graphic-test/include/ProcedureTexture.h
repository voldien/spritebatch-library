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
#ifndef SPRITEBATCH_PROCEDURETEXTURE_H_
#define SPRITEBATCH_PROCEDURETEXTURE_H_ 1

#include <texture.h>

/**
 *
 */
class ProcedureTexture {
public:
	static void createCheckTexture(int width, int height, int checkWidth, int checkheight, const float* color1, const float* color2, SBTexture* texture);
	static void createCircleTexture(int width, int height, const float* color, SBTexture* texture);

};

#endif