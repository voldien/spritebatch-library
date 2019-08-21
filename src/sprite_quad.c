#include"sprite.h"


#include"sprite.h"
#include"matrix.h"
#include"geometry.h"
#include"glfuncs.h"
#include"shaders.h"
#include<string.h>
#include<malloc.h>
#include<assert.h>
#include<math.h>

typedef struct sb_vertex_t {
	float pos[3];
	float uv[2];
	float color[4];
	int tex;
} SBVertex; //__attribute__ ((__packed__))


typedef struct sb_quad_sprite_t {
	SBVertex vertex[6];
} SBQuadSprite; //__attribute__ ((__packed__))

void sbDrawArray(unsigned int vao, int i, unsigned int draw);

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
	sbGetNumTextureUnits(&spritebatch->numMaxTextures);

	/*  Allocate textures.  */
	spritebatch->textures = (unsigned int *) malloc(sizeof(unsigned int) * spritebatch->numMaxTextures);
	memset(spritebatch->textures, 0, sizeof(unsigned int) * spritebatch->numMaxTextures);
	spritebatch->numTexture = 0;
	assert(spritebatch->textures);

	/*  Buffer allocation.  */
	spritebatch->nthBuffer = 0;
	spritebatch->nbuffers = sizeof(spritebatch->buffers) / sizeof(spritebatch->buffers[0]);
	memset(spritebatch->buffers, 0, spritebatch->nbuffers * sizeof(spritebatch->buffers[0]));

	/*	Sprites.    */
	spritebatch->scale = 1.0f;
	spritebatch->sprite = NULL;
	sbSpriteBatchAllocateSprite(spritebatch, numSprites);

	/*	Create vertex buffer.   */
	sbGenVertexArrays(1, &spritebatch->vao);
	spbGLBindVertexArray(spritebatch->vao);

	/*	TODO resolve.   */
	//spbGLBindBufferARB(GL_ARRAY_BUFFER_ARB, spritebatch->vbo);
	spbGLBindBufferARB(GL_ARRAY_BUFFER_ARB, spritebatch->buffers[0]);
	spbGLEnableVertexAttribArrayARB(0);
	spbGLEnableVertexAttribArrayARB(1);
	spbGLEnableVertexAttribArrayARB(2);
	spbGLEnableVertexAttribArrayARB(3);
	spbGLVertexAttribPointerARB(0, 3, GL_FLOAT, GL_FALSE, sizeof(SBVertex),
	                            (const void *) 0);
	spbGLVertexAttribPointerARB(1, 2, GL_FLOAT, GL_FALSE, sizeof(SBVertex),
	                            (const void *) 12);
	spbGLVertexAttribPointerARB(2, 4, GL_FLOAT, GL_FALSE, sizeof(SBVertex),
	                            (const void *) 20);
	spbGLVertexAttribPointerARB(3, 1, GL_INT, GL_FALSE, sizeof(SBVertex),
	                            (const void *) 36);

	spbGLBindVertexArray(0);

	if (!sbEnableRotation(spritebatch, 0)) {
		sbReleaseSpriteBatch(spritebatch);
		return NULL;
	}

	/*	Cache sprite uniform location.	*/
	spritebatch->uniform.locationViewMatrix = sbGetShaderLocation(
			&spritebatch->spriteShader, "gmat");
	spritebatch->uniform.locationTexture = sbGetShaderLocation(
			&spritebatch->spriteShader, "textures");

	/*	Validate cache uniform locations.   */
	if (spritebatch->uniform.locationTexture == -1 ||
	    spritebatch->uniform.locationViewMatrix == -1) {
		return NULL;
	}

	/*	Init shader.    */
	setShaderUniform1fv(&spritebatch->spriteShader, spritebatch->uniform.locationScale, 1, &spritebatch->scale);

	/*	Set texture index mapping.	*/
	for (x = 0; x < spritebatch->numMaxTextures; x++)
		texture[x] = x;

	/*  TODO fix constant size. */
	setShaderUniform1iv(&spritebatch->spriteShader, spritebatch->uniform.locationTexture, nrTextures,
	                    (const GLint *) &texture[0]);

	sbBindShader(NULL);

	/*	Initialize the batch	*/
	sbBeginSpriteBatch(spritebatch, NULL, 1.0f, 0.0f);
	sbEndSpriteBatch(spritebatch);

	return spritebatch;
}

int sbReleaseSpriteBatch(SBSpriteBatch *spritebatch) {
	int status;

	/*  Delete buffers. */
	//TODO resolve
//	if (spbGLIsBufferARB(spritebatch->vbo) == GL_TRUE)
//		sbDestroyBuffer(spritebatch->vbo);
	if (spGLIsVertexArray(spritebatch->vao) == GL_TRUE)
		spGLDeleteVertexArrays(1, &spritebatch->vao);

	/*	Delete shaders. */
	if (sbIsShader(&spritebatch->spriteShader))
		sbDeleteShaderProgram(&spritebatch->spriteShader);
	if (sbIsShader(&spritebatch->fontShader))
		sbDeleteShaderProgram(&spritebatch->fontShader);

	/*	Release sprite buffer.	*/
	//free(spritebatch->sprite);
	spritebatch->sprite = NULL;

	/*  Release texture mapper. */
	free(spritebatch->textures);
	spritebatch->textures = NULL;

	/*	Clear memory.	*/
	//status = !spbGLIsBufferARB(spritebatch->vbo);
	memset(spritebatch, 0, sizeof(*spritebatch));
	return status;
}

void sbSpriteBatchAllocateSprite(SBSpriteBatch *spritebatch, unsigned int num) {

	/*	Check for error.	*/
	if (spritebatch == NULL || num <= 0)
		return;

	/*	Flush current buffer if exists and is not in the middle of drawing.	*//*    TODO add better logic */
	if (spbGLIsBufferARB(spritebatch->buffers[spritebatch->nthBuffer]) && spritebatch->sprite && spritebatch->numDraw)
		sbFlushSpriteBatch(spritebatch);

	/*	Allocate local sprite buffer.	*/
	//spritebatch->sprite = realloc(spritebatch->sprite, num * sizeof(SBSprite));
	spritebatch->num = num;
	/*  Allocate sprite buffer on the graphic device.   */
	for (int i = 0; i < spritebatch->nbuffers; i++) {
		/*	Check if buffer has been created.	*/
		if (spbGLIsBufferARB(spritebatch->buffers[i]) == 0) {
			/*  Create vertex buffer.   */
			sbGenBuffers(1, &spritebatch->buffers[i]);
		}

		spbGLBindBufferARB(GL_ARRAY_BUFFER_ARB, spritebatch->buffers[i]);
		sbSetBufferSize(GL_ARRAY_BUFFER_ARB, spritebatch->buffers[i],
		                spritebatch->num * sizeof(SBQuadSprite), GL_DYNAMIC_DRAW);
		spbGLBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	}

	spritebatch->nthBuffer = 0;

	spbGLBindVertexArray(0);


}

int sbEnableRotation(SBSpriteBatch *spritebatch, int rotation) {
	if (!rotation) {
		/*	Load sprite shader.	*/
		if (!sbCreateShaderv(&spritebatch->spriteShader, gc_shader_spriteQuadV,
		                     gc_shader_spriteQuadF, NULL)) {
			/*	failure	*/
			return 0;
		}

	} else {
		/*	Load sprite shader.	*/
		if (!sbCreateShaderv(&spritebatch->spriteShader, gc_shader_spriteQuadV,
		                     gc_shader_spriteQuadF, NULL)) {
			/*	failure	*/
			return 0;
		}
	}
	return 1;
}

void sbBeginSpriteBatch(SBSpriteBatch *SB_RESTRICT spriteBatch,
                        const float *SB_RESTRICT camerapos, float scale, float rotation) {
	int rect[4];

	/*  Reset sprite and texture counter.   */
	spriteBatch->numDraw = 0;
	spriteBatch->numlabelDraw = 0;

	/*	Get current size of the viewport.	*/
	/*	TODO resolve.   */
	glGetIntegerv(GL_VIEWPORT, rect);
	spriteBatch->width = (unsigned int) (rect[2] - rect[0]);
	spriteBatch->height = (unsigned int) (rect[3] - rect[1]);
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

	/*  Update round robin buffer index.    */
	assert(spriteBatch->nbuffers > 0);
	spriteBatch->nthBuffer++;
	spriteBatch->nthBuffer %= spriteBatch->nbuffers;

	/*  Fetch buffer.   */
	assert(spriteBatch->nthBuffer >= 0 && spriteBatch->nthBuffer < spriteBatch->nbuffers);
	spriteBatch->sprite = (SBSprite *) sbMapBufferWOnly(GL_ARRAY_BUFFER_ARB,
	                                                    spriteBatch->buffers[spriteBatch->nthBuffer]);
	spbGLBindVertexArray(spriteBatch->vao);
	spGLBindVertexBuffer(0, spriteBatch->buffers[spriteBatch->nthBuffer], 0, sizeof(SBVertex));
}

void sbEndSpriteBatch(SBSpriteBatch *spriteBatch) {

	/*  Flush sprite buffers to GPU Memory. */
	sbFlushSpriteBatch(spriteBatch);

	/*	Draw sprites.	*/
	sbDisplaySprite(spriteBatch);
}

static int updateTextureTable(SBSpriteBatch *SB_RESTRICT spriteBatch, const SBTexture *SB_RESTRICT texture) {
	int i;

	/*  Update texture index table. */
	for (i = 0; i < spriteBatch->numMaxTextures; i++) {
		if (spriteBatch->textures[i] == texture->texture)
			return i;
		else {
			if (spriteBatch->textures[i] == NULL) {
				spriteBatch->textures[i] = texture->texture;
				spriteBatch->numTexture++;
				return i + 1;
			}
		}
	}
	return 0;
}

void sbDrawSprite(SBSpriteBatch *spriteBatch, SBTexture *texture,
                  const float *position, const float *rect, const float *color,
                  float scale, float angle, float depth) {

	sbAddSprite(spriteBatch, texture, position, rect, color, scale, angle, depth);

	if (spriteBatch->numDraw >= spriteBatch->num
	    || spriteBatch->numTexture >= spriteBatch->numMaxTextures) {

		/*  Flush if buffer is full.    */
		sbEndSpriteBatch(spriteBatch);

		/*  */
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

		/*  */
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

	int texIndex;
	const unsigned int numDraw = spritebatch->numDraw;
	SBQuadSprite *SB_RESTRICT sbQuadSprite = ((SBQuadSprite *) spritebatch->sprite);
	SBQuadSprite *SB_RESTRICT sprite = &sbQuadSprite[numDraw];

	if (spritebatch->numDraw == spritebatch->num)
		return 0;

	assert(texture->width > 0 && texture->height > 0 && spritebatch->width > 0 && spritebatch->height > 0);

	// Cache variables.
	const float texW = (float) texture->width;
	const float texH = (float) texture->height;
	const float screenW = (float) spritebatch->width;
	const float screenH = (float) spritebatch->height;

	const float xRot = cosf(angle);
	const float yRot = sinf(angle);
	/**
	 * The triangle has to be added in clockwise
	 * 1___3      6
	 * |  /      /|
	 * | /      / |
	 * |/      /__|
	 * 2     4     5
	 * /
	/*  Left top side.  */
	//TODO add scale and rotation.
	/*  Compute with in OpenGL view coordinate. */
	const float NorTexW = (texW / screenW) * (scale) * 2.0f;
	const float NorTexH = (texH / screenH) * (scale) * 2.0f;

	/*  Translate texture normalized to OpenGL view coordinate. */

	float tlCornerX = 2.0f * position[0] - 1.0f + NorTexW;
	float tlCornerY = 2.0f * position[1] - 1.0f - NorTexH;

	/*  Triangle #1.    */
	//lr1
	sprite->vertex[0].pos[0] = tlCornerX;
	sprite->vertex[0].pos[1] = tlCornerY;
	sprite->vertex[0].pos[2] = depth;
	//lr3
	sprite->vertex[2].pos[0] = tlCornerX - NorTexW * yRot;
	sprite->vertex[2].pos[1] = tlCornerY + NorTexH * xRot;
	sprite->vertex[2].pos[2] = depth;
	//lr2
	sprite->vertex[1].pos[0] = tlCornerX + NorTexW * xRot;
	sprite->vertex[1].pos[1] = tlCornerY + NorTexH * yRot;
	sprite->vertex[1].pos[2] = depth;

	/*  Triangle #2.    */
	//lr4 <--> lr2
	sprite->vertex[3].pos[0] = tlCornerX + NorTexW * xRot;
	sprite->vertex[3].pos[1] = tlCornerY + NorTexH * yRot;
	sprite->vertex[4].pos[2] = depth;
	//lr5
	sprite->vertex[5].pos[0] = tlCornerX - NorTexW * yRot + NorTexW * xRot;
	sprite->vertex[5].pos[1] = tlCornerY + NorTexH * xRot + NorTexH * yRot;
	sprite->vertex[3].pos[2] = depth;
	//lr6 <--> lr3
	sprite->vertex[4].pos[0] = tlCornerX - NorTexW * yRot;
	sprite->vertex[4].pos[1] = tlCornerY + NorTexH * xRot;
	sprite->vertex[5].pos[2] = depth;

	/*  Compute view rectangle. */
	if (rect) {
		/*  TODO compute the UV.    */
		sprite->vertex[0].uv[0] = 0.0f;
		sprite->vertex[0].uv[1] = 1.0f;

		sprite->vertex[1].uv[0] = 1.0f;
		sprite->vertex[1].uv[1] = 1.0f;

		sprite->vertex[2].uv[0] = 0.0f;
		sprite->vertex[2].uv[1] = 0.0f;

		sprite->vertex[3].uv[0] = 1.0f;
		sprite->vertex[3].uv[1] = 1.0f;

		sprite->vertex[4].uv[0] = 1.0f;
		sprite->vertex[4].uv[1] = 0.0f;

		sprite->vertex[5].uv[0] = 0.0f;
		sprite->vertex[5].uv[1] = 0.0f;
	} else {
		sprite->vertex[0].uv[0] = 0.0f;
		sprite->vertex[0].uv[1] = 1.0f;

		sprite->vertex[1].uv[0] = 1.0f;
		sprite->vertex[1].uv[1] = 1.0f;

		sprite->vertex[2].uv[0] = 0.0f;
		sprite->vertex[2].uv[1] = 0.0f;

		sprite->vertex[3].uv[0] = 1.0f;
		sprite->vertex[3].uv[1] = 1.0f;

		sprite->vertex[4].uv[0] = 1.0f;
		sprite->vertex[4].uv[1] = 0.0f;

		sprite->vertex[5].uv[0] = 0.0f;
		sprite->vertex[5].uv[1] = 0.0f;

	}
	/*  Compute diffuse color.  */
	if (color) {
		for (int i = 0; i < 6; i++) {
			sprite->vertex[i].color[0] = color[0];
			sprite->vertex[i].color[1] = color[1];
			sprite->vertex[i].color[2] = color[2];
			sprite->vertex[i].color[3] = color[3];
		}
	} else {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 4; j++)
				sprite->vertex[i].color[j] = 1.0f;
		}
	}

	/*  Update texture index table. */
	texIndex = updateTextureTable(spritebatch, texture);

	/*	sprite texture index.	*/
	for (int i = 0; i < 6; i++) {
		sprite->vertex[i].tex = (GLint) texIndex;
	}

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
		SBQuadSprite *sbQuadSprite = ((SBQuadSprite *) spritebatch->sprite);

		/*	Set last element in the index that going to be removed.*/
		memcpy(&sbQuadSprite[index],
		       &sbQuadSprite[spritebatch->numDraw - 1],
		       sizeof(SBQuadSprite));
		spritebatch->numDraw--;
	}
}

int sbFlushSpriteBatch(SBSpriteBatch *spritebatch) {

	/*  */
	if (spritebatch->numDraw > 0) {
		/*	DMA/Transfer sprite buffer to Graphic Memory.  */
		return sbUnmapBuffer(GL_ARRAY_BUFFER_ARB);
	}
	sbUnmapBuffer(GL_ARRAY_BUFFER_ARB);
	return 1;
}

void sbDisplaySprite(SBSpriteBatch *spriteBatch) {

	float matscale[3][3];
	float rotmat[3][3];
	float tranmat[3][3];
	float TR[3][3];

	/*  Only continue if elements needs to be drawn.    */
	if (spriteBatch->numDraw <= 0 && spriteBatch->numlabelDraw <= 0)
		return;

	/*	Bind textures.  */
	sbBindTextures(spriteBatch->textures, 0, spriteBatch->numTexture);

	/*	Load shader.    */
	sbBindShader(&spriteBatch->spriteShader);

	/*	Update view matrix and global scale*/
	sbMatrix3x3Translation(tranmat, spriteBatch->cameraPos);
	sbMatrix3x3Scale(matscale, spriteBatch->scale);
	sbMatrix3x3Rotation(rotmat, spriteBatch->rotation);
	sbMatrix3x3MultiMatrix3x3(tranmat, rotmat, TR);
	sbMatrix3x3MultiMatrix3x3(matscale, TR, spriteBatch->viewmatrix);

	/*	Update uniform variables.   */
	setShaderUniformMatrix3x3fv(&spriteBatch->spriteShader, spriteBatch->uniform.locationViewMatrix, 1,
	                            &spriteBatch->viewmatrix[0][0]);

	/*	Draw sprites.	*/
	spbGLBindVertexArray(spriteBatch->vao);
	glDrawArrays(GL_TRIANGLES, 0, spriteBatch->numDraw * 6);
	spbGLBindVertexArray(0);

}
