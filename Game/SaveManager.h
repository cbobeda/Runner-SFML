#pragma once

#include <string>

class SaveManager {
public:
    explicit SaveManager(const std::string& path = "save/save.txt");
    ~SaveManager() = default;

    int getSavedScore();
    void saveScore(int coins);

private:
    std::string filePath;
};