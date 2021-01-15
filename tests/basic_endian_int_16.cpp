#include <cstdint>
#include <cassert>
#include <endian.hpp>

using endian::ByteOrder;

int main() {
    uint16_t x = UINT16_C(0x1122);
    endian::little_uint16_t little_x = x;
    endian::big_uint16_t big_x = x;
    endian::pdp_uint16_t pdp_x = x;

    switch (ByteOrder::Native) {
        case ByteOrder::Little:
            assert(x == little_x.raw);
            assert(big_x.raw == UINT16_C(0x2211));
            assert(pdp_x.raw == UINT16_C(0x1122));
            break;
        case ByteOrder::Big:
            assert(x == big_x.raw);
            assert(x == little_x.raw);
            assert(little_x.raw == UINT16_C(0x2211));
            assert(pdp_x.raw == UINT16_C(0x2211));
            break;
        case ByteOrder::PDP:
            assert(x == pdp_x.raw);
            assert(little_x.raw == UINT16_C(0x1122));
            assert(big_x.raw == UINT16_C(0x2211));
            break;
    }

    x += 8;
    little_x += 8;
    big_x += 8;
    pdp_x += 8;

    switch (ByteOrder::Native) {
        case ByteOrder::Little:
            assert(x == little_x.raw);
            assert(big_x.raw == UINT16_C(0x2a11));
            assert(pdp_x.raw == UINT16_C(0x112a));
            break;
        case ByteOrder::Big:
            assert(x == big_x.raw);
            assert(x == little_x.raw);
            assert(little_x.raw == UINT16_C(0x2a11));
            assert(pdp_x.raw == UINT16_C(0x2a11));
            break;
        case ByteOrder::PDP:
            assert(x == pdp_x.raw);
            assert(little_x.raw == UINT16_C(0x112a));
            assert(big_x.raw == UINT16_C(0x2a11));
            break;
    }
}
