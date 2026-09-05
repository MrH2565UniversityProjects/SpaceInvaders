#pragma once
#include <string>
struct Coordinate{
    int x;
    int y;
};
using namespace std;
void HideCursor();
void ShowCursor();
void ClearScreen();
void Gotoxy(int x, int y);
void MoveCursorToTopLeft();
[[nodiscard]] Coordinate GetCursorPosition();
[[nodiscard]] string GetNumberInput(int maxLength, int cursorX, int cursorY);
[[nodiscard]] string GetInput(int maxLength);
[[nodiscard]] string IntToString(int number);
[[nodiscard]] int CalculateCenterIndex(int totalLength,int itemLength);
[[nodiscard]] string GenerateANSI(int code);
[[nodiscard]] bool fileExists(const string& filename);