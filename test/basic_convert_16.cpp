#include <cstdint>
#include <cassert>
#include <endian.hpp>

using endian::ByteOrder;

int main() {
    uint16_t x = UINT16_C(0x1122);
    uint16_t little_x = endian::convert<ByteOrder::Little, ByteOrder::Native>(x);
    uint16_t big_x = endian::convert<ByteOrder::Big, ByteOrder::Native>(x);
    uint16_t pdp_x = endian::convert<ByteOrder::PDP, ByteOrder::Native>(x);

    switch (ByteOrder::Native) {
        case ByteOrder::Little:
            assert(x == little_x);
            assert(big_x == UINT16_C(0x2211));
            assert(pdp_x == UINT16_C(0x1122));
            break;
        case ByteOrder::Big:
            assert(x == big_x);
            assert(x == little_x);
            assert(little_x == UINT16_C(0x2211));
            assert(pdp_x == UINT16_C(0x2211));
            break;
        case ByteOrder::PDP:
            assert(x == pdp_x);
            assert(little_x == UINT16_C(0x1122));
            assert(big_x == UINT16_C(0x2211));
            break;
    }
}
