#include "basicUI.h"

void drawLine(int startX, int startY, int length)
{
	gotoxy(startX + 1, startY);
	for (int i = 0; i < length - 1; i++)
	{
		std::cout << "─";
	}
}
void drawVertical(int startX, int startY, int width)
{
	gotoxy(startX, startY);
	for (int i = 1; i < width; i++)
	{
		gotoxy(startX, startY + i);
		std::cout << "│";
	}
}

void drawBlock(int startX, int startY, int length, int width) //把一個長寬訂好的block畫出來
{
	int endPosX = startX + length;
	int	endPosY = startY + width;
	for (int i = 0; i < length; i++)
	{
		gotoxy(startX + i, startY);
		std::wcout << "─";
		gotoxy(startX + i, endPosY);
		std::cout << "─";
	}
	for (int i = 0; i <= width; i++)
	{
		gotoxy(startX, startY + i);
		std::cout << "│";
		gotoxy(endPosX, startY + i);
		std::cout << "│";
	}
	gotoxy(startX, startY);
	std::cout << "┌";
	gotoxy(endPosX, startY);
	std::cout << "┐";
	gotoxy(startX, endPosY);
	std::cout << "└";
	gotoxy(endPosX, endPosY);
	std::cout << "┘";
}
