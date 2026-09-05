#include <fstream>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "color.h"
#include "Leaderboard.h"
#include "player.h"
#include "form.h"
#include "utilities.h"
using namespace std;


void LeaderboardMenu(){
    Form form = {"Leaderboard", 15, 2, false};
    Display display = {0, 4, 0, 1, {0, 0}};
    RenderBackground(display);
    InitialElementGrid(form);
    int counter = 0;
    Player players[20];
    ReadPlayersFromFile("scoreBoard.txt",players,counter);
    Table table = {
        104, 19, 2, 0, 7, {0,0}};
    AddTableToForm(form, &table);
    table.Cells[0][0] = {"Name"};
    table.Cells[0][1] = {"Score"};
    for(int i = 1;i <20;i++){
        if(i >= counter) break;
        table.Cells[i][0] = {players[i-1].name};
        table.Cells[i][1] = {to_string(players[i-1].score)};
    }
    while (form.isRunning)
    {
        RenderForm(form, display);
        Element SelectedElement = form.ElementsGrid[display.userPosition.row][display.userPosition.col];
        RenderFooter(GetKeyHints(SelectedElement.type),display.secondaryColor);
        char ch = getch();
        HandleInput(ch, display, form);
    }
    CloseForm(form);
}

string GetDefaultFileName(){
    return "scoreBoard.txt"; 
}
void bubbleSort(Player players[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}

void ReadPlayersFromFile(string Filename, Player players[], int &counter) {
    fstream dataFile;
    dataFile.open(Filename, ios::in);
    if (!dataFile) {
        cerr << "Error opening file!" << endl;
        return;
    }
    while (dataFile >> players[counter].name >> players[counter].score) {
        counter++;
        if (counter == 10) {
            break;
        }
    }
    dataFile.close();
}

void WritePlayersToFile(string Filename, Player players[], int counter) {
    fstream dataFile;
    dataFile.open(Filename, ios::out);
    if (!dataFile) {
        cerr << "Error writing to file!" << endl;
        return;
    }
    for (int i = 0; i < counter; i++) {
        dataFile << players[i].name << " " << players[i].score << endl;
    }
    dataFile.close();
}
void Leaderboard(string Filename)
{
    
};
void UpdateLeaderboard(string Filename,Player player){
    Player players[20];
    int counter = 0;
    bool isPlayed = false;
    ReadPlayersFromFile(Filename,players,counter);
    for(int i = 0;i<counter;i++){
        if(players[i].name ==  player.name){
            isPlayed = true;
            if(players[i].score > player.score){
                players[i] = player;
            }
        }
    }if(!isPlayed){
    players[counter] = player;
    counter++;
    }

    bubbleSort(players, counter);
    if (counter > 20) {
        counter = 20;
    }
    WritePlayersToFile(Filename, players, counter);
}
void UpdateLeaderboard(Player player){
    UpdateLeaderboard(GetDefaultFileName(),player);
}
