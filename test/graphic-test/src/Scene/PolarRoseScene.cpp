#include"Scenes/PolarRoseScene.h"
#include <GL/glew.h>
#include<math.h>
#include<assert.h>
#include <ProcedureTexture.h>

float PolarRoseScene::getTotalElapseTime(void) {
	return 8.0f;
}

void PolarRoseScene::init(void) {

	uint8_t pixel[4] = {0xFF, 0xFF, 0xFF, 0xFF};


	/*  Create texture.*/
	const float rgba[] = {1.0f, 1.0f, 1.0f, 1.0f};
	ProcedureTexture::createCircleTexture(512,512, rgba, &texture);

	sbCreateTexture(&texture, GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel);

	//sbSpriteBatchAllocateSprite(this->getSpriteBatch(), 10000);

	glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
}

void PolarRoseScene::releases(void) {
	sbDeleteTexture(&this->texture);
}

void PolarRoseScene::update(void) {

}

void PolarRoseScene::draw(float time) {
	const int n = 1500;
	const float camera[2] = {-1.0f, -1.0f};
	const float zoom = 1.0f / (2.0f * time);

	/*	Draw pixel in screen space with normalized coordinates.	*/
	sbBeginSpriteBatch(this->getSpriteBatch(), camera, zoom, time * 0.5);

	const float a = 5.5f;
	float k = 4.0;
	float y = 0.0f;
	const float nor = 2.0f;

	for (int i = 0; i < n; i++) {
		const float nf = (float)i;
		const float angle = (time * 0.5f + (nf / 0.1f));

		const float r = a * cosf(k * angle + y);

		/*  Cartesian coordinates. */
		const float x = r * cosf(angle);
		const float y = r * sinf(angle);

		/*  normalized coorinates.  */
		const float hx = -1.0f + 2.0f * x / nor;
		const float hy = -1.0f + 2.0f * y / nor;

		float pos[2] = {x, y};
		float color[] = {1.0f, 1.0f, 0.0f, 1.0f};
		sbDrawSpriteNormalize(this->getSpriteBatch(), &texture, pos, NULL, color, 100.0f, 0.0f, 0.0f);
	}

	sbEndSpriteBatch(this->getSpriteBatch());
}

const char *PolarRoseScene::getName(void) const {
	return "PolarRose";
}
