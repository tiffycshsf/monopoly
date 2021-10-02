#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include <conio.h>
#include"Character.h"
#include"EConsole.h"
#include"Bank.h"
#include"stock.h"

using namespace std;

class bankUI {
public:

	friend class Character;
	friend class stock;

	bankUI();
	bankUI(character & player);

	void loadBank();
	void loadRate();
	void loadData(character & player, Bank &bank);
	void loadOption();
	void switchOption();
	void showKey();
	void loadAll(character & player, Bank &bank);
	void move(int key, character & player, Bank &bank, map<string, stock> &Stock, bool &leave);
	void setRate(double &dIn, double &lIn);

	void switchItem();

	void loadStock(map<string, stock> &stock, character & player);
	void loadStockOp();
	void showStockKey();
	void loadPrice(map<string, stock> &stock, character & player);
	bool moveStock(int key, character & player, Bank &bank, map<string, stock> &Stock, bool &check);
	void switchStock();

private:

	double rateL;
	double rateD;

	int itemType;

	char stateC;
	int stateI;
	int stockState;

	int playerID;

	wfstream itemOp;

	wfstream bankIn;
	wfstream rateIn;
	wfstream dataIn;
	wfstream optionIn;
	wfstream keyIn;

	wfstream stockIn;
	wfstream stockOption;
	wfstream stockKeyin;
};