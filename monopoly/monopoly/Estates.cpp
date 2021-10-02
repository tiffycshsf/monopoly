//
//  Estates.cpp
//  Monopoly
//
//  Created by Hsu47 on 2019/5/22.
//  Copyright © 2019年 Hsu47. All rights reserved.
//

#include "Estates.h"

Estates::Estates()
{
	owner = -1;
}

void getInformation(map<int, Estates> &a)
{

	fstream openFile;
	openFile.open("basemap.txt");
	string temp = {};

	openFile >> temp >> temp >> temp;
	int temp1[7];
	while (1) {
		openFile >> temp1[0] >> temp >> temp1[1];
		
		if (temp1[1] == 1)
		{
			
			for (int i = 0; i < 5; i++)
			{
				openFile >> temp1[i + 2];
			}
			Estates model;
			model.pos = temp1[0];
			model.buy = temp1[2];
			model.level = 0;
			for (int i = 0; i < 4; i++) {
				model.price[i] = temp1[i + 3];
			
			}
			
			a[temp1[0]] = model;
			
		
		}
		if (temp1[0] == 27)
		{
			break;
		}
	}
}
void buyProperty(int player, int pos, map<int, Estates> a)
{

	a[pos].owner = player;
	// player.money -=a[pos].buy;
}
void upgrade(int player, int pos, map<int, Estates> a)
{
	a[pos].level += 1;
}
