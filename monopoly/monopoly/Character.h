#pragma once
#include <iostream>
#include <cstdlib>		//�ޤJ�~����ϥ�rand()���
#include <ctime>		//�ޤJ�~����ϥ�time()���
//#include "stock.h"
#include "item.h"
#include<map>
#include <vector>

using namespace std;

struct structure //�֦��ؿv�M����
{
	string place;
	int level;
};

class character {
private:
	int identityNum;	//����N��:0~3
	int place;			//�����m
	int cash;			//���⨭�W���{��


public:
	int nextStep;		//����U�@�B�����o�B��
	map<int, int> ownItem;
	character();
	bool died = false;  //�}���S

	friend class item;
	friend class stock;
	friend class controlDice;
	void setInit(int id, int stay, int money);
	int holdStock[10] = { 0 };	
	int throwDice(void);	//�M�w���᪺���ʦ���
	int throwDice(int step);
	int getCash(void);		//���o�ثe���{���`�B
	int getID(void);		//���o�ثe������s��
	int getPlace();
	void setPlace(int x);
	vector<structure> structList; 
	bool sleep = false; //�Ȱ��@�^�X
	
	void resetStruct();  //���]
	void sendMoney(unsigned int);	//��֨��⨭�W���{��
	void getMoney(unsigned int);		//�W�[���⨭�W���{��
};

extern character player[4];