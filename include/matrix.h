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
#ifndef _SB_MATRIX_H_
#define _SB_MATRIX_H_ 1
#include"def.h"

#ifdef __cplusplus	/* C++ environment	*/
extern "C"{
#endif

/**
 * Create right handed translation matrix.
 * @param tranmat
 * @param pos
 */
extern SBDECLSPEC void SBAPIENTRY sbMatrix3x3Translation(float tranmat[3][3], float pos[2]);

/**
 * Create right handed scale matrix.
 * @param scalemat
 * @param scale
 */
extern SBDECLSPEC void SBAPIENTRY sbMatrix3x3Scale(float scalemat[3][3], float scale);


/**
 * Create right handed scale matrix.
 * @param scalemat
 * @param scale
 */
extern SBDECLSPEC void SBAPIENTRY sbMatrix3x3Rotation(float scalemat[3][3], float rotation);


 /**
  * Multiply two matrices.
  * @param matscale
  * @param tranmat
  * @param viewmatrix
  */
extern SBDECLSPEC void SBAPIENTRY sbMatrix3x3MultiMatrix3x3(const float matscale[3][3], const float tranmat[3][3],
        float viewmatrix[3][3]);

#ifdef __cplusplus	/* C++ environment	*/
}
#endif

#endif
