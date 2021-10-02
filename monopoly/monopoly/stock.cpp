#include "stock.h"

string stock::allName[10] = { "�t����","�����H��","��^��ltd","�߶i��","�O����","�o�j�]","��P","�ǩn�Z�u��","�xG�q","�߹��q�l" };

void randProbability(map<string, stock> & a, string name)
{
	random_device rd;
	mt19937 generator(rd());

	/* �`�A���� */
	normal_distribution<double> norm(0.0, 2.5);
	a[name].changeAmount = norm(generator);
	if (a[name].changeAmount > 5)
	{

		a[name].changeAmount = 5;
		a[name].limit = 1;//����
	}
	else if (a[name].changeAmount < -5)
	{

		a[name].changeAmount = -5;
		a[name].limit = -1;//�^��
	}
	setOneDecimal(a[name].changeAmount);
}
void setOneDecimal(double& a)
{
	if (a < 0)
	{
		a = (int)(a * 10 - 0.5);
		a /= 10;
	}
	else
	{
		a = (int)(a * 10 + 0.5);
		a /= 10;
	}
}
void updatePrice(map<string, stock> &a, string name)
{
	double temp2 = a[name].value;
	double temp;
	temp = 1 + (a[name].changeAmount / 100);
	a[name].value *= temp;
	setOneDecimal(a[name].value);
	a[name].gap = a[name].value - temp2;
}
stock::stock()
{
}
stock::stock(string a)
{
	name = a;
	value = (rand() % 15 + 1) + (rand() % 4 + 1);
	limit = 0;
	gap = 0;
	changeAmount = 0;
}

stock::~stock()
{
}

void setStock(map<string, stock> &a)
{
	for (size_t i = 0; i < 10; i++)
	{
		stock b(stock::allName[i]);
		a[stock::allName[i]] = b;
		b.~stock();
	}
}
//����N��,�Ѳ��s�� ,�X�i,�Ѳ�,�Ȧ�,���Lcheck
void buyStock(character& player,int number,int i,map<string,stock> a,Bank b,bool checkError)
{
	
	if ((a[stock::allName[number]].value*i*1000)>b.getDeposit(player))
	{
		checkError = 1;
		//������
	}
	else
	{
		checkError = 0;
		int temp = a[stock::allName[number]].value*i * 1000;
		//b.buyShare(player, temp);

		player.holdStock[number] += i;
	}
	
}
//���� �Ѳ��N�� ���L�ܼ�
void isSell(character& player,int number,bool checkError)
{
	if (player.holdStock[number] != 0)
	{
		checkError = 0;
		//�i�H��
	}
	else
	{
		checkError = 1;
		//�L����
	}
}
void saveStock(map<string, stock>& a)
{
	fstream save;
	save.open("saveStock.txt", ios::out);
	for (size_t i = 0; i < 10; i++)
	{
		save << i << endl;
		save << a[stock::allName[i]].value <<" "<<a[stock::allName[i]].gap << " " << a[stock::allName[i]].changeAmount << " " << a[stock::allName[i]].limit << endl;
	}
	save.close();
}
void readStock(map<string, stock>& a)
{
	fstream read;
	read.open("saveStock.txt", ios::in);
	setStock(a);
	for (size_t i = 0; i < 10; i++)
	{
		int temp;
		read >> temp >> a[stock::allName[i]].value >> a[stock::allName[i]].gap >> a[stock::allName[i]].changeAmount >> a[stock::allName[i]].limit;
	}
	read.close();
}
//if(checkError == 0)
void sellStock(character& player, int number, int i, map<string, stock>a,Bank b)
{
	if (i<=player.holdStock[number])
	{
		unsigned int temp = a[stock::allName[number]].value*i * 1000;
		//b.sellShare(player, temp);
		player.holdStock[number] -= i;
	}
	else
	{
		//cout ��Ӧh
	}
}
////�Ѳ��C�^�X��s
//for (size_t i = 0; i < 10; i++)
//{
//	randProbability(share, stock::allName[i]);
//	updatePrice(share, stock::allName[i]);
//}
//
