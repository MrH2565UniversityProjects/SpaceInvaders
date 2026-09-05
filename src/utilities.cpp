#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "utilities.h"
#include "color.h"
using namespace std;
void HideCursor()
{
    cout << "\033[?25l";
    cout.flush();
}
void MoveCursorToTopLeft()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    SetConsoleCursorPosition(hConsole, coord);
}
void ShowCursor()
{
    cout << "\033[?25h";
    cout.flush();
}
void ClearScreen()
{
    system("cls");
}
void Gotoxy(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}
bool fileExists(const string& filename) {
    std::ifstream file(filename);
    return file.good();
}
Coordinate GetCursorPosition() {
    Coordinate coordinate;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        coordinate.x = csbi.dwCursorPosition.X; 
        coordinate.y = csbi.dwCursorPosition.Y;
    }
    return coordinate;
}

bool IsDigit(char ch)
{
    return ('0' <= ch) && ('9' >= ch);
}
string GetNumberInput(int maxLength, int cursorX, int cursorY)
{
    string input;
    char ch;

    while (true)
    {
        ch = getch();
        if (!(IsDigit(ch) || ch == '\r' || ch == '\b' || ch == 27))
            continue;

        if (ch == '\r')
        {
            break;
        }
        else if (ch == '\b')
        {
            if (!input.empty())
            {
                input.pop_back();
                Gotoxy(cursorX + input.length(), cursorY);
                cout << " \b";
            }
        }
        else if (ch == 27)
        {
            return "";
        }
        else if (input.length() < maxLength)
        {
            input.push_back(ch);
            cout << ch;
        }
    }

    return input;
}
string GetInput(int maxLength)
{
    string input;
    char ch;
    Coordinate point = GetCursorPosition();

    while (true)
    {
        ch = getch();
        if (ch == 32)
        {
            ch = '_';
        }
        if (ch == '\r')
        {
            break;
        }
        else if (ch == '\b')
        {
            if (!input.empty())
            {
                input.pop_back();
                Gotoxy(point.x + input.length(), point.y);
                cout << " \b";
            }
        }
        else if (ch == 27)
        {
            return "";
        }
        else if (input.length() < maxLength)
        {
            input.push_back(ch);
            cout << ch;
        }
    }

    return input;
}
int CalculateCenterIndex(int totalLength,int itemLength){
    return (totalLength-itemLength)/2;
}
string GenerateANSI(int code) {
    if ((code % 10 != 3 && code % 10 != 4)) {
        return FG_WHITE;
    }

    int colorCode = code / 10; 
    int mode = code % 10;   

    string ansiCode = "\033[" + to_string((mode == 3 ? 38 : 48)) + ";5;" + to_string(colorCode) + "m";
    return ansiCode;
}