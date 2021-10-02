#pragma once
#include<string>
#include<fstream>
#include <random>
#include<iostream>
#include<map>
#include<time.h>
#include<stdlib.h>
#include"Character.h"
#include "Bank.h"
//class character;
using namespace std;
class stock
{
public:
	stock();
	stock(string qqq);
	~stock();
	string name;
	int limit = 0;
	double gap;
	double value;
	double changeAmount;
	static string allName[10];
	friend class character;
};
void setStock(map<string, stock> &a);
void randProbability(map<string, stock> &, string name);
void setOneDecimal (double& a);
void updatePrice(map<string, stock> &, string name);
void buyStock(character& player, int number, int i, map<string, stock> a, Bank b, bool checkError);
void sellStock(character& player2, int number, int i, map<string, stock> a,Bank);
void isSell(character& player3 , int number,bool);
void saveStock(map<string, stock>&a);
void readStock(map<string, stock>&a);