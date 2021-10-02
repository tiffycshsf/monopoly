#ifndef LOADMAP_H
#define LOADMAP_H
#include <Vector>
#include <string>
#include <fstream>
#include <iostream>




using namespace std;



class Building //存地圖資料
{
public:
	Building(string index, string Name, int type, int* pay);
	Building(string index, string Name, int type);
	~Building();
	string getIndex();
	string getName();
	int getType();
	int* getPay();
	int getBelongs();
	int getLevel();
	void setBelongs(int id);
	void setLevel(int le);
	bool block = false;
private:
	string index; //編號
	string name; //地名
	int type; //型別
	int* pay; //購買與收費
	int belongs = -1; //誰的
	int level = 0; //等級

};

struct Point //紀錄位置用
{
	int X;
	int Y;
};

extern vector<Building> buildingList;
extern vector<Point> place;
extern int state;
//extern playerStruct player[4];


void loadMap(string fileName);
void saveMap();
void fillData();
void loadpPlayer();
void loadLevel(string fileName);
void splitStr2Vec(string s, vector<string>& buf, string judge);


#endif


