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
/*  */
FRAGLOCATION(0, vec4, fragColor);

/*  */
SMOOTH_IN float fangle;
SMOOTH_IN vec4 frect;
SMOOTH_IN mat2 coord;
FLAT_IN int ftexture;
SMOOTH_IN vec4 fcolor;

/*  Sprite textures.    */
uniform sampler2D textures[64];


void main(void){
    float distance = texture2D(textures[0], frect.zy).a;

    float smoothing = 0.0f;
    float alpha = smoothstep(0.5 - smoothing, 0.5 + smoothing, distance);

    /**/
    fragColor = vec4(fcolor.rgb, fcolor.a * alpha);
}