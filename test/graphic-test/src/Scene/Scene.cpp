
#include <Scenes/Scene.h>

#include"Scenes/Scene.h"
#include <assert.h>

Scene::Scene(void) {
	this->spriteBatch = new SBSpriteBatch();
	sbCreateSpriteBatch(this->spriteBatch);
}

void *Scene::getData(void) {
	return nullptr;
}

SBSpriteBatch *Scene::getSpriteBatch(void) {
	return this->spriteBatch;
}

Scene::~Scene(void) {
	sbReleaseSpriteBatch(this->spriteBatch);
	delete this->spriteBatch;
}
