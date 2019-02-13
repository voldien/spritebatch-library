#include"texture.h"
#include"glfuncs.h"
#include<assert.h>

#ifdef SPRITE_BATCH_EGL
#include<EGL/egl.h>
#include<EGL/eglext.h>
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


SBTexture* sbCreateTexture(SBTexture* SB_RESTRICT texture, unsigned int target, int level,
        int internalFormat, int width, int height, int border,
        unsigned int format, unsigned int type, const void * SB_RESTRICT pixels) {

	assert(texture);

	texture->target = target;
	texture->internalformat = (unsigned int) internalFormat;
	texture->width = (unsigned int) width;
	texture->height = (unsigned int) height;
	texture->internalformat = format;
	texture->type = type;

	/*	Generate texture object.	*/
	glGenTextures(1, &texture->texture);
	glBindTexture(target, texture->texture);
	glPixelStorei(GL_PACK_ALIGNMENT, 4);

	/*	Create texture.	*/
	switch (target) {
		case GL_TEXTURE_2D:
			glTexImage2D(target, level, internalFormat, width, height, border, format, type, pixels);
			break;
#ifndef GL_ES_VERSION_2_0
		case GL_TEXTURE_1D:
			glTexImage1D(target, level, internalFormat, width, border, format, type, pixels);
			break;
		case GL_TEXTURE_2D_ARRAY:
			glTexStorage3D(target, level, texture->internalformat, width, height, texture->layer);
			break;
		case GL_TEXTURE_3D:
			break;
#endif
		default:
			break;
	}

	/*	Texture sampler modes.	*/
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_REPEAT);

	glBindTexture(target, 0);
	if (sbIsTexture(texture) != GL_TRUE)
		return NULL;
	else
		return texture;
}

void sbBindTexture(SBTexture* SB_RESTRICT texture, int index){
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
}

void sbBindTextures(int* SB_RESTRICT textures, int index, int num){
	int i;
	/*	Load textures.  */
	if (!spbGLBindTextures) {
		for (i = 0; i < num; i++) {
			/*	TODO resolve.   */
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]);
		}
	} else {
		/*  Single gl call for binding all textures.    */
		spbGLBindTextures(0, num, textures);
	}
}

void sbDeleteTexture(SBTexture* texture){
	if(sbIsTexture(texture))
		glDeleteTextures(1, &texture->texture);
}

int sbIsTexture(const SBTexture* texture){
	return glIsTexture(texture->texture) == GL_TRUE;
}

int sbGetNumTextureUnits(int* units){
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB,
	              units);
}
