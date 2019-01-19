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
#ifndef _SB_TEXTURE_H_
#define _SB_TEXTURE_H_ 1
#include"def.h"

/**
 * Texture structure.
 */
typedef struct sb_texture{
	unsigned int target;            /*	Texture target. */
	unsigned int texture;           /*	Texture UID.    */
	unsigned int width;             /*	Texture width in pixels.    */
	unsigned int height;            /*	Texture height in pixels.   */
	unsigned int layer;             /*	Number of layers.   */
	unsigned int type;              /*	Internal data type per pixel channel.   */
	unsigned int internalformat;	/*	Internal pixel channel format.    */
}SBTexture;


#ifdef __cplusplus	/*	C++ environment	*/
extern "C"{
#endif

/**
 * Create spritebatch texture object.
 * @param texture
 * @param target
 * @param level
 * @param internalFormat
 * @param width
 * @param height
 * @param border
 * @param format
 * @param type
 * @param pixels
 * @return pointer address of texture object.
 */
extern SBDECLSPEC SBTexture* SBAPIENTRY sbCreateTexture(SBTexture* SB_RESTRICT texture,
        unsigned int target, int level, int internalFormat, int width,
        int height, int border, unsigned int format, unsigned int type,
        const void * SB_RESTRICT pixels);

/**
 * Delete texture. Releases texture resources from graphic memory.
 * @param texture valid texture object.
 */
extern SBDECLSPEC void SBAPIENTRY sbDeleteTexture(SBTexture* texture);

/**
 * Check if texture is a OpenGL texture object and is valid.
 * @param texture
 * @return None zero if true.
 */
extern SBDECLSPEC int SBAPIENTRY sbIsTexture(const SBTexture* texture);

#ifdef __cplusplus	/* C++ environment	*/
}
#endif 


#endif 

