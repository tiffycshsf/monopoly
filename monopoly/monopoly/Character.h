#pragma once
#include <iostream>
#include <cstdlib>		//引入才能夠使用rand()函數
#include <ctime>		//引入才能夠使用time()函數
//#include "stock.h"
#include "item.h"
#include<map>
#include <vector>

using namespace std;

struct structure //擁有建築和等級
{
	string place;
	int level;
};

class character {
private:
	int identityNum;	//角色代號:0~3
	int place;			//角色位置
	int cash;			//角色身上的現金


public:
	int nextStep;		//角色下一步應走得步數
	map<int, int> ownItem;
	character();
	bool died = false;  //破產沒

	friend class item;
	friend class stock;
	friend class controlDice;
	void setInit(int id, int stay, int money);
	int holdStock[10] = { 0 };	
	int throwDice(void);	//決定之後的移動次數
	int throwDice(int step);
	int getCash(void);		//取得目前的現金總額
	int getID(void);		//取得目前的角色編號
	int getPlace();
	void setPlace(int x);
	vector<structure> structList; 
	bool sleep = false; //暫停一回合
	
	void resetStruct();  //重設
	void sendMoney(unsigned int);	//減少角色身上的現金
	void getMoney(unsigned int);		//增加角色身上的現金
};

extern character player[4];