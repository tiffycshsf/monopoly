#include "basicUI.h"

void drawLine(int startX, int startY, int length)
{
	gotoxy(startX + 1, startY);
	for (int i = 0; i < length - 1; i++)
	{
		std::cout << "�w";
	}
}
void drawVertical(int startX, int startY, int width)
{
	gotoxy(startX, startY);
	for (int i = 1; i < width; i++)
	{
		gotoxy(startX, startY + i);
		std::cout << "�x";
	}
}

void drawBlock(int startX, int startY, int length, int width) //��@�Ӫ��e�q�n��block�e�X��
{
	int endPosX = startX + length;
	int	endPosY = startY + width;
	for (int i = 0; i < length; i++)
	{
		gotoxy(startX + i, startY);
		std::wcout << "�w";
		gotoxy(startX + i, endPosY);
		std::cout << "�w";
	}
	for (int i = 0; i <= width; i++)
	{
		gotoxy(startX, startY + i);
		std::cout << "�x";
		gotoxy(endPosX, startY + i);
		std::cout << "�x";
	}
	gotoxy(startX, startY);
	std::cout << "�z";
	gotoxy(endPosX, startY);
	std::cout << "�{";
	gotoxy(startX, endPosY);
	std::cout << "�|";
	gotoxy(endPosX, endPosY);
	std::cout << "�}";
}
