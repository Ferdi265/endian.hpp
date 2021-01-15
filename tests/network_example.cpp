#include <cstdint>
#include <cassert>
#include <endian.hpp>

using endian::ByteOrder;

ENDIAN_PACK(struct UDPHeader {
    endian::net_uint16_t source;
    endian::net_uint16_t dest;
    endian::net_uint16_t len;
    endian::net_uint16_t check;
});

uint8_t packet[] = {
    0xd1, 0x4b, 0x75, 0x30, 0x00, 0x12, 0x36, 0x55
};

int main() {
    const UDPHeader * header = reinterpret_cast<const UDPHeader *>(packet);

    assert(header->source == 53579);
    assert(header->dest == 30000);
    assert(header->len == 18);
    assert(header->check == 0x3655);

    assert((endian::hton<uint16_t>(0x1122) == endian::convert<ByteOrder::Network, ByteOrder::Native, uint16_t>(0x1122)));
    assert((endian::hton<uint32_t>(0x11223344) == endian::convert<ByteOrder::Network, ByteOrder::Native, uint32_t>(0x11223344)));
    assert((endian::ntoh<uint16_t>(0x1122) == endian::convert<ByteOrder::Native, ByteOrder::Network, uint16_t>(0x1122)));
    assert((endian::ntoh<uint32_t>(0x11223344) == endian::convert<ByteOrder::Native, ByteOrder::Network, uint32_t>(0x11223344)));
}
