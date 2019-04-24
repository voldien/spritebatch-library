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
#ifndef _SB_FONT_H_
#define _SB_FONT_H_ 1
#include <stddef.h>
#include"def.h"
#include"texture.h"

#ifdef __cplusplus	/* C++ environment	*/
extern "C"{
#endif

/**
 * Font structure.
 */
typedef struct sb_font_t {
	SBTexture texture;          /*  Font texture.   */
	unsigned int numChar;       /*  Number of character.   */
	float* advance;             /*  */
	float* width;               /*  Width of each character in pixels.  */
	float* height;              /*  Height of each character in pixels.*/
	/*  UV rectangle.   */
	float* tex_x1;              /*  */
	float* tex_x2;              /*  */
	float* tex_y1;              /*  */
	float* tex_y2;              /*  */
	/*  UV offset.  */
	float* offset_x;            /*  */
	float* offset_y;            /*  */
	/*  Size of the font.   */
	float size;                 /*  */
}SBFont;

/**
 * Create font structure.
 * @param cpath valid file path.
 * @param font non-null valid pointer.s
 * @return non-zero if successfully.
 */
extern SBDECLSPEC int SBAPIENTRY sbCreateFont(const char* SB_RESTRICT cpath, SBFont* SB_RESTRICT font, const size_t size);

/**
 * Release font resources.
 * @param font valid font object.
 * @return non-negative if successfully.
 */
extern SBDECLSPEC int SBAPIENTRY sbDeleteFont(SBFont* font);

/**
 * Converts the the high resolution font bitmap to
 * signed distance field.
 * @param font Valid font object.
 * @param src font bitmap atlas.
 * @param dst signed distance field atlas.
 * @param srcWidth bitmap width in pixels.
 * @param srcHeight bitmap height in pixels.
 * @param dstWidth signed distance field width in pixels.
 * @param dstHeight signed distance field height in pixels.
 * @param downscale
 * @return non-negative if successfully.
 */
extern SBDECLSPEC int SBAPIENTRY sbCreateSignDistanceField(SBFont* SB_RESTRICT font, const void* SB_RESTRICT src, void** SB_RESTRICT dst,
                                                           int srcWidth, int srcHeight, int* SB_RESTRICT dstWidth,
                                                           int* SB_RESTRICT dstHeight, int downscale);

#ifdef __cplusplus	/* C++ environment	*/
}
#endif


#endif
