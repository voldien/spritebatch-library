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

/*  Sprite attributes.  */
#line 1
ATTRIBUTE_IN(0) vec3 vertex;
ATTRIBUTE_IN(1) float angle;
ATTRIBUTE_IN(2) vec4 rect;
ATTRIBUTE_IN(3) int tex;
ATTRIBUTE_IN(4) float scale;
ATTRIBUTE_IN(5) vec4 color;

/*  */
uniform mat3 gmat;
uniform float gscale;
#ifdef gl_MaxVertexTextureImageUnits
uniform sampler2D textures[gl_MaxVertexTextureImageUnits];
#else
uniform sampler2D textures[16];
#endif 

/*  Compute varying attributes. */
SMOOTH_OUT float fangle;
SMOOTH_OUT vec4 frect;
SMOOTH_OUT mat2 coord;
FLAT_OUT int ftexture;
SMOOTH_OUT vec4 fcolor;

/**
 * Get texture by index.
 */
ivec2 getTexture(const in int index) {
#if __VERSION__ >= 410
	return textureSize(textures[index], 0);
#else
	switch(index) {
		case 0:
		return textureSize(textures[0], 0);
		case 1:
		return textureSize(textures[1], 0);
		case 2:
		return textureSize(textures[2], 0);
		case 3:
		return textureSize(textures[3], 0);
		case 4:
		return textureSize(textures[4], 0);
		case 5:
		return textureSize(textures[5], 0);
		case 6:
		return textureSize(textures[6], 0);
		case 7:
		return textureSize(textures[7], 0);
		case 8:
		return textureSize(textures[8], 0);
		case 9:
		return textureSize(textures[9], 0);
		case 10:
		return textureSize(textures[10], 0);
		case 11:
		return textureSize(textures[11], 0);
		case 12:
		return textureSize(textures[12], 0);
		case 13:
		return textureSize(textures[13], 0);
		case 14:
		return textureSize(textures[14], 0);
		case 15:
		return textureSize(textures[15], 0);
#ifdef gl_MaxTextureImageUnits
    #if gl_MaxTextureImageUnits > 16
		case 16:
		return textureSize(textures[16], 0);
		case 17:
		return textureSize(textures[17], 0);
		case 18:
		return textureSize(textures[18], 0);
		case 19:
		return textureSize(textures[19], 0);
		case 20:
		return textureSize(textures[20], 0);
		case 21:
		return textureSize(textures[21], 0);
		case 22:
		return textureSize(textures[22], 0);
		case 23:
		return textureSize(textures[23], 0);
		case 24:
		return textureSize(textures[24], 0);
		case 25:
		return textureSize(textures[25], 0);
		case 26:
		return textureSize(textures[26], 0);
		case 27:
		return textureSize(textures[27], 0);
		case 28:
		return textureSize(textures[28], 0);
		case 29:
		return textureSize(textures[29], 0);
		case 30:
		return textureSize(textures[30], 0);
		case 31:
		return textureSize(textures[31], 0);
		/*
		case 32:
		return textureSize(textures[32], 0);
		case 33:
		return textureSize(textures[33], 0);*/
    #endif
#endif
		default:
		return textureSize(textures[0], 0);
	}

#endif
}

void main(void) {

    /*  */
	float sin_theta = sin(angle);
	float cos_theta = cos(angle);

	/*	Compute rotation matrix.    */
	coord = mat2(cos_theta, sin_theta, -sin_theta, cos_theta);

	/*	Compute UV coordinates. */
	vec2 uv = coord
	        * vec2(float(getTexture(tex).x) * rect.z * scale,
	                float(getTexture(tex).y) * rect.w * scale);

	/*	Compute point size. */
	gl_PointSize = float(
	        max(abs(uv.x * sin(angle)) + abs(uv.y * cos(angle)),
	                abs(uv.x * cos(angle)) + abs(uv.y * sin(angle))));

    /*  Scale transformation.   */
	gl_PointSize *= gscale;

	/*  */
	gl_Position = vec4((gmat * vec3(vertex.xy, 1.0)).xy, vertex.z, 1.0);

	/*	*/
	fangle = angle;
	frect = rect;
	ftexture = tex;
	fcolor = color;
}
