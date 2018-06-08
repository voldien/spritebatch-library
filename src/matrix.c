#include"matrix.h"

void sbMatrix3x3Translation(float f_mat2[3][3], float camerapos[2]) {
	f_mat2[0][0] = 1;
	f_mat2[1][0] = 0.0f;
	f_mat2[2][0] = camerapos[0];
	f_mat2[0][1] = 0.0f;
	f_mat2[1][1] = 1;
	f_mat2[2][1] = camerapos[0];
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

void sbMatrix3x3MultiMatrix3x3(float lf_mat4[3][3], float rf_mat4[3][3], float outf_mat4[3][3]) {
	outf_mat4[0][0] = lf_mat4[0][0] * rf_mat4[0][0] + lf_mat4[1][0] * rf_mat4[1][0] + lf_mat4[2][0] * rf_mat4[2][0];
	outf_mat4[1][0] = lf_mat4[0][0] * rf_mat4[0][1] + lf_mat4[1][0] * rf_mat4[1][1] + lf_mat4[2][0] * rf_mat4[2][1];
	outf_mat4[2][0] = lf_mat4[0][0] * rf_mat4[0][2] + lf_mat4[1][0] * rf_mat4[1][2] + lf_mat4[2][0] * rf_mat4[2][2];

	outf_mat4[0][1] = lf_mat4[0][1] * rf_mat4[0][0] + lf_mat4[1][1] * rf_mat4[1][0] + lf_mat4[2][1] * rf_mat4[2][0];
	outf_mat4[1][1] = lf_mat4[0][1] * rf_mat4[0][1] + lf_mat4[1][1] * rf_mat4[1][1] + lf_mat4[2][1] * rf_mat4[2][1];
	outf_mat4[2][1] = lf_mat4[0][1] * rf_mat4[0][2] + lf_mat4[1][1] * rf_mat4[1][2] + lf_mat4[2][1] * rf_mat4[2][2];

	outf_mat4[0][2] = lf_mat4[0][2] * rf_mat4[0][0] + lf_mat4[1][2] * rf_mat4[1][0] + lf_mat4[2][2] * rf_mat4[2][0];
	outf_mat4[1][2] = lf_mat4[0][2] * rf_mat4[0][1] + lf_mat4[1][2] * rf_mat4[1][1] + lf_mat4[2][2] * rf_mat4[2][1];
	outf_mat4[2][2] = lf_mat4[0][2] * rf_mat4[0][2] + lf_mat4[1][2] * rf_mat4[1][2] + lf_mat4[2][2] * rf_mat4[2][2];
}
