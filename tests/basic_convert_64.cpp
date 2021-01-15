#include <cstdint>
#include <cassert>
#include <endian.hpp>

using endian::ByteOrder;

int main() {
    uint64_t x = UINT64_C(0x1122334455667788);
    uint64_t little_x = endian::convert<ByteOrder::Little, ByteOrder::Native>(x);
    uint64_t big_x = endian::convert<ByteOrder::Big, ByteOrder::Native>(x);
    uint64_t pdp_x = endian::convert<ByteOrder::PDP, ByteOrder::Native>(x);

    switch (ByteOrder::Native) {
        case ByteOrder::Little:
            assert(x == little_x);
            assert(big_x == UINT64_C(0x8877665544332211));
            assert(pdp_x == UINT64_C(0x7788556633441122));
            break;
        case ByteOrder::Big:
            assert(x == big_x);
            assert(x == little_x);
            assert(little_x == UINT64_C(0x8877665544332211));
            assert(pdp_x == UINT64_C(0x2211443366558877));
            break;
        case ByteOrder::PDP:
            assert(x == pdp_x);
            assert(little_x == UINT64_C(0x7788556633441122));
            assert(big_x == UINT64_C(0x2211443366558877));
            break;
    }
}
