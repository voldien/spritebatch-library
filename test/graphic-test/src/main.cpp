/**
	Sprite batch graphic functionality tests.
	Copyright (C) 2018  Valdemar Lindberg

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
#include"base.h"
#include<GL/glew.h>
#include<assert.h>
#include<list>
#include"Scenes/CircleScene.h"
#include"SceneExecutor.h"
#include"Scenes/PolarRoseScene.h"
#include"Scenes/RotationScene.h"
#include"Scenes/ArchimedeanScene.h"
#include"Scenes/TestScene.h"

void windowResizable(SDL_Window *pWindow, int i);

int main(int argc, const char **argv) {

	/*  */
	if (SDL_Init(SDL_INIT_EVENTS) != 0)
		return EXIT_FAILURE;

	/*  */
	SDL_Window *window = createWindow();
	assert(window);

	if (window == NULL)
		return EXIT_FAILURE;

	/*	Init glew library.	*/
	int status = glewInit();
	if (status != GLEW_OK) {
		deleteWindow(window);
		SDL_DestroyWindow(window);
		fprintf(stderr, "Could not Initialize GLEW - %s.", glewGetErrorString(status));
	}

	windowSetSize(window, 1280, 720);
	windowResizable(window, 0);

	/*  Create the list of scene for the test.  */
	std::list<BenchmarkScene *> testScenes;
	/*  */
	testScenes.push_back(new TestScene());      /*  */
	testScenes.push_back(new CircleScene());        /*  */
	testScenes.push_back(new PolarRoseScene());     /*  */
	testScenes.push_back(new ArchimedeanScene());   /*  */
	testScenes.push_back(new RotationScene());      /*  */

	
	SceneExecutor *sceneExecutor = new SceneExecutor(window);

	std::list<BenchmarkScene *>::iterator it = testScenes.begin();
	for (it; it != testScenes.end(); it++) {
		BenchmarkScene *scene = (*it);
		/*  */
		sceneExecutor->setNextScene(scene);
		sceneExecutor->run();
	}

	deleteWindow(window);
	deinit();

	/*  Simple unit test.   */
	return EXIT_SUCCESS;
}
