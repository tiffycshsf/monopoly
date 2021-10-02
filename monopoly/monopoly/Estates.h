
#pragma once

#include<iostream>
#include<map>
#include <vector>
#include <fstream>
#include<string>
using namespace std;

class Estates {


public:
	Estates();
	int pos;
	int buy;
	int owner = -1;
	int level;
	int price[4];

	//static map<int,bool>buyEstate;
	//static mpa<int,int>priceEstate;
	//static int** priceAll;



};
void getInformation(map<int, Estates> &a);
void buyProperty(int player, int pos);
void upgrade(int player, int pos, map<int, Estates> a);
//地圖位子 是否有人買
//地圖位子 0購買價格 1初始房屋價格 2等級一房屋 3
//buyEstate[xx]==0 付錢//buyEstate[xx] == 1 可以購買

