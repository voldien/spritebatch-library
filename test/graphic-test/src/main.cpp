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
#include"sprite.h"
#include"base.h"
#include<stdlib.h>
#include<GL/glew.h>
#include<GL/gl.h>
#include<assert.h>

int main(int argc, const char **argv) {

	SBSpriteBatch spriteBatch = { 0 };

	/*  */
	if (SDL_Init(SDL_INIT_EVENTS) != 0)
		return EXIT_FAILURE;

	/*  */
	SDL_Window *window = createWindow();
	assert(window);

	glewInit();

	SBTexture texture;

	/*	*/
	uint32_t alive = SDL_TRUE;
	SDL_Event event = {0};
	int visable;
	uint8_t pixel[4] = {0xFF, 0xFF, 0xFF, 0xFF};
	SBFont* font;
	float camera[2];
	float zoom = 1.0;

	if (!sbCreateSpriteBatch(&spriteBatch))
		goto error;

	sbSpriteBatchAllocateSprite(&spriteBatch, 100000);

	//sbCreateFont("/usr/share/fonts/opentype/cantarell/Cantarell-Oblique.otf", &font, 10);

	/*  Create width pixel. */
	assert(sbCreateTexture(&texture, GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel));

	/*	Time.	*/
	long int pretime = SDL_GetPerformanceCounter();

	/*	Continue program in till it dies.	*/
	while (alive) {

		/*	Iterate in till event queue is depleted.	*/
		while (SDL_PollEvent(&event)) {

			switch (event.type) {
				case SDL_APP_TERMINATING:
				case SDL_QUIT:
					alive = SDL_FALSE;
					break;
				case SDL_KEYUP:
					if (event.key.keysym.sym == SDLK_RETURN && (event.key.keysym.mod & SDLK_LSHIFT)) {
						SDL_SetWindowFullscreen(window, SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP ? 0
						                                                                                           : SDL_WINDOW_FULLSCREEN_DESKTOP);
					}
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						SDL_Event qevent = {0};
						event.type = SDL_QUIT;
						SDL_PushEvent(&qevent);
					}
					break;
				case SDL_MOUSEMOTION:
					camera[0] = event.motion.x / 10.0f;
					camera[1] = event.motion.y / 10.0f;
					break;
				case SDL_MOUSEWHEEL:
					zoom += event.wheel.y / 10.0f;
					break;
				case SDL_WINDOWEVENT:
					switch (event.window.event) {

						case SDL_WINDOWEVENT_EXPOSED:
						case SDL_WINDOWEVENT_SHOWN:
							visable = 1;
							break;
						case SDL_WINDOWEVENT_HIDDEN:
							visable = 0;
							break;
						case SDL_WINDOWEVENT_ENTER:
							visable = 1;
							break;
						case SDL_WINDOWEVENT_LEAVE:
							visable = 0;
							break;
						case SDL_WINDOWEVENT_CLOSE:
							alive = SDL_FALSE;
							break;
						case SDL_WINDOWEVENT_RESIZED:
							glViewport(0, 0, event.window.data1, event.window.data2);
							printf("viewport %dx%d\n", event.window.data1, event.window.data2);

							break;
					}
					break;
				default:
					break;
			}
		}
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);

		/*	Draw pixel in screen space with normalized coordinates.	*/
		sbBeginSpriteBatch(&spriteBatch, camera, zoom, 0.0f);

		const float time = (SDL_GetPerformanceCounter()) / 1000000000.0f;
		unsigned long delta = (SDL_GetPerformanceCounter - pretime);
		pretime = SDL_GetPerformanceCounter();


		const int n = 1500;
		for(int i = 0; i < n; i++){
			const float r = 100.0f + n;
			const float x = r * cosf(time + n);
			const float y = r * sinf(time + n);

			const float t = 300.0f;
			const float hx = -1.0f + 2.0f * (float)x / t;
			const float hy = -1.0f + 2.0f * (float)y / t;

			float pos[2] = {hx, hy};
			float color[] = {1,0,0,1};
			sbDrawSpriteNormalize(&spriteBatch, &texture, pos, NULL, color, 10.0f, 0.0f, 0.0f);
		}

		sbEndSpriteBatch(&spriteBatch);

		/*  Draw font in normalized coordinates.    */
//		sbBeginSpriteBatch(&spriteBatch, NULL, 1.0f, 0.0f);
//		const float fontPos[2] = {0, 0};
//		sbDrawSpriteLabelNormalized(&spriteBatch, "hello", &font, fontPos, NULL, NULL, 1.0f, 0.0f, 0.0f);
//
//		sbEndSpriteBatch(&spriteBatch);

		SDL_GL_SwapWindow(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	error:

	sbReleaseSpriteBatch(&spriteBatch);
	SDL_DestroyWindow(window);
	SDL_Quit();
	/*  Simple unit test.   */
	return EXIT_SUCCESS;
}