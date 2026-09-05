#include <iostream>
#include <cmath>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>
#include <chrono>
#include "utilities.h"
#include "game.h"
#include "color.h"
#include "settings.h"
#include "Audio.h"
#include "form.h"
#include "Leaderboard.h"
void DrawEnemies(EnemiesData &data);
Generalsettings settings;
EnemySpaceship enemyspaceship = {1, 1, {{20230,20230,0,20230,20230,0,20230,20230},{20232,20233,20235,0,0,20235,20232,20233}}, 500, 5, 5};
Enemy EnemyType3 = {10, {{7236, 0, 7236, 0, 7236}, {7232, 7235, 7232, 7235, 7232}, {7235, 7236, 7235, 7236, 7235}}, {{7236, 0, 7236, 0, 7236}, {7233, 7235, 7233, 7235, 7233}, {7235, 7236, 7235, 7236, 7235}}, true, true, 200};
Enemy EnemyType2 = {5, {{7532, 7536, 7536, 7536, 7533}, {7530, 7532, 0, 7533, 7530}, {7536, 7535, 7535, 7535, 7536}}, {{7532, 7536, 7536, 7536, 7533}, {7530, 7532, 19630, 7533, 7530}, {7536, 7535, 7535, 7535, 7536}}, true, true, 150};
Enemy EnemyType1 = {5, {{19730, 19730, 19730, 19730, 19730}, {19730, 3330, 19730, 3330, 19730}, {0, 19730, 0, 19730, 0}}, {{19730, 19730, 19730, 19730, 19730}, {19730, 3330, 19730, 3330, 19730}, {19730, 0, 0, 0, 19730}}, true, true, 100};
Enemy Enemies[3] = {EnemyType1, EnemyType2, EnemyType3};
Bullet EnemyBullet = {50, 5, "╽", 333, false, true, false};
Bullet NormalBullet = {50, 5, "╿", 1963, false, true, false};
Ship ship1 = {0, 30,{{1730,12438,12438,12438,12438,1730},{1730,1730,1730,1730,1730,1730}}, 58, 38};
Ship ship2 = {0, 30,{{5332,0,16738,16734,0,5333},{5330,5330,5337,5337,5330,5330}} , 58, 38};
Ship ship3 = {0, 30,{{20834,0,20834,20834,0,20834},{22030,22036,22030,22030,22036,22030}}, 58, 38};
Ship ships[3] = {ship1,ship2,ship3};
Wall wall = { 0 , 0 , { {0,21430,21430,21430,21430,21430,21430,21430,21430,21430,0,0,21530,21530,21530,21530,21530,21530,21530,21530,21530,21530,
	0,0,21630,21630,21630,21630,21630,21630,21630,21630,21630,21630,0,0,21730,21730,21730,21730,21730,21730,21730,21730,21730,21730,0,0,
	21830,21830,21830,21830,21830,21830,21830,21830,21830,21830,0,0,21930,21930,21930,21930,21930,21930,21930,21930,21930,21930,0,0,
	18330,18330,18330,18330,18330,18330,18330,18330,18330,18330,0,0,14730,14730,14730,14730,14730,14730,14730,14730,14730} ,
	{0,21430,21430,21435,21435,21435,21435,21435,21430,21430,0,0,21530,21530,21530,21535,21535,21535,21535,21530,21530,21530,0,0,
	21630,21630,21630,21630,21635,21636,0,21630,21630,21630,0,0,21730,21730,21730,0,21736,21736,0,21730,21730,21730,0,0,
	21830,21830,21830,21836,21836,21836,0,21830,21830,21830,0,0,21930,21930,21930,21935,21935,21935,21935,21930,21930,21930,0,0,
	18330,18330,18330,0,18336,0,18330,18330,18330,18330,0,0,14730,14730,0,14730,14730,0,14730,14730,14730} ,
	{0,21430,21430,0,21430,21430,21430,21430,21430,21430,0,0,21530,21530,21530,0,21535,21535,21535,21530,21530,21530,0,0,
	21630,21630,21630,0,21635,21635,0,21635,21630,21630,0,0,21730,21730,21730,0,21730,21730,0,21730,21730,21730,0,0,
	21830,21830,21830,0,0,0,0,21830,21830,21830,0,0,21930,21930,21930,0,21935,21935,21935,21930,21930,21930,0,0,
	18330,18330,18330,0,18335,0,18335,18330,18330,18330,0,0,14730,14730,0,14730,14730,0,14730,14730,14730} , 
	{0,21430,21430,0,21435,21435,21435,21435,21430,21430,0,0,21530,21530,21530,21535,21535,21535,0,21530,21530,21530,0,0,
	21630,21630,21630,21630,21630,21630,0,21630,21630,21630,0,0,21730,21730,21730,0,21735,21735,0,21730,21730,21730,0,0,
	21830,21830,21830,21835,21835,21835,0,21830,21830,21830,0,0,21930,21930,21930,21935,21935,21935,0,21930,21930,21930,0,0,
	18330,18330,18330,0,18335,18335,0,18330,18330,18330,0,0,14730,14730,0,0,0,0,14730,14730,14730} ,
	{0,21430,21430,21430,21430,21430,21430,21430,21430,21430,0,0,21530,21530,21530,21530,21530,21530,21530,21530,21530,21530,
	0,0,21630,21630,21630,21630,21630,21630,21630,21630,21630,21630,0,0,21730,21730,21730,21730,21730,21730,21730,21730,21730,21730,0,0,
	21830,21830,21830,21830,21830,21830,21830,21830,21830,21830,0,0,21930,21930,21930,21930,21930,21930,21930,21930,21930,21930,0,0,
	18330,18330,18330,18330,18330,18330,18330,18330,18330,18330,0,0,14730,14730,14730,14730,14730,14730,14730,14730,14730 } } , 14 , 30 , true } ;
void EraseFill(int row, int col, int cursorX, int cursorY)
{
    for (int i = 0; i < row; i++)
    {
        Gotoxy(cursorX, cursorY + i);
        for (int j = 0; j < col; j++)
        {
            cout << " " << FG_WHITE;
        }
    }
}
void EraseDown(int row, int col, int cursorX, int cursorY)
{
    Gotoxy(cursorX, cursorY + row - 1);
    for (int j = 0; j < col; j++)
    {
        cout << " " << FG_WHITE;
    }
}
void EraseUp(int col, int cursorX, int cursorY)
{
    Gotoxy(cursorX, cursorY);
    for (int j = 0; j < col; j++)
    {
        cout << " " << FG_WHITE;
    }
}
void EraseLeft(int row, int col, int cursorX, int cursorY)
{

    for (int j = 0; j < row; j++)
    {
        Gotoxy(cursorX, cursorY + j);
        cout << " " << FG_WHITE;
    }
}
void EraseRight(int row, int col, int cursorX, int cursorY)
{

    for (int j = 0; j < row; j++)
    {
        Gotoxy(cursorX + col - 1, cursorY + j);
        cout << " " << FG_WHITE;
    }
}
string GenerateCharacter(int code)
{
    switch (code)
    {
    case 0:
        return "█";
    case 1:
        return "▓";
    case 2:
        return "▌";
    case 3:
        return "▐";
    case 4:
        return "▲";
    case 5:
        return "▀";
    case 6:
        return "▄";
    case 7:
        return "░";
    case 8:
        return "▼";
    case 9:
        return "";
    }
    return "";
}
void DrawEntity(int *entity, int row, int col, int cursorX, int cursorY, bool isErase)
{
    int *currentEntity = entity;
    string lastColor = "";
    for (int i = 0; i < row; i++)
    {
        Gotoxy(cursorX, cursorY + i);
        for (int j = 0; j < col; j++)
        {
            int value = *currentEntity++;
            if (!isErase && value > 0)
            {
                string character = GenerateCharacter((value % 10));
                string color = GenerateANSI(value / 10);
                if (color != lastColor)
                {
                    lastColor = color;
                }
                cout << lastColor << character;
            }
            else
            {
                cout << " ";
            }
        }
        cout << FG_WHITE;
    }
}

void CreateLevel(GameOptions &game)
{
    LevelOptions startLevel;
    startLevel.number = 1;
    switch (game.difficulty)
    {
    case EASY:
        startLevel.enemyShotDelay = 500;
        startLevel.enemySpaceshipDelay = 5000;
        startLevel.enemySpeed = 2500;
        game.maxHealth = 50;
        break;
    case MEDIUM:
        startLevel.enemyShotDelay = 300;
        startLevel.enemySpaceshipDelay = 8000;
        startLevel.enemySpeed = 1500;
        game.maxHealth = 40;
        break;
    case HARD:
        startLevel.enemyShotDelay = 150;
        startLevel.enemySpaceshipDelay = 10000;
        startLevel.enemySpeed = 800;
        game.maxHealth = 30;
        break;
    case CUSTOM:
        startLevel.enemyShotDelay = 200;
        startLevel.enemySpaceshipDelay = 10000;
        startLevel.enemySpeed = game.EnemySpeed;
        break;
    }
    startLevel.health = game.maxHealth;
    game.currentLevel = startLevel;
}
void SetRightmostEnemy(EnemiesData &data)
{
    for (int i = ENEMY_COLS - 1; i >= 0; i--)
    {
        for (int j = 0; j < ENEMY_ROWS; j++)
        {
            if (data.enemies[j][i].isAlive)
            {
                data.rightmostEnemy = &data.enemies[j][i];
                break;
            }
        }
    }
}

void SetLeftmostEnemy(EnemiesData &data)
{
    for (int i = 0; i < ENEMY_COLS; i++)
    {
        for (int j = 0; j < ENEMY_ROWS; j++)
        {
            if (data.enemies[j][i].isAlive)
            {
                data.leftmostEnemy = &data.enemies[j][i];
                break;
            }
        }
    }
}
void SetBottomEnemies(EnemiesData &data, bool initialMode)
{
    for (int i = 0; i < ENEMY_COLS; i++)
    {
        // bool check = (initialMode || data.bottomEnemy[i] != nullptr) && (data.bottomEnemy[i] == nullptr || (*data.bottomEnemy[i]).isAlive);
        // for (int j = 2; j >= -1 && check; j--)
        for (int j = ENEMY_ROWS - 1; j >= -1; j--)
        {
            if (j == -1)
                data.bottomEnemy[i] = nullptr;
            else
            {
                if (data.enemies[j][i].isAlive)
                {
                    data.bottomEnemy[i] = &data.enemies[j][i];
                    break;
                }
            }
        }
    }
}
void SetBottommostEnemy(EnemiesData &data)
{
    for (int i = 0; i < ENEMY_COLS; i++)
    {
        for (int j = ENEMY_ROWS - 1; j >= 0; j--)
        {
            if (data.enemies[j][i].isAlive)
            {
                data.bottommostEnemy = &data.enemies[j][i];
                break;
            }
        }
    }
}
void initialEnemies(EnemiesData &data)
{
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < ENEMY_ROWS; i++)
    {
        for (int j = 0; j < ENEMY_COLS; j++)
        {
            data.enemies[i][j] = Enemies[2 - i];
            data.enemies[i][j].positionX = 15 + j * 10;
            data.enemies[i][j].positionY = 8 + i * 6;
            data.aliveEnemyCount++;
            //if (!(i == 2 && j == 5))
            //{
            //    data.enemies[i][j].isAlive = false;
            //    data.aliveEnemyCount--;
            //}
        }
    }
    SetRightmostEnemy(data);
    SetLeftmostEnemy(data);
    SetBottommostEnemy(data);
    SetBottomEnemies(data, true);
}
GameObjects InitializeGameObjects(GameOptions &game)
{
    GameObjects gameObjects;
    gameObjects.playerShip = ships[game.SpaceshipType];
    gameObjects.playerShip.health = game.currentLevel.health;
    gameObjects.playerBullet = NormalBullet;
    gameObjects.EnemyBullet = EnemyBullet;
    gameObjects.wall = wall;
    gameObjects.EnemySpaceship = enemyspaceship;

    initialEnemies(gameObjects.enemiesData);
        gameObjects.enemiesData.speed = game.currentLevel.enemySpeed;

    // Set Spaceship
    // set Enemies
    // set wall
    return gameObjects;
}
void PrintScreen()
{
    string screen = R"(
    ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
    ║   Level:      Health:      Score:                                                                                    ║  
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝)";
    cout << screen;
}
void DrawShip(GameObjects &gameObjects)
{
    DrawEntity((int *)gameObjects.playerShip.entity, SHIP_ROWS, SHIP_COLS, gameObjects.playerShip.positionX, gameObjects.playerShip.positionY, false);
}
void DrawWall(GameObjects &gameObjects)
{
    DrawEntity((int *)gameObjects.wall.entity, WALL_ROWS, WALL_COLS, gameObjects.wall.positionX, gameObjects.wall.positionY, false);
}
void DrawLevel(GameOptions &game)
{
    Gotoxy(14, 2);
    cout << FG_WHITE << game.currentLevel.number;
}
void DrawHealth(GameObjects &gameObjects, GameOptions &game)
{
    Gotoxy(27, 2);
    if(game.maxHealth == 0) return;
    string health = to_string((gameObjects.playerShip.health * 100) / game.maxHealth) + "%";
    cout << FG_WHITE << "    ";
    Gotoxy(27, 2);
    cout << FG_WHITE << health;
}
void DrawScore(GameObjects &gameObjects)
{
    Gotoxy(40, 2);
    cout << FG_WHITE << setw(10) << left << gameObjects.Score;
}
void Draw(GameObjects &gameObjects, GameOptions &game)
{
    DrawLevel(game);
    DrawHealth(gameObjects, game);
    DrawScore(gameObjects);
    DrawShip(gameObjects);
    DrawWall(gameObjects);
    DrawEnemies(gameObjects.enemiesData);
}
void MoveShip(GameObjects &gameObjects, bool left)
{
    int i;
    if (left)
    {
        EraseRight(SHIP_ROWS, SHIP_COLS, gameObjects.playerShip.positionX, gameObjects.playerShip.positionY);
        gameObjects.playerShip.positionX--;
    }
    else if (!left)
    {
        EraseLeft(SHIP_ROWS, SHIP_COLS, gameObjects.playerShip.positionX, gameObjects.playerShip.positionY);
        gameObjects.playerShip.positionX++;
    }
    DrawEntity((int *)gameObjects.playerShip.entity, SHIP_ROWS, SHIP_COLS, gameObjects.playerShip.positionX, gameObjects.playerShip.positionY, false);
}
void FirePlayerBullet(GameObjects &gameObjects)
{
    if (!gameObjects.playerBullet.isActive)
    {
        if(settings.Sound){
            PlayShotSound();
        }
        gameObjects.playerBullet = NormalBullet;
        gameObjects.playerBullet.positionX = gameObjects.playerShip.positionX + 2;
        gameObjects.playerBullet.positionY = gameObjects.playerShip.positionY - 1;
        gameObjects.playerBullet.isActive = true;
    }
}
void ShowPauseMenu(GameOptions &game)
{
    bool MusicIsPlay = false;
    Form form = {"Pause Menu", 5, 2};
    Display display = {0, 4, 0, 0, {0, 0}};
    InitialDisplay(display);
    RenderMinimalBackground(display);
    Generalsettings generalsettings;
    LoadSettings(generalsettings);
    form.isSoundEnabled = generalsettings.Sound;
    Button ContinueButton = {"Continue", {0, 0}, true, 0};
    Button RestartButton = {"Restart Game", {1, 0}, true, 2};
    Button QuitButton = {"Quit Game", {2, 0}, true, 3};
    Button ExitButton = {"Exit Space Invaders", {3, 0}, true, 4};
    InitialElementGrid(form);
    AddButtonToForm(form, &ContinueButton);
    AddButtonToForm(form, &RestartButton);
    AddButtonToForm(form, &QuitButton);
    AddButtonToForm(form, &ExitButton);

    while (form.isRunning)
    {
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
                break;
            case 1:
                break;
            case 2:
                game.status = RESETGAME;
                form.isRunning = false;
                break;
            case 3:
                game.status = QUITTOMENU;
                form.isRunning = false;
                break;
            case 4:
                exit(0);
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
void InputHandle(GameObjects &gameObjects, GameOptions &game)
{
    if (_kbhit())
    {
        char order;
        order = getch();
        order = toupper(order);
        if (order == settings.keybindings.Left_Player1 && gameObjects.playerShip.positionX > 6)
        {
            MoveShip(gameObjects, true);
        }
        else if (order == settings.keybindings.Right_Player1 && gameObjects.playerShip.positionX < widthScreen - 4)
        {
            MoveShip(gameObjects, false);
        }
        else if (order == settings.keybindings.Shoot_Player1)
        {
            FirePlayerBullet(gameObjects);
        }
        else if (order == 27)
        {
            ShowPauseMenu(game);
            EraseFill(25, 112, 8, 6);
        }
    }
}

void MovePlayerBullet(GameObjects &gameObjects)
{

    Gotoxy(gameObjects.playerBullet.positionX, gameObjects.playerBullet.positionY);
    cout << " " << FG_WHITE;
    gameObjects.playerBullet.positionY--;
    if (gameObjects.playerBullet.positionY > 4)
    {
        Gotoxy(gameObjects.playerBullet.positionX, gameObjects.playerBullet.positionY);
        string color = GenerateANSI(gameObjects.playerBullet.colorCode);
        cout << color << gameObjects.playerBullet.shape << FG_WHITE;
    }
    else
    {
        gameObjects.playerBullet.isActive = false;
    }
}
void CollisionWallEntity(Wall &wall, int row, int col)
{
    Gotoxy(wall.positionX + col, wall.positionY + row);
    if (wall.entity[row][col] != wall.PrimaryColor)
    {
        wall.entity[row][col] = 0;
        cout << " " << FG_WHITE;
    }
    else
    {
        wall.entity[row][col] = wall.SecondaryColor;
        cout << GenerateANSI(wall.entity[row][col]) << "█" << FG_WHITE;
    }
}
void CheckShipCollision(GameObjects &gameObjects, GameOptions &game)
{
    int j = gameObjects.EnemyBullet.positionX - gameObjects.playerShip.positionX;
    int i = gameObjects.EnemyBullet.positionY - gameObjects.playerShip.positionY;
    if ((i >= 0 && j >= 0 && j < SHIP_COLS && i < SHIP_ROWS) && gameObjects.playerShip.entity[i][j])
    {
        gameObjects.EnemyBullet.isActive = false;
        gameObjects.playerShip.health -= gameObjects.EnemyBullet.damage;
        DrawHealth(gameObjects, game);
        DrawEntity((int *)gameObjects.playerShip.entity, SHIP_ROWS, SHIP_COLS, gameObjects.playerShip.positionX, gameObjects.playerShip.positionY, false);
    }
}
void CheckWallCollision(GameObjects &gameObjects, Bullet &bullet)
{
    int j = bullet.positionX - gameObjects.wall.positionX;
    int i = bullet.positionY - gameObjects.wall.positionY;

    if (gameObjects.wall.isActive && (i >= 0 && j >= 0 && j < WALL_COLS && i < WALL_ROWS) && gameObjects.wall.entity[i][j])
    {
        bullet.isActive = false;
        gameObjects.wall.entity[i][j] = 0;
        CollisionWallEntity(gameObjects.wall, i, j);
    }
}

void MoveEnemies(GameObjects &gameObjects)
{
    bool goDown = false;
    EnemiesData &data = gameObjects.enemiesData;
    if (((data.dir == 1) && (*data.leftmostEnemy).positionX >= 110) || ((data.dir == -1) && (*data.rightmostEnemy).positionX <= 11))
    {
        goDown = true;
        data.dir = -data.dir;
    }

    for (int i = 0; i < ENEMY_ROWS; i++)
    {
        for (int j = 0; j < ENEMY_COLS; j++)
        {
            if (!goDown)
            {
                data.enemies[i][j].positionX += data.dir;
            }
            else
            {
                data.enemies[i][j].positionY += 1;
                if (gameObjects.wall.isActive && data.enemies[i][j].positionY >= gameObjects.wall.positionY)
                {
                    gameObjects.wall.isActive = false;
                    EraseFill(WALL_ROWS, WALL_COLS, gameObjects.wall.positionX, gameObjects.wall.positionY);
                }
            }
            data.enemies[i][j].positionY += data.effectdir;
            data.enemies[i][j].isFirstFrame = !data.enemies[i][j].isFirstFrame;
        }
    }
    data.effectdir = -data.effectdir;
}

void EraseEnemies(EnemiesData &data)
{
    for (int i = 0; i < ENEMY_ROWS; i++)
    {
        for (int j = 0; j < ENEMY_COLS; j++)
        {
            if (data.enemies[i][j].isAlive)
            {
                if ((data.effectdir > 0 || ((data.dir == 1) && (*data.leftmostEnemy).positionX >= 110) || ((data.dir == -1) && (*data.rightmostEnemy).positionX <= 5)))
                {
                    EraseUp(ENEMY_SPRITE_COLS, data.enemies[i][j].positionX, data.enemies[i][j].positionY);
                }
                else
                {
                    EraseDown(ENEMY_SPRITE_ROWS, ENEMY_SPRITE_COLS, data.enemies[i][j].positionX, data.enemies[i][j].positionY);
                }
                if (data.dir > 0)
                {
                    EraseLeft(ENEMY_SPRITE_ROWS, ENEMY_SPRITE_COLS, data.enemies[i][j].positionX, data.enemies[i][j].positionY);
                }
                else
                {
                    EraseRight(ENEMY_SPRITE_ROWS, ENEMY_SPRITE_COLS, data.enemies[i][j].positionX, data.enemies[i][j].positionY);
                }
            }
        }
    }
}

void DrawEnemies(EnemiesData &data)
{
    for (int i = 0; i < ENEMY_ROWS; i++)
    {
        for (int j = 0; j < ENEMY_COLS; j++)
        {
            if (data.enemies[i][j].isAlive)
            {
                int *entity = nullptr;
                if (data.enemies[i][j].isFirstFrame)
                {
                    entity = (int *)data.enemies[i][j].entity1;
                }
                else
                {
                    entity = (int *)data.enemies[i][j].entity2;
                }
                DrawEntity(entity, ENEMY_SPRITE_ROWS, ENEMY_SPRITE_COLS, data.enemies[i][j].positionX, data.enemies[i][j].positionY, false);
            }
        }
    }
}
void CheckEnemyCollision(GameObjects &gameObjects)
{
    for (int i = ENEMY_ROWS - 1; i >= 0; i--)
    {
        for (int j = 0; j < ENEMY_COLS; j++)
        {
            Enemy &enemy = gameObjects.enemiesData.enemies[i][j];
            if (enemy.isAlive &&
                gameObjects.playerBullet.positionX >= enemy.positionX &&
                gameObjects.playerBullet.positionX < enemy.positionX + 5 &&
                gameObjects.playerBullet.positionY >= enemy.positionY &&
                gameObjects.playerBullet.positionY < enemy.positionY + 3)
            {
                enemy.health -= gameObjects.playerBullet.damage;
                gameObjects.playerBullet.isActive = false;
                Gotoxy(gameObjects.playerBullet.positionX, gameObjects.playerBullet.positionY);
                cout << " ";
                if(settings.Sound){
                    PlayCollisionSound();
                }
                if (enemy.health <= 0)
                {
                    
                    enemy.isAlive = false;
                    gameObjects.enemiesData.aliveEnemyCount--;

                    gameObjects.Score += enemy.Score;
                    DrawScore(gameObjects);
                    EraseFill(ENEMY_SPRITE_ROWS, ENEMY_SPRITE_COLS, enemy.positionX, enemy.positionY);
                }
                if (!(*gameObjects.enemiesData.rightmostEnemy).isAlive)
                {
                    SetRightmostEnemy(gameObjects.enemiesData);
                }
                if (!(*gameObjects.enemiesData.leftmostEnemy).isAlive)
                {
                    SetLeftmostEnemy(gameObjects.enemiesData);
                }
                if (!(*gameObjects.enemiesData.bottommostEnemy).isAlive)
                {
                    SetBottommostEnemy(gameObjects.enemiesData);
                }
                SetBottomEnemies(gameObjects.enemiesData, false);

                return;
            }
        }
    }
}
bool WinCheck(GameObjects &gameObjects)
{
    return gameObjects.enemiesData.aliveEnemyCount == 0;
}

void FireEnemyBullet(GameObjects &gameObjects)
{
    EnemiesData &data = gameObjects.enemiesData;
    if (!gameObjects.EnemyBullet.isActive)
    {
        srand(static_cast<unsigned int>(time(NULL)));
        int i = rand() % ENEMY_COLS;
        gameObjects.EnemyBullet = EnemyBullet;
        while (data.bottomEnemy[i] == nullptr)
        {
            i = rand() % ENEMY_COLS;
        }
        gameObjects.EnemyBullet.positionX = (*data.bottomEnemy[i]).positionX + 2;
        gameObjects.EnemyBullet.positionY = (*data.bottomEnemy[i]).positionY + 3;
        gameObjects.EnemyBullet.isActive = true;
    }
}
void MoveEnemyBullet(GameObjects &gameObjects)
{
    Gotoxy(gameObjects.EnemyBullet.positionX, gameObjects.EnemyBullet.positionY);
    cout << " ";
    gameObjects.EnemyBullet.positionY++;
    if (gameObjects.EnemyBullet.positionY < lengthScreen - 1)
    {
        Gotoxy(gameObjects.EnemyBullet.positionX, gameObjects.EnemyBullet.positionY);
        string color = GenerateANSI(gameObjects.EnemyBullet.colorCode);
        cout << color << gameObjects.EnemyBullet.shape << FG_WHITE;
    }
    else
    {
        gameObjects.EnemyBullet.isActive = false;
    }
}
bool CheckEnemyCatchShip(GameObjects &gameObjects)
{
    return (*gameObjects.enemiesData.bottommostEnemy).positionY + 3 >= gameObjects.playerShip.positionY;
}
bool CheckShipAlive(GameObjects &gameObjects)
{
    return gameObjects.playerShip.health <= 0;
}
void CheckEnemySpaceshipCollision(GameObjects &gameObjects)
{
    int j = gameObjects.playerBullet.positionX - gameObjects.EnemySpaceship.positionX;
    int i = gameObjects.playerBullet.positionY - gameObjects.EnemySpaceship.positionY;
    if ((i >= 0 && j >= 0 && j < SPACESHIP_COLS && i < SPACESHIP_ROWS) && gameObjects.EnemySpaceship.entity[i][j])
    {
        if(settings.Sound){
                    PlayCollisionSound();
            }
        gameObjects.EnemySpaceship.isAlive = false;
        gameObjects.Score += gameObjects.EnemySpaceship.Score;
        DrawScore(gameObjects);
        EraseFill(SPACESHIP_ROWS, SPACESHIP_COLS, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY);
    }
}
void MoveEnemySpaceship(GameObjects &gameObjects)
{
    if (gameObjects.EnemySpaceship.direction)
        if (gameObjects.EnemySpaceship.positionX - 7 < widthScreen - 4)
        {
            EraseLeft(SHIP_ROWS, SHIP_COLS, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY);
            gameObjects.EnemySpaceship.positionX++;
            DrawEntity((int *)gameObjects.EnemySpaceship.entity, SPACESHIP_ROWS, SPACESHIP_COLS, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY, false);
        }
        else
        {
            gameObjects.EnemySpaceship.isAlive = false;
            gameObjects.EnemySpaceship.direction = false;
            EraseFill(SPACESHIP_ROWS, SPACESHIP_COLS, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY);
        }
    else
    {
        if (gameObjects.EnemySpaceship.positionX > 4)
        {
            EraseRight(SHIP_ROWS, SHIP_COLS, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY);
            gameObjects.EnemySpaceship.positionX--;
            DrawEntity((int *)gameObjects.EnemySpaceship.entity, SPACESHIP_ROWS, SPACESHIP_COLS, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY, false);
        }
        else
        {

            gameObjects.EnemySpaceship.isAlive = false;
            gameObjects.EnemySpaceship.direction = true;
            EraseFill(SPACESHIP_ROWS, SPACESHIP_COLS, gameObjects.EnemySpaceship.positionX, gameObjects.EnemySpaceship.positionY);
        }
    }
}
void SaveGame(const GameOptions &game)
{
    string filename = "usersave.bin";
    ofstream file(filename, ios::binary);
    if (file.is_open())
    {
        size_t nameLength = game.playerName.size();
        file.write(reinterpret_cast<const char *>(&nameLength), sizeof(nameLength));
        file.write(game.playerName.c_str(), nameLength);
        file.write(reinterpret_cast<const char *>(&game.difficulty), sizeof(game.difficulty));
        file.write(reinterpret_cast<const char *>(&game.maxHealth), sizeof(game.maxHealth));
        file.write(reinterpret_cast<const char *>(&game.EnemySpeed), sizeof(game.EnemySpeed));
        file.write(reinterpret_cast<const char *>(&game.currentLevel), sizeof(game.currentLevel));
        file.write(reinterpret_cast<const char *>(&game.isWin), sizeof(game.isWin));
        file.write(reinterpret_cast<const char *>(&game.status), sizeof(game.status));

        file.close();
    }
}

void LoadGame(GameOptions &game)
{
    string filename = "usersave.bin";
    ifstream file(filename, ios::binary);
    if (file.is_open())
    {
        size_t nameLength;
        file.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
        game.playerName.resize(nameLength);
        file.read(&game.playerName[0], nameLength);
        file.read(reinterpret_cast<char *>(&game.difficulty), sizeof(game.difficulty));
        file.read(reinterpret_cast<char *>(&game.maxHealth), sizeof(game.maxHealth));
        file.read(reinterpret_cast<char *>(&game.EnemySpeed), sizeof(game.EnemySpeed));
        file.read(reinterpret_cast<char *>(&game.currentLevel), sizeof(game.currentLevel));
        file.read(reinterpret_cast<char *>(&game.isWin), sizeof(game.isWin));
        file.read(reinterpret_cast<char *>(&game.status), sizeof(game.status));
        file.close();
    }
}
int PlayLevel(GameOptions &game)
{

    GameObjects gameObjects = InitializeGameObjects(game);
    gameObjects.Score = game.Score;
    int totalTime = 1;
    Draw(gameObjects, game);
    bool isRunning = true;
    bool &isWin = game.isWin;
    bool isLose = false;
    while (isRunning)
    {
        InputHandle(gameObjects, game);
        if (game.status != RUNNINGGAME)
        {
            isRunning = false;
        }
        if (clock() % game.currentLevel.enemyShotDelay == 0)
        {
            FireEnemyBullet(gameObjects);
        }

        if (clock() % gameObjects.enemiesData.speed == 0)
        {
            EraseEnemies(gameObjects.enemiesData);
            MoveEnemies(gameObjects);
            DrawEnemies(gameObjects.enemiesData);
            isLose = CheckEnemyCatchShip(gameObjects);
        }
        if (!gameObjects.EnemySpaceship.isAlive && clock() % game.currentLevel.enemySpaceshipDelay == 0)
        {
            gameObjects.EnemySpaceship = enemyspaceship;
        }
        if (clock() % 100 == 0 && gameObjects.EnemySpaceship.isAlive)
        {
            MoveEnemySpaceship(gameObjects);
        }
        if (gameObjects.EnemyBullet.isActive && clock() % gameObjects.EnemyBullet.speed == 0)
        {
            MoveEnemyBullet(gameObjects);
            CheckWallCollision(gameObjects, gameObjects.EnemyBullet);
            CheckShipCollision(gameObjects, game);
            isLose = CheckShipAlive(gameObjects);
        }
        if (gameObjects.playerBullet.isActive && clock() % gameObjects.playerBullet.speed == 1)
        {
            MovePlayerBullet(gameObjects);
            CheckWallCollision(gameObjects, gameObjects.playerBullet);
            CheckEnemyCollision(gameObjects);
            CheckEnemySpaceshipCollision(gameObjects);
            isWin = WinCheck(gameObjects);
        }

        if (isWin)
            isRunning = false;
        if (isLose)
            isRunning = false;
    }
        game.currentLevel.health = gameObjects.playerShip.health;
    return gameObjects.Score;
}
void NextLevel(GameOptions &game)
{
    LevelOptions startLevel = game.currentLevel;
    startLevel.number++;
    switch (game.difficulty)
    {
    case EASY:
        startLevel.enemyShotDelay *= 0.9;
        startLevel.enemySpaceshipDelay *= 1.1;
        startLevel.enemySpeed *= 0.9;
        break;
    case MEDIUM:
        startLevel.enemyShotDelay *= 0.8;
        startLevel.enemySpaceshipDelay *= 1.2;
        startLevel.enemySpeed *= 0.8;
        break;
    case HARD:
        startLevel.enemyShotDelay *= 0.5;
        startLevel.enemySpaceshipDelay *= 1.5;
        startLevel.enemySpeed *= 0.75;
        break;
    case CUSTOM:
        startLevel.enemyShotDelay *= 0.85;
        startLevel.enemySpaceshipDelay *= 1.1;
        break;
    }
    game.currentLevel = startLevel;
}
void LoadLevel(GameOptions &game, int number)
{
    CreateLevel(game);
    for (int i = 1; i < number; i++)
    {
        NextLevel(game);
    }
};
void ShowGameOver(int fgcolor, int bgcolor)
{
    int x = 35;
    int y = 18;
    string fg_color = GenerateANSI(fgcolor);
    string bg_color = GenerateANSI(bgcolor);
    Gotoxy(x, y);
    cout << fg_color << bg_color << "   _____                         ____                 _ ";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"(  / ____|                       / __ \               | |)";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << " | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __| |";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__| |)";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"( | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |  |_|)";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"(  \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|  (_))";
    y++;
    Gotoxy(x, y);
    cout << fg_color << bg_color << R"(                                                        )";
}
void LoseAnimation()
{
    for (int i = 0; i < 12; i++)
    {
        ShowGameOver(03, 1964);
        Sleep(150);
        ShowGameOver(04, 1963);
        Sleep(150);
    }
    Sleep(1000);
}
void RunGame(GameOptions &game, bool loadGame)
{
    system("cls");
    HideCursor();
    
    game.difficulty = HARD;
    
    LoadSettings(settings);
    CreateLevel(game);
    if(settings.Music){
        StopBackgroundMusic();
        PlayGameMusic();
    }
    GameOptions maingame = game;
    LevelOptions level = game.currentLevel;
    game.Score = 0;
    bool isLose = false;
    if (loadGame)
    {
        LoadGame(game);
        LoadLevel(game, game.currentLevel.number);
    }
     
    while (1)
    {
        game.status = RUNNINGGAME;
        PrintScreen();
        int currentScore = PlayLevel(game);
        if (game.status == RESETGAME)
        {
            system("cls");
            continue;
        }
        game.Score += currentScore;
        if (game.status == QUITTOMENU)
        {
            break;
        }
        if (game.isWin)
        {
            system("cls");
            NextLevel(game);
            level = game.currentLevel;
            game = maingame;
            game.currentLevel = level;
            continue;
        }

        else
        {
            isLose = true;
            LoseAnimation();
            break;
        }
    }
    if (!isLose)
    {
        SaveGame(game);
    }
    else
    {
        remove("usersave.bin");
        Player player = {game.playerName, game.Score};
        UpdateLeaderboard(GetDefaultFileName(), player);
    }
    StopGameMusic();
            PlayBackgroundMusic();

}
