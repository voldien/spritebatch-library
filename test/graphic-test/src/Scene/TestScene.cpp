#include"Scenes/TestScene.h"
#include <GL/glew.h>
#include<math.h>
#include<assert.h>

float TestScene::getTotalElapseTime(void) {
	return 4.0;
}

void TestScene::init(void) {
	uint8_t pixel[4] = {0xFF, 0xFF, 0xFF, 0xFF};

	sbCreateTexture(&this->texture, GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
}

void TestScene::releases(void) {

}

void TestScene::update(void) {

}

void TestScene::draw(float time) {

	const int n = 10;
	float color[n][4] = {
			{1.0f, 1.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 0.0f, 1.0f},
			{0.0f, 0.0f, 1.0f, 1.0f},
	};

	/*	Draw pixel in screen space with normalized coordinates.	*/
	sbBeginSpriteBatch(this->getSpriteBatch(), NULL, 1.0, 0.0f);

	for (int i = 0; i < n; i++) {

		const float angle = (time + (n / 0.1f));
		const float r = 0.3f;

		/*  Cartesian coordinates. */
		const float x = r * cosf(angle);
		const float y = r * sinf(angle);

		float pos[2] = {x, y};

		sbDrawSpriteNormalize(this->getSpriteBatch(), &texture, pos, NULL, color[i], 100.0f, angle, 0.0f);
	}

	sbEndSpriteBatch(this->getSpriteBatch());
}

const char *TestScene::getName(void) const {
	return "Test Scene";
}
