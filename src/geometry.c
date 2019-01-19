#include"geometry.h"
#include<stdio.h>
#include"glfuncs.h"

#ifdef GL_ES_VERSION_3_0
	#undef GL_ES_VERSION_3_0
	#include<GLES3/gl3.h>
#elif defined(GL_ES_VERSION_2_0)
	#undef GL_ES_VERSION_2_0
	#include<GLES2/gl2.h>
#else
	#include<GL/gl.h>
#include <assert.h>

#endif

void sbGenBuffers(int n, unsigned int* buffers){
	spbGLGenBuffersARB(n, buffers);
}

int sbCreateVBO(unsigned int target, unsigned int size, unsigned int mode){
	unsigned int vbo;
	sbGenBuffers(1, &vbo);
	spbGLBindBufferARB(target, vbo);
	spbGLBufferDataARB(target, size, NULL, mode);
	return vbo;
}

void sbSetBufferSize(unsigned int target, unsigned int buffer, unsigned int size, unsigned int mode){
	spbGLBindBufferARB(target, buffer);
	spbGLBufferDataARB(target, size, NULL, mode);
}

void sbGenVertexArrays(int n, unsigned int* arg){
	spbGLGenVertexArrays((GLsizei)n, arg);
}

int sbDestroyBuffer(unsigned int buffer){
	spbGLDeleteBuffersARB(1, &buffer);
	return spbGLIsBufferARB(buffer) != GL_FALSE;
}

void* sbMapBufferWOnly(unsigned int target, unsigned int buffer){
	spbGLBindBufferARB(target, buffer);
	void* data = spbGLMapBufferARB(target, GL_WRITE_ONLY_ARB);
	assert(data);
	return data;
}

int sbUnmapBuffer(unsigned int target){
	GLboolean status = spbGLUnmapBufferARB(target);
	assert(status == GL_TRUE);
	return status;
}
