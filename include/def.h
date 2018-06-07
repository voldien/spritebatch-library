/**
	Simple Sprite batch implementation using OpenGL.
	Copyright (C) 2017  Valdemar Lindberg

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
#ifndef _SB_DEF_H_
#define _SB_DEF_H_ 1
#include<limits.h>

/**
 *	Compiler version macro.
 */
#define SB_COMPILER_VERSION(major, minor, revision, state) SB_STR(major)SB_TEXT(".")SB_STR(minor)SB_TEXT(".")SB_STR(revision)

/**
 *    Compiler
 */
#ifdef _MSC_VER 	/*	Visual Studio C++ Compiler.	*/
	#define SB_VC
	#define SB_COMPILER 1
	#if _MSC_VER >= 1900
		#define SB_V13 _MSC_VER
	#elif _MSC_VER >= 1800
		#define SB_V12 _MSC_VER
	#elif _MSC_VER >= 1700
		#define SB_VC11 _MSC_VER
	#elif _MSC_VER >= 1600
		#define SB_VC10 _MSC_VER
	#elif _MSC_VER >= 1500
		#define SB_VC9 _MSC_VER
	#elif _MSC_VER >= 1400
		#define SB_VC8 _MSC_VER
	#elif _MSC_VER >= 1300
		#define SB_VC7 _MSC_VER
	#else
		#define SB_VC6 _MSC_VER
	#endif
    	#pragma warning(disable : 4201)
	#define SB_COMPILER_NAME "Visual Studio C++/C"

#elif defined(__clang__)  || defined(__llvm__)           /*  LLVM, clang   */
    #define SB_LLVM 1
	#define SB_CLANG 1
	#define SB_COMPILER 5
	#define SB_COMPILER_NAME "LLVM/CLANG"
	#define SB_COMPILER_MAJOR_VERSION __clang_major__
	#define SB_COMPILER_MINOR_VERSION __clang_minor__

#elif defined(__GNUC__) || defined(__SNC__) || defined( __GNUC_MINOR__)	/*  GNU C Compiler*/
	#define SB_GNUC 1
	#define SB_COMPILER 2
	#define SB_COMPILER_NAME "GNU C"
	#define SB_COMPILER_MAJOR_VERSION __clang_major__
	#define SB_COMPILER_MINOR_VERSION __clang_minor__

#elif defined(__GNUG__) /*  GNU C++ Compiler*/
	#define SB_GNUC 2

#elif defined(__ghs__)		/* GHS	*/
	#define SB_GHS 1
	#define SB_COMPILER 3

#elif defined(__HP_cc) || defined(__HP_aCC)			/*	*/

#elif defined(__PGI)			/*	*/

#elif defined(__ICC) || defined(__INTEL_COMPILER) /*  Intel Compiler  */
	#define SB_INTEL
	#define SB_COMPILER 4
	#define SB_COMPILER_NAME "Intel C++"

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)

#else
	#error Unsupported Compiler.
#endif

/**
 *	Platform define
 *	Architecture!
 */
#ifdef SB_VC
	#if defined(_M_IX86) || defined(_WIN32)
		#define SB_X86                          /**/
		#define SB_X32                          /**/
		#define SB_WIN32                        /**/
		#define SB_WINDOWS                      /**/
	#elif defined(_M_X64) || defined(_WIN64)
		#define SB_X64                          /**/
		#define SB_WIN64                        /**/
		#define SB_WINDOWS                      /**/
	#elif defined(_M_PPC)
		#define SB_PPC                          /**/
		#define SB_X360                         /**/
		#define SB_VMX                          /**/
	#elif defined(_M_ARM)
		#define SB_ARM                          /**/
		#define SB_ARM_NEON                     /**/
	#endif
#elif defined(SB_GNUC) || defined(SB_CLANG)
	#ifdef __CELLOS_LV2__   /**/
        #define SB_PS3                          /*	playstation 3*/
	#elif defined(__arm__)	/**/
		#define SB_ARM
        #define SB_PSP2                         /*	playstation portable 2*/
        #define SB_RAS_PI                       /*	rasberry pi	*/
	#endif
	#if defined(_WIN32) /**  Window*/
		#define SB_X86
		#define SB_WINDOWS                      /**/
	#endif
	#if ( defined(__linux__) || defined(__linux) || defined(linux) ) && (!(__ANDROID__) || !(ANDROID))/* Linux */
		#define SB_LINUX 1                       /**/
		#if defined(__amd64) || defined(__x86_64__) || defined(__i386__)
            #define SB_X86 1
			#define SB_X86_64 1
		#endif
		#if defined(__arm__)
              #define EX_ARM 1
        #endif

	#elif defined (ANDROID) || defined(__ANDROID__) || __ANDROID_API__ > 9  /** Android */
        #include<jni.h>
		#define SB_ANDROID 1
		/*  android Architecture*/
        #if defined(__arm__)
			#define SB_ARM 1
		  #if defined(__ARM_ARCH_7A__)
			#if defined(__ARM_NEON__)
			  #if defined(__ARM_PCS_VFP)
				#define ABI "armeabi-v7a/NEON (hard-float)"
			  #else
				#define ABI "armeabi-v7a/NEON"
			  #endif
			#else
			  #if defined(__ARM_PCS_VFP)
				#define ABI "armeabi-v7a (hard-float)"
			  #else
				#define ABI "armeabi-v7a"
			  #endif
			#endif
		  #else
		   #define ABI "armeabi"
		  #endif
		#elif defined(__i386__)
		   #define ABI "x86"
		#elif defined(__x86_64__)
		   #define ABI "x86_64"
		#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
		   #define ABI "mips64"
		#elif defined(__mips__)
		   #define ABI "mips"
		#elif defined(__aarch64__)
		   #define ABI "arm64-v8a"
		#else
		   #define ABI "unknown"
		#endif

	#elif defined (__APPLE__)   /*  Apple product   */
		#define SB_APPLE 1
		#if defined(__arm__)
			#define SB_APPLE_IOS    /*  Apple iphone/ipad OS    */
		#elif defined(MACOSX) || defined(macintosh) || defined(Macintosh)
			#define EX_MAC 1
		#endif
	#elif defined(__CYGWIN) 	/**/
		#define SB_CYGWIN 1
		#define SB_LINUX 1
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)   /*  BSD*/
		#define SB_BSD
    	#elif defined(__llvm__) || defined(__clang__)   	/*  llvm    */
        	#define SB_LLVM 1
	#endif

#elif defined(__ICC) || defined(__INTEL_COMPILER)


#else
	#error  Unsupported architecture!   /*  No architecture support implicitly. remove this line to compile anyway*/
#endif

#if defined(__native_client__)	/*	nacl google	*/
	#define SB_NACL 1
#endif
#if defined(__pnacl__)          /* portable nacl google */
	#define SB_PNACL 1
#endif
#if defined(__unix__) || defined(__unix) || defined(unix)	/*  Unix    */
	#   define SB_UNIX 1
#endif

/**
 *	Calling function convention.
 */
#ifdef SB_WINDOWS	        /** Windows Calling Convention.*/
	#define SBAPIENTRY     __cdecl
	#define SBAPIFASTENTRY __fastcall
	#define SBAPITHISENTRY __thiscall
	#define SBAPISTDENTRY  __stdcall
#elif defined(SB_ANDROID)   /** Android Calling Convention	*/
    #define SBAPIENTRY JNICALL
    #define SBAPIFASTENTRY JNICALL
    #define SBAPITHISENTRY JNICALL
    #define SBAPISTDENTRY JNICALL
#else
#   if !defined(__cdecl) && ( defined(SB_GNUC)  || defined(SB_CLANG) )
        #define __cdecl  __attribute__ ((__cdecl__))
        #define __stdcall  __attribute__ ((stdcall))
		#define __fastcall __attribute__((fastcall))
#   endif
	#define SBAPIENTRY     __cdecl
	#define SBAPISTDENTRY  __stdcall
	#define SBAPIFASTENTRY __fastcall
#endif

/**
 *	force inline.
 */
#if defined(SB_MSVC)
	#define SB_ALWAYS_INLINE __forceinline
#elif defined(SB_GNUC)
	#define SB_ALWAYS_INLINE inline __attribute__((always_inline))
#elif defined(SB_GNUC) || defined(SB_GHS)
	#define SB_ALWAYS_INLINE inline __attribute__((always_inline))
#else
	/*#pragma message("Warning: You'd need to add SB_ALWAYS_INLINE for this compiler.")*/
#endif

/**
 *	Alignment of data and vectors.
 */
#if defined(SB_GNUC) || defined(SB_CLANG)
	#define SB_ALIGN(alignment) __attribute__ ((aligned(alignment)))
	#define SB_VECTORALIGN(alignment) __attribute__ ((__vector_size__ (alignment), __may_alias__))
	#define SB_VECTORALIGNI(alignment) __attribute__ ((__vector_size__ (alignment)))
#elif defined(SB_VC)
	#define SB_ALIGN(alignment) __attribute__ ((aligned(alignment)))
	#define SB_VECTORALIGN(alignment) __attribute__ ((__vector_size__ (alignment), __may_alias__))
	#define SB_VECTORALIGNI(alignment) __attribute__ ((__vector_size__ (alignment)))
#endif

/**
 *	Restrict decleration.
 */
#ifndef SB_RESTRICT
	#if defined(SB_GNUC)
		#define SB_RESTRICT __restrict__
	#elif defined(SB_CLANG)
		#define SB_RESTRICT __restrict
	#elif defined(SB_VC)
		#define SB_RESTRICT __declspec(restrict)
	#else
		#define SB_RESTRICT
	#endif
#endif


/**
 *	library declaration.
 */
#if defined(SB_GNUC) || defined(SB_CLANG)
	#if defined(SB_UNIX)
		#define SBDECLSPEC	 __attribute__((__visibility__ ("default")))
	#else
		#define SBDECLSPEC
	#endif
#elif defined(SB_VC)
	#if SB_INTERNAL
		#define SBDECLSPEC __declspec(dllexport)
	#else
		#define SBDECLSPEC __declspec(dllimport)
	#endif
#endif

#endif
