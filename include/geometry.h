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
#ifndef _SB_GEOMETRY_H_
#define _SB_GEOMETRY_H_ 1
#include"def.h"

#ifdef __cplusplus	/* C++ environment	*/
extern "C"{
#endif

/**
 * Create opengl buffer object.
 * @param n
 * @param buffers
 */
extern SBDECLSPEC void SBAPIENTRY sbGenBuffers(int n, unsigned int* buffers);

/**
 *
 * @param target
 * @param buffer
 */
extern SBDECLSPEC void SBAPIENTRY sbBindBuffer(int target, int buffer);

/**
 *
 * @param target
 * @param buffer
 * @return
 */
extern SBDECLSPEC int SBAPIENTRY sbIsBuffer(int buffer);

/**
 *
 * @param target
 * @param size
 * @param mode
 * @return
 */
extern SBDECLSPEC int SBAPIENTRY sbCreateVBO(unsigned int target, unsigned int size, unsigned int mode);

/**
 * Allocate/Reallocate buffer size.
 * @param target
 * @param buffer
 * @param size
 * @param mode
 */
extern SBDECLSPEC void SBAPIENTRY sbSetBufferSize(unsigned int target, unsigned int buffer, unsigned int size, unsigned int mode);

/**
 *
 * @param target
 * @param buffer
 * @param puf
 * @param len
 */
extern SBDECLSPEC void SBAPIENTRY sbBufferSetSubData(unsigned int target, unsigned int buffer, const void* puf, unsigned int len);

/**
 * Generate vertex arrays.
 * @param n
 * @param arg
 */
extern SBDECLSPEC void SBAPIENTRY sbGenVertexArrays(int n, unsigned int* arg);

/**
 * Destroy the buffer object reference and deallocate
 * the associated memory buffer region.
 *
 * @param buffer
 * @return
 */
extern SBDECLSPEC int SBAPIENTRY sbDestroyBuffer(unsigned int buffer);

/**
 *
 * @param target
 * @param buffer
 * @return
 */
extern SBDECLSPEC void* SBAPIENTRY sbMapBufferWOnly(unsigned int target, unsigned int buffer);

/**
 *
 * @param target
 */
extern SBDECLSPEC int SBAPIENTRY sbUnmapBuffer(unsigned int target);

/**
 *
 * @param vao
 * @param i
 * @param numDraw
 */
extern SBDECLSPEC void SBAPIENTRY sbDrawArray(unsigned int vao, int i, unsigned int numDraw);


#ifdef __cplusplus	/* C++ environment	*/
}
#endif 

#endif
