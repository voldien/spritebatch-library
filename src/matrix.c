#include"matrix.h"
#include<math.h>

void sbMatrix3x3Translation(float f_mat2[3][3], float pos[2]) {
	f_mat2[0][0] = 1.0f;
	f_mat2[1][0] = 0.0f;
	f_mat2[2][0] = pos[0];
	f_mat2[0][1] = 0.0f;
	f_mat2[1][1] = 1.0f;
	f_mat2[2][1] = pos[1];
	f_mat2[0][2] = 0.0f;
	f_mat2[1][2] = 0.0f;
	f_mat2[2][2] = 1.0f;
}

void sbMatrix3x3Scale(float f_mat2[3][3], float scale) {
	f_mat2[0][0] = scale;
	f_mat2[1][0] = 0.0f;
	f_mat2[2][0] = 0.0f;
	f_mat2[0][1] = 0.0f;
	f_mat2[1][1] = scale;
	f_mat2[2][1] = 0.0f;
	f_mat2[0][2] = 0.0f;
	f_mat2[1][2] = 0.0f;
	f_mat2[2][2] = 1.0f;
}

void sbMatrix3x3Rotation(float f_mat3[3][3], float rotation){
	f_mat3[0][0] = cosf(rotation);
	f_mat3[1][0] = -sinf(rotation);
	f_mat3[2][0] = 0.0f;
	f_mat3[0][1] = sinf(rotation);
	f_mat3[1][1] = cosf(rotation);
	f_mat3[2][1] = 0.0f;
	f_mat3[0][2] = 0.0f;
	f_mat3[1][2] = 0.0f;
	f_mat3[2][2] = 1.0f;
}

void sbMatrix3x3MultiMatrix3x3(const float larg[3][3], const float rarg[3][3], float outf[3][3]) {
	const float a00 = larg[0][0], a01 = larg[0][1], a02 = larg[0][2],
			a10 = larg[1][0], a11 = larg[1][1], a12 = larg[1][2],
			a20 = larg[2][0], a21 = larg[2][1], a22 = larg[2][2],
			b00 = rarg[0][0], b01 = rarg[0][1], b02 = rarg[0][2],
			b10 = rarg[1][0], b11 = rarg[1][1], b12 = rarg[1][2],
			b20 = rarg[2][0], b21 = rarg[2][1], b22 = rarg[2][2];

	outf[0][0] = b00 * a00 + b01 * a10 + b02 * a20;
	outf[0][1] = b00 * a01 + b01 * a11 + b02 * a21;
	outf[0][2] = b00 * a02 + b01 * a12 + b02 * a22;

	outf[1][0] = b10 * a00 + b11 * a10 + b12 * a20;
	outf[1][1] = b10 * a01 + b11 * a11 + b12 * a21;
	outf[1][2] = b10 * a02 + b11 * a12 + b12 * a22;

	outf[2][0] = b20 * a00 + b21 * a10 + b22 * a20;
	outf[2][1] = b20 * a01 + b21 * a11 + b22 * a21;
	outf[2][2] = b20 * a02 + b21 * a12 + b22 * a22;
}
