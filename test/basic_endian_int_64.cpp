#include <cstdint>
#include <cassert>
#include <endian.hpp>

using endian::ByteOrder;

int main() {
    uint64_t x = UINT64_C(0x1122334455667788);
    endian::little_uint64_t little_x = x;
    endian::big_uint64_t big_x = x;
    endian::pdp_uint64_t pdp_x = x;

    switch (ByteOrder::Native) {
        case ByteOrder::Little:
            assert(x == little_x.raw);
            assert(big_x.raw == UINT64_C(0x8877665544332211));
            assert(pdp_x.raw == UINT64_C(0x7788556633441122));
            break;
        case ByteOrder::Big:
            assert(x == big_x.raw);
            assert(x == little_x.raw);
            assert(little_x.raw == UINT64_C(0x8877665544332211));
            assert(pdp_x.raw == UINT64_C(0x2211443366558877));
            break;
        case ByteOrder::PDP:
            assert(x == pdp_x.raw);
            assert(little_x.raw == UINT64_C(0x7788556633441122));
            assert(big_x.raw == UINT64_C(0x2211443366558877));
            break;
    }

    x += 2;
    little_x += 2;
    big_x += 2;
    pdp_x += 2;

    switch (ByteOrder::Native) {
        case ByteOrder::Little:
            assert(x == little_x.raw);
            assert(big_x.raw == UINT64_C(0x8a77665544332211));
            assert(pdp_x.raw == UINT64_C(0x778a556633441122));
            break;
        case ByteOrder::Big:
            assert(x == big_x.raw);
            assert(x == little_x.raw);
            assert(little_x.raw == UINT64_C(0x8a77665544332211));
            assert(pdp_x.raw == UINT64_C(0x2211443366558a77));
            break;
        case ByteOrder::PDP:
            assert(x == pdp_x.raw);
            assert(little_x.raw == UINT64_C(0x778a556633441122));
            assert(big_x.raw == UINT64_C(0x2211443366558a77));
            break;
    }
}
