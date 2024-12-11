#include "Leaderboard.h"

#include "Leaderboard.h"

Leaderboard::Leaderboard(const std::string& file) : filename(file) {
    loadFromFile();
}

void Leaderboard::loadFromFile() {
    entries.clear();
    std::wifstream file(filename);
    if (!file.is_open()) {
        std::wcerr << L"Error: Could not open leaderboard file!" << std::endl;
        return;
    }

    std::wstring line;
    while (std::getline(file, line)) {
        std::wistringstream iss(line);
        Entry entry;
        if (iss >> entry.nickname >> entry.score) {
            entries.push_back(entry);
        }
    }
    file.close();

    // Сортировка по убыванию очков
    std::sort(entries.begin(), entries.end());
}

void Leaderboard::saveToFile() const {
    std::wofstream file(filename, std::ios::trunc);
    if (!file.is_open()) {
        std::wcerr << L"Error: Could not write to leaderboard file!" << std::endl;
        return;
    }

    for (const auto& entry : entries) {
        file << entry.nickname << L" " << entry.score << std::endl;
    }
    file.close();
}

void Leaderboard::addEntry(const std::wstring& nickname, int score) {
    entries.push_back({nickname, score});

    // Сортировка по убыванию и обрезка до топ-5
    std::sort(entries.begin(), entries.end());
    if (entries.size() > 5) {
        entries.resize(5);
    }

    saveToFile();
}

const std::vector<Leaderboard::Entry>& Leaderboard::getEntries() const {
    return entries;
}

void Leaderboard::display(int x, int y) const {
    gotoxy(x, y);
    std::wcout << L"Leaderboard:";
    for (size_t i = 0; i < entries.size(); ++i) {
        gotoxy(x, y + 1 + i);
        std::wcout << i + 1 << L". " << entries[i].nickname << L" " << entries[i].score;
    }
}
