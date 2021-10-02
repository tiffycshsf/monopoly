#include "Character.h"
#include "loadMap.h"
#include "EConsole.h"
#include <string>

character::character()
{
	ownItem[0] = 1;
	ownItem[1] = 1;
	cash = 30000;
}

void character::setInit(int id, int stay, int money)
{
	identityNum = id;
	place = stay;
	cash = money;
}

int character::getPlace()
{
	return place;
}

void character::setPlace(int x)
{
	place = x;
}

void character::resetStruct()
{
	structList.clear();
	for (int i = 0; i < buildingList.size(); i++)
	{
		if (buildingList[i].getBelongs() == identityNum)
		{
			structure temp;
			temp.level = buildingList[i].getLevel();
			temp.place = buildingList[i].getIndex();
			structList.push_back(temp);
		}
	}
}

int character::throwDice(void) {
	srand(time(NULL));

	nextStep = rand() % 6 + 1;
	place = (place + nextStep) % 28;

	fstream dice;
	string num;

	for (int time = 0; time < 3; time++)
	{
		for (int i = 1; i <= 19; i++)
		{
			gotoxy(100, 18);
			num = to_string(i);
			dice.open("Dice/" + num + ".txt");
			string temp;
			int line = 0;
			while (getline(dice, temp))
			{
				gotoxy(100, 18 + line);
				cout << temp;
				line++;
			}
			dice.close();
			Sleep(50);
		}
	}
	dice.open("Dice/clean.txt");
	string temp;
	int line = 0;
	while (getline(dice, temp))
	{
		gotoxy(100, 18 + line);
		cout << temp;
		line++;
	}
	dice.close();
	
	return nextStep;
}

int character::throwDice(int step)
{
	if (step > 0 && step <= 6)
	{
		place = (place + step) % 28;

		fstream dice;
		string num;

		for (int time = 0; time < 3; time++)
		{
			for (int i = 1; i <= 19; i++)
			{
				gotoxy(100, 18);
				num = to_string(i);
				dice.open("Dice/" + num + ".txt");
				string temp;
				int line = 0;
				while (getline(dice, temp))
				{
					gotoxy(100, 18 + line);
					cout << temp;
					line++;
				}
				dice.close();
				Sleep(50);
			}
		}
		dice.open("Dice/clean.txt");
		string temp;
		int line = 0;
		while (getline(dice, temp))
		{
			gotoxy(100, 18 + line);
			cout << temp;
			line++;
		}
		dice.close();
		return 0;
	}
	else
	{
		gotoxy(100, 20);
		cout << "超出步數";
		Sleep(1000);
		gotoxy(100, 20);
		cout << "              ";
		return -1;
	}
	
}

int character::getCash(void) {
	return cash;
}

int character::getID(void) {
	return identityNum;
}

void character::sendMoney(unsigned int money) {
	if (money > this->cash) {
		cout << "金額不足，無法減少現金";
	}
	else {
		this->cash -= money;
	}
}

void character::getMoney(unsigned int money) {
	this->cash += money;
}
