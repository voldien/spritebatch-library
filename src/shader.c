#include"shader.h"
#include"glfuncs.h"
#include"shaders.h"
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>

#ifdef GL_ES_VERSION_3_0
	#undef GL_ES_VERSION_3_0
	#include<GLES3/gl3.h>
#elif defined(GL_ES_VERSION_2_0)
	#undef GL_ES_VERSION_2_0
	#include<GLES2/gl2.h>
#else
	#include<GL/gl.h>

#endif

unsigned int sbGetGLSLVersion(void) {

	unsigned int version;
	char glstring[128] = {0};
	char *wspac;

	/*	Extract version number.	*/
	strcpy(glstring, (const char *) glGetString(GL_SHADING_LANGUAGE_VERSION));
	wspac = strstr(glstring, " ");
	if (wspac) {
		*wspac = '\0';
	}
	if (strstr(glstring, ".") != NULL) {
		unsigned int major = (unsigned int) (glstring[0] - '0') * 100;
		unsigned int minor = (unsigned int) (glstring[2] - '0') * 10;

		return major + minor;
	} else {
		version = (unsigned int) strtof(glstring, NULL) * 100;
		return version;
	}
}

SBShader prevshader = {0};
SBShader *preshader = &prevshader;

static void sbGetCurrentShader(SBShader *shader) {
	glGetIntegerv(GL_CURRENT_PROGRAM, &shader->program);
}

void sbBindShader(const SBShader *shader) {
	if (shader == NULL)
		spbGLUseProgram(0);
	else
		spbGLUseProgram(shader->program);
}

int sbGetShaderLocation(const SBShader *shader, const char *name){
	return spbGLGetUniformLocation(shader->program, name);
}


void setShaderUniform1iv(SBShader *SB_RESTRICT shader, int location, int count,
                         const int *SB_RESTRICT pvalue) {
	if (spbGLProgramUniform1iv) {
		spbGLProgramUniform1iv(shader->program, location, count, pvalue);
	} else {
		sbGetCurrentShader(preshader);
		sbBindShader(shader);
		spbGLUniform1ivARB(location, count, pvalue);
		sbBindShader(preshader);
	}
}


void setShaderUniform1fv(SBShader *SB_RESTRICT shader, int location, int count,
                         const float *SB_RESTRICT pvalue) {
	if (spbGLProgramUniform1fv) {
		spbGLProgramUniform1fv(shader->program, location, count, pvalue);
	} else {
		sbGetCurrentShader(preshader);
		sbBindShader(shader);
		spbGLUniform1fvARB(location, count, pvalue);
		sbBindShader(preshader);
	}
}

void setShaderUniformMatrix3x3fv(SBShader *SB_RESTRICT shader, int location, int count,
                                 const float *SB_RESTRICT pvalue) {
	if (spbGLProgramUniformMatrix3fv) {
		spbGLProgramUniformMatrix3fv(shader->program, location, count, GL_FALSE, (const GLfloat *) pvalue);
	} else {
		sbGetCurrentShader(preshader);
		sbBindShader(shader);
		spbGLUniformMatrix3fvARB(location, count, GL_FALSE, (const GLfloat *) pvalue);
		sbBindShader(preshader);
	}
}

int sbCreateShaderv(SBShader* shader, const char* cvertexSource,
		const char* cfragmentSource, const char* cgeometrySource) {

	int error;
	int ver, fra, geo;

	assert(shader);

	/*	Create program	.*/
	shader->program = spbGLCreateProgram();
	if(shader->program < 0)
		return 0;

	/*	*/
	ver = fra = geo = 0;
	if(cvertexSource){
		ver = sbCompileShaderSourcev(cvertexSource, GL_VERTEX_SHADER_ARB);
		spbGLAttachShader(shader->program, ver);
	}
	if(cfragmentSource){
		fra = sbCompileShaderSourcev(cfragmentSource, GL_FRAGMENT_SHADER_ARB);
		spbGLAttachShader(shader->program, fra);
	}
#if defined(__gl_h_)
	if(cgeometrySource){
		geo = sbCompileShaderSourcev(cgeometrySource, GL_GEOMETRY_SHADER_ARB);
		spbGLAttachShader(shader->program, geo);
	}
#endif

	/*	*/
	spbGLLinkProgram(shader->program);

#if defined(__gl_h_)
	error = sbShaderCompileLog(shader->program, GL_PROGRAM);
	/*	if shader failed. clean up resources.	*/
	if(!error){
		sbDeleteShaderProgram(shader);
		return error;
	}

#endif

	/*	*/
	spbGLValidateProgram(shader->program);

	/*	detach shader object and release their resources.	*/
	if(spbGLIsShader(ver)){
		spbGLDetachShader(shader->program, ver);
		spbGLDeleteShader(ver);
	}
	if(spbGLIsShader(ver)){
		spbGLDetachShader(shader->program, fra);
		spbGLDeleteShader(fra);
	}
	if(spbGLIsShader(ver)){
		spbGLDetachShader(shader->program, geo);
		spbGLDeleteShader(geo);
	}

	return 1;
}

int sbIsShader(const SBShader* shader){
	return spbGLIsProgramARB(shader->program) == GL_TRUE;
}

int sbDeleteShaderProgram(SBShader* shader){
	int error;

	spbGLDeleteProgram(shader->program);

	/*	Check if program is valid.  */
	return spbGLIsProgramARB(shader->program) == GL_FALSE;
}

int sbCompileShaderSourcev(const char* source, unsigned int flag){

	GLuint shader;
	int status;
	GLint cstatus;
	GLint value;

	const char* strcore;
	char glversion[64];
	const char* sources[3];
	const int numsources = sizeof(sources) / sizeof(sources[0]);

	/*	Check if core.	*/
	glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &value);
	strcore = (value == GL_CONTEXT_CORE_PROFILE_BIT) ? "core" : "";

	/*	Create version string.	*/
	memset(glversion, 0, sizeof(glversion));
	sprintf(glversion, "#version %d %s\n", sbGetGLSLVersion(), strcore);

	/*	*/
	sources[0] = glversion;
	sources[1] = gc_shader_def;
	sources[2] = source;

	printf(glversion);

	/*	Compile*/
	shader = spbGLCreateShader(flag);
	spbGLShaderSourceARB(shader, numsources, sources, NULL);
	spbGLCompileShaderARB(shader);

	/*	*/
	/*	Check for compiling errors.	*/
	spbGLGetShaderiv(shader, GL_COMPILE_STATUS, &cstatus);
	if (cstatus == GL_FALSE) {
		if(flag == GL_VERTEX_SHADER_ARB)
			fprintf(stderr, "vertex\n");
		if(flag == GL_FRAGMENT_SHADER_ARB)
			fprintf(stderr, "fragment\n");
		GLchar infolog[2048];
		spbGLGetShaderInfoLog(shader, sizeof(infolog), NULL, infolog);
		fprintf(stderr, "%s\n", infolog);
	}

	return shader;
}

int sbShaderCompileLog(unsigned int program, unsigned int shaderflag) {
	int lStatus,validate;

	/* Check if shader	*/
	if(spbGLIsProgram(program)){

		char log[512];

		/*	*/
		spbGLGetProgramiv(program, GL_LINK_STATUS, &lStatus);
		spbGLGetProgramiv(program, GL_VALIDATE_STATUS, &validate);

		/*	*/
		if(lStatus == GL_TRUE)
			return 1;

		/*	*/
		if(lStatus == GL_FALSE){
			spbGLGetProgramInfoLog(program, sizeof(log), NULL, log);
			printf("\x1B[31m""Failed to compile shader\n%s\n", log);
		}

		return lStatus;
	}else
		return 0;
}

