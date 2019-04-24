#include"SceneExecutor.h"
#include"sprite.h"
#include"base.h"
#include"Scenes/Scene.h"
#include<stdlib.h>
#include<GL/glew.h>
#include<assert.h>
#include <Scenes/BenchmarkScene.h>
#include <SceneExecutor.h>


SceneExecutor::SceneExecutor(void *window) {
	this->window = (SDL_Window *) window;

	SDL_GL_SetSwapInterval(SDL_FALSE);
	/*  Create query.   */
	glGenQueries(sizeof(this->queries) / sizeof(this->queries[0]), &this->queries[0]);
}


SceneExecutor::~SceneExecutor(void) {
	glDeleteQueries(sizeof(this->queries) / sizeof(this->queries[0]), &this->queries[0]);
}


void SceneExecutor::setNextScene(BenchmarkScene *scene) {
	this->scene = scene;
	this->scene->init();

	windowTitle(this->window, "Benchmark - %s - sec: %f", this->scene->getName(), this->scene->getTotalElapseTime());

	this->frameCounter = 0;
	this->primitiveCounter = 0;
	this->sampleCounter = 0;
}

void SceneExecutor::run(void) {

	uint32_t alive = SDL_TRUE;
	SDL_Event event = {0};
	float elapseTime;

	/*	Time.	*/
	long int pretime = SDL_GetPerformanceCounter();
	long int startTime = SDL_GetPerformanceCounter();

	/*	Continue program in till it dies.	*/
	while (alive) {
		BenchmarkScene *scene = this->scene;

		/*  Compute total time and determine if done.   */
		elapseTime = (float) (SDL_GetPerformanceCounter() - startTime) / (float) SDL_GetPerformanceFrequency();
		if (scene->getTotalElapseTime() < elapseTime)
			break;

		/*	Iterate in till event queue is depleted.	*/
		while (SDL_PollEvent(&event)) {

			switch (event.type) {
				case SDL_APP_TERMINATING:
				case SDL_QUIT:
					alive = SDL_FALSE;
					break;
				case SDL_WINDOWEVENT:
					switch (event.window.event) {
						case SDL_WINDOWEVENT_CLOSE:
							alive = SDL_FALSE;
							break;
						case SDL_WINDOWEVENT_RESIZED:
							glViewport(0, 0, event.window.data1, event.window.data2);
							//printf("viewport %dx%d\n", event.window.data1, event.window.data2);

							break;
					}
					break;
				default:
					break;
			}
		}

		/*  */
		unsigned long delta = (SDL_GetPerformanceCounter() - pretime);
		const float deltaTimef = (float) delta / (float) SDL_GetPerformanceFrequency();
		pretime = SDL_GetPerformanceCounter();

		/*  */
		scene->update();
		glBeginQuery(GL_SAMPLES_PASSED, this->queries[0]);
		glBeginQuery(GL_PRIMITIVES_GENERATED, this->queries[1]);

		scene->draw(elapseTime);
		glEndQuery(GL_PRIMITIVES_GENERATED);
		glEndQuery(GL_SAMPLES_PASSED);

		SDL_GL_SwapWindow((SDL_Window *) this->window);

		int nrPrimitives;
		int nrSamples;
		glGetQueryObjectiv(this->queries[0], GL_QUERY_RESULT, &nrSamples);
		glGetQueryObjectiv(this->queries[1], GL_QUERY_RESULT, &nrPrimitives);

		/*  Present the value */
		printf("time: %f;deltaTime: %f; primitives-generated: %d; samples: %d\n", elapseTime, deltaTimef, nrPrimitives,
		       nrSamples);

		/*  */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->frameCounter++;
		this->primitiveCounter += nrPrimitives;
		this->sampleCounter += nrSamples;
	}
	printf("Total Frame Count: %d; Total Primitive Count: %d; Total Sample Count: %d; Elapsed Time: %f; Scene: %s\n\n",
	       this->frameCounter, this->primitiveCounter, this->sampleCounter, this->scene->getTotalElapseTime(),
	       this->scene->getName());
}

