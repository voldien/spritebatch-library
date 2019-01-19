/**
	Common glsl macro functions
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

#extension GL_ARB_explicit_uniform_location : enable
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shader_image_size : enable
#extension GL_ARB_bindless_texture : enable
#extension GL_ARB_explicit_attrib_location : enable

//#extension GL_EXT_gpu_shader4 : enable

/*	Check if mobile OpenGL is used.	*/
#line 0
#ifdef GL_ES
    precision mediump float;
    precision mediump int;
#endif

/*	Translate fragment location decleration based on what version.	*/
#if defined(GL_ARB_explicit_attrib_location)
	#define FRAGLOCATION(x, vtype, name) layout(location = x) out vtype name
#elif __VERSION__ == 130
	#define FRAGLOCATION(x, vtype, name) out vtype name
#else
	#define FRAGLOCATION(x)
#endif

/*	Translate based on glsl version.	*/
#if defined(GL_ARB_explicit_attrib_location)
	#define ATTRIBUTE_IN(x) layout(location = x) in
	#define ATTRIBUTE_OUT(x) layout(location = x) out
#else
	#define ATTRIBUTE_IN(x) attribute
	#define ATTRIBUTE_OUT(x) attribute
#endif

/*	Translate based on glsl version.	*/
#if __VERSION__ > 120
	#define OUT out
	#define SMOOTH_OUT smooth out
	#define FLAT_OUT flat out
	#define IN in
	#define SMOOTH_IN smooth in
	#define FLAT_IN flat in
#else
	#define OUT varying
	#define SMOOTH_OUT smooth varying
	#define FLAT_IN flat varying
	#define IN varying
	#define SMOOTH_IN smooth varying
	#define FLAT_IN flat varying
#endif

uniform int numTextures;

#line 0