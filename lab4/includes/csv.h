#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <vector>
#include <string>
#include <stdexcept>
#include <optional>
#include <type_traits>
#include "tuple.h"

template <typename T>
T convert(const std::string& str) {
    T value;
    std::istringstream ss(str);
    if (!(ss >> value)) {
        throw std::runtime_error("Conversion failed for value: " + str);
    }
    return value;
}

template <>
std::string convert<std::string>(const std::string& str) {
    return str;
}



template <typename... Args>
class CSVParser {
public:
    CSVParser(std::istream& inputStream, int skip_lines)
        : stream(inputStream) {
            std::cout << "ignoring " << skip_lines << " lines" << std::endl;
            std::string dummy;
            for (int i = 0; i < skip_lines; i++) {
                std::getline(inputStream, dummy, '\n');
            }
    }


    class Iterator {
    public:
        Iterator(std::istream& stream, bool end = false)
            : stream(stream), endReached(end), lineNumber(0) {
            if (!end) {
                ++(*this); 
            }
        }

        std::tuple<Args...> operator*() const {
            return currentRow;
        }

        Iterator& operator++() {
            std::string line;
            while (std::getline(stream, line)) {
                ++lineNumber;

                if (line.empty()) {
                    continue;
                }

                std::istringstream lineStream(line);
                parseLine(lineStream);
                return *this;
            }

            endReached = true; 
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return endReached != other.endReached;
        }

    private:
        void parseLine(std::istringstream& lineStream) {
            std::vector<std::string> fields;
            std::string field;
            bool insideQuotes = false;

            char c;
            while (lineStream.get(c)) {
                if (c == '"') {
                    insideQuotes = !insideQuotes;
                } else if (c == ',' && !insideQuotes) {
                    fields.push_back(field);
                    field.clear();
                } else {
                    field += c;
                }
            }

            if (!field.empty()) {
                fields.push_back(field);
            }

            if (fields.size() != sizeof...(Args)) {
                throw std::runtime_error(
                    "Error at line " + std::to_string(lineNumber) +
                    ": Expected " + std::to_string(sizeof...(Args)) +
                    " columns, but got " + std::to_string(fields.size()));
            }

            currentRow = createTuple(fields, std::index_sequence_for<Args...>());
        }

        template <std::size_t... Is>
        std::tuple<Args...> createTuple(const std::vector<std::string>& fields, std::index_sequence<Is...>) {
            return std::make_tuple(convert<Args>(fields[Is])...);
        }

        std::istream& stream;
        std::tuple<Args...> currentRow;
        bool endReached;
        std::size_t lineNumber;
    };

    Iterator begin() {
        return Iterator(stream, false);
    }

    Iterator end() {
        return Iterator(stream, true);
    }

   

private:
    std::istream& stream;
    //std::ifstream fileStream; 
};
