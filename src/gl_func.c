#include"glfuncs.h"
/*	*/
#ifdef SB_UNIX
	#include<GL/glx.h>
	#include<GL/glxext.h>
#endif


#ifdef GL_ES_VERSION_3_0
	#undef GL_ES_VERSION_3_0
	#include<GLES3/gl3ext.h>
#elif defined(GL_ES_VERSION_2_0)
	#undef GL_ES_VERSION_2_0
	#include<GLES2/gl2ext.h>
#else
	#include<GL/glext.h>
#include <dlfcn.h>

#endif

/*  */
PFNGLPOINTPARAMETERIPROC spbGLPointParameteri;
PFNGLPOINTPARAMETERFPROC spbGLPointParameterf;

/*  Shader. */
PFNGLCOMPILESHADERARBPROC spbGLCompileShaderARB;
PFNGLCREATESHADERPROC spbGLCreateShader;
PFNGLSHADERSOURCEARBPROC spbGLShaderSourceARB;
PFNGLGETUNIFORMLOCATIONPROC spbGLGetUniformLocation;
PFNGLDELETEPROGRAMPROC spbGLDeleteProgram;
PFNGLISSHADERPROC spbGLIsShader;
PFNGLDETACHSHADERPROC spbGLDetachShader;
PFNGLDELETESHADERPROC spbGLDeleteShader;
PFNGLATTACHSHADERPROC spbGLAttachShader;
PFNGLCREATEPROGRAMPROC spbGLCreateProgram;
PFNGLLINKPROGRAMPROC spbGLLinkProgram;
PFNGLUSEPROGRAMPROC spbGLUseProgram;
PFNGLGETPROGRAMIVPROC spbGLGetProgramiv;
PFNGLISPROGRAMPROC spbGLIsProgram;
PFNGLGETPROGRAMINFOLOGPROC spbGLGetProgramInfoLog;
PFNGLGETSHADERIVPROC spbGLGetShaderiv;
PFNGLGETSHADERINFOLOGPROC spbGLGetShaderInfoLog;
PFNGLVALIDATEPROGRAMPROC spbGLValidateProgram;

PFNGLPROGRAMUNIFORM1IVPROC spbGLProgramUniform1iv;
PFNGLPROGRAMUNIFORM1FVPROC spbGLProgramUniform1fv;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC spbGLProgramUniformMatrix3fv;

/*  */
PFNGLISPROGRAMARBPROC spbGLIsProgramARB;
PFNGLUNIFORM1IVARBPROC spbGLUniform1ivARB;
PFNGLUNIFORM1FVARBPROC spbGLUniform1fvARB;
PFNGLUNIFORMMATRIX3FVARBPROC spbGLUniformMatrix3fvARB;

/*  Buffer. */
PFNGLGENVERTEXARRAYSPROC spbGLGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC spbGLBindVertexArray;
PFNGLISVERTEXARRAYPROC spGLIsVertexArray;
PFNGLDELETEVERTEXARRAYSPROC spGLDeleteVertexArrays;

PFNGLBINDBUFFERARBPROC spbGLBindBufferARB;
PFNGLBUFFERDATAARBPROC spbGLBufferDataARB;
PFNGLDELETEBUFFERSARBPROC spbGLDeleteBuffersARB;
PFNGLISBUFFERARBPROC spbGLIsBufferARB;
PFNGLGENBUFFERSARBPROC spbGLGenBuffersARB;
PFNGLMAPBUFFERARBPROC spbGLMapBufferARB;
PFNGLUNMAPBUFFERARBPROC spbGLUnmapBufferARB;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC spbGLEnableVertexAttribArrayARB;
PFNGLVERTEXATTRIBPOINTERARBPROC spbGLVertexAttribPointerARB;
PFNGLBINDTEXTURESPROC spbGLBindTextures;

static SB_ALWAYS_INLINE void* load_gl_func(const char* symbol){
#ifdef SB_UNIX
	return (*glXGetProcAddressARB)((const GLubyte*)symbol);
#elif SB_WIN
	return wglGetProcAddress(symbol);
#endif
}

/**
 * Load all internal OpenGL Libriaries.
 */
int sb_internal_load_gl_func(void){

	/*  If any function is not null implies function has already been invoked.  */
	if(spbGLPointParameteri != NULL)
		return 2;

	/*  */
	spbGLPointParameteri = (PFNGLPOINTPARAMETERIPROC)load_gl_func("glPointParameteri");
	spbGLPointParameterf = (PFNGLPOINTPARAMETERFPROC)load_gl_func("glPointParameterf");

	/*  Load shader functions.  */
	spbGLCompileShaderARB = (PFNGLCOMPILESHADERARBPROC)load_gl_func("glCompileShaderARB");
	spbGLCreateShader = (PFNGLCREATESHADERPROC)load_gl_func("glCreateShader");
	spbGLShaderSourceARB = (PFNGLSHADERSOURCEARBPROC)load_gl_func("glShaderSourceARB");
	spbGLGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)load_gl_func("glGetUniformLocation");
	spbGLDeleteProgram = (PFNGLDELETEPROGRAMPROC)load_gl_func("glDeleteProgram");
	spbGLIsShader = (PFNGLISSHADERPROC)load_gl_func("glIsShader");
	spbGLDetachShader = (PFNGLDETACHSHADERPROC)load_gl_func("glDetachShader");
	spbGLDeleteShader = (PFNGLDELETESHADERPROC)load_gl_func("glDeleteShader");
	spbGLAttachShader = (PFNGLATTACHSHADERPROC)load_gl_func("glAttachShader");
	spbGLCreateProgram = (PFNGLCREATEPROGRAMPROC)load_gl_func("glCreateProgram");
	spbGLLinkProgram = (PFNGLLINKPROGRAMPROC)load_gl_func("glLinkProgram");
	spbGLUseProgram = (PFNGLUSEPROGRAMPROC )load_gl_func("glUseProgram");
	spbGLGetProgramiv = (PFNGLGETPROGRAMIVPROC)load_gl_func("glGetProgramiv");
	spbGLIsProgram = (PFNGLISPROGRAMPROC)load_gl_func("glIsProgram");
	spbGLGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)load_gl_func("glGetProgramInfoLog");
	spbGLGetShaderiv = (PFNGLGETSHADERIVPROC)load_gl_func("glGetShaderiv");
	spbGLGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)load_gl_func("glGetShaderInfoLog");
	spbGLValidateProgram = (PFNGLVALIDATEPROGRAMPROC)load_gl_func("glValidateProgram");

	/*  */
	spbGLIsProgramARB = (PFNGLISPROGRAMARBPROC)load_gl_func("glIsProgramARB");
	spbGLUniform1ivARB = (PFNGLUNIFORM1IVARBPROC)load_gl_func("glUniform1ivARB");
	spbGLUniform1fvARB = (PFNGLUNIFORM1FVARBPROC)load_gl_func("glUniform1fvARB");
	spbGLUniformMatrix3fvARB = (PFNGLUNIFORMMATRIX3FVARBPROC)load_gl_func("glUniformMatrix3fvARB");

	spbGLProgramUniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC)load_gl_func("glProgramUniform1iv");
	spbGLProgramUniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC)load_gl_func("glProgramUniform1fv");
	spbGLProgramUniformMatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)load_gl_func("glProgramUniformMatrix3fv");

	/*  */
	spbGLGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)load_gl_func("glGenVertexArrays");
	spbGLBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)load_gl_func("glBindVertexArray");
	spGLIsVertexArray = (PFNGLISVERTEXARRAYPROC)load_gl_func("glIsVertexArray");
	spGLDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)load_gl_func("glDeleteVertexArrays");

	/*  Load buffer functions.  */
	spbGLBindBufferARB = (PFNGLBINDBUFFERARBPROC)load_gl_func("glBindBufferARB");
	spbGLBufferDataARB = (PFNGLBUFFERDATAARBPROC)load_gl_func("glBufferDataARB");
	spbGLDeleteBuffersARB = load_gl_func("glDeleteBuffersARB");
	spbGLIsBufferARB = (PFNGLISBUFFERARBPROC)load_gl_func("glIsBufferARB");
	spbGLGenBuffersARB = (PFNGLGENBUFFERSARBPROC)load_gl_func("glGenBuffersARB");

	/*  Load buffer map functions.  */
	spbGLMapBufferARB = (PFNGLMAPBUFFERARBPROC)load_gl_func("glMapBufferARB");
	spbGLUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC)load_gl_func("glUnmapBufferARB");

	/*  */
	spbGLEnableVertexAttribArrayARB = load_gl_func("glEnableVertexAttribArrayARB");
	spbGLVertexAttribPointerARB = load_gl_func("glVertexAttribPointerARB");

	/*  */
	spbGLBindTextures = load_gl_func("glBindTextures");

	return 1;
}
