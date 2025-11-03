// file_utils.cpp
#include "file_utils.h"
#include <fstream>
#include <iostream>

bool writeToFile(const std::string& filename, const std::vector<std::string>& lines) {
    std::ofstream file(filename);
    if (!file) return false;

    for (const auto& line : lines) {
        file << line << "\n";
    }
    file.close();
    return true;
}

std::vector<std::string> readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> lines;
    std::string line;

    if (!file) return {};

    while (getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}
