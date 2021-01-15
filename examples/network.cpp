#include <cstdint>
#include <iostream>
#include <endian.hpp>

struct UDPHeader {
    endian::net_uint16_t source;
    endian::net_uint16_t dest;
    endian::net_uint16_t len;
    endian::net_uint16_t check;
} __attribute__((packed));

uint8_t packet[] = {
    0xd1, 0x4b, 0x75, 0x30, 0x00, 0x12, 0x36, 0x55
};

int main() {
    const UDPHeader * header = reinterpret_cast<const UDPHeader *>(packet);

    std::cout << "source port     = " << header->source << "\n";
    std::cout << "dest port       = " << header->dest << "\n";
    std::cout << "packet length   = " << header->len << "\n";
    std::cout << "packet checksum = " << header->check << "\n";
}
