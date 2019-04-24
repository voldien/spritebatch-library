#include <cstddef>
#include <stdexcept>
#include <cassert>
#include<GL/glew.h>
#include"ProcedureTexture.h"
#include<texture.h>

//
void ProcedureTexture::createCheckTexture(int width, int height, int checkWidth, int checkheight, const float *color1,
                                          const float *color2, SBTexture *texture) {


	unsigned int x, y, Xpatter, Ypatter, bpp = 4;
	Xpatter = (width / checkWidth);    // pattern count in X
	Ypatter = (height / checkheight);    // pattern count in Y
	const size_t size = width * height * bpp;
	unsigned char *pbuf;


	if (!(width > 0 && height > 0))
		throw std::invalid_argument("width and height must be greater than 0");

	pbuf = (unsigned char *) malloc(size);
	assert(pbuf);


	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {

			float patternIndexX = (float) x / (float) checkWidth;
			float patternIndexY = (float) y / (float) checkheight;

			if ((int) patternIndexX % 2 == 0) {
				pbuf[x * height * 4 + y * 4] = (
						((int) patternIndexY % 2 == 0) ? 0 : 255);
				pbuf[x * height * 4 + y * 4 + 1] = (
						((int) patternIndexY % 2 == 0) ? 0 : 255);
				pbuf[x * height * 4 + y * 4 + 2] = (
						((int) patternIndexY % 2 == 0) ? 0 : 255);
				pbuf[x * height * 4 + y * 4 + 3] = 255;
			} else {
				pbuf[x * height * 4 + y * 4] = (
						((int) patternIndexY % 2 == 0) ? 255 : 0);
				pbuf[x * height * 4 + y * 4 + 1] = (
						((int) patternIndexY % 2 == 0) ? 255 : 0);
				pbuf[x * height * 4 + y * 4 + 2] = (
						((int) patternIndexY % 2 == 0) ? 255 : 0);
				pbuf[x * height * 4 + y * 4 + 3] = 255;
			}
			continue;
		}    // iteration of X
		continue;
	}    // iteration of Y

	assert(sbCreateTexture(texture, GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pbuf));
	free(pbuf);
}

void ProcedureTexture::createCircleTexture(int width, int height, const float *color, SBTexture *texture) {

	int x, y;
	const size_t bpp = 4;
	const size_t size = width * height * bpp;
	unsigned char *pbuf;

	if (!(width > 0 && height > 0))
		throw std::invalid_argument("width and height must be greater than 0");

	pbuf = (unsigned char *) malloc(size);
	assert(pbuf);


	

	assert(sbCreateTexture(texture, GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, pbuf));
}
