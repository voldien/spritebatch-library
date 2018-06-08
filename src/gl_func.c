
/*	*/
#ifdef __unix__
	#include<GL/glx.h>
#endif


#ifdef GL_ES_VERSION_3_0
	#undef GL_ES_VERSION_3_0
	#include<GLES3/gl3.h>
	#include<GLES3/gl3ext.h>
	#include<GLES3/gl3platform.h>
#elif defined(GL_ES_VERSION_2_0)
	#undef GL_ES_VERSION_2_0
	#include<GLES2/gl2.h>
	#include<GLES2/gl2ext.h>
	#include<GLES2/gl2platform.h>
#else
	#include<GL/gl.h>
	#include<GL/glu.h>
	#include<GL/glext.h>
#endif

PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
PFNGLISPROGRAMARBPROC glIsProgramARB;
PFNGLUNIFORM1IVARBPROC glUniform1ivARB;

PFNGLBINDBUFFERARBPROC glBindBufferARB;
PFNGLBUFFERDATAARBPROC glBufferDataARB;
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
PFNGLISBUFFERARBPROC glIsBufferARB;
PFNGLGENBUFFERSARBPROC glGenBuffersARB;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDTEXTURESPROC glBindTextures;

static void* load_gl_func(const char* symbol){
#ifdef SB_UNIX
	return glXGetProcAddressARB(symbol);
#elif SB_WIN
#endif
}

void sb_internal_load_gl_func(void){
	/*  Load shader functions.  */
	glCompileShaderARB = load_gl_func("glCompileShaderARB");
	glIsProgramARB = load_gl_func("glIsProgramARB");
	glUniform1ivARB = load_gl_func("glUniform1ivARB");

	/*  Load buffer functions.  */
	glBindBufferARB = load_gl_func("glBindBufferARB");
	glBufferDataARB = load_gl_func("glBufferDataARB");
	glDeleteBuffersARB = load_gl_func("glDeleteBuffersARB");
	glIsBufferARB = load_gl_func("glIsBufferARB");
	glGenBuffersARB = load_gl_func("glGenBuffersARB");
	glGenVertexArrays = load_gl_func("glGenVertexArrays");

	glBindTextures = load_gl_func("glBindTextures");
}
