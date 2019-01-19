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
#include"font.h"

#ifdef __cplusplus	/*	C++ environment	*/
extern "C" {
#endif

/**
 *	Sprite attributes.
 *
 */
typedef struct sb_sprite_t {
	float pos[3];       /*	World position.	*/
	float angle;        /*	Angle in radian.	*/
	float rect[4];      /*	View rectangle. */
	int texture;        /*	Texture index.*/
	float scale;        /*	Uniform aligned scale.	*/
	float color[4];     /*	Diffuse Color.	*/
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

	/*  Number of sprite allocated.   */
	unsigned int num;           /*	Number of allocated sprites.    */
	unsigned int numDraw;       /*	Number of sprite in batch.  */
	unsigned int numlabelDraw;  /*	Number of label sprite in batch.    */
	unsigned int vbo;           /*	Sprite buffer uid.  */
	unsigned int vao;           /*	Vertex geometry object uid. */
	void* pspritemap;           /*  TODO add support for DMA sprites.   */
	void* plabelmap;            /*  TODO add support for DMA labels.    */

	/*	*/
	SBShader spriteShader;      /*	Sprite shader.  */
	SBShader fontShader;        /*  Font shader.    */

	/*	*/
	int numTexture;             /*	Number of associated textures.	*/
	int numMaxTextures;         /*	Max number of texture units.	*/

	/*	*/
	unsigned int* textures;     /*  Texture index table.    */
	SBSprite* sprite;           /*  Sprite buffer.  */
	SBSprite* label;            /*  Label buffer.  */

	/*  */
	float scale;                /*  Global aligned world scale. */
	float cameraPos[2];         /*  Camera position in world space. */
	float rotation;             /*  Global rotation.    */

	/*	*/
	unsigned int width;         /*  Viewport width from sbBeginSpriteBatch. */
	unsigned int height;        /*  Viewport height from sbBeginSpriteBatch. */

	/*	view matrix.	*/
	float viewmatrix[3][3];     /*  Cached view matrix for sprite transformations.   */

	/*	cached uniform location.	*/
	SBSpriteUniformIndex uniform;   /*  Shader uniform location.    */

} SBSpriteBatch;

/**
 * Get version of the library.
 * @return non-null terminated character pointer.
 */
extern SBDECLSPEC const char* SBAPISTDENTRY sbGetVersion(void);

/**
 * Initialize spritebatch structure and associated
 * data with the structure object.
 *
 * @remark ExCreateSpriteBatch will allocate 4096 sprite shape by default.
 * This can be changed by using ExSpriteBatchAllocateSprite.
 *
 * @param spriteBatch valid memory object.
 * @return Non NULL pointer if successfully.
 */
extern SBDECLSPEC SBSpriteBatch* SBAPIENTRY sbCreateSpriteBatch(
		SBSpriteBatch* spriteBatch);

/**
 * Release resources associated with spritebatch.
 * @param spritebatch valid spritebatch object.
 * @return non-zero if successfully.
 */
extern SBDECLSPEC int SBAPIENTRY sbReleaseSpriteBatch(
		SBSpriteBatch* spritebatch);

/**
 * Allocate sprite batch.
 * @param spritebatch valid spritebatch object.
 * @param num number of sprites.
 */
extern SBDECLSPEC void SBAPIENTRY sbSpriteBatchAllocateSprite(
		SBSpriteBatch* spritebatch, unsigned int num);

/**
 * Begin spritebatch for adding sprite element for rendering.
 * @param spriteBatch valid spritebatch object.
 * @param camerapos camera position
 * @param scale global aligned scale.
 * @param rotation rotation in radian.
 */
extern SBDECLSPEC void SBAPIENTRY sbBeginSpriteBatch(
        SBSpriteBatch* SB_RESTRICT spriteBatch,
        const float* SB_RESTRICT camerapos, float scale, float rotation);

/**
 * End and flush the spritebatch and subsequently
 * invoke draw call.
 * @param spriteBatch valid spritebatch object.
 */
extern SBDECLSPEC void SBAPIENTRY sbEndSpriteBatch(SBSpriteBatch* spriteBatch);

/**
 * Draw sprite in pixel screen coordinate.
 * @param spriteBatch valid spritebatch object.
 * @param texture valid texture object.
 * @param position 2D position in pixels.
 * @param rect
 * @param color normalized color RGBA.
 * @param scale aligned scale.
 * @param angle rotation in radian.
 * @param depth from -1 - 1
 */
extern SBDECLSPEC void SBAPIENTRY sbDrawSprite(SBSpriteBatch* spriteBatch,
		SBTexture* texture, const float* position, const float* rect,
		const float* color, float scale, float angle, float depth);

/**
 * Draw sprite in normalized screen coordinate.
 * @param spriteBatch valid spritebatch object.
 * @param texture valid texture object.
 * @param position
 * @param rect
 * @param color normalized color RGBA.
 * @param scale aligned scale.
 * @param angle rotation in radian.
 * @param depth from -1 - 1
 * @return
 */
extern SBDECLSPEC void SBAPIENTRY sbDrawSpriteNormalize(
		SBSpriteBatch* spritebatch, SBTexture* texture, const float* position,
		const float* rect, const float* color, float scale, float angle,
		float depth);

/**
 * Draw
 * @param spritebatch
 * @param label
 * @param font
 * @param position
 * @param rect
 * @param color normalized color RGBA.
 * @param scale aligned scale.
 * @param angle rotation in radian.
 * @param depth from -1 - 1
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
 * @param color normalized color RGBA.
 * @param scale aligned scale.
 * @param angle rotation in radian.
 * @param depth from -1 - 1
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
 * @param color normalized color RGBA.
 * @param scale aligned scale.
 * @param angle rotation in radian.
 * @param depth from -1 - 1
 * @return
 */
extern SBDECLSPEC int SBAPIENTRY sbAddSpriteNormalized(
        SBSpriteBatch* spritebatch, SBTexture* texture, const float* position,
        const float* rect, const float* color, float scale, float angle,
        float depth);

/**
 * Append sprite to spritebatch at back end
 * of the queue.
 * @param spriteBatch
 * @param texture
 * @param position
 * @param rect
 * @param color normalized color RGBA.
 * @param scale aligned scale.
 * @param angle rotation in radian.
 * @param depth from -1 - 1
 * @return
 */
extern SBDECLSPEC int SBAPIENTRY sbAddSprite(SBSpriteBatch* spriteBatch,
		SBTexture* texture, const float* position, const float* rect,
		const float* color, float scale, float angle, float depth);

/**
 * Remove sprite object from sprite batch.
 *
 * @param spritebatch valid spritebatch.
 * @param index non-negative number.
 */
extern SBDECLSPEC void SBAPIENTRY sbRemoveSprite(SBSpriteBatch* spritebatch,
        int index);

/**
 * Flush current sprite buffer instantly to
 * the GPU memory.
 *
 * @param spritebatch valid spritebatch.
 * @return non-zero if successfully.
 */
extern SBDECLSPEC int SBAPIENTRY sbFlushSpriteBatch(
		SBSpriteBatch* spritebatch);

/**
 * Display all sprite assigned to spritebatch.
 *
 * @param spritebatch valid spritebatch object.
 */
extern SBDECLSPEC void SBAPIENTRY sbDisplaySprite(SBSpriteBatch* spritebatch);

#ifdef __cplusplus	/* C++ environment	*/
}
#endif 

#endif
