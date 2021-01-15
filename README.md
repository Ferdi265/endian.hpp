# `endian.hpp`

A small header-only C++ endianness library with `constexpr` support for C++14 and later.

## Overview

All types and functions are defined in the `endian` namespace.

The following types are defined by this library:

```c++
/// identifiers for different byte orders
enum class ByteOrder {
    Little,
    Big,
    PDP,

    Network = Big,
    Native = /* implementation-defined */
};

/// convert an integral type between byte orders
template <ByteOrder to, ByteOrder from, typename T>
constexpr T convert(T t);

/// convert an integral type to network byte order from native byte order
template <typename T>
constexpr T hton(T t);

/// convert an integral type to native byte order from network byte order
template <typename T>
constexpr T ntoh(T t);

/// transparently wrap an integral type of the specified byte order
///
/// endian_int is a packed struct to simplify use in network data structures
template <ByteOrder endian, typename T>
struct endian_int; /* packed */

/// convenience type aliases
using little_int8_t = endian_int<ByteOrder::Little, int8_t>;
using little_int16_t = endian_int<ByteOrder::Little, int16_t>;
using little_int32_t = endian_int<ByteOrder::Little, int32_t>;
using little_int64_t = endian_int<ByteOrder::Little, int64_t>;
using little_uint8_t = endian_int<ByteOrder::Little, uint8_t>;
using little_uint16_t = endian_int<ByteOrder::Little, uint16_t>;
using little_uint32_t = endian_int<ByteOrder::Little, uint32_t>;
using little_uint64_t = endian_int<ByteOrder::Little, uint64_t>;
using big_int8_t = endian_int<ByteOrder::Big, int8_t>;
using big_int16_t = endian_int<ByteOrder::Big, int16_t>;
using big_int32_t = endian_int<ByteOrder::Big, int32_t>;
using big_int64_t = endian_int<ByteOrder::Big, int64_t>;
using big_uint8_t = endian_int<ByteOrder::Big, uint8_t>;
using big_uint16_t = endian_int<ByteOrder::Big, uint16_t>;
using big_uint32_t = endian_int<ByteOrder::Big, uint32_t>;
using big_uint64_t = endian_int<ByteOrder::Big, uint64_t>;
using pdp_int8_t = endian_int<ByteOrder::PDP, int8_t>;
using pdp_int16_t = endian_int<ByteOrder::PDP, int16_t>;
using pdp_int32_t = endian_int<ByteOrder::PDP, int32_t>;
using pdp_int64_t = endian_int<ByteOrder::PDP, int64_t>;
using pdp_uint8_t = endian_int<ByteOrder::PDP, uint8_t>;
using pdp_uint16_t = endian_int<ByteOrder::PDP, uint16_t>;
using pdp_uint32_t = endian_int<ByteOrder::PDP, uint32_t>;
using pdp_uint64_t = endian_int<ByteOrder::PDP, uint64_t>;
using net_int8_t = endian_int<ByteOrder::Network, int8_t>;
using net_int16_t = endian_int<ByteOrder::Network, int16_t>;
using net_int32_t = endian_int<ByteOrder::Network, int32_t>;
using net_int64_t = endian_int<ByteOrder::Network, int64_t>;
using net_uint8_t = endian_int<ByteOrder::Network, uint8_t>;
using net_uint16_t = endian_int<ByteOrder::Network, uint16_t>;
using net_uint32_t = endian_int<ByteOrder::Network, uint32_t>;
using net_uint64_t = endian_int<ByteOrder::Network, uint64_t>;
```

## Limitations

This library depends on C++14 features for `constexpr` support. It's most likely
possible to rewrite the functions to compile under C++11 as well.

This library only works on systems with `CHAR_BIT == 8`.

The native endianness is detected automatically. If it cannot be detected,
`ENDIAN_HPP_NATIVE_BYTE_ORDER` can be defined to one of `Little`, `Big`, `PDP`,
or `Network` to set the native endianness manually.
