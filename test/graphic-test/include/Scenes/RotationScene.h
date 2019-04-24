#ifndef _SPRITEBATCH_ROTATIONSCENE_H_
#define _SPRITEBATCH_ROTATIONSCENE_H_ 1
#include "BenchmarkScene.h"

class RotationScene : public BenchmarkScene {
public:
	float getTotalElapseTime(void) override;

	void init(void) override;

	void releases(void) override;

	void update(void) override;

	void draw(float time) override;

	const char *getName(void) const override;
private:
	SBTexture texture;
};

#endif