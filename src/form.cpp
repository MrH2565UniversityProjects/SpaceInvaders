#include <iostream>
#include <iomanip>
#include <cctype>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include "color.h"
#include "form.h"
#include "settings.h"
#include "utilities.h"
#include "Audio.h"
using namespace std;
bool IsElementSelected(Position position, Display display)
{
    return position.row == display.userPosition.row && position.col == display.userPosition.col;
}
int GetItemIndexByValue(Selectbox selectbox, int value)
{
    int index = 0;
    for (int i = 0; i < selectbox.ItemsCount; i++)
    {
        if (selectbox.Items[i].value == value)
        {
            index = i;
            break;
        }
    }
    return index;
}
Coordinate GetCenteredCoordinates(int width, int height)
{
    const int mainFormWidth = 120;
    const int mainFormHeight = 30;
    int x = CalculateCenterIndex(mainFormWidth, width) + 3;
    int y = CalculateCenterIndex(mainFormHeight, height) + 1;
    return {x, y};
}
void DrawBox(int width, int height, string fg_color, string rest_color, int borderStyle)
{
    string borderCharacters1[6] = {"┐", "┌", "┘", "└", "─", "│"};
    string borderCharacters2[6] = {"┓", "┏", "┛", "┗", "━", "┃"};
    string borderCharacters3[6] = {"╗", "╔", "╝", "╚", "═", "║"};
    string *usageBorder = nullptr;
    switch (borderStyle)
    {
    case 1:
        usageBorder = borderCharacters1;
        break;
    case 2:
        usageBorder = borderCharacters2;
        break;
    case 3:
        usageBorder = borderCharacters3;
        break;
    default:
        usageBorder = borderCharacters1;
        break;
    }
    Coordinate point = GetCursorPosition();
    for (int i = 0; i < height; i++)
    {
        string right;
        string inner;
        string left;
        if (i == 0)
        {
            right = usageBorder[0];
            left = usageBorder[1];
            inner = usageBorder[4];
        }
        else if (i == height - 1)
        {
            right = usageBorder[2];
            left = usageBorder[3];
            inner = usageBorder[4];
        }
        else
        {
            right = usageBorder[5];
            left = usageBorder[5];
            inner = " ";
        }

        cout << fg_color << left;
        for (int j = 0; j < width - 2; j++)
        {
            cout << inner;
        }
        cout << right;
        Gotoxy(point.x, point.y + i + 1);
    }
    cout << rest_color;
}
void RenderTable(Table &table, Display display)
{
    Coordinate elementPos = {start_area.x, start_area.y};
    elementPos.y += (table.position.row - display.start_row) * FORM_ROW_STEP;
    elementPos.x += (table.position.col) * FORM_COL_STEP;
    int remainingWidth = table.totalWidth;
    int unassignedColsCount = 0;

    for (int i = 0; i < table.cols_count; i++)
    {
        if (table.colsLength[i] == 0)
        {
            unassignedColsCount++;
        }
        remainingWidth -= table.colsLength[i] + 1;
    }
    remainingWidth--;

    if (unassignedColsCount != 0)
    {
        int defaultColWidth = remainingWidth / unassignedColsCount;
        for (int i = 0; i < table.cols_count; i++)
        {
            if (table.colsLength[i] == 0)
            {
                table.colsLength[i] = defaultColWidth;
            }
        }
    }
    if (IsElementSelected(table.position, display))
    {
        cout << display.primaryColor;
    }
    else if (!table.IsEnabled)
    {
        cout << FG_GRAY;
    }
    else
    {
        cout << display.secondaryColor;
    }

    for (int row = table.start_row; row - table.start_row < table.Showed_rows_count && row <= table.rows_count; row++)
    {
        Gotoxy(elementPos.x, elementPos.y + (row - table.start_row) * 2);

        for (int col = 0; col < table.cols_count; col++)
        {
            if (col == 0)
            {
                cout << (row == table.start_row ? "╔" : "╠");
            }
            else
            {
                cout << (row == table.start_row ? "╦" : "╬");
            }

            for (int i = 0; i < table.colsLength[col]; i++)
            {
                cout << "═";
            }
        }
        cout << (row == table.start_row ? "╗" : "╣");

        if (row < table.rows_count)
        {
            Gotoxy(elementPos.x, elementPos.y + (row - table.start_row) * 2 + 1);
            for (int col = 0; col < table.cols_count; col++)
            {
                if (col == 0)
                {
                    cout << "║";
                }

                int contentStart = CalculateCenterIndex(table.colsLength[col], table.Cells[row][col].content.length());
                cout << string(contentStart, ' ') << table.Cells[row][col].content
                     << string(table.colsLength[col] - contentStart - table.Cells[row][col].content.length(), ' ');
                cout << "║";
            }
        }
    }

    Gotoxy(elementPos.x, elementPos.y + table.Showed_rows_count * 2);
    for (int col = 0; col < table.cols_count; col++)
    {
        if (col == 0)
        {
            cout << "╚";
        }
        else
        {
            cout << "╩";
        }
        for (int i = 0; i < table.colsLength[col]; i++)
        {
            cout << "═";
        }
    }
    cout << "╝";
    cout << display.secondaryColor;
}
void RenderBackground(Display display)
{
    Gotoxy(0, 0);
    cout << BG_BLACK << display.secondaryColor << blank_form;
}
void RenderMinimalBackground(Display display)
{
    Gotoxy(0, 0);
    cout << BG_BLACK << display.secondaryColor << minimal_form;
}
void RenderButton(Button button, Display display, Coordinate elementPos)
{
    string fg_color = "";
    if (IsElementSelected(button.position, display))
    {
        fg_color = display.primaryColor;
    }
    else if (!button.IsEnabled)
    {
        fg_color = FG_GRAY;
    }
    else
    {
        fg_color = display.secondaryColor;
    }
    elementPos.y += (button.position.row - display.start_row) * FORM_ROW_STEP;
    elementPos.x += (button.position.col - display.start_col) * FORM_COL_STEP;
    int width = ELEMENT_WIDTH;
    int height = ELEMENT_HEIGHT;
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, fg_color, display.secondaryColor, 2);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    cout << fg_color << button.text << display.secondaryColor;
}
void RenderTextbox(Textbox &textbox, Display display, Coordinate elementPos)
{
    string fg_color = "";
    if (IsElementSelected(textbox.position, display))
    {
        fg_color = display.primaryColor;
    }
    else if (!textbox.IsEnabled)
    {
        fg_color = FG_GRAY;
    }
    else
    {
        fg_color = display.secondaryColor;
    }
    elementPos.y += (textbox.position.row - display.start_row) * FORM_ROW_STEP;
    elementPos.x += (textbox.position.col - display.start_col) * FORM_COL_STEP;
    int width = ELEMENT_WIDTH;
    int height = ELEMENT_HEIGHT;
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, fg_color, display.secondaryColor, 2);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));

    string title = textbox.title.substr(0, 10);
    cout << fg_color << setw(10) << left << title;
    string placeholder;
    if (!textbox.value.empty())
    {
        placeholder = textbox.value;
    }
    else
    {
        placeholder = textbox.placeholder;
    }
    placeholder = placeholder.substr(0, 28);
    cout << fg_color << " " << setw(28) << left << placeholder << display.secondaryColor;
}
void RenderKeybox(Keybox &keybox, Display display, Coordinate elementPos)
{
    string fg_color = "";
    if (IsElementSelected(keybox.position, display))
    {
        fg_color = display.primaryColor;
    }
    else if (!keybox.IsEnabled)
    {
        fg_color = FG_GRAY;
    }
    else
    {
        fg_color = display.secondaryColor;
    }
    elementPos.y += (keybox.position.row - display.start_row) * FORM_ROW_STEP;
    elementPos.x += (keybox.position.col - display.start_col) * FORM_COL_STEP;
    int width = ELEMENT_WIDTH;
    int height = ELEMENT_HEIGHT;
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, fg_color, display.secondaryColor, 2);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));

    string title = keybox.title.substr(0, 10);
    cout << fg_color << setw(10) << left << title;
    Gotoxy(elementPos.x + 37, elementPos.y + 1);
    cout << fg_color << "<";
    Gotoxy(elementPos.x + width - 5, elementPos.y + 1);
    cout << fg_color << ">";
    string key = " ";
    switch (keybox.value)
    {
    case '^':
        key = "UP ";
        break;
    case '/':
        key = "DOWN ";
        break;
    case '>':
        key = "LEFT ";
        break;
    case '<':
        key = "RIGHT";
        break;
    case '\r':
        key = "ENTER";
        break;
    case ' ':
        key = "SPACE";
        break;
    case '*':
        key = "ESC";
        break;
    default:
        key[0] = keybox.value;
        break;
    }
    int x = CalculateCenterIndex(8, key.length()) + 38;
    Gotoxy(elementPos.x + x, elementPos.y + 1);
    cout << fg_color << key << display.secondaryColor;
}
void RenderLabel(Label label, Display display, Coordinate elementPos)
{
    string fg_color = "";
    fg_color = display.secondaryColor;
    elementPos.y += (label.position.row - display.start_row) * FORM_ROW_STEP;
    elementPos.x += (label.position.col - display.start_col) * FORM_COL_STEP;
    int width = ELEMENT_WIDTH;
    int height = label.row * FORM_ROW_STEP - 1;
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, fg_color, display.secondaryColor, 3);
    for (int i = 0; i < label.linesCount; i++)
    {
        Line line = label.lines[i];
        int x_centerIndex = CalculateCenterIndex(width - 2, line.length);
        int y_centerIndex = CalculateCenterIndex(height - 2, label.linesCount);
        Gotoxy(elementPos.x + x_centerIndex + 1, elementPos.y + y_centerIndex + i + 1);
        cout << fg_color << line.text << display.secondaryColor;
    }
}
void RenderRangebar(Rangebar &Rangebar, Display display, Coordinate elementPos)
{
    string fg_color = "";
    if (IsElementSelected(Rangebar.position, display))
    {
        fg_color = display.primaryColor;
    }
    else if (!Rangebar.IsEnabled)
    {
        fg_color = FG_GRAY;
    }
    else
    {
        fg_color = display.secondaryColor;
    }
    elementPos.y += (Rangebar.position.row - display.start_row) * FORM_ROW_STEP;
    elementPos.x += (Rangebar.position.col - display.start_col) * FORM_COL_STEP;
    int width = ELEMENT_WIDTH;
    int height = ELEMENT_HEIGHT;
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, fg_color, display.secondaryColor, 2);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    cout << fg_color << Rangebar.text << display.secondaryColor;
    Gotoxy(elementPos.x + 14, elementPos.y + (height / 2));
    int dis = Rangebar.max - Rangebar.min;
    float ProgressRate = (Rangebar.value - Rangebar.min) * 1.0 / dis;

    int fillCharacterCount = ProgressRate * 28;
    cout << fg_color;
    for (int i = 0; i < 29; i++)
    {
        if (i < fillCharacterCount)
            cout << "▓";
        else if (i == fillCharacterCount)
            cout << "█";
        else
            cout << "░";
    }
    cout << display.secondaryColor;
    Gotoxy(elementPos.x + width - 6, elementPos.y + (height / 2));
    if (Rangebar.UsePercentage)
    {
        int percentage = ProgressRate * 100;
        cout << fg_color << percentage << "%" << display.secondaryColor;
    }
    else
    {
        cout << fg_color << Rangebar.value << display.secondaryColor;
    }
}

void RenderFooter(string text, string fg_color)
{
    Gotoxy(footer_area.x, footer_area.y);
    cout << fg_color << text;
    for (int i = footer_area.x + text.length(); i < end_area.x; i++)
    {
        cout << " ";
    }
}
void RenderNullElement(Position position, Display display, Coordinate elementPos)
{
    elementPos.y += (position.row - display.start_row) * FORM_ROW_STEP;
    elementPos.x += (position.col - display.start_col) * FORM_COL_STEP;
    int width = ELEMENT_WIDTH;
    int height = ELEMENT_HEIGHT;
    for (int j = 0; j < height; j++)
    {
        Gotoxy(elementPos.x, elementPos.y + j);
        for (int i = 0; i < width; i++)
        {
            cout << " ";
        }
    }
}
void RenderCheckbox(Checkbox &checkbox, Display display, Coordinate elementPos)
{
    string fg_color = "";
    if (IsElementSelected(checkbox.position, display))
    {
        fg_color = display.primaryColor;
    }
    else if (!checkbox.IsEnabled)
    {
        fg_color = FG_GRAY;
    }
    else
    {
        fg_color = display.secondaryColor;
    }
    elementPos.y += (checkbox.position.row - display.start_row) * FORM_ROW_STEP;
    elementPos.x += (checkbox.position.col - display.start_col) * FORM_COL_STEP;
    int width = ELEMENT_WIDTH;
    int height = ELEMENT_HEIGHT;
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, fg_color, display.secondaryColor, 2);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    cout << fg_color << checkbox.text << display.secondaryColor;
    Gotoxy(elementPos.x + width - 4, elementPos.y + (height / 2));
    if (checkbox.isChecked)
    {
        cout << fg_color << "▒█" << display.secondaryColor;
    }
    else
    {
        cout << fg_color << "█░" << display.secondaryColor;
    }
}
void RenderSelectbox(Selectbox &selectbox, Display display, Coordinate elementPos)
{
    string fg_color = "";
    if (IsElementSelected(selectbox.position, display))
    {
        fg_color = display.primaryColor;
    }
    else if (!selectbox.IsEnabled)
    {
        fg_color = FG_GRAY;
    }
    else
    {
        fg_color = display.secondaryColor;
    }
    elementPos.y += (selectbox.position.row - display.start_row) * FORM_ROW_STEP;
    elementPos.x += (selectbox.position.col - display.start_col) * FORM_COL_STEP;
    int width = ELEMENT_WIDTH;
    int height = ELEMENT_HEIGHT;
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, fg_color, display.secondaryColor, 2);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    string title = selectbox.title.substr(0, 12);
    cout << fg_color << setw(12) << left << title;
    Gotoxy(elementPos.x + 18, elementPos.y + 1);
    cout << fg_color << "<";
    Gotoxy(elementPos.x + width - 3, elementPos.y + 1);
    cout << fg_color << ">";
    string itemTitle = selectbox.Items[selectbox.SelectedIndex].text.substr(0, 20);
    int x = CalculateCenterIndex(26, itemTitle.length()) + 20;
    Gotoxy(elementPos.x + x, elementPos.y + 1);
    cout << fg_color << selectbox.Items[selectbox.SelectedIndex].text << display.secondaryColor;
}
void RenderForm(Form &form, Display &display)
{
    Coordinate Start_pos = start_area;
    if (display.end_col - display.start_col == 0 && form.isCenter)
    {
        Start_pos.x += 26;
    }
    for (int i = display.start_col; i <= display.end_col; i++)
    {
        for (int j = display.start_row; j <= display.end_row; j++)
        {
            Element element = form.ElementsGrid[j][i];
            if (element.ptr != nullptr)
            {
                switch (element.type)
                {
                case CHECKBOX:
                    RenderCheckbox(*((Checkbox *)element.ptr), display, Start_pos);
                    break;
                case SELECTBOX:
                    RenderSelectbox(*((Selectbox *)element.ptr), display, Start_pos);
                    break;
                case RANGEBAR:
                    RenderRangebar(*((Rangebar *)element.ptr), display, Start_pos);
                    break;
                case TEXTBOX:
                    RenderTextbox(*((Textbox *)element.ptr), display, Start_pos);
                    break;
                case BUTTON:
                    RenderButton(*((Button *)element.ptr), display, Start_pos);
                    break;
                case TABLE:
                    RenderTable(*((Table *)element.ptr), display);
                    break;

                case KEYBOX:
                    RenderKeybox(*((Keybox *)element.ptr), display, Start_pos);
                    break;
                case LABEL:

                    RenderLabel(*((Label *)element.ptr), display, Start_pos);
                    break;
                }
            }
            else if (form.renderNullElements && element.type != NONRENDER)
            {
                RenderNullElement({j, i}, display, Start_pos);
            }
        }
    }
}

void ShowMessageBox(Messagebox &messagebox, string sec_color)
{
    int maxLineLength = 40;
    for (int i = 0; i < messagebox.linesCount; i++)
    {
        maxLineLength = maxLineLength > messagebox.lines[i].length() ? maxLineLength : messagebox.lines[i].length();
    }
    int width = maxLineLength + 6;
    int height = 10 + messagebox.linesCount;
    int centerIndex;
    Coordinate elementPos = GetCenteredCoordinates(width, height);
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, sec_color, sec_color, 3);
    switch (messagebox.icon)
    {
    case INFORMATION:
        centerIndex = CalculateCenterIndex(width - 2, 20);
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 1);
        cout << FG_BLUE << R"( ___ _  _ ___ ___  )";
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 2);
        cout << FG_BLUE << R"(|_ _| \| | __/ _ \ )";
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 3);
        cout << FG_BLUE << R"( | || .` | _| (_) |)";
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 4);
        cout << FG_BLUE << R"(|___|_|\_|_| \___/ )";
        break;
    case WARNING:
        centerIndex = CalculateCenterIndex(width - 2, 37);
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 1);
        cout << FG_YELLOW << R"(__      ___   ___ _  _ ___ _  _  ___ )" << sec_color;
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 2);
        cout << FG_YELLOW << R"(\ \    / /_\ | _ \ \| |_ _| \| |/ __|)" << sec_color;
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 3);
        cout << FG_YELLOW << R"( \ \/\/ / _ \|   / .` || || .` | (_ |)" << sec_color;
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 4);
        cout << FG_YELLOW << R"(  \_/\_/_/ \_\_|_\_|\_|___|_|\_|\___|)" << sec_color;
        break;
    case CRITICAL:
        centerIndex = CalculateCenterIndex(width - 2, 23);
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 1);
        cout << FG_RED << R"( ___ ___ ___  ___  ___ )" << sec_color;
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 2);
        cout << FG_RED << R"(| __| _ \ _ \/ _ \| _ \)" << sec_color;
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 3);
        cout << FG_RED << R"(| _||   /   / (_) |   /)" << sec_color;
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 4);
        cout << FG_RED << R"(|___|_|_\_|_\\___/|_|_\)" << sec_color;
        break;
    }
    centerIndex = CalculateCenterIndex(width - 2, messagebox.header.length());
    Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 6);
    cout << sec_color << messagebox.header << sec_color;
    for (int i = 0; i < messagebox.linesCount; i++)
    {
        string text = messagebox.lines[i];
        centerIndex = CalculateCenterIndex(width - 2, text.length());
        Gotoxy(elementPos.x + centerIndex + 1, elementPos.y + 8 + i);
        cout << sec_color << text << sec_color;
    }
    RenderFooter("[Any Key]: Close Messagebox", sec_color);
    char ch = getch();
}
bool CanAccess(Form &form, Position position)
{
    return position.row >= 0 && position.row < form.rows_count &&
           position.col >= 0 && position.col < form.cols_count;
}

void UpdateSelectBoxSelection(Selectbox &selectbox, int input)
{
    if (input == 5)
    {
        selectbox.SelectedIndex--;
        if (selectbox.SelectedIndex < 0)
            selectbox.SelectedIndex = selectbox.ItemsCount - 1;
    }
    else if (input == 6)
    {
        selectbox.SelectedIndex++;
        if (selectbox.SelectedIndex > selectbox.ItemsCount - 1)
            selectbox.SelectedIndex = 0;
    }
}
void UpdateRangebarValue(Rangebar &Rangebar, int input)
{
    int dis = Rangebar.max - Rangebar.min;
    int step = (dis < 28) ? 1 : dis / 28;
    if (input == 5 && Rangebar.value > Rangebar.min)
    {
        Rangebar.value -= step;
        if (Rangebar.value < Rangebar.min)
            Rangebar.value = Rangebar.min;
    }
    else if (input == 6 && Rangebar.value < Rangebar.max)
    {
        Rangebar.value += step;
        if (Rangebar.value > Rangebar.max)
            Rangebar.value = Rangebar.max;
    }
}

void ScrollTable(Table &table, int input)
{
    if (input == 5 && table.start_row > 0)
    {
        table.start_row--;
    }
    else if (input == 6 && table.rows_count - table.start_row >= table.Showed_rows_count)
    {
        table.start_row++;
    }
}
void ToggleCheckboxState(Checkbox &checkbox)
{
    checkbox.isChecked = !checkbox.isChecked;
}
bool IsElementEnabled(Element element)
{
    switch (element.type)
    {
    case CHECKBOX:
        return (*((Checkbox *)element.ptr)).IsEnabled;
    case SELECTBOX:
        return (*((Selectbox *)element.ptr)).IsEnabled;
    case RANGEBAR:
        return (*((Rangebar *)element.ptr)).IsEnabled;
    case TEXTBOX:
        return (*((Textbox *)element.ptr)).IsEnabled;
    case BUTTON:
        return (*((Button *)element.ptr)).IsEnabled;
    case TABLE:
        return (*((Table *)element.ptr)).IsEnabled;
    case KEYBOX:
        return (*((Keybox *)element.ptr)).IsEnabled;
    default:
        return false;
    }
}
bool CanSelect(Element element)
{
    bool IsEnabled = IsElementEnabled(element);
    return element.ptr != nullptr && element.type != LABEL && IsEnabled;
}
void HandleNavigation(char input, Form &form, Display &display)
{
    input = std::tolower(static_cast<unsigned char>(input));
    int visibleRows = display.end_row - display.start_row;
    int visibleCols = display.end_col - display.start_col;
    Position newUserPosition = display.userPosition;
    switch (input)
    {
    case 'w':
        while (newUserPosition.row > 0)
        {
            newUserPosition.row--;
            if (CanSelect(form.ElementsGrid[newUserPosition.row][newUserPosition.col]))
                break;
        }
        break;

    case 's':
        while (newUserPosition.row < form.rows_count - 1)
        {
            newUserPosition.row++;
            if (CanSelect(form.ElementsGrid[newUserPosition.row][newUserPosition.col]))
                break;
        }
        break;

    case 'a':
        while (newUserPosition.col > 0)
        {
            newUserPosition.col--;
            if (CanSelect(form.ElementsGrid[newUserPosition.row][newUserPosition.col]))
                break;
        }
        break;

    case 'd':
        while (newUserPosition.col < form.cols_count - 1)
        {
            newUserPosition.col++;
            if (CanSelect(form.ElementsGrid[newUserPosition.row][newUserPosition.col]))
                break;
        }
        break;

    default:
        return;
    }
    if (CanSelect(form.ElementsGrid[newUserPosition.row][newUserPosition.col]))
    {
        bool isChange = false;
        if (newUserPosition.row < display.start_row)
        {
            display.start_row = 0 > display.start_row - (display.userPosition.row - newUserPosition.row) ? 0 : display.start_row - (display.userPosition.row - newUserPosition.row);
            display.end_row = display.start_row + visibleRows;
            isChange = true;
        }
        else if (newUserPosition.row > display.end_row)
        {
            display.end_row = form.rows_count - 1 > display.end_row + (newUserPosition.row - display.userPosition.row) ? display.end_row + (newUserPosition.row - display.userPosition.row) : form.rows_count - 1;
            display.start_row = display.end_row - visibleRows;
            isChange = true;
        }

        if (newUserPosition.col < display.start_col)
        {
            display.start_col = 0 > display.start_col - (display.userPosition.col - newUserPosition.col) ? 0 : display.start_col - (display.userPosition.col - newUserPosition.col);
            display.end_col = display.start_col + visibleCols;
            isChange = true;
        }
        else if (newUserPosition.col > display.end_col)
        {
            display.end_col = form.cols_count - 1 > display.end_col + (newUserPosition.col - display.userPosition.col) ? display.end_col + (newUserPosition.col - display.userPosition.col) : form.cols_count - 1;
            display.start_col = display.end_col - visibleCols;
            isChange = true;
        }
        form.renderBackground = isChange;
        if ((newUserPosition.col != display.userPosition.col || newUserPosition.row != display.userPosition.row) && form.isSoundEnabled)
        {
            PlayNavigateSound();
        }
        display.userPosition = newUserPosition;
    }
}

void GetTextboxValue(Textbox &textbox, Display &display, Coordinate elementPos)
{
    string fg_color = "";
    fg_color = FG_YELLOW;
    int width = ELEMENT_WIDTH;
    int height = ELEMENT_HEIGHT;
    elementPos.y += (textbox.position.row - display.start_row) * FORM_ROW_STEP;
    elementPos.x += (textbox.position.col) * FORM_COL_STEP;
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, fg_color, display.secondaryColor, 2);
    RenderFooter("[Enter]: Set Value", display.secondaryColor);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));
    string title = textbox.title.substr(0, 10);
    cout << fg_color << setw(10) << left << title;
    Gotoxy(elementPos.x + 15, elementPos.y + (height / 2));
    ShowCursor();
    textbox.value = GetInput(30);
    HideCursor();
}

void GetKeyboxValue(Keybox &keybox, Display &display, Coordinate elementPos)
{
    string fg_color = FG_YELLOW;
    elementPos.y += (keybox.position.row - display.start_row) * FORM_ROW_STEP;
    elementPos.x += (keybox.position.col - display.start_col) * FORM_COL_STEP;
    int width = ELEMENT_WIDTH;
    int height = ELEMENT_HEIGHT;
    Gotoxy(elementPos.x, elementPos.y);
    DrawBox(width, height, fg_color, display.secondaryColor, 2);
    Gotoxy(elementPos.x + 4, elementPos.y + (height / 2));

    string title = keybox.title.substr(0, 10);
    cout << fg_color << setw(10) << left << title;
    Gotoxy(elementPos.x + 37, elementPos.y + 1);
    cout << fg_color << "<";
    Gotoxy(elementPos.x + width - 5, elementPos.y + 1);
    cout << fg_color << ">";
    Gotoxy(elementPos.x + 39, elementPos.y + 1);

    while (true)
    {
        unsigned char ch = getch();

        if (ch == 0xE0 || ch == 0x00)
        {
            unsigned char arrow = getch();
            /* switch (arrow)
            {
            case 72:
                keybox.value = '^';
                return;
            case 80:
                keybox.value = '/';
                return;
            case 77:
                keybox.value = '>';
                return;
            case 75:
                keybox.value = '<';
                return;
            default:
                continue;
            } */
            continue;
        }
        else if (ch == 27)
        {
            keybox.value = '*';
            return;
        }
        else if (ch == 13)
        {
            keybox.value = '\r';
            return;
        }
        else if (ch == 32)
        {
            keybox.value = ' ';
            return;
        }
        else if (std::isalnum(ch))
        {
            keybox.value = std::toupper(ch);
            return;
        }
        else
        {
            continue;
        }
    }
}

void OnPress6(void *element, ElementType type, Display &display, Form &form)
{
    Coordinate Start_pos = start_area;
    if (display.end_col - display.start_col == 0 && form.isCenter)
    {
        Start_pos.x += 26;
    }
    switch (type)
    {
    case CHECKBOX:
        ToggleCheckboxState(*((Checkbox *)element));
        break;
    case SELECTBOX:
        UpdateSelectBoxSelection(*((Selectbox *)element), 6);
        break;
    case RANGEBAR:
        UpdateRangebarValue(*((Rangebar *)element), 6);
        break;
    case TEXTBOX:
        GetTextboxValue(*((Textbox *)element), display, Start_pos);
        break;
    case TABLE:
        ScrollTable(*((Table *)element), 6);
        break;
    case KEYBOX:
        GetKeyboxValue(*((Keybox *)element), display, Start_pos);
        break;
    }
}
void OnPress5(void *element, ElementType type, Display &display)
{
    switch (type)
    {
    case SELECTBOX:
        UpdateSelectBoxSelection(*((Selectbox *)element), 5);
        break;
    case RANGEBAR:
        UpdateRangebarValue(*((Rangebar *)element), 5);
        break;
    case TABLE:
        ScrollTable(*((Table *)element), 5);
        break;
    }
}
void HandleInput(char input, Display &display, Form &form)
{
    Element element = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
    if (input == 'x')
    {
        OnPress6(element.ptr, element.type, display, form);
    }
    else if (input == 'z')
    {
        OnPress5(element.ptr, element.type, display);
    }
    else if (input == 27)
    {
        form.isRunning = false;
    }
    else
    {
        HandleNavigation(input, form, display);
    }
}
string GetKeyHints(ElementType type)
{
    string result = "";
    switch (type)
    {
    case CHECKBOX:
        result = "[X]: Toggle Checkbox";
        break;
    case SELECTBOX:
        result = "[Z]: Previous Option  [X]: Next Option";
        break;
    case TEXTBOX:
        result = "[X]: Edit Text";
        break;
    case RANGEBAR:
        result = "[Z]: Decrease Value  [X]: Increase Value";
        break;
    case KEYBOX:
        result = "[X]: Edit Key";
        break;
    case BUTTON:
        result = "[ENTER]: Press Button";
        break;
    default:
        result = "Use [W], [A], [S], [D] to Navigate, [Enter] to Select.";
        break;
    }
    return result;
}

void DeleteElement(Form &form, Position position)
{
    switch (form.ElementsGrid[position.row][position.col].type)
    {
    case CHECKBOX:
        delete (Checkbox *)form.ElementsGrid[position.row][position.col].ptr;
        form.ElementsGrid[position.row][position.col].ptr = nullptr;
        form.ElementsGrid[position.row][position.col].type = NULLELEMENT;
        break;
    case SELECTBOX:
        delete (Selectbox *)form.ElementsGrid[position.row][position.col].ptr;
        form.ElementsGrid[position.row][position.col].ptr = nullptr;
        form.ElementsGrid[position.row][position.col].type = NULLELEMENT;
        break;
    case RANGEBAR:
        delete (Rangebar *)form.ElementsGrid[position.row][position.col].ptr;
        form.ElementsGrid[position.row][position.col].ptr = nullptr;
        form.ElementsGrid[position.row][position.col].type = NULLELEMENT;
        break;
    }
}
void AddElementToForm(Form &form, Element &element, Position position)
{
    if (form.ElementsGrid[position.row][position.col].ptr == nullptr && form.ElementsGrid[position.row][position.col].type == NULLELEMENT)
    {
        DeleteElement(form, position);
        form.ElementsGrid[position.row][position.col] = element;
    }
};
void AddButtonToForm(Form &form, Button *button)
{
    Element element = {button, BUTTON};
    AddElementToForm(form, element, (*button).position);
}
void AddTextboxToForm(Form &form, Textbox *textbox)
{
    Element element = {textbox, TEXTBOX};
    AddElementToForm(form, element, (*textbox).position);
}
void AddRangebarToForm(Form &form, Rangebar *rangebar)
{
    Element element = {rangebar, RANGEBAR};
    AddElementToForm(form, element, (*rangebar).position);
}
void AddCheckboxToForm(Form &form, Checkbox *checkbox)
{
    Element element = {checkbox, CHECKBOX};
    AddElementToForm(form, element, (*checkbox).position);
}
void AddSelectboxToForm(Form &form, Selectbox *selectbox)
{
    Element element = {selectbox, SELECTBOX};
    AddElementToForm(form, element, (*selectbox).position);
}
void AddTableToForm(Form &form, Table *table)
{
    Element element = {table, TABLE};
    AddElementToForm(form, element, (*table).position);
}
void AddKeyboxToForm(Form &form, Keybox *keybox)
{
    Element element = {keybox, KEYBOX};
    AddElementToForm(form, element, (*keybox).position);
}
void AddNonRenderElementToForm(Form &form, Position position)
{
    Element element = {nullptr, NONRENDER};

    AddElementToForm(form, element, position);
}
void AddLabelToForm(Form &form, Label *label)
{
    Element element = {label, LABEL};

    AddElementToForm(form, element, (*label).position);
    Position pos = (*label).position;
    for (int i = 1; i < (*label).row; i++)
    {
        pos.row++;
        AddNonRenderElementToForm(form, pos);
    }
}
void InitialElementGrid(Form &form)
{
    form.ElementsGrid = new Element *[form.rows_count];
    for (int i = 0; i < form.rows_count; i++)
    {
        form.ElementsGrid[i] = new Element[form.cols_count];
        for (int j = 0; j < form.cols_count; j++)
        {
            form.ElementsGrid[i][j].ptr = nullptr;
            form.ElementsGrid[i][j].type = NULLELEMENT;
        }
    }
}
void FreeElementGrid(Form &form)
{
    for (int i = 0; i < form.rows_count; i++)
    {
        delete[] form.ElementsGrid[i];
    }
    delete[] form.ElementsGrid;
};
void CloseForm(Form &form)
{
    FreeElementGrid(form);
}
void InitialDisplay(Display &display)
{
    Generalsettings settings;
    LoadSettings(settings);
    display.primaryColor = GenerateANSI(settings.PrimaryColor);
    display.secondaryColor = GenerateANSI(settings.SecondaryColor);
}
