/**
	Simple Sprite batch implementation using OpenGL.
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
#ifndef _TEST_BASE_H_
#define _TEST_BASE_H_ 1

#include <SDL2/SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create OpenGL window.
 * @return non-null if successfully.
 */
extern SDL_Window *createWindow(void);

/**
 * Delete window and its associated resources.
 * @param window
 */
extern void deleteWindow(SDL_Window *window);

/**
 * Set window title.
 * @param window
 * @param format
 * @param ...
 */
extern void windowTitle(SDL_Window *window, const char *format, ...);

/**
 * 
 * @param window
 * @param width
 * @param height
 */
extern void windowSetSize(SDL_Window *window, int width, int height);

extern void windowResizable(SDL_Window *pWindow, int i);

/**
 * Enable OpenGL debug.
 */
extern void spEnableDebug(void);

/**
 * Initialize.
 */
extern void init(void);

/**
 * Release resources.
 */
extern void deinit(void);

#ifdef __cplusplus
}
#endif

#endif
