#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>
#include "general_funcs.h"

class Leaderboard {
public:
    struct Entry {
        std::wstring nickname;
        int score;

        bool operator<(const Entry& other) const {
            return score > other.score; // Сортировка по убыванию очков
        }
    };

private:
    std::vector<Entry> entries;
    std::string filename;

public:
    explicit Leaderboard(const std::string& file);
    void loadFromFile();
    void saveToFile() const;
    void addEntry(const std::wstring& nickname, int score);
    const std::vector<Entry>& getEntries() const;
    void display(int x, int y) const;
};
