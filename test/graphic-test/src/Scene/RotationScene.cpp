#include"Scenes/RotationScene.h"
#include <GL/glew.h>
#include<math.h>
#include<assert.h>

float RotationScene::getTotalElapseTime(void) {
	return 7.0f;
}

void RotationScene::init(void) {
	uint8_t pixel[4] = {0xFF, 0xFF, 0xFF, 0xFF};

	assert(sbCreateTexture(&this->texture, GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel));

	sbSpriteBatchAllocateSprite(this->getSpriteBatch(), 1024);

	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
}

void RotationScene::releases(void) {

}

void RotationScene::update(void) {

}

void RotationScene::draw(float time) {
	const int n = 100;
	const float camera[2] = {-1.0f, -1.0f};
	const float zoom = 1.0f / (20.0f * time);

	/*	Draw pixel in screen space with normalized coordinates.	*/
	sbBeginSpriteBatch(this->getSpriteBatch(), camera, zoom, 0.0f);

	const float a = 5.5f;
	float k = 1.0;
	float y = 0.0f;
	const float nor = 2.0f;

	for (int i = 0; i < n; i++) {
		const float angle = (time + (n / 0.1f));
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

const char *RotationScene::getName(void) const {
	return "Rotations";
}
