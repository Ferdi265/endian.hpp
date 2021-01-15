#include <cstdint>
#include <cassert>
#include <endian.hpp>

using endian::ByteOrder;

int main() {
    uint32_t x = UINT32_C(0x11223344);
    uint32_t little_x = endian::convert<ByteOrder::Little, ByteOrder::Native>(x);
    uint32_t big_x = endian::convert<ByteOrder::Big, ByteOrder::Native>(x);
    uint32_t pdp_x = endian::convert<ByteOrder::PDP, ByteOrder::Native>(x);

    switch (ByteOrder::Native) {
        case ByteOrder::Little:
            assert(x == little_x);
            assert(big_x == UINT32_C(0x44332211));
            assert(pdp_x == UINT32_C(0x33441122));
            break;
        case ByteOrder::Big:
            assert(x == big_x);
            assert(x == little_x);
            assert(little_x == UINT32_C(0x44332211));
            assert(pdp_x == UINT32_C(0x22114433));
            break;
        case ByteOrder::PDP:
            assert(x == pdp_x);
            assert(little_x == UINT32_C(0x33441122));
            assert(big_x == UINT32_C(0x22114433));
            break;
    }
}
