#include <iostream>
#include <fstream>
#include <string>

void read_header(std::ifstream& file) {
    if (!file) {
        std::cerr << "Invalid file stream\n";
        return;
    }

    char header[8];
    file.read(header, sizeof(header));

    if (file.gcount() < static_cast<std::streamsize>(sizeof(header))) {
        std::cerr << "File is too small to contain a valid TIFF header\n";
        return;
    }
    
    std::cout << "TIFF Header (8 bytes): ";
    for (int i = 0; i < 8; ++i) {
        std::cout << std::hex << (static_cast<unsigned int>(header[i]) & 0xFF) << " ";
    }
    std::cout << std::dec << "\n";
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