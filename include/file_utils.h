#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <vector>
#include <string>


bool writeToFile(const std::string& filename, const std::vector<std::string>& content);
std::vector<std::string> readFile(const std::string& filename);

#endif