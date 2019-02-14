#include"sprite.h"
#include"matrix.h"
#include"geometry.h"
#include"glfuncs.h"
#include"shaders.h"
#include<string.h>
#include<malloc.h>
#include<assert.h>

#ifdef GL_ES_VERSION_3_0
	#include<GLES3/gl3.h>
#elif defined(GL_ES_VERSION_2_0)
	#undef GL_ES_VERSION_2_0
	#include<GLES2/gl2.h>
#else
#endif

const char *sbGetVersion(void) {
	return SPB_VERSION;
}

SBSpriteBatch *sbCreateSpriteBatch(SBSpriteBatch *spritebatch) {
	int x;
	int texture[512];
	const int numSprites = 4096;
	GLfloat mpointsize;
	const size_t nrTextures = 16;

	/*	Constants.	*/
	const uint32_t vertex_offset = 0;
	const uint32_t angle_offset = 12;
	const uint32_t rect_offset = 12 + 4;
	const uint32_t tex_offset = 12 + 20;
	const uint32_t scale_offset = 12 + 24;
	const uint32_t color_offset = 12 + 28;

	/*	Load OpenGL functions.	*/
	if (!sb_internal_load_gl_func())
		return NULL;

	/*	Get	max combined texture units.	*/
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB,
	              &spritebatch->numMaxTextures);
	spritebatch->textures = (int *) malloc(sizeof(unsigned int) * spritebatch->numMaxTextures);
	memset(spritebatch->textures, 0, sizeof(unsigned int) * spritebatch->numMaxTextures);
	spritebatch->numTexture = 0;
	assert(spritebatch->textures);

	/*	Sprites.    */
	spritebatch->scale = 1.0f;
	spritebatch->sprite = NULL;
	sbSpriteBatchAllocateSprite(spritebatch, numSprites);

	/*	*/
	sbGenVertexArrays(1, &spritebatch->vao);
	spbGLBindVertexArray(spritebatch->vao);

	/*	*/
	spbGLBindBufferARB(GL_ARRAY_BUFFER_ARB, spritebatch->vbo);
	spbGLEnableVertexAttribArrayARB(0);
	spbGLEnableVertexAttribArrayARB(1);
	spbGLEnableVertexAttribArrayARB(2);
	spbGLEnableVertexAttribArrayARB(3);
	spbGLEnableVertexAttribArrayARB(4);
	spbGLEnableVertexAttribArrayARB(5);
	spbGLVertexAttribPointerARB(0, 3, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
	                            (const void *) vertex_offset);
	spbGLVertexAttribPointerARB(1, 1, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
	                            (const void *) angle_offset);
	spbGLVertexAttribPointerARB(2, 4, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
	                            (const void *) rect_offset);
	spbGLVertexAttribPointerARB(3, 1, GL_INT, GL_FALSE, sizeof(SBSprite),
	                            (const void *) tex_offset);
	spbGLVertexAttribPointerARB(4, 1, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
	                            (const void *) scale_offset);
	spbGLVertexAttribPointerARB(5, 4, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
	                            (const void *) color_offset);

	spbGLBindVertexArray(0);

	/*	Load sprite shader.	*/
	if (!sbCreateShaderv(&spritebatch->spriteShader, gc_shader_spriteV,
	                     gc_shader_spriteF, NULL)) {
		/*	failure	*/
		sbReleaseSpriteBatch(spritebatch);
		return NULL;
	}
	/*  Load sprite label shader.   */
	if (!sbCreateShaderv(&spritebatch->fontShader, gc_shader_labelV,
	                     gc_shader_labelF, NULL)) {
		/*	failure	*/
		sbReleaseSpriteBatch(spritebatch);
		return NULL;
	}

	/*	Cache sprite uniform location.	*/
	spritebatch->uniform.locationViewMatrix = sbGetShaderLocation(
			&spritebatch->spriteShader, "gmat");
	spritebatch->uniform.locationScale = sbGetShaderLocation(
			&spritebatch->spriteShader, "gscale");
	spritebatch->uniform.locationTexture = sbGetShaderLocation(
			&spritebatch->spriteShader, "textures");

	/*	Validate cache uniform locations.   */
	if (spritebatch->uniform.locationScale == -1 ||
	    spritebatch->uniform.locationTexture == -1 ||
	    spritebatch->uniform.locationViewMatrix == -1) {
		return NULL;
	}

	/*	Init shader.    */
	spbGLUseProgram(spritebatch->spriteShader.program);
	spbGLUniform1fvARB(spritebatch->uniform.locationScale, 1, &spritebatch->scale);

	/*	Set texture index mapping.	*/
	for (x = 0; x < spritebatch->numMaxTextures; x++)
		texture[x] = x;

	/*  TODO fix constant size. */
	spbGLUniform1ivARB(spritebatch->uniform.locationTexture, nrTextures,
	                   (const GLint *) &texture[0]);

	spbGLUseProgram(0);

	/*	Enable hardware sprite feature. */
#if !defined(GL_ES_VERSION_2_0)
	glEnable(GL_POINT_SPRITE_ARB);
	glEnable(GL_PROGRAM_POINT_SIZE_ARB);
	spbGLPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
	spbGLPointParameterf(GL_POINT_SIZE_MIN, 1.0f);
	glGetFloatv(GL_POINT_SIZE_MAX, &mpointsize);
	spbGLPointParameterf(GL_POINT_SIZE_MAX, mpointsize);
	//spbGLPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE_ARB, 60.0f);
	spbGLPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, 1.0f);
	//GL_POINT_DISTANCE_ATTENUATION_ARB
#endif

	/*	Initialize the batch	*/
	sbBeginSpriteBatch(spritebatch, NULL, 1.0f, 0.0f);
	sbEndSpriteBatch(spritebatch);

	return spritebatch;
}

int sbReleaseSpriteBatch(SBSpriteBatch *spritebatch) {
	int status;

	/*  Delete buffers. */
	if (spbGLIsBufferARB(spritebatch->vbo) == GL_TRUE)
		sbDestroyBuffer(spritebatch->vbo);
	if (spGLIsVertexArray(spritebatch->vao) == GL_TRUE)
		spGLDeleteVertexArrays(1, &spritebatch->vao);

	/*	Delete shaders. */
	if (sbIsShader(&spritebatch->spriteShader))
		sbDeleteShaderProgram(&spritebatch->spriteShader);
	if (sbIsShader(&spritebatch->fontShader))
		sbDeleteShaderProgram(&spritebatch->fontShader);

	/*	Release sprite buffer.	*/
	free(spritebatch->sprite);
	spritebatch->sprite = NULL;

	/*  Release texture mapper. */
	free(spritebatch->textures);
	spritebatch->textures = NULL;

	/*	Clear memory.	*/
	status = !spbGLIsBufferARB(spritebatch->vbo);
	memset(spritebatch, 0, sizeof(*spritebatch));
	return status;
}

void sbSpriteBatchAllocateSprite(SBSpriteBatch *spritebatch, unsigned int num) {

	/*	Check for error.	*/
	if (spritebatch == NULL || num <= 0)
		return;

	/*	Flush current buffer if exists.	*/
	if (spbGLIsBufferARB(spritebatch->vbo) && spritebatch->sprite)
		sbFlushSpriteBatch(spritebatch);

	/*	Check if buffer has been created.	*/
	if (spbGLIsBufferARB(spritebatch->vbo) == 0) {
		/*  Create vertex buffer.   */
		sbGenBuffers(1, &spritebatch->vbo);
		spbGLBindBufferARB(GL_ARRAY_BUFFER_ARB, spritebatch->vbo);
	}

	/*	Allocate local sprite buffer.	*/
	spritebatch->sprite = realloc(spritebatch->sprite, num * sizeof(SBSprite));
	spritebatch->num = num;
	/*  Allocate sprite buffer on the graphic device.   */
	sbSetBufferSize(GL_ARRAY_BUFFER_ARB, spritebatch->vbo,
	                spritebatch->num * sizeof(SBSprite), GL_DYNAMIC_DRAW);
	spbGLBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
}

void sbBeginSpriteBatch(SBSpriteBatch *SB_RESTRICT spriteBatch,
                        const float *SB_RESTRICT camerapos, float scale, float rotation) {
	int rect[4];

	/*  Reset sprite and texture counter.   */
	spriteBatch->numDraw = 0;
	spriteBatch->numlabelDraw = 0;

	/*	Get current size of the viewport.	*/
	glGetIntegerv(GL_VIEWPORT, rect);
	spriteBatch->width = (unsigned int)(rect[2] - rect[0]);
	spriteBatch->height = (unsigned int)(rect[3] - rect[1]);
	spriteBatch->scale = scale;
	spriteBatch->rotation = rotation;

	/*	Camera view position.	*/
	if (camerapos) {
		spriteBatch->cameraPos[0] = -camerapos[0];
		spriteBatch->cameraPos[1] = camerapos[1];
	} else {
		spriteBatch->cameraPos[0] = 0;
		spriteBatch->cameraPos[1] = 0;
	}

	/*	Clean texture map buffer.	*/
	const size_t size = sizeof(unsigned int) * spriteBatch->numTexture;
	memset(spriteBatch->textures, 0, size);
	spriteBatch->numTexture = 0;
}

void sbEndSpriteBatch(SBSpriteBatch *spriteBatch) {

	/*  Flush sprite buffers to GPU Memory. */
	sbFlushSpriteBatch(spriteBatch);

	/*	Draw sprites.	*/
	sbDisplaySprite(spriteBatch);
}

static void updateTextureTable(SBSpriteBatch *SB_RESTRICT spriteBatch, const SBTexture *SB_RESTRICT texture) {
	int i;

	/*  Update texture index table. */
	for (i = 0; i < spriteBatch->numMaxTextures; i++) {
		if (spriteBatch->textures[i] == texture->texture)
			break;
		else {
			if (spriteBatch->textures[i] == NULL) {
				spriteBatch->textures[i] = texture->texture;
				spriteBatch->numTexture++;
				break;
			}
		}
	}
}

void sbDrawSprite(SBSpriteBatch *spriteBatch, SBTexture *texture,
                  const float *position, const float *rect, const float *color,
                  float scale, float angle, float depth) {

	sbAddSprite(spriteBatch, texture, position, rect, color, scale, angle, depth);

	if (spriteBatch->numDraw >= spriteBatch->num
	    || spriteBatch->numTexture >= spriteBatch->numMaxTextures) {

		/*  Flush if buffer is full.    */
		sbEndSpriteBatch(spriteBatch);

		const float cameraPos[2] = {-spriteBatch->cameraPos[0], spriteBatch->cameraPos[1]};
		sbBeginSpriteBatch(spriteBatch, cameraPos, spriteBatch->scale, spriteBatch->rotation);
	}
}


void sbDrawSpriteNormalize(SBSpriteBatch *spritebatch, SBTexture *texture, const float *position,
                           const float *rect, const float *color, float scale, float angle, float depth) {

	sbAddSpriteNormalized(spritebatch, texture, position, rect, color, scale, angle, depth);

	if (spritebatch->numDraw >= spritebatch->num
	    || spritebatch->numTexture >= spritebatch->numMaxTextures) {
		/*  Flush if buffer is full.    */
		sbEndSpriteBatch(spritebatch);

		const float cameraPos[2] = {-spritebatch->cameraPos[0], spritebatch->cameraPos[1]};
		sbBeginSpriteBatch(spritebatch, cameraPos, spritebatch->scale, spritebatch->rotation);
	}
}

int sbDrawSpriteLabel(SBSpriteBatch *spritebatch, const char *label, SBFont *font, float *position, float *rect,
                      float *color, float scale,
                      float angle, float depth) {
	int i;
	const size_t len = strlen(label);
	float xOffset = 0;
	float yOffset = 0;

	/*  Iterate through each character. */
	for (i = 0; i < len; i++) {
		const int charIndex = label[i];
		const float fontRect[4] = {font->tex_x1[charIndex], font->tex_x1[charIndex], font->tex_y1[charIndex],
		                           font->tex_y2[charIndex]};
		const float charPos[] = {position[0] + xOffset, position[1] + yOffset};

		/*  Draw.   */
		sbDrawSprite(spritebatch, &font->texture, charPos, fontRect, color, scale, angle, depth);

		/*  Update offset.  */
		xOffset += font->width[charIndex] + font->offset_x[charIndex];
		yOffset += font->height[charIndex] + font->offset_x[charIndex];
	}

	return 0;
}

int sbDrawSpriteLabelNormalized(SBSpriteBatch *spritebatch, const char *label,
                                SBFont *font, float *position, float *rect, float *color, float scale,
                                float angle, float depth) {
	int i;
	const size_t len = strlen(label);
	/*  Iterate through each character. */
	for (i = 0; i < len; i++) {
		const float x = position[0] * (float) spritebatch->width;
		const float y = position[1] * (float) spritebatch->height;

		const float normalizePos[2] = {x, y};
		sbDrawSpriteLabel(spritebatch, label, font, normalizePos, rect, color, scale, angle, depth);
	}
	return 1;
}

int sbAddSpriteNormalized(SBSpriteBatch *spritebatch, SBTexture *texture,
                          const float *position, const float *rect, const float *color,
                          float scale, float angle, float depth) {

	int index;
	unsigned int numDraw;
	numDraw = spritebatch->numDraw;
	SBSprite *sprite = &spritebatch->sprite[numDraw];

	if (spritebatch->numDraw == spritebatch->num)
		return 0;

	/*	Screen coordinate. [0,0] - [w,h], top left -> bottom right. to  normalized coordinate system.   */
	sprite->pos[0] = 2.0f * position[0] - 1.0f + (((float) texture->width) / ((float) spritebatch->width));
	sprite->pos[1] = 2.0f * position[1] - 1.0f - (((float) texture->height) / ((float) spritebatch->height));
	sprite->pos[2] = depth;

	/*  Compute view rectangle. */
	if (rect) {
		sprite->rect[0] = rect[0];
		sprite->rect[1] = rect[1];
		sprite->rect[2] = rect[2];
		sprite->rect[3] = rect[3];
	} else {
		sprite->rect[0] = 0.0f;
		sprite->rect[1] = 0.0f;
		sprite->rect[2] = 1.0f;
		sprite->rect[3] = 1.0f;
	}
	/*  Compute diffuse color.  */
	if (color) {
		sprite->color[0] = color[0];
		sprite->color[1] = color[1];
		sprite->color[2] = color[2];
		sprite->color[3] = color[3];
	} else {
		sprite->color[0] = 1.0f;
		sprite->color[1] = 1.0f;
		sprite->color[2] = 1.0f;
		sprite->color[3] = 1.0f;
	}
	/*  Assign angle and scale. */
	sprite->angle = angle;
	sprite->scale = scale;

	/*  Update texture index table. */
	index = updateTextureTable(spritebatch, texture);

	/*	sprite texture index.	*/
	sprite->texture = (GLint) index;

	/*	Update sprite count.    */
	spritebatch->numDraw++;

	return 1;
}

int sbAddSprite(SBSpriteBatch *spriteBatch, SBTexture *texture, const float *position,
                const float *rect, const float *color, float scale, float angle,
                float depth) {

	/*  Normalize coordinate.    */
	const float x = position[0] / (float) spriteBatch->width;
	const float y = position[1] / (float) spriteBatch->height;

	/*  */
	const float normalizePos[2] = {x, y};
	sbAddSpriteNormalized(spriteBatch, texture, (const float *) normalizePos, rect, color, scale, angle, depth);

	return 1;
}

void sbRemoveSprite(SBSpriteBatch *spritebatch, int index) {

	/*  Check if index is valid.    */
	if (index < spritebatch->numDraw) {

		/*	Set last element in the index that going to be removed.*/
		memcpy(&spritebatch->sprite[index],
		       &spritebatch->sprite[spritebatch->numDraw - 1],
		       sizeof(SBSprite));
		spritebatch->numDraw--;
	}
}

int sbFlushSpriteBatch(SBSpriteBatch *spritebatch) {

	/*  */
	if (spritebatch->numDraw > 0) {
		/*	DMA/Transfer sprite buffer to Graphic Memory.  */

		void *pbuf = sbMapBufferWOnly(GL_ARRAY_BUFFER_ARB, spritebatch->vbo);
		memcpy(pbuf, (const void *) spritebatch->sprite, spritebatch->numDraw * sizeof(SBSprite));
		return sbUnmapBuffer(GL_ARRAY_BUFFER_ARB);
	}
	return 1;
}

void sbDisplaySprite(SBSpriteBatch *spriteBatch) {

	unsigned int i;
	float matscale[3][3];
	float rotmat[3][3];
	float tranmat[3][3];
	float TR[3][3];

	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);

	/*  Only continue if elements needs to be drawn.    */
	if (spriteBatch->numDraw <= 0 && spriteBatch->numlabelDraw <= 0)
		return;

	/*	Load textures.  */
	if (!spbGLBindTextures) {
		for (i = 0; i < spriteBatch->numTexture; i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, spriteBatch->textures[i]);
		}
	} else {
		/*  Single gl call for binding all textures.    */
		spbGLBindTextures(0, spriteBatch->numTexture, spriteBatch->textures);
	}

	/*	Load shader.    */
	sbBindShader(&spriteBatch->spriteShader);

	/*	Update view matrix and global scale*/
	sbMatrix3x3Translation(tranmat, spriteBatch->cameraPos);
	sbMatrix3x3Scale(matscale, spriteBatch->scale);
	sbMatrix3x3Rotation(rotmat, spriteBatch->rotation);
	sbMatrix3x3MultiMatrix3x3(tranmat, rotmat, TR);
	sbMatrix3x3MultiMatrix3x3(matscale, TR, spriteBatch->viewmatrix);

	/*	Update uniform variables.   */
	setShaderUniform1fv(&spriteBatch->spriteShader, spriteBatch->uniform.locationScale, 1, &spriteBatch->scale);
	setShaderUniformMatrix3x3fv(&spriteBatch->spriteShader, spriteBatch->uniform.locationViewMatrix, 1, &spriteBatch->viewmatrix[0][0]);

	/*	Draw sprites.	*/
	spbGLBindVertexArray(spriteBatch->vao);
	glDrawArrays(GL_POINTS, 0, spriteBatch->numDraw);
	/*	labels.	*/
//	spbGLUseProgram(spriteBatch->fontShader.program);
//	glDrawArrays(GL_POINTS, (spriteBatch->num -spriteBatch->numlabelDraw) , spriteBatch->numlabelDraw);
	spbGLBindVertexArray(0);


	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
}
