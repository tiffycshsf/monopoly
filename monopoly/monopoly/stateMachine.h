#pragma once
#include <iostream>
using namespace std;


//�C�����A��
// 0 = �_�l�e��
// 1 = �C���e��
// 2 = exc�ﶵ



void loadUI(string state); 
void menuCtr(int ctr);
void optionCtr(int ctr);
void templateCtr(int ctr);
int selecterU(int num, int state);
int selecterLeft();

extern int stateMachine;