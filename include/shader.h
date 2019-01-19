/**
	Simple Sprite batch implementation using OpenGL.
	Copyright (C) 2015  Valdemar Lindberg

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
#ifndef _SB_SHADER_H_
#define _SB_SHADER_H_ 1
#include"def.h"

/**
 *
 */
typedef struct sb_shader_t {
	unsigned int program;       /*	shader program. */
	unsigned int flag;          /*  */
} SBShader;

#ifdef __cplusplus	/*	C++ environment	*/
extern "C"{
#endif

/**
 *	Load shader object from source GLSL
 *	source code.
 * @param shader
 * @param cvertexSource
 * @param cfragmentSource
 * @param cgeometry_source
 * @return 0 if failed.
 */
extern SBDECLSPEC int SBAPIENTRY sbCreateShaderv(SBShader* SB_RESTRICT shader,
        const char* SB_RESTRICT cvertexSource,
        const char* SB_RESTRICT cfragmentSource,
        const char* SB_RESTRICT cgeometry_source);

/**
 * Check if shader object is a valid shader object.
 * @param shader valid shader object.
 * @return non-zero if valid, zero otherwise.
 */
extern SBDECLSPEC int SBAPIENTRY sbIsShader(const SBShader* shader);

/**
 * Delete shader object.
 * @param shader valid shader object.
 * @return 0 if failed
 */
extern SBDECLSPEC int SBAPIENTRY sbDeleteShaderProgram(SBShader* shader);

/**
 * Compile GLSL shader.
 * @param source main source code.
 * @param flag type shader.
 * @return non-negative number of successfully.
 */
extern SBDECLSPEC int SBAPIENTRY sbCompileShaderSourcev(const char* source,
        unsigned int flag);

/**
 * Shader compile log.
 * @param program
 * @param shaderflag
 * @return
 */
extern SBDECLSPEC int SBAPIENTRY sbShaderCompileLog(unsigned int program,
        unsigned int shaderflag);


#ifdef __cplusplus
}
#endif

#endif 
