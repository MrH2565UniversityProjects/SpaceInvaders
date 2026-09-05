#include <iostream>
#include <windows.h>
#include "form.h"
#include "utilities.h"
#include "Settings.h"
#include "Audio.h"
// #include "Game.h"
#include "Game.h"
#include "Leaderboard.h"
using namespace std;

void SurvivalGameplaySettings()
{
    Form form = {"Gameplay Settings", 10, 2};
    GameOptions gameoptions;
    Generalsettings generalsettings;
    LoadSettings(generalsettings);
    form.isSoundEnabled = generalsettings.Sound;
    Display display = {0, 4, 0, 1, {0, 0}};
    InitialDisplay(display);
    Textbox PlayerName = {"Name:", "Enter Your Name", "", "", true, false, {0, 0}};
    Selectbox difficulty = {{{"Easy", 0}, {"Medium", 1}, {"Hard", 2}}, "Difficulty:", 3, 0, {1, 0}};
    Label SpaceshipLabel = {{"Spaceship Settings", 18}, 1, {2, 0}};
    Selectbox SpaceshipType = {{{"A", 0}, {"B", 1}, {"C", 2}}, "Type:", 3, 0, {3, 0},true};
    Button StartButton = {"Start", {4, 0}, true, 0};
    InitialElementGrid(form);
    AddTextboxToForm(form, &PlayerName);
    AddLabelToForm(form, &SpaceshipLabel);
    AddSelectboxToForm(form, &difficulty);
    AddSelectboxToForm(form, &SpaceshipType);
    AddButtonToForm(form, &StartButton);
    while (form.isRunning)
    {
        if (form.renderBackground)
        {
            RenderBackground(display);
            form.renderBackground = false;
        }
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type), display.secondaryColor);
        char ch = getch();
        if (SelectedElement.type == BUTTON && ch == '\r')
        {
            Button *button = (Button *)(SelectedElement.ptr);
            switch ((*button).id)
            {
            case 0:
                form.isRunning = false;
                gameoptions.difficulty = (GameDifficulty)difficulty.SelectedIndex;
                gameoptions.playerName = PlayerName.value;
                gameoptions.SpaceshipType = SpaceshipType.SelectedIndex;
                RunGame(gameoptions, false);
                ClearScreen();
                form.renderBackground = true;
                break;
            case 1:
                break;
            }
        }
        else
        {
            HandleInput(ch, display, form);
        }
    }
    CloseForm(form);
}

void CustomGameplaySettings()
{
    Form form = {"Gameplay Settings", 8, 2};
    Generalsettings generalsettings;
    LoadSettings(generalsettings);
    form.isSoundEnabled = generalsettings.Sound;
    Display display = {0, 4, 0, 1, {0, 0}};
    InitialDisplay(display);
    GameOptions gameoptions;
    Textbox PlayerName = {"Name:", "Enter Your Name", "", "", true, false, {0, 0}};
    Label Spaceship = {{"Spaceship Settings", 18}, 1, {1, 0}};
    Selectbox SpaceshipType = {{{"A", 0}, {"B", 1}, {"C", 2}}, "Type:", 3, 0, {2, 0},true};
    Rangebar Health = {"Health:", 10, 60, 20, false, {3, 0}};
    Button StartButton = {"Start", {4, 0}, true, 0};
    InitialElementGrid(form);
    AddTextboxToForm(form, &PlayerName);
    AddLabelToForm(form, &Spaceship);
    AddSelectboxToForm(form, &SpaceshipType);
    AddRangebarToForm(form, &Health);
    AddButtonToForm(form, &StartButton);
    while (form.isRunning)
    {
        if (form.renderBackground)
        {
            RenderBackground(display);
            form.renderBackground = false;
        }
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type), display.secondaryColor);
        char ch = getch();
        if (SelectedElement.type == BUTTON && ch == '\r')
        {
            Button *button = (Button *)(SelectedElement.ptr);
            switch ((*button).id)
            {
            case 0:
                form.isRunning = false;
                gameoptions.difficulty = (GameDifficulty)3;
                gameoptions.playerName = PlayerName.value;
                gameoptions.SpaceshipType = SpaceshipType.SelectedIndex;
                gameoptions.maxHealth = Health.value;
                RunGame(gameoptions, false);
                ClearScreen();
                form.renderBackground = true;
                break;
            case 1:
                break;
            }
        }
        else
        {
            HandleInput(ch, display, form);
        }
    }
    CloseForm(form);
}
void GameModesMenu()
{
    Form form = {"Game Modes", 5, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    Generalsettings generalsettings;
    LoadSettings(generalsettings);
    form.isSoundEnabled = generalsettings.Sound;
    InitialDisplay(display);
    Button SurvivalButton = {"Survival", {0, 0}, true, 0};
    Button CustomGameButton = {"Custom Game", {1, 0}, true, 1};

    InitialElementGrid(form);
    AddButtonToForm(form, &SurvivalButton);
    AddButtonToForm(form, &CustomGameButton);
    while (form.isRunning)
    {
        if (form.renderBackground)
        {
            RenderBackground(display);
            form.renderBackground = false;
        }
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type), display.secondaryColor);
        char ch = getch();
        if (SelectedElement.type == BUTTON && ch == '\r')
        {
            Button *button = (Button *)(SelectedElement.ptr);
            switch ((*button).id)
            {
            case 0:
                SurvivalGameplaySettings();
                form.renderBackground = true;
                break;
            case 1:
                CustomGameplaySettings();
                form.renderBackground = true;
                break;
            }
        }
        else
        {
            HandleInput(ch, display, form);
        }
    }
}
void KeyBindings(Generalsettings &settings)
{
    Form form = {"Key Bindings", 5, 2};
    Keybindings &keybindings = settings.keybindings;
    form.isSoundEnabled = settings.Sound;
    Label Player1 = {{"Player1", 7}, 1, {0, 0}};
    Label Player2 = {{"Player2", 7}, 1, {0, 1}};
    Display display = {0, 4, 0, 1, {1, 0}};
    InitialDisplay(display);
    Keybox Left_Player1 = {"Move Left:", keybindings.Left_Player1, {1, 0}};
    Keybox Right_Player1 = {"Move Right:", keybindings.Right_Player1, {2, 0}};
    Keybox Shoot_Player1 = {"Shoot:", keybindings.Shoot_Player1, {3, 0}};
    Keybox Left_Player2 = {"Move Left:", keybindings.Left_Player2, {1, 1}};
    Keybox Right_Player2 = {"Move Right:", keybindings.Right_Player2, {2, 1}};
    Keybox Shoot_Player2 = {"Shoot:", keybindings.Shoot_Player2, {3, 1}};
    Button BackButton = {"Back", {4, 0}, true, 0};
    InitialElementGrid(form);
    AddKeyboxToForm(form, &Left_Player1);
    AddKeyboxToForm(form, &Right_Player1);
    AddKeyboxToForm(form, &Shoot_Player1);
    AddKeyboxToForm(form, &Left_Player2);
    AddKeyboxToForm(form, &Right_Player2);
    AddKeyboxToForm(form, &Shoot_Player2);
    AddLabelToForm(form, &Player1);
    AddLabelToForm(form, &Player2);
    AddButtonToForm(form, &BackButton);
    while (form.isRunning)
    {
        if (form.renderBackground)
        {
            RenderBackground(display);
            form.renderBackground = false;
        }
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type), display.secondaryColor);
        char ch = getch();
        if (SelectedElement.type == BUTTON && ch == '\r')
        {
            break;
        }
        HandleInput(ch, display, form);
    }

    keybindings.Left_Player1 = Left_Player1.value;
    keybindings.Right_Player1 = Right_Player1.value;
    keybindings.Shoot_Player1 = Shoot_Player1.value;
    keybindings.Left_Player2 = Left_Player2.value;
    keybindings.Right_Player2 = Right_Player2.value;
    keybindings.Shoot_Player2 = Shoot_Player2.value;

    CloseForm(form);
}
void GeneralSettings()
{
    Generalsettings generalsettings;
    LoadSettings(generalsettings);
    Form form = {"Settings", 10, 2};
    form.isSoundEnabled = generalsettings.Sound;
    Display display = {0, 4, 0, 1, {1, 0}};
    InitialDisplay(display);
    Label AudioSettings = {{"Audio Settings", 14}, 1, {0, 0}};
    Checkbox MusicCheckbox = {"Music", false, {1, 1}};
    Checkbox SoundCheckbox = {"Sound", false, {1, 0}};
    Button KeyBindingsButton = {"Key Bindings", {2, 0}, true, 0};
    Label Colors = {{"Colors", 6}, 1, {3, 0}};
    Selectbox PrimaryColor = {{{"CYAN", 333}, {"BLUE", 213}, {"PURPLE", 543}, {"WHITE", 2553}}, "Primary", 4, 0, {4, 0}};
    Selectbox SecondaryColor = {{{"CYAN", 333}, {"BLUE", 213}, {"PURPLE", 543}, {"WHITE", 2553}}, "Secondary", 4, 0, {4, 1}};
    Button SaveChangesButton = {"Save Changes", {5, 0}, true, 1};
    Button ResetSettingsButton = {"ResetSettings", {5, 1}, true, 2};
    MusicCheckbox.isChecked = generalsettings.Music;
    SoundCheckbox.isChecked = generalsettings.Sound;
    PrimaryColor.SelectedIndex = GetItemIndexByValue(PrimaryColor, generalsettings.PrimaryColor);
    SecondaryColor.SelectedIndex = GetItemIndexByValue(SecondaryColor, generalsettings.SecondaryColor);
    InitialElementGrid(form);
    AddCheckboxToForm(form, &MusicCheckbox);
    AddCheckboxToForm(form, &SoundCheckbox);
    AddLabelToForm(form, &AudioSettings);
    AddLabelToForm(form, &Colors);
    AddButtonToForm(form, &KeyBindingsButton);
    AddButtonToForm(form, &ResetSettingsButton);
    AddSelectboxToForm(form, &PrimaryColor);
    AddSelectboxToForm(form, &SecondaryColor);
    AddButtonToForm(form, &SaveChangesButton);

    while (form.isRunning)
    {
        if (form.renderBackground)
        {
            RenderBackground(display);
            form.renderBackground = false;
        }
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type), display.secondaryColor);
        char ch = getch();
        if (SelectedElement.type == BUTTON && ch == '\r')
        {
            Button *button = (Button *)(SelectedElement.ptr);
            switch ((*button).id)
            {
            case 0:
                KeyBindings(generalsettings);
                break;
            case 1:
                generalsettings.Music = MusicCheckbox.isChecked;
                generalsettings.Sound = SoundCheckbox.isChecked;
                generalsettings.PrimaryColor = PrimaryColor.Items[PrimaryColor.SelectedIndex].value;
                generalsettings.SecondaryColor = SecondaryColor.Items[SecondaryColor.SelectedIndex].value;
                SaveSettings(generalsettings);

                form.isRunning = false;
                break;
            case 2:
                break;
            case 3:
                break;
            }
        }
        else
        {
            HandleInput(ch, display, form);
        }
    }

    CloseForm(form);
}
void HowToPlay(Display display)
{
    Messagebox howToPlay = {"How To Play",
                            {"Objective: Shoot all aliens before they reach you.",
                             "Controls: Move with arrow keys, shoot with spacebar.",
                             "Tips: Use shields for cover and shoot bonus UFOs for extra points.",
                             "Game Over: Lose if aliens reach your base or you run out of lives."},
                            4,
                            INFORMATION,
                            true};
    ShowMessageBox(howToPlay, display.secondaryColor);
}
void MainMenu()
{
    bool MusicIsPlay = false;
    Form form = {"Main Menu", 6, 2};
    Display display = {0, 4, 0, 1, {0, 0}};
    InitialDisplay(display);
    Generalsettings generalsettings;
    LoadSettings(generalsettings);
    form.isSoundEnabled = generalsettings.Sound;
    Button NewGameButton = {"New Game", {0, 0}, true, 0};
    Button LoadGameButton = {"Load Game", {1, 0}, false, 1};
    Button SettingsButton = {"Settings", {2, 0}, true, 2};
    Button HowToPlayButton = {"How to play", {3, 0}, true, 3};
    Button LeaderboardButton = {"Leaderboard", {4, 0}, true, 4};
    Button ExitButton = {"Exit", {5, 0}, true, 5};
    LoadGameButton.IsEnabled = fileExists("usersave.bin");
    InitialElementGrid(form);
    AddButtonToForm(form, &NewGameButton);
    AddButtonToForm(form, &LoadGameButton);
    AddButtonToForm(form, &SettingsButton);
    AddButtonToForm(form, &HowToPlayButton);
    AddButtonToForm(form, &LeaderboardButton);
    AddButtonToForm(form, &ExitButton);
    while (form.isRunning)
    {
        if (!MusicIsPlay && generalsettings.Music)
        {
            PlayBackgroundMusic();
            MusicIsPlay = true;
        }
        else if (MusicIsPlay && !generalsettings.Music)
        {
            StopBackgroundMusic();
            MusicIsPlay = false;
        }
        if (form.renderBackground)
        {
            RenderBackground(display);
            form.renderBackground = false;
        }
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type), display.secondaryColor);
        GameOptions gameoptions;
        char ch = getch();
        if (SelectedElement.type == BUTTON && ch == '\r')
        {
            Button *button = (Button *)(SelectedElement.ptr);
            switch ((*button).id)
            {
            case 0:
                GameModesMenu();
                LoadGameButton.IsEnabled = fileExists("usersave.bin");

                form.renderBackground = true;
                break;
            case 1:

                RunGame(gameoptions, true);
                LoadGameButton.IsEnabled = fileExists("usersave.bin");

                ClearScreen();
                form.renderBackground = true;
                break;
            case 2:
                GeneralSettings();
                InitialDisplay(display);
                LoadSettings(generalsettings);
                form.isSoundEnabled = generalsettings.Sound;
                form.renderBackground = true;
                break;
            case 3:
                if (generalsettings.Sound)
                {
                    PlayAlertSound();
                }
                HowToPlay(display);
                form.renderBackground = true;
                break;
            case 4:
                LeaderboardMenu();
                form.renderBackground = true;
                break;
            case 5:
                form.isRunning = false;
                break;
            }
        }
        else
        {
            HandleInput(ch, display, form);
        }
    }
    CloseForm(form);
}
int main()
{
    ClearScreen();
    SendMessage(GetConsoleWindow(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    HideCursor();
    MainMenu();
    return 0;
}