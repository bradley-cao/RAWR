#ifndef READ_H
#define READ_H

#include <fstream>
#include <string>

extern bool little_endian;
extern bool big_endian;

void read_header(std::ifstream& file);
void process_file(const std::string& filename);
void parse_ifd(std::ifstream& file, uint8_t offset);

#endif