/**
	Sprite batch functionality tests.
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
#include<stdio.h>
#include<check.h>
#include<stdlib.h>

void createSpriteBatch(SBSpriteBatch *spriteBatch, SBFont *font, SDL_Window **window) {

	SBSpriteBatch *sbSpriteBatch;
	int width, height;

	init();

	*window = createWindow();
	ck_assert(window);

	SDL_GetWindowSize(*window, &width, &height);

	/*  Create sprite batch.    */
	sbSpriteBatch = sbCreateSpriteBatch(spriteBatch);
	ck_assert_ptr_eq(sbSpriteBatch, spriteBatch);

	/*  Check data structure states.    */
	ck_assert(spriteBatch->sprite);
	ck_assert(spriteBatch->rotation == 0.0f);
	ck_assert(spriteBatch->scale == 1.0f);
	ck_assert(spriteBatch->cameraPos[0] == 0.0f);
	ck_assert(spriteBatch->cameraPos[1] == 0.0f);
	ck_assert(spriteBatch->numTexture == 0);

	/*  Check current resolution.   */
	ck_assert(spriteBatch->width == width);
	ck_assert(spriteBatch->height == height);

	/*  Check init state.   */
	ck_assert(spriteBatch->numDraw == 0);
	ck_assert(spriteBatch->num > 0);

	/*  Check texture cache has been allocated. */
	ck_assert(spriteBatch->textures != 0);

	/*  Check shader uniform were successfully.  */
	ck_assert(spriteBatch->uniform.locationScale >= 0);
	ck_assert(spriteBatch->uniform.locationTexture >= 0);
	ck_assert(spriteBatch->uniform.locationViewMatrix >= 0);

	/*  Create font.    */
	ck_assert(sbCreateFont("/usr/share/fonts/opentype/cantarell/Cantarell-Oblique.otf", font, 10) == 1);
}


START_TEST(create){

	SBSpriteBatch spriteBatch;
	SBFont font;
	SDL_Window *window;

	createSpriteBatch(&spriteBatch, &font, &window);
	ck_assert(sbDeleteFont(&font));


	SDL_DestroyWindow(window);
	deinit();
}
END_TEST

START_TEST(simulation){
	SBSpriteBatch spriteBatch;
	SBFont font;
	SDL_Window* window;
	float pos[2] = {0,0};
	SBTexture texture = {0};

	createSpriteBatch(&spriteBatch, &font, &window);

	sbBeginSpriteBatch(&spriteBatch, NULL, 1.0f, 0.0f);
	ck_assert_int_eq(spriteBatch.numDraw, 0);
	ck_assert_int_eq(spriteBatch.numTexture, 0);
	ck_assert_int_eq(spriteBatch.numlabelDraw, 0);

	sbDrawSprite(&spriteBatch, &texture, pos, NULL, NULL, 1.0f, 0.0f, 1.0f);
	/*  Check sprite state. */
	ck_assert_int_eq(spriteBatch.sprite[0].angle, 0.0f);

	/*  Check spritebatch state.    */
	ck_assert_int_eq(spriteBatch.numDraw, 1);
	ck_assert_int_eq(spriteBatch.numTexture, 1);
	ck_assert_int_eq(spriteBatch.numlabelDraw, 0);


	sbDrawSpriteLabel(&spriteBatch, "hello", &font, pos, NULL, NULL, 1.0f, 0.0f, 1.0f );

	/*  Check spritebatch state.    */
	ck_assert_int_eq(spriteBatch.numDraw, 1);
	ck_assert_int_eq(spriteBatch.numTexture, 0);
	ck_assert_int_eq(spriteBatch.numlabelDraw, 1);

	sbEndSpriteBatch(&spriteBatch);
	ck_assert_int_eq(spriteBatch.numDraw, 0);
	ck_assert_int_eq(spriteBatch.numTexture, 0);
	ck_assert_int_eq(spriteBatch.numlabelDraw, 0);

	SDL_DestroyWindow(window);
	deinit();

}
END_TEST

Suite* schCreateSuite(void){

	/*	Create suite and test cases.	*/
	Suite* suite = suite_create("sprite-batch");
	TCase* testCreate = tcase_create("create");
	TCase* simulation = tcase_create("simulation");

	/*	Link test cases with functions.	*/
	tcase_add_test(testCreate, create);
	tcase_add_test(simulation, simulation);

	/*	Add test cases to test suite.	*/
	suite_add_tcase(suite, testCreate);
	suite_add_tcase(suite, simulation);

	return suite;
}

void schCreationUnitTest(void) {

	int number_failed;
	Suite *s;
	SRunner *sr;

	/*	Create test suits */
	s = schCreateSuite();

	/*  Create suite runner.    */
	sr = srunner_create(s);
	srunner_run_all(sr, CK_VERBOSE);

	/*	Retrieve number of failures. */
	number_failed = srunner_ntests_failed(sr);

	/*  Display number of total failures and clean up.  */
	printf("number of total failure : %d\n", number_failed);
	printf("\n");
	srunner_free(sr);
}

int main(int argc, const char **argv) {

	/*  Simple unit test.   */
	printf("spritebatch version:%s\n", sbGetVersion());
	schCreationUnitTest();

	SBFont font;
	sbCreateFont("/usr/share/fonts/opentype/cantarell/Cantarell-Oblique.otf", &font, 10) ;

	return EXIT_SUCCESS;
}