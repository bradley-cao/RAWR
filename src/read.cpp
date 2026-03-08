#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("test.NEF", std::ios::binary);

    if (!file) {
        std::cerr << "Could not open file\n";
        return 1;
    }

    char buffer[4096];

    // TODO: ONLY PARSE HEADER

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

    file.close();
    return 0;
}