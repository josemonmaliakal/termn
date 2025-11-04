#include <gtest/gtest.h>
#include "../include/file_utils.h"
#include <fstream>
#include <cstdio> // for remove()

TEST(FileUtilsTest, CreateAndReadFile) {
    std::string filename = "test1.txt";
    std::vector<std::string> data = {"Hello", "World"};

    // Create file
    bool result = writeToFile(filename, data);
    EXPECT_TRUE(result);

    // Read file
    auto lines = readFile(filename);
    EXPECT_EQ(lines.size(), 2);
    EXPECT_EQ(lines[0], "Hello");
    EXPECT_EQ(lines[1], "World");

    // Cleanup
    remove(filename.c_str());
}

TEST(FileUtilsTest, ReadNonexistentFile) {
    auto lines = readFile("nonexistent.txt");
    EXPECT_TRUE(lines.empty());
}
