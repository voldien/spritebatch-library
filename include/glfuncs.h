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
#ifdef GL_ES_VERSION_3_0
#include<GLES3/gl3.h>
#elif defined(GL_ES_VERSION_2_0)
#undef GL_ES_VERSION_2_0
	#include<GLES2/gl2.h>
#else
#include<GL/gl.h>
#include<GL/glext.h>
#endif

#ifdef __cplusplus	/* C++ environment	*/
extern "C"{
#endif

/**
 * Load all OpenGL functions.
 */
extern SBDECLSPEC int sb_internal_load_gl_func(void);

/*  Point primitive.    */
extern SBDECLSPEC PFNGLPOINTPARAMETERIPROC spbGLPointParameteri;
extern SBDECLSPEC PFNGLPOINTPARAMETERFPROC spbGLPointParameterf;

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

/*  Uniforms.   */
extern SBDECLSPEC PFNGLUNIFORM1IVARBPROC spbGLUniform1ivARB;
extern SBDECLSPEC PFNGLUNIFORM1FVARBPROC spbGLUniform1fvARB;
extern SBDECLSPEC PFNGLUNIFORMMATRIX3FVARBPROC spbGLUniformMatrix3fvARB;

/*  Program uniforms.   */
extern SBDECLSPEC PFNGLPROGRAMUNIFORM1IVPROC spbGLProgramUniform1iv;
extern SBDECLSPEC PFNGLPROGRAMUNIFORM1FVPROC spbGLProgramUniform1fv;
extern SBDECLSPEC PFNGLPROGRAMUNIFORMMATRIX3FVPROC spbGLProgramUniformMatrix3fv;

/*  */
extern SBDECLSPEC PFNGLGENVERTEXARRAYSPROC spbGLGenVertexArrays;
extern SBDECLSPEC PFNGLBINDVERTEXARRAYPROC spbGLBindVertexArray;
extern SBDECLSPEC PFNGLISVERTEXARRAYPROC spGLIsVertexArray;
extern SBDECLSPEC PFNGLDELETEVERTEXARRAYSPROC spGLDeleteVertexArrays;
extern SBDECLSPEC PFNGLBINDVERTEXBUFFERPROC spGLBindVertexBuffer;

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
