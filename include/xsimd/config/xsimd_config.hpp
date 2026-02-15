/***************************************************************************
 * Copyright (c) Johan Mabille, Sylvain Corlay, Wolf Vollprecht and         *
 * Martin Renou                                                             *
 * Copyright (c) QuantStack                                                 *
 * Copyright (c) Serge Guelton                                              *
 *                                                                          *
 * Distributed under the terms of the BSD 3-Clause License.                 *
 *                                                                          *
 * The full license is in the file LICENSE, distributed with this software. *
 ****************************************************************************/

#ifndef XSIMD_CONFIG_HPP
#define XSIMD_CONFIG_HPP

#define XSIMD_VERSION_MAJOR 14
#define XSIMD_VERSION_MINOR 0
#define XSIMD_VERSION_PATCH 0

#if defined(__GNUC__) && defined(__BYTE_ORDER__)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define XSIMD_LITTLE_ENDIAN
#endif
#elif defined(_WIN32)
// We can safely assume that Windows is always little endian
#define XSIMD_LITTLE_ENDIAN
#elif defined(i386) || defined(i486) || defined(intel) || defined(x86) || defined(i86pc) || defined(__alpha) || defined(__osf__)
#define XSIMD_LITTLE_ENDIAN
#endif

/**
 * high level free functions
 *
 * @defgroup xsimd_config_macro Instruction Set Detection
 */

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 1 if runtime-checkable extensions should be optionally available when possible, 0 otherwise.
 */
#ifndef XSIMD_OPTIONAL_ALL
#define XSIMD_OPTIONAL_ALL 0
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 1 if SSE/FMA/AVX extensions are optionally available on x86/x64, 0 otherwise
 */
#ifndef XSIMD_OPTIONAL_X86
#if XSIMD_OPTIONAL_ALL && (defined(__i386__) || defined(__x86_64__))
#define XSIMD_OPTIONAL_X86 1
#else
#define XSIMD_OPTIONAL_X86 0
#endif
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 1 if NEON(64) extensions are optionally available on ARM, 0 otherwise
 */
#ifndef XSIMD_OPTIONAL_ARM
#if XSIMD_OPTIONAL_ALL && (defined(__arm__) || defined(__aarch64__))
#define XSIMD_OPTIONAL_ARM 1
#else
#define XSIMD_OPTIONAL_ARM 0
#endif
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if SSE2 is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __SSE2__
#define XSIMD_WITH_SSE2 2
#else
#define XSIMD_WITH_SSE2 XSIMD_OPTIONAL_X86
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if SSE3 is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __SSE3__
#define XSIMD_WITH_SSE3 2
#else
#define XSIMD_WITH_SSE3 XSIMD_OPTIONAL_X86
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if SSSE3 is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __SSSE3__
#define XSIMD_WITH_SSSE3 2
#else
#define XSIMD_WITH_SSSE3 XSIMD_OPTIONAL_X86
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if SSE4.1 is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __SSE4_1__
#define XSIMD_WITH_SSE4_1 2
#else
#define XSIMD_WITH_SSE4_1 XSIMD_OPTIONAL_X86
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if SSE4.2 is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __SSE4_2__
#define XSIMD_WITH_SSE4_2 2
#else
#define XSIMD_WITH_SSE4_2 XSIMD_OPTIONAL_X86
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if AVX is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __AVX__
#define XSIMD_WITH_AVX 2
#else
#define XSIMD_WITH_AVX XSIMD_OPTIONAL_X86
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if AVX2 is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __AVX2__
#define XSIMD_WITH_AVX2 2
#else
#define XSIMD_WITH_AVX2 XSIMD_OPTIONAL_X86
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if AVXVNNI is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __AVXVNNI__
#define XSIMD_WITH_AVXVNNI 2
#else
#define XSIMD_WITH_AVXVNNI XSIMD_OPTIONAL_X86
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if FMA3 for SSE is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __FMA__

#if defined(__SSE__)
#ifndef XSIMD_WITH_FMA3_SSE // Leave the opportunity to manually disable it, see #643
#define XSIMD_WITH_FMA3_SSE 2
#endif
#else

#if XSIMD_WITH_FMA3_SSE > 1
#error "Manually set XSIMD_WITH_FMA3_SSE is incompatible with current compiler flags"
#endif

#define XSIMD_WITH_FMA3_SSE XSIMD_OPTIONAL_X86
#endif

#else

#if XSIMD_WITH_FMA3_SSE > 1
#error "Manually set XSIMD_WITH_FMA3_SSE is incompatible with current compiler flags"
#endif

#define XSIMD_WITH_FMA3_SSE XSIMD_OPTIONAL_X86
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if FMA3 for AVX is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __FMA__

#if defined(__AVX__)
#ifndef XSIMD_WITH_FMA3_AVX // Leave the opportunity to manually disable it, see #643
#define XSIMD_WITH_FMA3_AVX 2
#endif
#else

#if XSIMD_WITH_FMA3_AVX > 1
#error "Manually set XSIMD_WITH_FMA3_AVX is incompatible with current compiler flags"
#endif

#define XSIMD_WITH_FMA3_AVX XSIMD_OPTIONAL_X86
#endif

#if defined(__AVX2__)
#ifndef XSIMD_WITH_FMA3_AVX2 // Leave the opportunity to manually disable it, see #643
#define XSIMD_WITH_FMA3_AVX2 2
#endif
#else

#if XSIMD_WITH_FMA3_AVX2 > 1
#error "Manually set XSIMD_WITH_FMA3_AVX2 is incompatible with current compiler flags"
#endif

#define XSIMD_WITH_FMA3_AVX2 XSIMD_OPTIONAL_X86
#endif

#else

#if XSIMD_WITH_FMA3_AVX > 1
#error "Manually set XSIMD_WITH_FMA3_AVX is incompatible with current compiler flags"
#endif

#if XSIMD_WITH_FMA3_AVX2 > 1
#error "Manually set XSIMD_WITH_FMA3_AVX2 is incompatible with current compiler flags"
#endif

#define XSIMD_WITH_FMA3_AVX XSIMD_OPTIONAL_X86
#define XSIMD_WITH_FMA3_AVX2 XSIMD_OPTIONAL_X86

#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if FMA4 is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __FMA4__
#define XSIMD_WITH_FMA4 2
#else
#define XSIMD_WITH_FMA4 XSIMD_OPTIONAL_X86
#endif

// AVX512 instructions are supported starting with gcc 6
// see https://www.gnu.org/software/gcc/gcc-6/changes.html
// Check clang first, newer clang always defines __GNUC__ = 4
#if !(defined(__clang__) && __clang_major__ >= 6) && defined(__GNUC__) && __GNUC__ < 6
#define XSIMD_ALLOWED_AVX512 0
#define XSIMD_OPTIONAL_AVX512 0
#else
#define XSIMD_ALLOWED_AVX512 1
#define XSIMD_OPTIONAL_AVX512 XSIMD_OPTIONAL_X86
#if __GNUC__ == 6
#define XSIMD_AVX512_SHIFT_INTRINSICS_IMM_ONLY 1
#endif
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if AVX512F is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __AVX512F__
#define XSIMD_WITH_AVX512F XSIMD_ALLOWED_AVX512
#else
#define XSIMD_WITH_AVX512F XSIMD_OPTIONAL_AVX512
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if AVX512CD is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __AVX512CD__
#define XSIMD_WITH_AVX512CD XSIMD_ALLOWED_AVX512
#else
#define XSIMD_WITH_AVX512CD XSIMD_OPTIONAL_AVX512
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if AVX512DQ is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __AVX512DQ__
#define XSIMD_WITH_AVX512DQ XSIMD_ALLOWED_AVX512
#else
#define XSIMD_WITH_AVX512DQ XSIMD_OPTIONAL_AVX512
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if AVX512BW is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __AVX512BW__
#define XSIMD_WITH_AVX512BW XSIMD_ALLOWED_AVX512
#else
#define XSIMD_WITH_AVX512BW XSIMD_OPTIONAL_AVX512
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if AVX512ER is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __AVX512ER__
#define XSIMD_WITH_AVX512ER XSIMD_ALLOWED_AVX512
#else
#define XSIMD_WITH_AVX512ER XSIMD_OPTIONAL_AVX512
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if AVX512PF is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __AVX512PF__
#define XSIMD_WITH_AVX512PF XSIMD_ALLOWED_AVX512
#else
#define XSIMD_WITH_AVX512PF XSIMD_OPTIONAL_AVX512
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if AVX512IFMA is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __AVX512IFMA__
#define XSIMD_WITH_AVX512IFMA XSIMD_ALLOWED_AVX512
#else
#define XSIMD_WITH_AVX512IFMA XSIMD_OPTIONAL_AVX512
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if AVX512VBMI is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __AVX512VBMI__
#define XSIMD_WITH_AVX512VBMI XSIMD_ALLOWED_AVX512
#else
#define XSIMD_WITH_AVX512VBMI XSIMD_OPTIONAL_AVX512
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if AVX512VBMI2 is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __AVX512VBMI2__
#define XSIMD_WITH_AVX512VBMI2 XSIMD_ALLOWED_AVX512
#else
#define XSIMD_WITH_AVX512VBMI2 XSIMD_OPTIONAL_AVX512
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if AVX512VNNI is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#ifdef __AVX512VNNI__

#if XSIMD_WITH_AVX512VBMI2
#define XSIMD_WITH_AVX512VNNI_AVX512VBMI2 XSIMD_ALLOWED_AVX512
#define XSIMD_WITH_AVX512VNNI_AVX512BW XSIMD_ALLOWED_AVX512
#else
#define XSIMD_WITH_AVX512VNNI_AVX512VBMI2 XSIMD_OPTIONAL_AVX512
#define XSIMD_WITH_AVX512VNNI_AVX512BW XSIMD_ALLOWED_AVX512
#endif

#else

#define XSIMD_WITH_AVX512VNNI_AVX512VBMI2 XSIMD_OPTIONAL_AVX512
#define XSIMD_WITH_AVX512VNNI_AVX512BW XSIMD_OPTIONAL_AVX512

#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if NEON64 is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#if defined(__aarch64__) || defined(_M_ARM64)
#define XSIMD_WITH_NEON64 2
#else
#define XSIMD_WITH_NEON64 XSIMD_OPTIONAL_ARM
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if NEON is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#if (defined(__ARM_NEON) && __ARM_ARCH >= 7) || XSIMD_WITH_NEON64 > 1
#define XSIMD_WITH_NEON 2
#else
#define XSIMD_WITH_NEON XSIMD_OPTIONAL_ARM
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if i8mm neon64 extension is available at compile-time, 1 if available with a runtime check, 0 otherwise.
 */
#if defined(__ARM_FEATURE_MATMUL_INT8)
#define XSIMD_WITH_I8MM_NEON64 2
#else
#define XSIMD_WITH_I8MM_NEON64 XSIMD_OPTIONAL_ARM
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if SVE is available and bit width is pre-set at compile-time, to 0 otherwise.
 */
#if defined(__ARM_FEATURE_SVE) && defined(__ARM_FEATURE_SVE_BITS) && __ARM_FEATURE_SVE_BITS > 0
#define XSIMD_WITH_SVE 2
#define XSIMD_SVE_BITS __ARM_FEATURE_SVE_BITS
#else
#define XSIMD_WITH_SVE 0
#define XSIMD_SVE_BITS 0
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if RVV is available and bit width is pre-set at compile-time, to 0 otherwise.
 */
#if defined(__riscv_vector) && defined(__riscv_v_fixed_vlen) && __riscv_v_fixed_vlen > 0
#define XSIMD_WITH_RVV 2
#define XSIMD_RVV_BITS __riscv_v_fixed_vlen
#else
#define XSIMD_WITH_RVV 0
#define XSIMD_RVV_BITS 0
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if WebAssembly SIMD is available at compile-time, 0 otherwise.
 */
#ifdef __EMSCRIPTEN__
#define XSIMD_WITH_WASM 2
#else
#define XSIMD_WITH_WASM 0
#endif

/**
 * @ingroup xsimd_config_macro
 *
 * Set to 2 if VMX with VSX extension is available at compile-time, 0 otherwise.
 */
#if defined(__VEC__) && defined(__VSX__)
#define XSIMD_WITH_VSX 2
#else
#define XSIMD_WITH_VSX 0
#endif

// Workaround for MSVC compiler
#ifdef _MSC_VER

#if XSIMD_WITH_AVX512

#undef XSIMD_WITH_AVX2
#define XSIMD_WITH_AVX2 2

#endif

#if XSIMD_WITH_AVX2

#undef XSIMD_WITH_AVX
#define XSIMD_WITH_AVX 2

#undef XSIMD_WITH_FMA3_AVX
#define XSIMD_WITH_FMA3_AVX 2

#undef XSIMD_WITH_FMA3_AVX2
#define XSIMD_WITH_FMA3_AVX2 2

#endif

#if XSIMD_WITH_AVX

#undef XSIMD_WITH_SSE4_2
#define XSIMD_WITH_SSE4_2 2

#endif

#if XSIMD_WITH_SSE4_2

#undef XSIMD_WITH_SSE4_1
#define XSIMD_WITH_SSE4_1 2

#endif

#if XSIMD_WITH_SSE4_1

#undef XSIMD_WITH_SSSE3
#define XSIMD_WITH_SSSE3 2

#endif

#if XSIMD_WITH_SSSE3

#undef XSIMD_WITH_SSE3
#define XSIMD_WITH_SSE3 2

#endif

#if ((defined(_M_AMD64) || defined(_M_X64)) && !defined(_M_ARM64EC)) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)
#undef XSIMD_WITH_SSE2
#define XSIMD_WITH_SSE2 2
#elif XSIMD_WITH_SSE3
#undef XSIMD_WITH_SSE2
#define XSIMD_WITH_SSE2 XSIMD_WITH_SSE3
#endif

#endif

#if !XSIMD_WITH_SSE2 && !XSIMD_WITH_SSE3 && !XSIMD_WITH_SSSE3 && !XSIMD_WITH_SSE4_1 && !XSIMD_WITH_SSE4_2 && !XSIMD_WITH_AVX && !XSIMD_WITH_AVX2 && !XSIMD_WITH_AVXVNNI && !XSIMD_WITH_FMA3_SSE && !XSIMD_WITH_FMA4 && !XSIMD_WITH_FMA3_AVX && !XSIMD_WITH_FMA3_AVX2 && !XSIMD_WITH_AVX512F && !XSIMD_WITH_AVX512CD && !XSIMD_WITH_AVX512DQ && !XSIMD_WITH_AVX512BW && !XSIMD_WITH_AVX512ER && !XSIMD_WITH_AVX512PF && !XSIMD_WITH_AVX512IFMA && !XSIMD_WITH_AVX512VBMI && !XSIMD_WITH_AVX512VBMI2 && !XSIMD_WITH_NEON && !XSIMD_WITH_NEON64 && !XSIMD_WITH_SVE && !XSIMD_WITH_RVV && !XSIMD_WITH_WASM && !XSIMD_WITH_VSX && !XSIMD_WITH_EMULATED
#define XSIMD_NO_SUPPORTED_ARCHITECTURE
#endif

#endif
