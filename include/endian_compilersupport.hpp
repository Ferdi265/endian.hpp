#ifndef _ENDIAN_COMPILERSUPPORT_HPP
#define _ENDIAN_COMPILERSUPPORT_HPP

#include <climits>

/// implementation limits
#if CHAR_BIT != 8
#error "endian.hpp only supports platforms with CHAR_BIT == 8"
#endif

/// portable packed structs
#if defined(_MSC_VER)
#define _ENDIAN_PACK(...) __pragma(pack(push, 1)) __VA_ARGS__ __pragma(pack(pop))
#else
#define _ENDIAN_PACK(...) __VA_ARGS__ __attribute__((packed))
#endif

/// endian detection logic from Boost.Endian
// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define _ENDIAN_NATIVE_BYTE_ORDER Little
#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define _ENDIAN_NATIVE_BYTE_ORDER Big
#elif defined(__BYTE_ORDER__) && defined(__ORDER_PDP_ENDIAN__) && __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
#define _ENDIAN_NATIVE_BYTE_ORDER PDP
#elif defined (__LITTLE_ENDIAN__)
#define _ENDIAN_NATIVE_BYTE_ORDER Little
#elif defined(__BIG_ENDIAN__)
#define _ENDIAN_NATIVE_BYTE_ORDER Big
#elif defined(_MSC_VER) || defined(__i386__) || defined(__x86_64)
#define _ENDIAN_NATIVE_BYTE_ORDER Little
#elif defined(ENDIAN_HPP_NATIVE_BYTE_ORDER)
#define _ENDIAN_NATIVE_BYTE_ORDER ENDIAN_HPP_NATIVE_BYTE_ORDER
#else
#error "endian.hpp failed to determine the native endianness"
#endif

#endif
