#include "win.h"

win::win(string winnerIn)
{
	type = -1;
	winner = winnerIn;
}

void win::loadWin()
{
	wstring out;
	winIn.open("win.txt");
	//Clr();
	//gotoxy(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 245);
	while (getline(winIn, out)) {
		wcout << out << endl;
	}
	winIn.close();

	gotoxy(34, 22);
	cout << winner;


	winMod();
}

void win::winMod()
{
	if (type == 0) {
		gotoxy(50, 27);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 245);
		cout << "���}�C��";

		gotoxy(50, 25);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 95);
		cout << "�^�D���";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		type = 1;
	}
	else if (type == 1) {
		gotoxy(50, 25);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 245);
		cout << "�^�D���";

		gotoxy(50, 27);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 95);
		cout << "���}�C��";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		type = 0;
	}
}

