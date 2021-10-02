#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h> /* �üƬ������ */
#include <time.h>   /* �ɶ�������� */
#include<string>
#include<fstream>
#include"Character.h"

using namespace std;

struct Account {
	int depositNum;	//�s���`�B;�|�H�Q�v�W�[���B
	int loanNum;	//�U���`�B;�|�H�Q�v�W�[���B�A��U�ڪ��B>�b����B�ɡA�N���a���Ȧ�}��
};

class Bank {
private:
	vector<Account> totalAccounts;				//���a���N���|������vector��index�A�d��O0~3
	float depositInterest;						//�s�ڧQ�v
	float loanInterest;							//�U�ڧQ�v

public:
	Bank();
	Bank(int);									//�̾ڪ��a�H�Ʀbvector�s�W�b��ƶq
	int getDeposit(character);					//�^�ǬY���a���s���`�B
	int getLoan(character);						//�^�ǬY���a���U���`�B
	void buyShare(character, unsigned int);
	void sellShare(character, unsigned int);
	/////
	bool deposit(character, unsigned int, bool);		//�s�ڡA��s�ڧ������W�{���|�p��0�ɡA����s��
	/////
	bool withdraw(character, unsigned int, bool);		//���ڡA���ڧ����b����B�|�p��0�ɡA���ണ��
	/////
	bool loan(character, unsigned int, bool);			//�U��
	/////
	bool giveBack(character, unsigned int, bool);		//�ٴڡA���ٴڧ������W�{���|�p��0�ɡA�����ٴ�

	void depositRate(character, float);			//�W�[�s�ڪ��B(�t�X�Q�v)
	void loanRate(character, float);			//�W�[�U�ڪ��B(�t�X�Q�v)

	float getDepositRate(void);					//���o�ثe���s�ڧQ�v
	float getLoanRate(void);					//���o�ثe���U�ڧQ�v


	void setDeposit(character, int);			//Ū�ɮɭ��s�]�w���a�s��
	void setLoan(character, int);				//Ū�ɮɭ��s�]�w���a�U��
	void setDepositRate(float);					//Ū�ɮɭ��s�]�w�s�ڧQ�v
	void setLoanRate(float);					//Ū�ɮɭ��s�]�w�U�ڧQ�v

	friend class Character;
};

void saveBank(Bank &b);
void readBank(Bank &b);
void setBank(Bank &b);