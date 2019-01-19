#include"font.h"
#include<GL/gl.h>
#include<math.h>
#include<ft2build.h>
#include <assert.h>
#include FT_FREETYPE_H

inline static int nextp2(int n) {
	int res = 1;
	while (res < n)res <<= 1;
	return res;
}

int sbCreateFont(const char *cpath, SBFont *font, const size_t size) {

	const size_t numChar = 255;
	const size_t nrFontFields = 9;
	FT_ULong i;
	int j, l;
	size_t width, height;
	FT_Library ft;

	/*  */
	FT_GlyphSlot slot;
	FT_Matrix matrix;                 /* transformation matrix */
	FT_Vector pen;                    /* untransformed origin  */
	FT_Bitmap *bmp;
	int glyph_width;
	int glyph_height;
	int num_segments_x = numChar;
	int num_segments_y = numChar;
	int segment_size_x = 0;
	int segment_size_y = 0;
	int font_tex_width;
	int font_tex_height;
	int bitmap_offset_x = 0, bitmap_offset_y = 0;

	/*  */
	FT_Glyph_Metrics *metrics;
	FT_Face face;

	/*  Validate arguments. */
	if (size <= 0.0f || font == NULL)
		return -1;

	/*  Init library.   */
	if (FT_Init_FreeType(&ft) != 0) {
		fprintf(stderr, "could not init freetype.\n");
		return -1;
	}

	/*  Load default.   */
	if (cpath == NULL) {
		cpath = "";
	}

	/*  Load font face by the path. */
	if (FT_New_Face(ft, cpath, 0, &face) != 0) {
		fprintf(stderr, "could not file:%s\n", cpath);
		FT_Done_FreeType(ft);
		return -1;
	}

	/*  Set the size of the font.   */
	if (FT_Set_Char_Size(face, 0, size * (1 << 6), 96, 96) != 0) {
		FT_Done_Face(ft);
		FT_Done_FreeType(ft);
		return -1;
	}

	/*	First calculate the max width and height of a character in a passed font	*/
	for (i = 0; i < numChar; i++) {

		/*  Load character. */
		if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
			fprintf(stderr, "FT_Load_Char failed: %c\n", i);
			return -1;
		}

		/*  */
		slot = face->glyph;
		bmp = &slot->bitmap;

		/*  Character bitmap size.  */
		glyph_width = bmp->width;
		glyph_height = bmp->rows;

		/*  Compute max width and height.   */
		if (glyph_width > segment_size_x) {
			segment_size_x = glyph_width;
		}

		if (glyph_height > segment_size_y) {
			segment_size_y = glyph_height;
		}
	}

	/*  Compute texture size.    */
	font_tex_width = nextp2(num_segments_x * segment_size_x);
	font_tex_height = nextp2(num_segments_y * segment_size_y);

	/*	Allocate pixel data.    */
	char *font_texture_data = (char *) malloc(sizeof(char) * 2 * font_tex_width * font_tex_height);
	memset((void *) font_texture_data, 0, sizeof(char) * 2 * font_tex_width * font_tex_height);

	/*  Allocate font attribute fields. */
	font->advance = (float *) malloc(sizeof(float) * nrFontFields * numChar);
	assert(font->advance);
	font->width = &font->advance[1 * numChar];
	font->height = &font->advance[2 * numChar];
	font->tex_x1 = &font->advance[3 * numChar];
	font->tex_x2 = &font->advance[4 * numChar];
	font->tex_y1 = &font->advance[5 * numChar];
	font->tex_y2 = &font->advance[6 * numChar];
	font->offset_x = &font->advance[7 * numChar];
	font->offset_y = &font->advance[8 * numChar];

	/*  Iterate through each character. */
	for (i = 0; i < numChar; i++) {

		/*  */
		if (FT_Load_Char(face, i, FT_LOAD_RENDER) != 0) {
			fprintf(stderr, "FT_Load_Char failed: %c\n", i);
			return -1;
		}

		/*  Rotate the face.    */
		matrix.xx = (FT_Fixed) (-cos(3.14) * 0x10000L);
		matrix.xy = (FT_Fixed) (-sin(3.14) * 0x10000L);
		matrix.yx = (FT_Fixed) (sin(3.14) * 0x10000L);
		matrix.yy = (FT_Fixed) (cos(3.14) * 0x10000L);

		div_t temp = div(i, num_segments_x);

		bitmap_offset_x = segment_size_x * temp.rem;
		bitmap_offset_y = segment_size_y * temp.quot;

		pen.x = bitmap_offset_x;
		pen.y = bitmap_offset_y;
		FT_Set_Transform(face, &matrix, &pen);


		/*  */
		slot = face->glyph;
		bmp = &slot->bitmap;

		/*  Get power of two size.  */
		glyph_width = nextp2(bmp->width);
		glyph_height = nextp2(bmp->rows);

		for (int row = 0; row < glyph_height; ++row) {
			for (int col = 0; col < glyph_width; ++col) {
				int x = pen.x + col;
				int y = pen.y + row;
				font_texture_data[y * glyph_width + x] = bmp->buffer[row * bmp->pitch + col];
			}
		}

		/*	Iterate through each pixel of the bitmap.   */
//		for (j = 0; j < glyph_height; j++) {
//			for (l = 0; l < glyph_width; l++) {
//
//				font_texture_data[l * glyph_width + l] = bmp->buffer[j * bmp->pitch + l];
//				/*
//				font_texture_data[2 * ((bitmap_offset_x + l) + (j + bitmap_offset_y) * font_tex_width) + 0] =
//				font_texture_data[2 * ((bitmap_offset_x + l) + (j + bitmap_offset_y) * font_tex_width) + 1] =
//						(l >= bmp->width || j >= bmp->rows)? 0 : bmp->buffer[l + bmp->width * j];*/
//			}
//		}

		/*  Set character properties.   */
		font->advance[i] = (float) (slot->advance.x >> 6);
		font->tex_x1[i] = (float) bitmap_offset_x / (float) font_tex_width;
		font->tex_x2[i] = (float) (bitmap_offset_x + bmp->width) / (float) font_tex_width;
		font->tex_y1[i] = (float) bitmap_offset_y / (float) font_tex_height;
		font->tex_y2[i] = (float) (bitmap_offset_y + bmp->rows) / (float) font_tex_height;
		font->width[i] = bmp->width;
		font->height[i] = bmp->rows;
		font->offset_x[i] = (float) slot->bitmap_left;
		font->offset_y[i] = (float) ((slot->metrics.horiBearingY - face->glyph->metrics.height) >> 6);
	}

	/*  Release resources.  */
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	/*  Generate signed distance field font.    */
	void *signedTexture;
	sbCreateSignDistanceField(font, font_texture_data, &signedTexture, font_tex_width, font_tex_height, &width, &height,
	                          4);
	assert(signedTexture);

	printf("%d:%d\n", width, height);

	/*  Allocate texture.   */
	sbCreateTexture(&font->texture, 0, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, signedTexture);

	/*  Free resources. */
	free(signedTexture);
	free(font_texture_data);
	return 1;
}

int sbDeleteFont(SBFont *font) {
	sbDeleteTexture(&font->texture);
	free(font->advance);
}


int sbCreateSignDistanceField(SBFont *SB_RESTRICT font, const void *SB_RESTRICT src, void **SB_RESTRICT dst,
                              int srcWidth, int srcHeight, int *SB_RESTRICT dstWidth,
                              int *SB_RESTRICT dstHeight, int downscale) {

	return 1;
}
