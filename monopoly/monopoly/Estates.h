
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
//�a�Ϧ�l �O�_���H�R
//�a�Ϧ�l 0�ʶR���� 1��l�Ыλ��� 2���Ť@�Ы� 3
//buyEstate[xx]==0 �I��//buyEstate[xx] == 1 �i�H�ʶR

