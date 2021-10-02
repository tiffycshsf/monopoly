#pragma once
#include "loadMap.h"
#include "EConsole.h"
#include "Character.h"
#include <iomanip>

/*special syntax*/
// ● --> player told from different color

vector<Building> buildingList;
vector<Point> place;
//playerStruct player[4];
fstream testMap;
string Map[3];
character player[4];

int state;


Building::Building(string index, string name, int type, int* pay)
{
	this->index = index;
	this->name = name;
	this->type = type;
	this->pay = pay;
		
}

Building::Building(string index, string name, int type)
{
	this->index = index;
	this->name = name;
	this->type = type;
}

Building::~Building()
{
}

string Building::getIndex()
{
	return this->index;
}

string Building::getName()
{
	return this->name;
}

int Building::getType()
{
	return this->type;
}

int* Building::getPay()
{
	return this->pay;
}

int Building::getBelongs()
{
	return belongs;
}

int Building::getLevel()
{
	return level;
}

void Building::setBelongs(int id)
{
	belongs = id;
}

void Building::setLevel(int le)
{
	level = le;
}


void loadMap(string fileName)
{
	loadLevel(fileName);
	buildingList.clear();
	while (!testMap.eof())
	{
		string tempIndex;
		string tempName;
		int tempType;
		testMap >> tempIndex;

		if (tempIndex == "playerstate") //搜到這個跳離迴圈下面是玩家資訊
		{
			string ignore;
			testMap >> state; //回合
			loadpPlayer();
			break;
		}
		else
		{
			testMap >> tempName;
			testMap >> tempType;
			if (tempType == 1) // 符合一般房子的狀況
			{
				int* tempPay;
				tempPay = new int[5];
				for (int i = 0; i < 5; i++)
				{
					testMap >> tempPay[i];
				}
				buildingList.push_back(Building(tempIndex, tempName, tempType, tempPay)); //存好
			}
			else
			{
				buildingList.push_back(Building(tempIndex, tempName, tempType));
			}
		}
	}
}

void fillData()  //把文字填入方格順便紀錄每格的位置
{
	int posX = 31;
	int posY = 0;
	for (int i = 0; i < buildingList.size(); i++)
	{
		int len = buildingList[i].getName().length(); //計算文字長度
		cout << setw(9 + len / 2) << right; //置中
		Point temp;
		if (i < 8)
		{
			//把每點位置都記錄到place裡面
			temp.X = posX + 1;
			temp.Y = posY + 3 + 5 * i;
			place.push_back(temp);
			//print 地名
			gotoxy(posX + 1, posY + 3 + 5 * i);
			cout << buildingList[i].getName();
		}
		else if (8 <= i && i < 15)
		{
			//把每點位置都記錄到place裡面
			temp.X = posX + 1 + (i - 7) * 20;
			temp.Y = 38;
			place.push_back(temp);
			//print 地名
			gotoxy(posX + 1 + (i - 7) * 20, posY + 38);
			cout << buildingList[i].getName();
		}
		else if (15 <= i && i < 22)
		{
			//把每點位置都記錄到place裡面
			temp.X = posX + 141;
			temp.Y = posY + 38 - ((i - 14) * 5);
			place.push_back(temp);
			//print 地名
			gotoxy(posX + 141, posY + 38 - ((i - 14) * 5));
			cout << buildingList[i].getName();
		}
		else
		{
			//把每點位置都記錄到place裡面
			temp.X = posX + 141 - ((i - 21) * 20);
			temp.Y = posY + 3;
			place.push_back(temp);
			//print 地名
			gotoxy(posX + 141 - ((i - 21) * 20), posY + 3);
			cout << buildingList[i].getName();
		}

	}
	/*for (int i = 0; i < buildingList.size(); i++)
	{
		cout << buildingList[i].getIndex() << " " << buildingList[i].getName() << " " << buildingList[i].getType() << " ";
		if (buildingList[i].getType() == 1)
		{
			int* tempPtr = buildingList[i].getPay();
			for (int j = 0; j < 5; j++)
			{
				cout << tempPtr[j] << " ";
			}
			cout << endl;
		}
		else
		{
			cout << endl;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		cout << player[i].place << " " << player[i].money;
		for (int j = 0; j < player[i].structList.size(); j++)
		{
			cout << " " << player[i].structList[j].place << " " << player[i].structList[j].level;
		}
	}*/
}

void loadpPlayer()
{
	string playerInfo;
	vector<string> temp;
	getline(testMap, playerInfo); //換行的符號要先清掉，沒加這行下面的getline第一個為空
	while (getline(testMap,playerInfo)) //一行一行抓資料
	{
		temp.clear();
		splitStr2Vec(playerInfo, temp," "); //用空格分割字串
		if (temp.size() > 0)
		{
			int id, stay, money;
			id = atoi(temp[0].c_str());
			stay = atoi(temp[1].c_str());
			money = atoi(temp[2].c_str());
			player[id].setInit(id, stay, money);
			player[id].structList.clear();

			int index = 3;
			while (temp.size() > index)
			{
				structure Stemp;
				Stemp.place = temp[index];
				Stemp.level = atoi(temp[index + 1].c_str());
				player[id].structList.push_back(Stemp);
				index += 2;

				int Buildpos = atoi(Stemp.place.c_str());
				buildingList[Buildpos].setBelongs(id);
				buildingList[Buildpos].setLevel(Stemp.level);
			}
		}
	}
	testMap.close();
}

void loadLevel(string fileName)
{
	testMap.open(fileName);
	for (int i = 0; i < 3; i++) //關卡資訊 先不管
	{
		testMap >> Map[i];
	}
}

void splitStr2Vec(string s, vector<string>& buf, string judge)
{
	int current = 0; //最初由 0 的位置開始找
	int next;
	while (1)
	{
		next = s.find_first_of(judge, current);
		if (next != current)
		{
			string tmp = s.substr(current, next - current);
			if (tmp.size() != 0) //忽略空字串
				buf.push_back(tmp);
		}
		if (next == string::npos) break;
		current = next + 1; //下次由 next + 1 的位置開始找起。
	}
}

void saveMap()
{
	fstream save;
	save.open("saveMap.txt", ios::out);
	save << Map[0];
	save << " " << Map[1];
	save << " " << Map[2] << endl;
	for (int i = 0; i < 28; i++)
	{
		save << buildingList[i].getIndex() << " ";
		save << buildingList[i].getName() << " ";
		save << buildingList[i].getType();

		if (buildingList[i].getType() == 1)
		{
			for (int j = 0; j < 5; j++)
			{
				save << " " << buildingList[i].getPay()[j];
			}
		}
		save << endl;
	}
	save << "playerstate " << state << endl;
	for (int i = 0; i < 4; i++)
	{
		save << player[i].getID() << " " << player[i].getPlace() << " " << player[i].getCash();
		for (int j = 0; j < player[i].structList.size(); j++)
		{
			save << " " << player[i].structList[j].place << " " << player[i].structList[j].level;
		}
		save << endl;
	}
}