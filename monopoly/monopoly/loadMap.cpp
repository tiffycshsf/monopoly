#pragma once
#include "loadMap.h"
#include "EConsole.h"
#include "Character.h"
#include <iomanip>

/*special syntax*/
// �� --> player told from different color

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

		if (tempIndex == "playerstate") //�j��o�Ӹ����j��U���O���a��T
		{
			string ignore;
			testMap >> state; //�^�X
			loadpPlayer();
			break;
		}
		else
		{
			testMap >> tempName;
			testMap >> tempType;
			if (tempType == 1) // �ŦX�@��Фl�����p
			{
				int* tempPay;
				tempPay = new int[5];
				for (int i = 0; i < 5; i++)
				{
					testMap >> tempPay[i];
				}
				buildingList.push_back(Building(tempIndex, tempName, tempType, tempPay)); //�s�n
			}
			else
			{
				buildingList.push_back(Building(tempIndex, tempName, tempType));
			}
		}
	}
}

void fillData()  //���r��J��涶�K�����C�檺��m
{
	int posX = 31;
	int posY = 0;
	for (int i = 0; i < buildingList.size(); i++)
	{
		int len = buildingList[i].getName().length(); //�p���r����
		cout << setw(9 + len / 2) << right; //�m��
		Point temp;
		if (i < 8)
		{
			//��C�I��m���O����place�̭�
			temp.X = posX + 1;
			temp.Y = posY + 3 + 5 * i;
			place.push_back(temp);
			//print �a�W
			gotoxy(posX + 1, posY + 3 + 5 * i);
			cout << buildingList[i].getName();
		}
		else if (8 <= i && i < 15)
		{
			//��C�I��m���O����place�̭�
			temp.X = posX + 1 + (i - 7) * 20;
			temp.Y = 38;
			place.push_back(temp);
			//print �a�W
			gotoxy(posX + 1 + (i - 7) * 20, posY + 38);
			cout << buildingList[i].getName();
		}
		else if (15 <= i && i < 22)
		{
			//��C�I��m���O����place�̭�
			temp.X = posX + 141;
			temp.Y = posY + 38 - ((i - 14) * 5);
			place.push_back(temp);
			//print �a�W
			gotoxy(posX + 141, posY + 38 - ((i - 14) * 5));
			cout << buildingList[i].getName();
		}
		else
		{
			//��C�I��m���O����place�̭�
			temp.X = posX + 141 - ((i - 21) * 20);
			temp.Y = posY + 3;
			place.push_back(temp);
			//print �a�W
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
	getline(testMap, playerInfo); //���檺�Ÿ��n���M���A�S�[�o��U����getline�Ĥ@�Ӭ���
	while (getline(testMap,playerInfo)) //�@��@�����
	{
		temp.clear();
		splitStr2Vec(playerInfo, temp," "); //�ΪŮ���Φr��
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
	for (int i = 0; i < 3; i++) //���d��T ������
	{
		testMap >> Map[i];
	}
}

void splitStr2Vec(string s, vector<string>& buf, string judge)
{
	int current = 0; //�̪�� 0 ����m�}�l��
	int next;
	while (1)
	{
		next = s.find_first_of(judge, current);
		if (next != current)
		{
			string tmp = s.substr(current, next - current);
			if (tmp.size() != 0) //�����Ŧr��
				buf.push_back(tmp);
		}
		if (next == string::npos) break;
		current = next + 1; //�U���� next + 1 ����m�}�l��_�C
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