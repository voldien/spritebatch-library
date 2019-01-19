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
#line 1
//#extension GL_EXT_gpu_shader4 : enable

/*  Sprite attributes.  */
ATTRIBUTE_IN(0) vec3 vertex;
ATTRIBUTE_IN(1) float angle;
ATTRIBUTE_IN(2) vec4 rect;
ATTRIBUTE_IN(3) int tex;
ATTRIBUTE_IN(4) float scale;
ATTRIBUTE_IN(5) vec4 color;

/*  */
SMOOTH_OUT float fangle;
SMOOTH_OUT vec4 frect;
SMOOTH_OUT mat2 coord;
FLAT_OUT int ftexture;
SMOOTH_OUT vec4 fcolor;

void main(void){

}