#include <cstdint>
#include <cassert>
#include <endian.hpp>

using endian::ByteOrder;

int main() {
    uint32_t x = UINT32_C(0x11223344);
    endian::little_uint32_t little_x = x;
    endian::big_uint32_t big_x = x;
    endian::pdp_uint32_t pdp_x = x;

    switch (ByteOrder::Native) {
        case ByteOrder::Little:
            assert(x == little_x.raw);
            assert(big_x.raw == UINT32_C(0x44332211));
            assert(pdp_x.raw == UINT32_C(0x33441122));
            break;
        case ByteOrder::Big:
            assert(x == big_x.raw);
            assert(x == little_x.raw);
            assert(little_x.raw == UINT32_C(0x44332211));
            assert(pdp_x.raw == UINT32_C(0x22114433));
            break;
        case ByteOrder::PDP:
            assert(x == pdp_x.raw);
            assert(little_x.raw == UINT32_C(0x33441122));
            assert(big_x.raw == UINT32_C(0x22114433));
            break;
    }

    x += 6;
    little_x += 6;
    big_x += 6;
    pdp_x += 6;

    switch (ByteOrder::Native) {
        case ByteOrder::Little:
            assert(x == little_x.raw);
            assert(big_x.raw == UINT32_C(0x4a332211));
            assert(pdp_x.raw == UINT32_C(0x334a1122));
            break;
        case ByteOrder::Big:
            assert(x == big_x.raw);
            assert(x == little_x.raw);
            assert(little_x.raw == UINT32_C(0x4a332211));
            assert(pdp_x.raw == UINT32_C(0x22114a33));
            break;
        case ByteOrder::PDP:
            assert(x == pdp_x.raw);
            assert(little_x.raw == UINT32_C(0x334a1122));
            assert(big_x.raw == UINT32_C(0x22114a33));
            break;
    }
}
