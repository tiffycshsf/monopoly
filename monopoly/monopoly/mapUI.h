#ifndef MAPUI_H
#define MAPUI_H
#include "basicUI.h"

using namespace std;
void drawMap();
void billboard();


void drawMap() //¨C¤p®æ20*5
{
	int posX = 31;
	int posY = 0;
	drawBlock(posX + 0, posY + 0, 160, 40);
	drawLine(posX + 0, posY + 5, 160);
	drawVertical(posX + 20, posY + 0, 40);
	drawLine(posX + 0, posY + 35, 160);
	drawVertical(posX + 140, posY + 0, 40);
	for (int i = 2; i < 7; i++)
	{
		drawLine(posX + 0, posY + 5*i, 20);
		drawLine(posX + 140, posY + 5 * i, 20);
	}
	for (int i = 2; i < 7; i++)
	{
		drawVertical(posX + 20 * i, posY + 0, 5);
		drawVertical(posX + 20*i, posY + 35, 5);
	}
}

/*void billboard(string contain)
{
	drawBlock(80, 10, 40, 20);
	gotoxy(100-contain.length(), 20);
	SetColor(5);
	cout << contain;
	SetColor(0);
}*/


#endif