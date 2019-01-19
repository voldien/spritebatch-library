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
/*  */
#line 1
FRAGLOCATION(0, vec4, fragColor);

/*  */
SMOOTH_IN float fangle;
SMOOTH_IN vec4 frect;
SMOOTH_IN mat2 coord;
FLAT_IN int ftexture;
SMOOTH_IN vec4 fcolor;

/*  Sprite textures.    */
uniform sampler2D textures[32];

/**
 * Get texture by index.
 */
ivec2 getTexture(const in int index) {
#if __VERSION__ < 410
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
		default:
		return textureSize(textures[0], 0);
	}
#else
	return textureSize(textures[index], 0);
#endif
}

vec4 gettextfrag(const in int index, const in vec2 uv){
#if __VERSION__ < 410
	switch(index) {
		case 0:
		    return texture(textures[0], uv);
		case 1:
		    return texture(textures[1], uv);
		case 2:
		    return texture(textures[2], uv);
		case 3:
		    return texture(textures[3], uv);
		case 4:
		    return texture(textures[4], uv);
		case 5:
		    return texture(textures[5], uv);
		case 6:
		    return texture(textures[6], uv);
		case 7:
		    return texture(textures[7], uv);
		case 8:
		    return texture(textures[8], uv);
		case 9:
		    return texture(textures[9], uv);
		case 10:
		    return texture(textures[10], uv);
		case 11:
		    return texture(textures[11], uv);
		case 12:
		    return texture(textures[12], uv);
		case 13:
		    return texture(textures[13], uv);
		case 14:
		    return texture(textures[14], uv);
		case 15:
		    return texture(textures[15], uv);
		case 16:
		    return texture(textures[16], uv);
		case 17:
		    return texture(textures[17], uv);
		case 18:
		    return texture(textures[18], uv);
		case 19:
		    return texture(textures[19], uv);
		case 20:
		    return texture(textures[20], uv);
		case 21:
		    return texture(textures[21], uv);
		case 22:
		    return texture(textures[22], uv);
		case 23:
		    return texture(textures[23], uv);
		case 24:
		    return texture(textures[24], uv);
		case 25:
		    return texture(textures[25], uv);
		case 26:
		    return texture(textures[26], uv);
		case 27:
		    return texture(textures[27], uv);
		case 28:
		    return texture(textures[28], uv);
		case 29:
		    return texture(textures[29], uv);
		case 30:
		    return texture(textures[30], uv);/*
		case 31:
		    return texture(textures[31], uv);
		case 32:
		    return texture(textures[32], uv);
		case 33:
		    return texture(textures[33], uv);*/
		default:
		    return vec4(0.0);
	}
#else
	return texture2D(textures[index], uv);
#endif
}

void main(void){
    /*  Get texture width and height.   */
	float texwidth = float(getTexture(ftexture).x);
	float texheight = float(getTexture(ftexture).y);

	/*  */
	vec2 fragscale = vec2(clamp( texheight / texwidth, 1.0, 10.0 ) , clamp( texwidth / texheight, 1.0 ,10.0) );

    const vec2 coord = frect.xy  + ((vec2(1.0) - frect.zw) / 2.0) * vec2(-1.0, 1.0)  + vec2(0.5) + coord * ((gl_PointCoord - vec2(0.5) ) * frect.zw * fragscale.xy);

	const vec4 finalColor = gettextfrag(ftexture, coord);// * fcolor;
    fragColor = finalColor;
}
