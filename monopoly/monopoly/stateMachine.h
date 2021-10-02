#pragma once
#include <iostream>
using namespace std;


//遊戲狀態機
// 0 = 起始畫面
// 1 = 遊戲畫面
// 2 = exc選項



void loadUI(string state); 
void menuCtr(int ctr);
void optionCtr(int ctr);
void templateCtr(int ctr);
int selecterU(int num, int state);
int selecterLeft();

extern int stateMachine;