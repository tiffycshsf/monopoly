#include "EConsole.h"
#include "stateMachine.h"
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

int stateMachine = 0;
void menuCtr(int ctr)
{
	int posX = 100;
	int PosY = 20;
	switch (ctr)
	{
	case 0:
		gotoxy(posX + 5, PosY + 2);
		SetColor(8);
		cout << "�}�s�C��";
		gotoxy(posX + 5, PosY + 6);
		SetColor(0);
		cout << "�~��C��";
		gotoxy(posX + 5, PosY + 10);
		SetColor(0);
		cout << "���}�C��";
		SetColor(0);
		break;
	case 1:
		gotoxy(posX + 5, PosY + 2);
		SetColor(0);
		cout << "�}�s�C��";
		gotoxy(posX + 5, PosY + 6);
		SetColor(8);
		cout << "�~��C��";
		gotoxy(posX + 5, PosY + 10);
		SetColor(0);
		cout << "���}�C��";
		SetColor(0);
		break;
	case 2:
		gotoxy(posX + 5, PosY + 2);
		SetColor(0);
		cout << "�}�s�C��";
		gotoxy(posX + 5, PosY + 6);
		SetColor(0);
		cout << "�~��C��";
		gotoxy(posX + 5, PosY + 10);
		SetColor(8);
		cout << "���}�C��";
		SetColor(0);
		break;
	}
}

void optionCtr(int ctr)
{
	int posX = 100;
	int posY = 10;
	switch (ctr)
	{
	case 0:
		gotoxy(posX + 4, posY + 2);
		SetColor(8);
		wcout << "�~��C��";
		gotoxy(posX + 4, posY + 6);
		SetColor(0);
		wcout << "���s�}�l";
		gotoxy(posX + 4, posY + 10);
		SetColor(0);
		wcout << "�^�D���";
		gotoxy(posX + 4, posY + 14);
		SetColor(0);
		wcout << "���}�C��";
		SetColor(0);
		break;
	case 1:
		gotoxy(posX + 4, posY + 2);
		SetColor(0);
		wcout << "�~��C��";
		gotoxy(posX + 4, posY + 6);
		SetColor(8);
		wcout << "���s�}�l";
		gotoxy(posX + 4, posY + 10);
		SetColor(0);
		wcout << "�^�D���";
		gotoxy(posX + 4, posY + 14);
		SetColor(0);
		wcout << "���}�C��";
		SetColor(0);
		break;
	case 2:
		gotoxy(posX + 4, posY + 2);
		SetColor(0);
		wcout << "�~��C��";
		gotoxy(posX + 4, posY + 6);
		SetColor(0);
		wcout << "���s�}�l";
		gotoxy(posX + 4, posY + 10);
		SetColor(8);
		wcout << "�^�D���";
		gotoxy(posX + 4, posY + 14);
		SetColor(0);
		wcout << "���}�C��";
		SetColor(0);
		break;
	case 3:
		gotoxy(posX + 4, posY + 2);
		SetColor(0);
		wcout << "�~��C��";
		gotoxy(posX + 4, posY + 6);
		SetColor(0);
		wcout << "���s�}�l";
		gotoxy(posX + 4, posY + 10);
		SetColor(0);
		wcout << "�^�D���";
		gotoxy(posX + 4, posY + 14);
		SetColor(8);
		wcout << "���}�C��";
		SetColor(0);
		break;
	default:
		break;
	}
}

void templateCtr(int ctr)
{
	int posX = 100;
	int posY = 15;
	switch (ctr)
	{
	case 0: //�T�w
		gotoxy(posX + 6, posY + 10);
		SetColor(8);
		wcout << "�T�w";
		gotoxy(posX + 27, posY + 10);
		SetColor(0);
		wcout << "����";
		SetColor(0);
		break;
	case 1: //����
		gotoxy(posX + 6, posY + 10);
		SetColor(0);
		wcout << "�T�w";
		gotoxy(posX + 27, posY + 10);
		SetColor(8);
		wcout << "����";
		SetColor(0);
		break;
	default:
		break;
	}
}

void loadUI(string state) //menu main board option regret restore
{
	fstream UI;
	string sy;
	int line = 0;
	if (state == "menu")
	{
		int PosX = 100;
		int PosY = 20;
		UI.open("menu.txt");
		while (getline(UI, sy))
		{
			gotoxy(PosX, PosY + line);
			cout << sy << endl;
			line++;
		}
		UI.close();
		gotoxy(PosX + 5, PosY + 2);
		SetColor(8);
		cout << "�}�s�C��";
		SetColor(0);
	}
	else if (state == "option")
	{
		int posX = 100;
		int posY = 10;
		UI.open("option.txt");
		while (getline(UI, sy))
		{
			cout.width(2);
			gotoxy(posX, posY + line);
			cout << sy << endl;
			line++;
		}
		UI.close();
	}
	else if (state == "buy")
	{
		int posX = 100;
		int posY = 15;
		UI.open("template.txt");
		while (getline(UI, sy))
		{
			gotoxy(posX, posY + line);
			cout << sy << endl;
			line++;
		}
		UI.close();

		gotoxy(posX + 13, posY + 4); 
		SetColor(1);
		cout << "���n�ʶR��?";
		SetColor(0);

		gotoxy(posX + 6, posY + 10);
		SetColor(8);
		wcout << "�T�w";
		SetColor(0);
	}
	else if (state == "upgrade")
	{
		int posX = 100;
		int posY = 15;
		UI.open("template.txt");
		while (getline(UI, sy))
		{
			gotoxy(posX, posY + line);
			cout << sy << endl;
			line++;
		}
		UI.close();

		gotoxy(posX + 13, posY + 4);
		SetColor(1);
		cout << "���n�ɯŶ�?";
		SetColor(0);

		gotoxy(posX + 6, posY + 10);
		SetColor(8);
		wcout << "�T�w";
		SetColor(0);
	}
	else if (state == "clean")
	{
		int posX = 100;
		int posY = 15;
		UI.open("template.txt");
		while (getline(UI, sy))
		{
			gotoxy(posX, posY + line);
			wcout << "                                              ";
			line++;
		}
		UI.close();

		gotoxy(posX + 6, posY + 10);
		wcout << "    ";
		gotoxy(posX + 27, posY + 10);
		wcout << "    ";

	}
}

int selecterU(int num, int state)
{
	char key;
	int numCtr = 0;
	while (key = _getch()) //Ū��
	{
		if (key == 13)
		{
			break;
		}

		if (key == 72) //key up code
		{
			if (numCtr != 0 && numCtr <= num - 1)
			{
				numCtr--;
			}
		}
		else if (key == 80) //key down code
		{
			if (numCtr != num - 1 && numCtr >= 0)
			{
				numCtr++;
			}
		}

		if (state == 0)
		{
			menuCtr(numCtr);
		}
		else if (state == 1)
		{
			optionCtr(numCtr);
		}

	}

	return numCtr;
}

int selecterLeft() 
{
	char key;
	int numCtr = 0; //0 �T�w 1 ����
	while (key = _getch()) //Ū��
	{
		if (key == 13)
		{
			break;
		}

		if (key == 75 || key == 77) //key up code
		{
			if (numCtr == 1)
			{
				numCtr = 0;
			}
			else
			{
				numCtr = 1;
			}
		}

		templateCtr(numCtr);

	}

	return numCtr;
}