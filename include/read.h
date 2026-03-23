#ifndef READ_H
#define READ_H

#include <fstream>
#include <string>

void read_header(std::ifstream& file);
void process_file(const std::string& filename);

#endif