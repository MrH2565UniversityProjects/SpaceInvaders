#pragma once
#include <string>
using namespace std;

/// Screen position in console coordinates.
struct Coordinate{
    int x;
    int y;
};

/// Hides the console cursor.
void HideCursor();

/// Shows the console cursor.
void ShowCursor();

/// Clears the entire console screen.
void ClearScreen();

/// Moves the console cursor to the given (row, column).
void Gotoxy(int x, int y);

/// Moves the console cursor back to the top-left corner.
void MoveCursorToTopLeft();

/// Returns the current console cursor position.
[[nodiscard]] Coordinate GetCursorPosition();

/// Reads a digits-only string from the user.
/// Returns the entered value, or an empty string if ESC was pressed.
[[nodiscard]] string GetNumberInput(int maxLength, int cursorX, int cursorY);

/// Reads a free-text string from the user (spaces are stored as '_').
/// Returns an empty string if ESC was pressed.
[[nodiscard]] string GetInput(int maxLength);

/// Converts an integer to its decimal string representation.
[[nodiscard]] string IntToString(int number);

/// Returns the start index that centers an item of length `itemLength`
/// inside a region of length `totalLength`.
[[nodiscard]] int CalculateCenterIndex(int totalLength, int itemLength);

/// Builds an ANSI escape sequence from a packed color code:
/// last digit = mode (3 foreground, 4 background),
/// remaining digits = 256-color palette index.
[[nodiscard]] string GenerateANSI(int code);

/// Checks whether a file exists and is readable.
[[nodiscard]] bool fileExists(const string& filename);
