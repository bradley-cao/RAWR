#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "read.h"

bool little_endian = false;
bool big_endian = false;

void read_header(std::ifstream& file) {
    if (!file) {
        std::cerr << "Invalid file stream\n";
        return;
    }

    uint8_t header[8];
    file.read(reinterpret_cast<char*>(header), sizeof(header));

    if (file.gcount() < static_cast<std::streamsize>(sizeof(header))) {
        std::cerr << "File is too small to contain a valid TIFF header\n";
        return;
    }
    
    std::cout << "TIFF Header (8 bytes): ";
    for (int i = 0; i < 8; ++i) {
        std::cout << std::hex << static_cast<uint>(header[i]) << " ";
    }
    std::cout << std::dec << "\n";

    // determine endianness (first two bytes of header should be 49)
    little_endian = (header[0] == 0x49 && header[1] == 0x49);
    big_endian = (header[0] == 0x4D && header[1] == 0x4D);

    if (little_endian) {
        if (header[2] != 0x2A || header[3] != 0x00) {
            std::cerr << "TIFF Identifier does not match indicated endianness\n";
            return;
        }
        std::cout << "This TIFF file is Little Endian\n";
        parse_ifd(file, 8); // temporary placeholder 
    }

    if (big_endian) {
        if (header[2] != 0x00 || header[3] != 0x2A) {
            std::cerr << "TIFF Identifier does not match indicated endianness\n";
            return;
        }
        std::cout << "This TIFF file is Big Endian\n";
        parse_ifd(file, 8); // temporary placeholder
    }
}

void parse_ifd(std::ifstream& file, uint8_t offset) {
    // IFD Size=2+(Number of Entries×12)+4
    // subtract 8 from offset, since TIFF header is guaranteed to be 8 bytes
    offset = offset - 8;

    // first two bytes represent number of directory entries
    uint8_t num_entries[2];
    file.read(reinterpret_cast<char*>(num_entries), 2); 

    std::cout << "Number of Directory Entries: " << std::hex 
              << static_cast<uint>(num_entries[0]) << static_cast<uint>(num_entries[1]) << "\n";
}

void read_full(std::ifstream& file) {
    char buffer[4096];
    while (file.read(buffer, sizeof(buffer))) {
        std::streamsize count = file.gcount();
        for (std::streamsize i = 0; i < count; ++i) {
            unsigned char byte = buffer[i];
            std::cout << std::hex << (int)byte << " ";
        }
    }

    // Handle last partial read
    std::streamsize count = file.gcount();
    for (std::streamsize i = 0; i < count; ++i) {
        unsigned char byte = buffer[i];
        std::cout << std::hex << (int)byte << " ";
    }
}

void process_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Could not open file: " << filename << "\n";
        return;
    }

    read_header(file);
    file.close(); // close safely
}