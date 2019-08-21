#include"Scenes/CircleScene.h"
#include<math.h>
#include<GL/glew.h>
#include <assert.h>
#include <ProcedureTexture.h>

void CircleScene::init(void) {
	uint8_t pixel[4] = {0xFF, 0xFF, 0xFF, 0xFF};

	/*  Create texture.*/
	const float rgba1[] = {1.0f, 1.0f, 1.0f, 1.0f};
	const float rgba2[] = {0.0f, 0.0f, 0.0f, 1.0f};
	ProcedureTexture::createCheckTexture(128, 128, 12, 12, rgba1, rgba2, &texture);

	sbSpriteBatchAllocateSprite(this->spriteBatch, 1024);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void CircleScene::update(void) {

}

void CircleScene::draw(float time) {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	const float camera[2] = {0.0f, 0.0f};
	const float zoom = 1.0 / 5.0;

	/*	Draw pixel in screen space with normalized coordinates.	*/
	sbBeginSpriteBatch(this->getSpriteBatch(), camera, zoom, 0.0f);

	const int n = 1500;
	for (int i = 0; i < n; i++) {

		const float nf = (float) i;
		const float r = 1.9f;
		const float x = r * cosf(time + nf / 0.1f);
		const float y = r * sinf(time + nf / 0.1f);

		const float rot = time + (1.0f / 1000.0f) *nf;

		const float t = 1.0f;
		const float hx = -1.0f + 2.0f * x / t;
		const float hy = -1.0f + 2.0f * y / t;

		const float pos[2] = {x, y};
		const float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
		sbDrawSpriteNormalize(this->getSpriteBatch(), &texture, pos, NULL, color, 0.5f, 0, 1.0f);
	}

	sbEndSpriteBatch(this->getSpriteBatch());
}

const char *CircleScene::getName(void) const {
	return "Circle";
}

void CircleScene::releases(void) {
	sbDeleteTexture(&this->texture);
}

float CircleScene::getTotalElapseTime(void) {
	return 5.0f;
}
