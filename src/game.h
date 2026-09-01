#pragma once
#include <iostream>
#include <cmath>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const unsigned short int lengthScreen = 41;
const unsigned short int widthScreen = 120;

enum GameDifficulty{
    EASY,
    MEDIUM,
    HARD,
    CUSTOM
};

struct EnemySpaceship
{
	bool direction;
	bool isAlive;
	int entity[2][8];
	int Score;
	int positionX;
	int positionY;
};
struct LevelOptions{
    int number = 1;
    int enemyShotDelay = 100;
	int enemySpaceshipDelay = 100;
    int wallIndex = 0;
	int health = 0;
	int enemySpeed;
};
enum GameStatus{
	RUNNINGGAME,
	RESETGAME,
	QUITTOMENU
};
struct GameOptions{
    string playerName;
    GameDifficulty difficulty;
    int SpaceshipType;
    int maxHealth;
	int EnemySpeed;
    LevelOptions currentLevel;
	bool isWin = false;
	GameStatus status = RUNNINGGAME;
	int Score = 0;
};

struct Bullet
{
	unsigned short int speed;
	unsigned short int damage;
	string shape;
	int colorCode;
	bool direction;
	int positionX;
	int positionY;
	bool isActive;
};

struct Ship
{
	unsigned short int health;
	unsigned short int bulletsCount;
	int entity[2][6];
	int positionX;
	int positionY;
};

struct Enemy
{
	unsigned short int health;
	int entity1[3][5];
	int entity2[3][5];
	bool IsOne = 0;
	bool isAlive;
	int Score = 100;
	int positionX;
	int positionY;
};

struct EnemiesData
{
	Enemy enemies[3][10];
	Enemy *bottomEnemy[10] = {nullptr};
	Enemy *bottommostEnemy = nullptr;
	Enemy *leftmostEnemy = nullptr;
	Enemy *rightestEnemy = nullptr;
	int aliveEnemyCount = 0;
	int dir = 1;
	int effectdir = 1;
	int speed = 500;
};

struct Wall
{
	int PrimaryColor;
	int SecondaryColor;
	int entity[5][100];
	int positionX;
	int positionY;
	bool isActive;
};

struct GameObjects{
    Ship playerShip;
    Bullet playerBullet;
	Bullet EnemyBullet;
    EnemiesData enemiesData;
    Wall wall;
	EnemySpaceship EnemySpaceship;
	int Score = 0;
};
void RunGame(GameOptions &game, bool loadGame);