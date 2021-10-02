#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include <conio.h>
#include"EConsole.h"

using namespace std;

class win {
public:
	win(string winnerIn);

	void loadWin();
	void winMod();
	

	int type;
private:
	wfstream winIn;
	string winner;
};
