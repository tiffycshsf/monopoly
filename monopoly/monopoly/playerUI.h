#ifndef PLAYERUI_H
#define PLAYERUI_H
#include "basicUI.h"
#include "Bank.h"
void playerUI(int playerID);
void setMoney(int playerID);
void setStock(int playerID);
void setBank(int playerID, Bank &bank);
void setStruct(int playerID);
void playerPlace(int playerID);
void playerdied(int playerID);
void informationBlock(int round,int turn);

bool victory();
void StructBelong();

int blockplace();//»ÙÃªª«©ñ¸m
#endif