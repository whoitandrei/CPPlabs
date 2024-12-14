#include <iostream>
#include <tuple>
#include <fstream>

template<typename Tuple, unsigned N, unsigned Size> 
class TuplePrinter {
    public:
        static void print(std::ostream& out, const Tuple& tuple) {
            out << std::get<N>(tuple) << ", ";
            TuplePrinter<Tuple, N + 1, Size>::print(out, tuple);
        }
};

template<typename Tuple, unsigned Size> 
class TuplePrinter<Tuple, Size, Size> {
    public:
        static void print(std::ostream& out, const Tuple& tuple) {
            out << std::get<Size>(tuple);
        }
};


template<typename... Args> 
std::ostream & operator<<(std::ostream& out, const std::tuple<Args...>& arg) {
    out << "(";
    TuplePrinter<std::tuple<Args...>, 0, sizeof...(Args) - 1>::print(out, arg);
    out << ")";
    return out;
};
