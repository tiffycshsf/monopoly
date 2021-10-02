#include "playerUI.h"
#include "Character.h"
#include "loadMap.h"
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include "Bank.h"
using namespace std;

int lastPlace[4];


void playerUI(int playerID)
{
	int posX = 0;
	int posY = 0;
	int color = 0;
	int X, Y;
	switch (playerID)
	{
	case 0:
		posX = 0;
		posY = 0;
		color = 24;
		break;
	case 1:
		posX = 0;
		posY = 21;
		color = 40;
		break;
	case 2:
		posX = 192;
		posY = 0;
		color = 56;
		break;
	case 3:
		posX = 192;
		posY = 21;
		color = 72;
		break;
	default:
		break;
	}

	drawBlock(posX, posY, 30, 20);
	drawLine(posX, posY + 2, 30);
	drawVertical(posX + 7, posY, 2);
	drawLine(posX, posY + 4, 30);
	/*gotoxy(posX + 8, posY +8);
	std::cout << "30000";*/

	drawVertical(posX + 7, posY + 4, 3);
	drawVertical(posX + 14, posY + 4, 3);
	drawLine(posX, posY + 7, 30);
	drawLine(posX, posY + 9, 30);
	drawVertical(posX + 14, posY + 9, 11);
	//drawVertical(posX + 22, posY + 12, 8);

	//gotoxy(posX + 7, posY + 7);
	//std::cout << "�֦��a��";

	//�򥻬[�c��@�w�n��ܪ���r
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	gotoxy(posX + 1, posY + 1); //ID
	std::cout << " ID: " << playerID;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(posX + 9, posY + 1); //�겣
	std::cout << "�{���겣:  ";
	std::cout << player[playerID].getCash();
	//�Ѳ���
	/*gotoxy(posX + 11, posY + 3); //�Ѳ�title
	std::cout << "�Ѳ�����";
	gotoxy(posX + 2, posY + 5);
	std::cout << "�Ѳ�A";
	gotoxy(posX + 9, posY + 5);
	std::cout << "�Ѳ�B";
	gotoxy(posX + 16, posY + 5);
	std::cout << "�Ѳ�C";
	gotoxy(posX + 24, posY + 5);
	std::cout << "�Ѳ�D";*/
	//�Ȧ��
	gotoxy(posX + 11, posY + 3); //�Ȧ�title
	std::cout << "�w�O�v��";
	gotoxy(posX + 2, posY + 5);
	std::cout << "�U��";
	gotoxy(posX + 9, posY + 5);
	std::cout << "�w�s";
	gotoxy(posX + 16, posY + 5);
	std::cout << "   �]�Ȫ��p";
	//�a����
	gotoxy(posX + 13, posY + 8);
	std::cout << "�a��";

	for (int i = 0; i < player[playerID].structList.size(); i++)
	{
		string Listemp;
		for (int j = 0; j < buildingList.size(); j++)
		{
			if (player[playerID].structList[i].place == buildingList[j].getIndex())
			{
				Listemp = buildingList[j].getName();
				break;
			}
		}

		if (i < 10)
		{
			gotoxy(posX + 2, posY + 10 + i);
			cout << Listemp;
			gotoxy(posX + 13, posY + 10 + i);
			cout << player[playerID].structList[i].level;
		}
		else if (i >= 10 && i < 20)
		{
			gotoxy(posX + 16, posY + 10 + (i - 10));
			cout << Listemp;
			gotoxy(posX + 29, posY + 10 + (i - 10));
			cout << player[playerID].structList[i].level;
		}
	}

	//���a�b�a�ϤW��m���
	if (player[playerID].died == false)
	{
		X = place[player[playerID].getPlace()].X;
		Y = place[player[playerID].getPlace()].Y;
		gotoxy(X + 2 + (playerID * 3), Y - 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), playerID + 1);
		cout << "��";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�C��^�k�쪬
		lastPlace[playerID] = player[playerID].getPlace();
	}
	else //���`�����
	{
		X = place[player[playerID].getPlace()].X;
		Y = place[player[playerID].getPlace()].Y;
		gotoxy(X + 2 + (playerID * 3), Y - 2);
		cout << "  ";
	}

}


void playerdied(int playerID) //�}��
{
	player[playerID].died = true;
	//�a��UI�M��
	int X;
	int Y;
	X = place[player[playerID].getPlace()].X;
	Y = place[player[playerID].getPlace()].Y;
	gotoxy(X + 2 + (playerID * 3), Y - 2);
	cout << "  ";
	// ����&�D��&�Цa�� �M��
	player[playerID].setInit(playerID, player[playerID].getPlace(), -1);

	for (int j = 0; j < buildingList.size(); j++)
	{
		if (playerID == buildingList[j].getBelongs())
		{
			buildingList[j].setBelongs(-1);
			buildingList[j].setLevel(0);
		}
	}
	setMoney(playerID);
	player[playerID].resetStruct();
	StructBelong();
	setStruct(playerID);
}

void setMoney(int playerID)
{
	int posX = 0;
	int posY = 0;
	int color = 0;
	switch (playerID)
	{
	case 0:
		posX = 0;
		posY = 0;
		color = 1;
		break;
	case 1:
		posX = 0;
		posY = 21;
		color = 2;
		break;
	case 2:
		posX = 192;
		posY = 0;
		color = 3;
		break;
	case 3:
		posX = 192;
		posY = 21;
		color = 4;
		break;
	default:
		break;
	}

	gotoxy(posX + 9, posY + 1); //�겣
	cout << "                     ";
	gotoxy(posX + 9, posY + 1); 
	std::cout << "�{���겣:  ";
	std::cout << player[playerID].getCash();
}


void setStock(int playerID)
{
	int posX = 0;
	int posY = 0;
	int color = 0;
	switch (playerID)
	{
	case 0:
		posX = 0;
		posY = 0;
		color = 1;
		break;
	case 1:
		posX = 0;
		posY = 21;
		color = 2;
		break;
	case 2:
		posX = 192;
		posY = 0;
		color = 3;
		break;
	case 3:
		posX = 192;
		posY = 21;
		color = 4;
		break;
	default:
		break;
	}

	gotoxy(posX + 2, posY + 6); //�Ѳ�A
	std::cout << "     ";
	gotoxy(posX + 9, posY + 6); //�Ѳ�B
	std::cout << "     ";
	gotoxy(posX + 16, posY + 6); //�Ѳ�C
	std::cout << "     ";
	gotoxy(posX + 24, posY + 6); //�Ѳ�D
	std::cout << "     ";
/*
	gotoxy(posX + 2, posY + 6); //�Ѳ�A
	std::cout << "     ";
	gotoxy(posX + 9, posY + 6); //�Ѳ�B
	std::cout << "     ";
	gotoxy(posX + 16, posY + 6); //�Ѳ�C
	std::cout << "     ";
	gotoxy(posX + 24, posY + 6); //�Ѳ�D
	std::cout << "     ";
*/
}

void setBank(int playerID , Bank &bank)
{
	int posX = 0;
	int posY = 0;
	int color = 0;
	switch (playerID)
	{
	case 0:
		posX = 0;
		posY = 0;
		color = 1;
		break;
	case 1:
		posX = 0;
		posY = 21;
		color = 2;
		break;
	case 2:
		posX = 192;
		posY = 0;
		color = 3;
		break;
	case 3:
		posX = 192;
		posY = 21;
		color = 4;
		break;
	default:
		break;
	}

	gotoxy(posX + 2, posY + 6);
	std::cout << setw(3) << bank.getLoanRate() << right; //�U��
	gotoxy(posX + 9, posY + 6);
	std::cout << setw(3) << bank.getDepositRate() << right; //�w�s
	gotoxy(posX + 16, posY + 6);
	std::cout << setw(12) << bank.getDeposit(player[playerID]) << right;

}

void setStruct(int playerID)
{
	int posX = 0;
	int posY = 0;
	int color = 0;
	switch (playerID)
	{
	case 0:
		posX = 0;
		posY = 0;
		color = 1;
		break;
	case 1:
		posX = 0;
		posY = 21;
		color = 2;
		break;
	case 2:
		posX = 192;
		posY = 0;
		color = 3;
		break;
	case 3:
		posX = 192;
		posY = 21;
		color = 4;
		break;
	default:
		break;
	}

	for (int i = 0; i < 5; i++)
	{
		gotoxy(posX + 2, posY + 15 + i);
		cout << "             ";
		gotoxy(posX + 16, posY + 15 + i);
		cout << "             ";
	}

	for (int i = 0; i < player[playerID].structList.size(); i++)
	{
		string Listemp;
		for (int j = 0; j < buildingList.size(); j++)
		{
			if (player[playerID].structList[i].place == buildingList[j].getIndex())
			{
				Listemp = buildingList[j].getName();
				break;
			}
		}

		if (i < 10)
		{
			gotoxy(posX + 2, posY + 10 + i);
			cout << Listemp;
			gotoxy(posX + 13, posY + 10 + i);
			cout << player[playerID].structList[i].level;
		}
		else if (i >= 10 && i < 20)
		{
			gotoxy(posX + 16, posY + 10 + (i - 10));
			cout << Listemp;
			gotoxy(posX + 29, posY + 10 + (i - 10));
			cout << player[playerID].structList[i].level;
		}
	}
}

void playerPlace(int playerID)
{
	int posX = 0;
	int posY = 0;
	int color = 0;
	int X = 0, Y = 0;
	int step = 0;
	switch (playerID)
	{
	case 0:
		posX = 0;
		posY = 0;
		color = 1;
		break;
	case 1:
		posX = 0;
		posY = 21;
		color = 2;
		break;
	case 2:
		posX = 192;
		posY = 0;
		color = 3;
		break;
	case 3:
		posX = 192;
		posY = 21;
		color = 4;
		break;
	default:
		break;
	}
	//�M�ŤW�@�Ӧ�m
	while ((lastPlace[playerID] + step) % 28 != player[playerID].getPlace())
	{
		X = place[(lastPlace[playerID] + step) % 28].X;
		Y = place[(lastPlace[playerID] + step) % 28].Y;
		gotoxy(X + 2 + (playerID * 3), Y - 2);
		cout << "  ";
		step++;//��s�B��
		X = place[(lastPlace[playerID] + step) % 28].X;
		Y = place[(lastPlace[playerID] + step) % 28].Y;
		gotoxy(X + 2 + (playerID * 3), Y - 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		cout << "��";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //�C��^�k�쪬
		Sleep(500);
	}
	lastPlace[playerID] = player[playerID].getPlace(); //��s��m
}

void StructBelong()
{
	int posX = 31;
	int posY = 0;
	for (int i = 0; i < buildingList.size(); i++) //Init
	{
		int len = buildingList[i].getName().length(); //�p���r����
		cout << setw(9 + len / 2) << right; //�m��
		if (i < 8)
		{
			gotoxy(posX + 1, posY + 3 + 5 * i);
			cout << buildingList[i].getName();
		}
		else if (8 <= i && i < 15)
		{
			gotoxy(posX + 1 + (i - 7) * 20, posY + 38);
			cout << buildingList[i].getName();
		}
		else if (15 <= i && i < 22)
		{
			gotoxy(posX + 141, posY + 38 - ((i - 14) * 5));
			cout << buildingList[i].getName();
		}
		else
		{
			gotoxy(posX + 141 - ((i - 21) * 20), posY + 3);
			cout << buildingList[i].getName();
		}
		for (int i = 0; i < 10 - len / 2; i++)
		{
			cout << " ";
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < player[i].structList.size(); j++)
		{
			string Listemp;
			for (int k = 0; k < buildingList.size(); k++)
			{
				if (player[i].structList[j].place == buildingList[k].getIndex())
				{
					Listemp = buildingList[k].getName();
					break;
				}
			}
			int len = Listemp.length(); //�p���r����
			cout << setw(9 + len / 2) << right; //�m��
			int location = atoi(player[i].structList[j].place.c_str());
			gotoxy(place[location].X, place[location].Y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 24 + 16 * i);
			cout << Listemp;
			for (int i = 0; i < 10 - len / 2; i++)
			{
				cout << " ";
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}

	for (int i = 0; i < buildingList.size(); i++)
	{
		if (buildingList[i].block == true) //���]����
		{
			gotoxy(place[i].X+18, place[i].Y);
			cout << "x";
		}
		else
		{
			gotoxy(place[i].X + 18, place[i].Y);
			cout << " ";
		}
	}
}

void informationBlock(int round,int turn) 
{
	int posX = 100;
	int posY = 45;
	drawBlock(posX, posY, 45, 6);
	drawLine(posX, posY + 2, 16);
	drawVertical(posX + 7, posY, 6);
	drawVertical(posX + 16, posY, 6);
	drawVertical(posX + 30, posY, 6);
	gotoxy(posX + 2, posY + 1);
	cout << "�^�X";
	gotoxy(posX + 11, posY + 1);
	cout << "����";

	gotoxy(posX + 4, posY + 4);
	cout << round;

	gotoxy(posX + 9, posY + 4);
	cout << "player" << turn;

	gotoxy(posX + 19, posY + 1);
	cout << "�ť����Y��";
	gotoxy(posX + 19, posY + 3);
	cout << "exc ���";
	gotoxy(posX + 20, posY + 5);
	cout << "B/b �Ȧ�";
	gotoxy(posX + 32, posY + 1);
	cout << "Z/z �D��";
	gotoxy(posX + 32, posY + 3);
	cout << "X/x �ʶR/�ɯ�";
	gotoxy(posX + 32, posY + 5);
	cout << "C/c �����^�X";
}

bool victory()
{
	int count = 0; //�٦b���W���H��
	for (int i = 0; i < 4; i++)
	{
		if (player[i].died == false)
		{
			count++;
		}
	}

	if (count <= 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int blockplace() 
{
	char key;
	int numCtr = 0;
	gotoxy(place[numCtr].X, place[numCtr].Y);
	cout<< "��";
	while (key = _getch()) //Ū��
	{

		if (key == 13) //enter �T�w
		{
			gotoxy(place[numCtr].X, place[numCtr].Y);
			cout << "   ";
			gotoxy(98, 20);
			cout << "                             ";
			return numCtr;
			break;
		}
		else if (key == 27) //exc����
		{
			gotoxy(place[numCtr].X, place[numCtr].Y);
			cout << "   ";
			return -1;
			break;
		}

		gotoxy(place[numCtr].X, place[numCtr].Y);
		cout << "   ";
		if (key == 72) //key up code
		{
			numCtr--;
			if (numCtr < 0)
			{
				numCtr = 27;
			}
		}
		else if (key == 80) //key down code
		{
			numCtr++;
			if (numCtr > 27)
			{
				numCtr = 0;
			}
		}

		gotoxy(place[numCtr].X, place[numCtr].Y);
		cout << "��";


	}
}