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

/*  Shader. */
extern SBDECLSPEC PFNGLCOMPILESHADERARBPROC spbGLCompileShaderARB;
extern SBDECLSPEC PFNGLISPROGRAMARBPROC spbGLIsProgramARB;
extern SBDECLSPEC PFNGLUNIFORM1IVARBPROC spbGLUniform1ivARB;

/*  Buffer. */
extern SBDECLSPEC PFNGLGENVERTEXARRAYSPROC spbGLGenVertexArrays;
extern SBDECLSPEC PFNGLBINDVERTEXARRAYPROC spbGLBindVertexArray;
extern SBDECLSPEC PFNGLISVERTEXARRAYPROC spGLIsVertexArray;
extern SBDECLSPEC PFNGLDELETEVERTEXARRAYSPROC spGLDeleteVertexArrays;

/*  */
extern SBDECLSPEC PFNGLBINDBUFFERARBPROC spbGLBindBufferARB;
extern SBDECLSPEC PFNGLBUFFERDATAARBPROC spbGLBufferDataARB;
extern SBDECLSPEC PFNGLDELETEBUFFERSARBPROC spbGLDeleteBuffersARB;
extern SBDECLSPEC PFNGLISBUFFERARBPROC spbGLIsBufferARB;
extern SBDECLSPEC PFNGLGENBUFFERSARBPROC spbGLGenBuffersARB;

/*  */
extern SBDECLSPEC PFNGLMAPBUFFERARBPROC spbGLMapBufferARB;
extern SBDECLSPEC PFNGLUNMAPBUFFERARBPROC spbGLUnmapBufferARB;

/*  */
extern SBDECLSPEC PFNGLENABLEVERTEXATTRIBARRAYARBPROC spbGLEnableVertexAttribArrayARB;
extern SBDECLSPEC PFNGLVERTEXATTRIBPOINTERARBPROC spbGLVertexAttribPointerARB;

/*  */
extern SBDECLSPEC PFNGLBINDTEXTURESPROC spbGLBindTextures;


#ifdef __cplusplus    /* C++ environment	*/
}
#endif


#endif
