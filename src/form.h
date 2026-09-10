#pragma once
#include <iostream>
#include "utilities.h"
#include "color.h"
using namespace std;
const Coordinate start_area = {12, 8};
const Coordinate end_area = {116, 25};
const Coordinate footer_area = {12, 29};
const int ELEMENT_WIDTH = 50;
const int ELEMENT_HEIGHT = 3;
const int FORM_ROW_STEP = 4;
const int FORM_COL_STEP = 54;
const string blank_form = R"(
    ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
    ║       _______  _____  _______ _______ _______      _____ __   _ _    _ _______ ______  _______  ______ _______       ║
    ║       |______ |_____] |_____| |       |______        |   | \  |  \  /  |_____| |     \ |______ |_____/ |______       ║
    ║       ______| |       |     | |_____  |______      __|__ |  \_|   \/   |     | |_____/ |______ |    \_ ______|       ║
    ║                                                                                                                      ║
    ╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ║                                                                                                                      ║
    ╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣
    ║                                                                                                                      ║
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝)";
const string minimal_form = R"(
  
  
  
  
  
        ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ║                                                                                                              ║
        ╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════╣
        ║                                                                                                              ║
        ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝)";
enum ElementType
{
    BUTTON,
    TEXTBOX,
    CHECKBOX,
    SELECTBOX,
    RANGEBAR,
    TABLE,
    KEYBOX,
    LABEL,
    NULLELEMENT,
    NONRENDER
};
enum MessageboxIcon
{
    NONE,
    INFORMATION,
    WARNING,
    CRITICAL,
};
struct Position
{
    int row;
    int col;
};
struct TableCell
{
    string content;
};
struct Line{
    string text;
    int length = 0;
};
struct Label
{
    Line lines[10];
    int linesCount;
    Position position;
    int row = 1;
    bool IsEnabled = true;
    int id = 0;
};
struct Table
{

    int totalWidth;
    int rows_count;
    int cols_count;
    int start_row;
    int Showed_rows_count;
    int colsLength[5] = {0};
    TableCell Cells[20][5];
    bool IsEnabled = true;
    Position position;
    int id = 0;
};
struct Display
{

    int start_row = 0;
    int end_row = 4;
    int start_col = 0;
    int end_col = 1;
    Position userPosition = {0, 0};
    string primaryColor = FG_CYAN;
    string secondaryColor = FG_WHITE;   
    int id = 0;
};
struct Button
{
    string text;
    Position position;
    bool IsEnabled = true;
    int id = 0;
};
struct SelectboxItem
{

    string text;
    int value;
};
struct Selectbox
{

    SelectboxItem Items[10];
    string title = "";
    int ItemsCount = 0;
    int SelectedIndex = 0;

    Position position;
    bool IsEnabled = true;
    int id = 0;
};
struct Checkbox
{
    string text;
    bool isChecked;
    Position position;
    bool IsEnabled = true;
    int id = 0;
};
struct Rangebar
{
    string text;
    int min = 0;
    int max = 100;
    int value;
    bool UsePercentage = false;
    Position position;
    bool IsEnabled = true;
    int id = 0;
};
struct Textbox
{
    string title;
    string placeholder;
    string validationMessage;
    string value = "";
    bool CanEdit = true;
    bool IsNumberOnly = false;
    Position position;
    bool IsEnabled = true;
    int id = 0;
};
struct Element
{
    void *ptr;
    ElementType type;
};
struct Form
{

    string title;
    int rows_count = 5;
    int cols_count = 1;
    bool renderNullElements = true;
    bool isCenter = true;
    bool isRunning = true;
    bool renderBackground = true;
    bool isSoundEnabled = true;
    Element **ElementsGrid;
};
struct Keybox
{

    string title;
    char value;

    Position position;
    bool IsEnabled = true;
    int id = 0;
};

struct Messagebox
{

    string header = "";
    string lines[10];
    int linesCount = 0;
    MessageboxIcon icon = NONE;
    bool IsEnabled = false;
 int id = 0;
 };
bool IsElementSelected(Position position, Display display);

void DrawBox(int width, int height, string fg_color,string rest_color, int borderStyle);
void RenderBackground(Display display);
void RenderMinimalBackground(Display display);

void RenderButton(Button button, Display display);
void RenderTextbox(Textbox &textbox, Display display);
void RenderRangebar(Rangebar &Rangebar, Display display);
void AddTableToForm(Form &form, Table *table);
void RenderFooter(string text,string fg_color);
void RenderNullElement(Position position, Display display);
void RenderCheckbox(Checkbox &checkbox, Display display);
void RenderSelectbox(Selectbox &selectbox, Display display);
void RenderForm(Form &form, Display &display);

bool CanAccess(Form &form, Position position);
void UpdateSelectBoxSelection(Selectbox &selectbox, int input);
void UpdateRangebarValue(Rangebar &Rangebar, int input);
void ToggleCheckboxState(Checkbox &checkbox);
void HandleNavigation(char input, Form &form, Display &display);
void GetTextboxValue(Textbox &textbox, Display &display);
void OnPress6(void *element, ElementType type, Display &display);
void OnPress5(void *element, ElementType type, Display &display);
int GetItemIndexByValue(Selectbox selectbox, int value);
void HandleInput(char input, Display &display, Form &form);
string GetKeyHints(ElementType type);
void ShowMessageBox(Messagebox &messagebox,string sec_color);
void DeleteElement(Form &form, Position position);
void AddElementToForm(Form &form, Element &element, Position position);
void AddButtonToForm(Form &form, Button *button);
void AddTextboxToForm(Form &form, Textbox *textbox);
void AddRangebarToForm(Form &form, Rangebar *rangebar);
void AddCheckboxToForm(Form &form, Checkbox *checkbox);
void AddSelectboxToForm(Form &form, Selectbox *selectbox);
void AddKeyboxToForm(Form &form, Keybox *keybox);
void AddLabelToForm(Form &form, Label *label);
void InitialElementGrid(Form &form);
void InitialDisplay(Display &display);
void FreeElementGrid(Form &form);
void CloseForm(Form &form);