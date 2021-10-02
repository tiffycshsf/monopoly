#pragma once
#include <iostream>
#include <vector>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
#include<string>
#include<fstream>
#include"Character.h"

using namespace std;

struct Account {
	int depositNum;	//存款總額;會隨利率增加金額
	int loanNum;	//貸款總額;會隨利率增加金額，當貸款金額>帳戶金額時，代表玩家的銀行破產
};

class Bank {
private:
	vector<Account> totalAccounts;				//玩家的代號會對應到vector的index，範圍是0~3
	float depositInterest;						//存款利率
	float loanInterest;							//貸款利率

public:
	Bank();
	Bank(int);									//依據玩家人數在vector新增帳戶數量
	int getDeposit(character);					//回傳某玩家的存款總額
	int getLoan(character);						//回傳某玩家的貸款總額
	void buyShare(character, unsigned int);
	void sellShare(character, unsigned int);
	/////
	bool deposit(character, unsigned int, bool);		//存款，當存款完的身上現金會小於0時，不能存款
	/////
	bool withdraw(character, unsigned int, bool);		//提款，當提款完的帳戶金額會小於0時，不能提款
	/////
	bool loan(character, unsigned int, bool);			//貸款
	/////
	bool giveBack(character, unsigned int, bool);		//還款，當還款完的身上現金會小於0時，不能還款

	void depositRate(character, float);			//增加存款金額(配合利率)
	void loanRate(character, float);			//增加貸款金額(配合利率)

	float getDepositRate(void);					//取得目前的存款利率
	float getLoanRate(void);					//取得目前的貸款利率


	void setDeposit(character, int);			//讀檔時重新設定玩家存款
	void setLoan(character, int);				//讀檔時重新設定玩家貸款
	void setDepositRate(float);					//讀檔時重新設定存款利率
	void setLoanRate(float);					//讀檔時重新設定貸款利率

	friend class Character;
};

void saveBank(Bank &b);
void readBank(Bank &b);
void setBank(Bank &b);