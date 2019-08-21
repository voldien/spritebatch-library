#include"Scenes/ArchimedeanScene.h"
#include <GL/glew.h>
#include<math.h>
#include<assert.h>
#include <ProcedureTexture.h>

float ArchimedeanScene::getTotalElapseTime(void) {
	return 9.0;
}

void ArchimedeanScene::init(void) {
	uint8_t pixel[4] = {0xFF, 0xFF, 0xFF, 0xFF};


	/*  */
	const float rgba[] = {1.0f, 1.0f, 1.0f, 1.0f};
	//ProcedureTexture::createCircleTexture(512, 512, rgba, &texture);

	assert(sbCreateTexture(&texture, GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel));

	sbSpriteBatchAllocateSprite(this->getSpriteBatch(), 1024);

	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
}

void ArchimedeanScene::releases(void) {
	sbDeleteTexture(&this->texture);
}

void ArchimedeanScene::update(void) {

}

void ArchimedeanScene::draw(float time) {
	const float camera[2] = {0.0f, 0.0f};
	const float zoom = 1.0f / time;

	/*	Draw pixel in screen space with normalized coordinates.	*/
	sbBeginSpriteBatch(this->getSpriteBatch(), camera, zoom, 0.0f);

	const float a = 1.0f;
	float b = 1.0;
	float y = 0.0f;
	const int n = 100000;
	for (int i = 0; i < n; i++) {
		const float nf = (float) i;
		const float angle = (time + nf);
		const float r = a + b * angle;

		const float x = r * cosf(angle);
		const float y = r * sinf(angle);

		const float t = 300.0f;
		const float hx = -1.0f + 2.0f * (float) x / t;
		const float hy = -1.0f + 2.0f * (float) y / t;

		float pos[2] = {hx, hy};
		float color[] = {1.0f, 1.0f, 0.0f, 1.0f};
		sbDrawSpriteNormalize(this->getSpriteBatch(), &texture, pos, NULL, color, 10.0f, 0.0f, 0.0f);
	}

	sbEndSpriteBatch(this->getSpriteBatch());
}

const char *ArchimedeanScene::getName(void) const {
	return "Archimedean";
}
