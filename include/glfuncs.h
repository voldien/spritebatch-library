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
#ifndef _GLFUNCS_H_
#define _GLFUNCS_H_ 1
#include"def.h"
#include<GL/gl.h>
#include<GL/glext.h>

#ifdef __cplusplus	/* C++ environment	*/
extern "C"{
#endif

/**
 * Load all OpenGL functions.
 */
extern SBDECLSPEC int sb_internal_load_gl_func(void);

/*  */
extern SBDECLSPEC PFNGLPOINTPARAMETERIPROC glPointParameteri;
extern SBDECLSPEC PFNGLPOINTPARAMETERFPROC glPointParameterf;

/*  Shader. */
extern SBDECLSPEC PFNGLISPROGRAMARBPROC spbGLIsProgramARB;
extern SBDECLSPEC PFNGLCOMPILESHADERARBPROC spbGLCompileShaderARB;
extern SBDECLSPEC PFNGLCREATESHADERPROC spbGLCreateShader;
extern SBDECLSPEC PFNGLSHADERSOURCEARBPROC spbGLShaderSourceARB;
extern SBDECLSPEC PFNGLGETUNIFORMLOCATIONPROC spbGLGetUniformLocation;
extern SBDECLSPEC PFNGLDELETEPROGRAMPROC spbGLDeleteProgram;
extern SBDECLSPEC PFNGLISSHADERPROC spbGLIsShader;
extern SBDECLSPEC PFNGLDETACHSHADERPROC spbGLDetachShader;
extern SBDECLSPEC PFNGLDELETESHADERPROC spbGLDeleteShader;
extern SBDECLSPEC PFNGLATTACHSHADERPROC spbGLAttachShader;
extern SBDECLSPEC PFNGLCREATEPROGRAMPROC spbGLCreateProgram;
extern SBDECLSPEC PFNGLLINKPROGRAMPROC spbGLLinkProgram;
extern SBDECLSPEC PFNGLUSEPROGRAMPROC spbGLUseProgram;
extern SBDECLSPEC PFNGLGETPROGRAMIVPROC spbGLGetProgramiv;
extern SBDECLSPEC PFNGLISPROGRAMPROC spbGLIsProgram;
extern SBDECLSPEC PFNGLGETPROGRAMINFOLOGPROC spbGLGetProgramInfoLog;
extern SBDECLSPEC PFNGLGETSHADERIVPROC spbGLGetShaderiv;
extern SBDECLSPEC PFNGLGETSHADERINFOLOGPROC spbGLGetShaderInfoLog;
extern SBDECLSPEC PFNGLVALIDATEPROGRAMPROC spbGLValidateProgram;

/**/
extern SBDECLSPEC PFNGLUNIFORM1IVARBPROC spbGLUniform1ivARB;
extern SBDECLSPEC PFNGLUNIFORM1FVARBPROC spbGLUniform1fvARB;
extern SBDECLSPEC PFNGLUNIFORMMATRIX3FVARBPROC spbGLUniformMatrix3fvARB;

/*  */
extern SBDECLSPEC PFNGLGENVERTEXARRAYSPROC spbGLGenVertexArrays;
extern SBDECLSPEC PFNGLBINDVERTEXARRAYPROC spbGLBindVertexArray;
extern SBDECLSPEC PFNGLISVERTEXARRAYPROC spGLIsVertexArray;
extern SBDECLSPEC PFNGLDELETEVERTEXARRAYSPROC spGLDeleteVertexArrays;

/*  Buffer. */
extern SBDECLSPEC PFNGLBINDBUFFERARBPROC spbGLBindBufferARB;
extern SBDECLSPEC PFNGLBUFFERDATAARBPROC spbGLBufferDataARB;
extern SBDECLSPEC PFNGLDELETEBUFFERSARBPROC spbGLDeleteBuffersARB;
extern SBDECLSPEC PFNGLISBUFFERARBPROC spbGLIsBufferARB;
extern SBDECLSPEC PFNGLGENBUFFERSARBPROC spbGLGenBuffersARB;

/*  Buffer mapper.  */
extern SBDECLSPEC PFNGLMAPBUFFERARBPROC spbGLMapBufferARB;
extern SBDECLSPEC PFNGLUNMAPBUFFERARBPROC spbGLUnmapBufferARB;

/*  */
extern SBDECLSPEC PFNGLENABLEVERTEXATTRIBARRAYARBPROC spbGLEnableVertexAttribArrayARB;
extern SBDECLSPEC PFNGLVERTEXATTRIBPOINTERARBPROC spbGLVertexAttribPointerARB;

/*  Textures.   */
// glTexStorage3D
extern SBDECLSPEC PFNGLBINDTEXTURESPROC spbGLBindTextures;


#ifdef __cplusplus    /* C++ environment	*/
}
#endif


#endif
