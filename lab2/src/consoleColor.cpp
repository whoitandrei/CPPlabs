#include <Windows.h>

void setConsoleColor(int textColor, int backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>((backgroundColor << 4) | textColor));}

void resetConsoleColor() {
   setConsoleColor(7, 0); // 7 - белый текст, 0 - черный фон
}