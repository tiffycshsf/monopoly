#include"Character.h"
#include "EConsole.h"
#include "loadMap.h"
#include <fstream>
#include <conio.h>

string item::getInstruction()
{
	return instruction;
}
string item::getName()
{
	return name;
}
item::item()
{
	name = "預設";
	instruction = {};
}


item::~item()
{
}

string controlDice::getName()
{
	return name;
}

controlDice::controlDice()
{
	name = "遙控骰子";
	instruction = "指定1~6步前進";
}

void controlDice::getEffect(character player)
{
	int temp;
	cin >> temp;
	player.nextStep = temp;

}



string roadBlock::getName()
{
	return name;
}

void roadBlock::getEffect(int a, int b)
{
	//地圖路障[a][b] = 1;
}


roadBlock::roadBlock()
{
	instruction = "放置於物件上，玩家碰到立即停在此格";
	name = "路障";
}
roadBlock::~roadBlock()
{
}

controlDice::~controlDice()
{
}

int showItem(map<int, int>&a)
{
	int line = 0;
	map<int, int>::iterator temp;
	if (!a.empty())
	{
		for (temp = a.begin(); temp != a.end(); temp++)
		{
			gotoxy(100, 20 + line);
			switch (temp->first)
			{

			case 0:
			{
				controlDice controlDice;
				cout << controlDice.getName();
				cout << " : " << temp->second;
				line++;
				break;
			}
			case 1:
			{
				roadBlock roadBlock;
				cout << roadBlock.getName();
				cout << " : " << temp->second;
				line++;
				break;
			}

			}
		}
	}
	return a.size();
}

int selectItem(int size)
{
	char key;
	int numCtr = 0;
	gotoxy(98, 20 + numCtr);
	cout << "●";
	while (key = _getch()) //讀取
	{

		if (key == 13)
		{
			for (int i = 0; i < size; i++) //UI清空
			{
				gotoxy(98, 20 + i);
				cout << "                          ";
			}
			return numCtr;
			break;
		}
		else if (key == 27)
		{
			for (int i = 0; i < size; i++) //UI清空
			{
				gotoxy(98, 20 + i);
				cout << "                          ";
			}
			return -1;
			break;
		}

		gotoxy(98, 20 + numCtr);
		cout << "  ";
		if (key == 72) //key up code
		{
			if (numCtr != 0 && numCtr <= size - 1)
			{
				numCtr--;
			}
		}
		else if (key == 80) //key down code
		{
			if (numCtr != size - 1 && numCtr >= 0)
			{
				numCtr++;
			}
		}

		gotoxy(98, 20 + numCtr);
		cout << "●";


	}



}
//道具編號 0是骰子 1式路障
void useItem(character player, int a)
{
	switch (a)
	{
	case 0:
	{
		int temp;
		cin >> temp;
		player.nextStep = temp;
		break;
	}
	case 1:
	{
		//UI build roadblock(int a ,int b);
	}

	}
}

void saveItem()
{
	fstream save;
	save.open("saveItem.txt", ios::out);
	for (size_t i = 0; i < 4; i++)
	{
		save << player[i].getID() << endl;
		//save << "0" << endl;
		save << player[i].ownItem[0] << endl;
		//save << "1" << endl;
		save << player[i].ownItem[1] << endl;
	}//存完道具
	save << "blcok" << endl;
	for (size_t i = 0; i < 28; i++)
	{
		if (buildingList[i].block == true)
		{
			save << buildingList[i].getIndex() << " " << "1" << endl;
		}
	}
	save.close();
}
void readItem()
{
	fstream read;
	string ignore;
	int temp, number1, number2;
	read.open("saveItem.txt", ios::in);
	for (size_t i = 0; i < 4; i++)
	{
		read >> temp;
		if (read.eof())
		{
			read.close();
			break;
		}
		read >> number1 >> number2;
		player[temp].ownItem[0] = number1;
		player[temp].ownItem[1] = number2;
	}
	read >> ignore;
	while (1)
	{
		read >> temp;
		if (read.eof())
		{
			read.close();
			break;
		}
		read >> number1;
		buildingList[temp].block = number1;
	}

}