#include"base.h"
#include "base.h"

#include<GL/gl.h>

PFNGLDEBUGMESSAGECALLBACKARBPROC glDebugMessageCallbackARB = NULL;
PFNGLDEBUGMESSAGECALLBACKAMDPROC glDebugMessageCallbackAMD = NULL;

SDL_Window *createWindow(void) {

	SDL_Window *window = NULL;
	SDL_GLContext *glc = NULL;
	SDL_DisplayMode mode;
	int fvalue;
	char title[128];

	/*	Create title for window.	*/
	sprintf(title, "SpriteBatch Test - %s", "");
	SDL_InitSubSystem(SDL_INIT_VIDEO);

	/*	Create window.	*/
	SDL_GetCurrentDisplayMode(0, &mode);
	window = SDL_CreateWindow(title,
	                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                          mode.w / 2, mode.h / 2,
	                          SDL_WINDOW_OPENGL | /*	SDL_WINDOW_BORDERLESS |	*/
	                          SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "Failed to create SDL window, %s.\n", SDL_GetError());
		return NULL;
	}
	SDL_ShowWindow(window);

	/*	Enable debug in debug mode.	*/
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
	                    SDL_GL_CONTEXT_DEBUG_FLAG);

	/*	Default framebuffer settings.	*/
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, SDL_TRUE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE);
	SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, SDL_FALSE);

	/*  Disable multi sampling.  */
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, SDL_FALSE);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
	

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	/*	Create OpenGL Context.*/
	glc = SDL_GL_CreateContext(window);
	if (glc == NULL) {
		fprintf(stderr, "Failed to create OpenGL context, %s.\n", SDL_GetError());
		return NULL;
	}

	/*	Make window current with OpenGL context.	*/
	if (SDL_GL_MakeCurrent(window, glc) != 0) {
		fprintf(stderr, "Failed to make current, %s.\n", SDL_GetError());
		return NULL;
	}

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	/*	Enable debug.	*/
	spEnableDebug();

	/*	Setup the rendering pipeline.	*/
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDisable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_FRONT_AND_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DITHER);

	/*  Enable v-sync.  */
	SDL_GL_SetSwapInterval(SDL_TRUE);

	return window;
}

void init(void) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		exit(EXIT_FAILURE);
}

void deinit(void) {
	SDL_Quit();
}


void callback_debug_gl(GLenum source, GLenum type, GLuint id, GLenum severity,
                       GLsizei length, const GLchar *message, GLvoid *userParam) {
	char *sourceString;
	char *typeString;
	char *severityString;

	switch (source) {
		case GL_DEBUG_CATEGORY_API_ERROR_AMD:
		case GL_DEBUG_SOURCE_API: {
			sourceString = "API";
			break;
		}
		case GL_DEBUG_CATEGORY_APPLICATION_AMD:
		case GL_DEBUG_SOURCE_APPLICATION: {
			sourceString = "Application";
			break;
		}
		case GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD:
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: {
			sourceString = "Window System";
			break;
		}
		case GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD:
		case GL_DEBUG_SOURCE_SHADER_COMPILER: {
			sourceString = "Shader Compiler";
			break;
		}
		case GL_DEBUG_SOURCE_THIRD_PARTY: {
			sourceString = "Third Party";
			break;
		}
		case GL_DEBUG_CATEGORY_OTHER_AMD:
		case GL_DEBUG_SOURCE_OTHER: {
			sourceString = "Other";
			break;
		}
		default: {
			sourceString = "Unknown";
			break;
		}
	}/**/
	printf(sourceString);

	switch (type) {
		case GL_DEBUG_TYPE_ERROR: {
			typeString = "Error";
			break;
		}
		case GL_DEBUG_CATEGORY_DEPRECATION_AMD:
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: {
			typeString = "Deprecated Behavior";
			break;
		}
		case GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD:
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: {
			typeString = "Undefined Behavior";
			break;
		}
		case GL_DEBUG_TYPE_PORTABILITY_ARB: {
			typeString = "Portability";
			break;
		}
		case GL_DEBUG_CATEGORY_PERFORMANCE_AMD:
		case GL_DEBUG_TYPE_PERFORMANCE: {
			typeString = "Performance";
			break;
		}
		case GL_DEBUG_CATEGORY_OTHER_AMD:
		case GL_DEBUG_TYPE_OTHER: {
			typeString = "Other";
			break;
		}
		default: {
			typeString = "Unknown";
			break;
		}
	}/**/
	printf(typeString);

	switch (severity) {
		case GL_DEBUG_SEVERITY_HIGH: {
			severityString = "High";
			break;
		}
		case GL_DEBUG_SEVERITY_MEDIUM: {
			severityString = "Medium";
			break;
		}
		case GL_DEBUG_SEVERITY_LOW: {
			severityString = "Low";
			break;
		}
		default: {
			severityString = "Unknown";
			break;
		}
	}/**/
	printf(severityString);

	printf(message);
	printf(" id: %d,\n", id);
}

void spEnableDebug(void) {

	glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKARBPROC) SDL_GL_GetProcAddress("glDebugMessageCallbackARB");
	glDebugMessageCallbackAMD = (PFNGLDEBUGMESSAGECALLBACKAMDPROC) SDL_GL_GetProcAddress("glDebugMessageCallbackAMD");

	/*	Check if debug callback is supported.	*/
	if (!glDebugMessageCallbackAMD && !glDebugMessageCallbackARB) {
		fprintf(stderr, "Failed loading OpenGL callback functions.\n");
		return;
	}

	/*	Set Debug message callback.	*/
	if (glDebugMessageCallbackARB) {
		glDebugMessageCallbackARB((GLDEBUGPROCARB) callback_debug_gl, NULL);
	}
	if (glDebugMessageCallbackAMD) {
		glDebugMessageCallbackAMD((GLDEBUGPROCARB) callback_debug_gl, NULL);
	}

	/*	Enable debug output.	*/
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
}