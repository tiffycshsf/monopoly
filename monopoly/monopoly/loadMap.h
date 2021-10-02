#ifndef LOADMAP_H
#define LOADMAP_H
#include <Vector>
#include <string>
#include <fstream>
#include <iostream>




using namespace std;



class Building //�s�a�ϸ��
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
	string index; //�s��
	string name; //�a�W
	int type; //���O
	int* pay; //�ʶR�P���O
	int belongs = -1; //�֪�
	int level = 0; //����

};

struct Point //������m��
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


