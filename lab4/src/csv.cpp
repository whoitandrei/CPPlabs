#include "..\includes\csv.h"


int main(int argc, char* argv[]) {
    
        try {
            std::ifstream csv_stream("test.csv");
            //std::istream& csv_stream(std::cin);    
            CSVParser<int, std::string, double> parser(csv_stream, 5);
            for (std::tuple<int, std::string, double> rs : parser) {
                std::cout << rs << "\n";
            }
        }
        catch (const std::runtime_error& error) {
            std::cerr << "fatal: " << error.what() << std::endl;
        }
    return 0;
}
