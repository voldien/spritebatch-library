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
 *
 */
typedef struct sb_font_t{
	struct sb_texture texture;  /*  */
	unsigned short* texUV;
	float size;
}SBFont;

/**
 * Create font.
 * @param cpath
 * @param font
 * @return non-zero if successfully.
 */
extern SBDECLSPEC int SBAPIENTRY sbCreateFont(const char* SB_RESTRICT cpath, SBFont* SB_RESTRICT font, const size_t size);

#ifdef __cplusplus	/* C++ environment	*/
}
#endif


#endif
