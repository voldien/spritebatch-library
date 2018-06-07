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
#ifndef _SB_SPRITE_H_
#define _SB_SPRITE_H_ 1
#include"texture.h"
#include"shader.h"
#include "font.h"

#ifdef __cplusplus	/*	C++ environment	*/
extern "C" {
#endif

/**
 *	Read only global.
 */
extern const char* gc_sb_sprite_vertex_shader;
extern const char* gc_sb_sprite_fragment_shader;
extern const char* gc_sb_sprite_geometry_shader;
extern const char* gc_sb_label_vertex_shader;
extern const char* gc_sb_label_fragment_shader;
extern const char* gc_sb_label_geometry_shader;

/**
 *	Sprite attributes.
 *
 */
typedef struct sb_sprite_t {
	float pos[3];       /*	position.	*/
	float angle;        /*	angle.	*/
	float rect[4];      /*	*/
	int texture;        /*	texture index.*/
	float scale;        /*	uniform scale.	*/
	float color[4];     /*	color.	*/
} SBSprite;

/**
 *	Uniform location cache.
 */
typedef struct sb_sprite_uniform_index_t {
	int locationViewMatrix;     /*	*/
	int locationScale;          /*	*/
	int locationTexture;        /*	*/
} SBSpriteUniformIndex;

/**
 *	Sprite batch.
 */
typedef struct sb_sprite_batch_t {
	/*
	 *	number of sprite allocated.
	 */
	unsigned int num;           /*	*/
	unsigned int numDraw;       /*	*/
	unsigned int numlabelDraw;  /*	*/
	unsigned int vbo;           /*	*/
	unsigned int vao;           /*	*/

	/*	*/
	SBShader spriteShader;      /*	*/
	SBShader fontShader;        /*  */

	/*	*/
	int numTexture;             /*	Number of associated textures.	*/
	int numMaxTextures;         /*	Max number of texture units.	*/

	/*	*/
	int* texture;               /*  */
	SBSprite* sprite;           /*  */

	float scale;                /*  */
	float cameraPos[2];         /*  */
	float rotation;             /*  */

	/*	*/
	unsigned int width;         /*  */
	unsigned int height;        /*  */

	/*	view matrix.	*/
	float viewmatrix[3][3];     /*  */

	/*	cached uniform location.	*/
	SBSpriteUniformIndex uniform;

} SBSpriteBatch;

/**
 * Initialize spritebatch structure and associated
 * data with the structure object.
 *
 * @remark ExCreateSpriteBatch will allocate 4096 sprite shape by default.
 * This can be changed by using ExSpriteBatchAllocateSprite.
 *
 * @param spriteBatch
 * @return Non NULL pointer if successfully.
 */
extern SBDECLSPEC SBSpriteBatch* SBAPIENTRY sbCreateSpriteBatch(
		SBSpriteBatch* spriteBatch);

/**
 * Release resources associated with spritebatch.
 * @param spritebatch
 * @return non-zero if successfully.
 */
extern SBDECLSPEC int SBAPIENTRY sbReleaseSpriteBatch(
		SBSpriteBatch* spritebatch);

/**
 * Allocate sprite batch.
 * @param spritebatch
 * @param num number of sprites.
 */
extern SBDECLSPEC void SBAPIENTRY sbSpriteBatchAllocateSprite(
		SBSpriteBatch* spritebatch, unsigned int num);

/**
 * Begin spritebatch for adding sprite element for rendering.
 * @param spriteBatch
 * @param camerapos
 * @param scale
 */
extern SBDECLSPEC void SBAPIENTRY sbBeginSpriteBatch(
        SBSpriteBatch* SB_RESTRICT spriteBatch,
        const float* SB_RESTRICT camerapos, float scale);

/**
 * End and flush the spritebatch.
 * @param spriteBatch
 */
extern SBDECLSPEC void SBAPIENTRY sbEndSpriteBatch(SBSpriteBatch* spriteBatch);

/**
 *	Draw the
 *
 *	@Return
 */
extern SBDECLSPEC void SBAPIENTRY sbDrawSprite(SBSpriteBatch* spritebatch,
		SBTexture* texture, const float* position, const float* rect,
		const float* color, float scale, float angle, float depth);

/**
 *	Draw sprite in normalized screen coordinate.
 *
 *	@Return
 */
extern SBDECLSPEC int SBAPIENTRY sbDrawSpriteNormalize(
		SBSpriteBatch* spritebatch, SBTexture* texture, const float* position,
		const float* rect, const float* color, float scale, float angle,
		float depth);
/**
 * Not implemented
 * @param spritebatch
 * @param label
 * @param font
 * @param position
 * @param rect
 * @param color
 * @param scale
 * @param angle
 * @param depth
 * @return
 */
extern SBDECLSPEC int SBAPIENTRY sbDrawSpriteLabel(SBSpriteBatch* spritebatch, const char* label,
		SBFont* font, float* position, float* rect, float* color, float scale,
		float angle, float depth);

/**
 *
 * @param spritebatch
 * @param label
 * @param font
 * @param position
 * @param rect
 * @param color
 * @param scale
 * @param angle
 * @param depth
 * @return
 */
extern SBDECLSPEC int SBAPIENTRY sbDrawSpriteLabelNormalized(SBSpriteBatch* spritebatch, const char* label,
                                                   SBFont* font, float* position, float* rect, float* color, float scale,
                                                   float angle, float depth);

/**
 * Add normalized sprite.
 * @param spritebatch
 * @param texture
 * @param position
 * @param rect
 * @param color
 * @param scale
 * @param angle
 * @param depth
 */
extern SBDECLSPEC void SBAPIENTRY sbAddSpriteNormalized(
        SBSpriteBatch* spritebatch, SBTexture* texture, const float* position,
        const float* rect, const float* color, float scale, float angle,
        float depth);

/**
 * Append sprite to spritebatch at back end
 * of the queue.
 * @param spritebatch
 * @param texture
 * @param position
 * @param rect
 * @param color
 * @param scale
 * @param angle
 * @param depth
 * @return
 */
extern SBDECLSPEC int SBAPIENTRY sbAddSprite(SBSpriteBatch* spritebatch,
		SBTexture* texture, const float* position, const float* rect,
		const float* color, float scale, float angle, float depth);

/**
 * Remove sprite object from sprite batch.
 *
 * @param spritebatch
 * @param index
 */
extern SBDECLSPEC void SBAPIENTRY sbRemoveSprite(SBSpriteBatch* spritebatch,
        int index);

/**
 * Flush current sprite buffer instantly to
 * the GPU.
 *
 * @param spritebatch
 * @return non-zero if successfully.
 */
extern SBDECLSPEC int SBAPIENTRY sbFlushSpriteBatch(
		SBSpriteBatch* spritebatch);

/**
 * Display all sprite assigned to spritebatch.
 *
 * @param spritebatch
 */
extern SBDECLSPEC void SBAPIENTRY sbDisplaySprite(SBSpriteBatch* spritebatch);

#ifdef __cplusplus	/* C++ environment	*/
}
#endif 

#endif
