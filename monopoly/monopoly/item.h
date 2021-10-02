#pragma once
#include<iostream>
#include<map>
//#include"Character.h"
#include<string>

using namespace std;

class character;
class item
{
private:
	string name;
	string instruction;
public:
	item();
	~item();
	//virtual void getEffect();
	virtual string getInstruction();
	virtual string getName();
};

class controlDice :public item
{
private:
	string name;
	string instruction;
public:
	string getName();
	controlDice();
	~controlDice();
	void getEffect(character);
};

class roadBlock :public item
{
public:
	string getName();
	void getEffect(int, int);
	roadBlock();
	~roadBlock();
private:
	string name;
	string instruction;
};

int selectItem(int size );
void useItem(character player, int a);
int showItem(map<int,int>&a);
void readItem();
void saveItem();
