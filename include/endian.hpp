#ifndef _ENDIAN_HPP
#define _ENDIAN_HPP

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include "endian_compilersupport.hpp"

namespace endian {

/// identifiers for different byte orders
enum class ByteOrder {
    Little = 0,
    Big = 1,
    PDP = 2,

    Network = Big,
    Native = _ENDIAN_NATIVE_BYTE_ORDER
};

/// convert an integral type between byte orders
template <ByteOrder to, ByteOrder from, typename T>
constexpr T convert(T t);

/// convert an integral type to network byte order from native byte order
template <typename T>
constexpr T hton(T t) {
    return convert<ByteOrder::Network, ByteOrder::Native, T>(t);
}

/// convert an integral type to native byte order from network byte order
template <typename T>
constexpr T ntoh(T t) {
    return convert<ByteOrder::Native, ByteOrder::Network, T>(t);
}

/// transparently wrap an integral type of the specified byte order
template <ByteOrder endian, typename T>
struct endian_int;

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

/// implementation details below

namespace detail {
    /// interface

    /// convert a type T to a canonical unsigned type for its size (e.g. uint8_t for size 1)
    template <typename T, size_t size = sizeof (T)>
    struct canonicalize_integral;

    /// swap byte order in the integer
    template <typename T, typename C = typename canonicalize_integral<T>::type, size_t size = sizeof (T)>
    struct byte_swap;

    /// swap intra-word order in the integer
    template <typename T, typename C = typename canonicalize_integral<T>::type, size_t size = sizeof (T)>
    struct pdp_swap;

    /// convert an integer to little endian from a specific byte order
    template <ByteOrder from, typename T>
    struct to_little;

    /// convert an integer to a specific byte order from little endian
    template <ByteOrder to, typename T>
    struct from_little;

    /// implementation

    template <typename T>
    struct canonicalize_integral<T, 1> {
        using type = uint8_t;
    };

    template <typename T>
    struct canonicalize_integral<T, 2> {
        using type = uint16_t;
    };

    template <typename T>
    struct canonicalize_integral<T, 4> {
        using type = uint32_t;
    };

    template <typename T>
    struct canonicalize_integral<T, 8> {
        using type = uint64_t;
    };

    template <typename T, typename C>
    struct byte_swap<T, C, 1> {
        constexpr static T convert(T t) {
            return t;
        }
    };

    template <typename T, typename C>
    struct byte_swap<T, C, 2> {
        constexpr static T convert(T t) {
            C c = static_cast<C>(t);
            return static_cast<T>(
                ((c & UINT16_C(0xff00)) >> 8) |
                ((c & UINT16_C(0x00ff)) << 8)
            );
        }
    };

    template <typename T, typename C>
    struct byte_swap<T, C, 4> {
        constexpr static T convert(T t) {
            C c = static_cast<C>(t);
            return static_cast<T>(
                ((c & UINT32_C(0xff000000)) >> 24) |
                ((c & UINT32_C(0x00ff0000)) >>  8) |
                ((c & UINT32_C(0x0000ff00)) <<  8) |
                ((c & UINT32_C(0x000000ff)) << 24)
            );
        }
    };

    template <typename T, typename C>
    struct byte_swap<T, C, 8> {
        constexpr static T convert(T t) {
            C c = static_cast<C>(t);
            return static_cast<T>(
                ((c & UINT64_C(0xff00000000000000)) >> 56) |
                ((c & UINT64_C(0x00ff000000000000)) >> 40) |
                ((c & UINT64_C(0x0000ff0000000000)) >> 24) |
                ((c & UINT64_C(0x000000ff00000000)) >>  8) |
                ((c & UINT64_C(0x00000000ff000000)) <<  8) |
                ((c & UINT64_C(0x0000000000ff0000)) << 24) |
                ((c & UINT64_C(0x000000000000ff00)) << 40) |
                ((c & UINT64_C(0x00000000000000ff)) << 56)
            );
        }
    };

    template <typename T, typename C>
    struct pdp_swap<T, C, 1> {
        constexpr static T convert(T t) {
            return t;
        }
    };

    template <typename T, typename C>
    struct pdp_swap<T, C, 2> {
        constexpr static T convert(T t) {
            C c = static_cast<C>(t);
            return static_cast<T>(
                ((c & UINT16_C(0xff00)) >> 8) |
                ((c & UINT16_C(0x00ff)) << 8)
            );
        }
    };

    template <typename T, typename C>
    struct pdp_swap<T, C, 4> {
        constexpr static T convert(T t) {
            C c = static_cast<C>(t);
            return static_cast<T>(
                ((c & UINT32_C(0xff000000)) >> 8) |
                ((c & UINT32_C(0x00ff0000)) << 8) |
                ((c & UINT32_C(0x0000ff00)) >> 8) |
                ((c & UINT32_C(0x000000ff)) << 8)
            );
        }
    };

    template <typename T, typename C>
    struct pdp_swap<T, C, 8> {
        constexpr static T convert(T t) {
            C c = static_cast<C>(t);
            return static_cast<T>(
                ((c & UINT64_C(0xff00000000000000)) >> 8) |
                ((c & UINT64_C(0x00ff000000000000)) << 8) |
                ((c & UINT64_C(0x0000ff0000000000)) >> 8) |
                ((c & UINT64_C(0x000000ff00000000)) << 8) |
                ((c & UINT64_C(0x00000000ff000000)) >> 8) |
                ((c & UINT64_C(0x0000000000ff0000)) << 8) |
                ((c & UINT64_C(0x000000000000ff00)) >> 8) |
                ((c & UINT64_C(0x00000000000000ff)) << 8)
            );
        }
    };

    template <typename T>
    struct to_little<ByteOrder::Little, T> {
        constexpr static T convert(T t) {
            return t;
        }
    };

    template <typename T>
    struct to_little<ByteOrder::Big, T> {
        constexpr static T convert(T t) {
            return byte_swap<T>::convert(t);
        }
    };

    template <typename T>
    struct to_little<ByteOrder::PDP, T> {
        constexpr static T convert(T t) {
            return byte_swap<T>::convert(pdp_swap<T>::convert(t));
        }
    };

    template <typename T>
    struct from_little<ByteOrder::Little, T> {
        constexpr static T convert(T t) {
            return t;
        }
    };

    template <typename T>
    struct from_little<ByteOrder::Big, T> {
        constexpr static T convert(T t) {
            return byte_swap<T>::convert(t);
        }
    };

    template <typename T>
    struct from_little<ByteOrder::PDP, T> {
        constexpr static T convert(T t) {
            return pdp_swap<T>::convert(byte_swap<T>::convert(t));
        }
    };
}

template <ByteOrder to, ByteOrder from, typename T>
constexpr T convert(T t) {
    static_assert(std::is_integral<T>::value, "endian::convert only supports integral types");
    return detail::from_little<to, T>::convert(detail::to_little<from, T>::convert(t));
}

template <ByteOrder endian, typename T>
_ENDIAN_PACK(struct endian_int {
    static_assert(std::is_integral<T>::value, "endian::endian_int only supports integral types");
    T raw;

    /// defaulted constructors and destructor
    constexpr endian_int() noexcept = default;
    constexpr endian_int(const endian_int&) noexcept = default;
    constexpr endian_int(endian_int&&) noexcept = default;
    ~endian_int() noexcept = default;

    /// defaulted assignment operators
    constexpr endian_int& operator=(const endian_int&) noexcept = default;
    constexpr endian_int& operator=(endian_int&&) noexcept = default;

    /// converting constructor converts from host byte order
    constexpr endian_int(const T& t) noexcept : raw(convert<endian, ByteOrder::Native, T>(t)) {}

    /// conversion operator converts to host byte order
    constexpr operator T() const noexcept {
        return convert<ByteOrder::Native, endian, T>(raw);
    }

    /// delegate compound assignment operators to wrapped type
    constexpr endian_int& operator+=(const endian_int& other) noexcept {
        return *this = (*this + other);
    }
    constexpr endian_int& operator-=(const endian_int& other) noexcept {
        return *this = (*this - other);
    }
    constexpr endian_int& operator*=(const endian_int& other) noexcept {
        return *this = (*this * other);
    }
    constexpr endian_int& operator/=(const endian_int& other) noexcept {
        return *this = (*this / other);
    }
    constexpr endian_int& operator%=(const endian_int& other) noexcept {
        return *this = (*this % other);
    }
    constexpr endian_int& operator^=(const endian_int& other) noexcept {
        return *this = (*this ^ other);
    }
    constexpr endian_int& operator&=(const endian_int& other) noexcept {
        return *this = (*this & other);
    }
    constexpr endian_int& operator|=(const endian_int& other) noexcept {
        return *this = (*this | other);
    }
    constexpr endian_int& operator>>=(const endian_int& other) noexcept {
        return *this = (*this >> other);
    }
    constexpr endian_int& operator<<=(const endian_int& other) noexcept {
        return *this = (*this << other);
    }

    /// delegate pre/post increment/decrement to wrapped type
    constexpr endian_int& operator++() noexcept {
        return *this += 1;
    }
    constexpr endian_int& operator--() noexcept {
        return *this -= 1;
    }
    constexpr endian_int operator++(int) noexcept {
        endian_int before = *this;
        ++*this;
        return before;
    }
    constexpr endian_int operator--(int) noexcept {
        endian_int before = *this;
        --*this;
        return before;
    }
});

}

#undef _ENDIAN_NATIVE_BYTE_ORDER
#undef _ENDIAN_PACK

#endif
