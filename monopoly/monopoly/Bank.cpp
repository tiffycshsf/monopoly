#include"Bank.h"

Bank::Bank(void) {
	Account newPlayer;
	newPlayer.depositNum = 0;
	newPlayer.loanNum = 0;

	totalAccounts.push_back(newPlayer);
}

Bank::Bank(int tatalPlayer) {
	Account newPlayer;
	newPlayer.depositNum = 0;
	newPlayer.loanNum = 0;

	for (int i = 1; i <= tatalPlayer; i++) {
		totalAccounts.push_back(newPlayer);
	}
}

int Bank::getDeposit(character player) {

	return totalAccounts[player.getID()].depositNum;
}

int Bank::getLoan(character player) {

	return totalAccounts[player.getID()].loanNum;
}

void Bank::buyShare(character player, unsigned int money)
{
	totalAccounts[player.getID()].depositNum -= money;
}

void Bank::sellShare(character player, unsigned int money)
{
	totalAccounts[player.getID()].depositNum += money;
}


//check預設傳進來為false
bool Bank::deposit(character player, unsigned int money, bool check) {
	if (getDeposit(player) >= 0 && player.getCash() >= money) {
		totalAccounts[player.getID()].depositNum += money;
		player.sendMoney(money);
		check = true;
		return check;
	}
	else {
		cout << "身上現金不足，無法存款";
		return check;
	}
}

//check預設傳進來為false
bool Bank::withdraw(character player, unsigned int money, bool check) {
	if (getDeposit(player) >= money) {
		totalAccounts[player.getID()].depositNum -= money;
		player.getMoney(money);
		check = true;
		return check;
	}
	else {
		cout << "帳戶金額不足，無法提款";
		return check;
	}
}

//check預設傳進來為false
bool Bank::loan(character player, unsigned int money, bool check) {
	totalAccounts[player.getID()].loanNum += money;
	player.getMoney(money);
	check = true;
	return check;
}

//check預設傳進來為false
bool Bank::giveBack(character player, unsigned int money, bool check) {
	if (getLoan(player) >= money && player.getCash() >= money) {
		totalAccounts[player.getID()].loanNum -= money;
		player.sendMoney(money);
		check = true;
		return check;
	}
	else {
		cout << "身上現金不足，無法還款";
		return check;
	}
}

float Bank::getDepositRate(void) {
	srand(time(NULL));
	depositInterest = (1 + (rand() % 21) * 0.1)*0.01; //浮動存款利率為1%~3%
	return depositInterest;
}

float Bank::getLoanRate(void) {
	srand(time(NULL));
	loanInterest = (3 + (rand() % 21) * 0.1)*0.01;	//浮動貸款利率為3%~5%
	return loanInterest;
}

void Bank::depositRate(character player, float interest) {
	totalAccounts[player.getID()].depositNum *= (1 + interest);
}


void Bank::loanRate(character player, float interest) {
	totalAccounts[player.getID()].loanNum *= (1 + interest);
}

void Bank::setDeposit(character player, int money) {

	totalAccounts[player.getID()].depositNum = money;
}

void Bank::setLoan(character player, int money) {

	totalAccounts[player.getID()].loanNum = money;
}

void Bank::setDepositRate(float rate) {
	depositInterest = rate;
}

void Bank::setLoanRate(float rate) {
	loanInterest = rate;
}


void saveBank(Bank &b) {
	fstream save;
	save.open("saveBank.txt", ios::out);
	for (size_t i = 0; i < 4; i++)
	{
		save << i << endl;
		save << b.getDeposit(player[i]) << " " << b.getLoan(player[i]) << endl;
	}
	save << b.getDepositRate() << b.getLoanRate();

	save.close();
}

void readBank(Bank &b)
{
	fstream read;
	read.open("saveBank.txt", ios::in);
	setBank(b);
	for (size_t i = 0; i < 4; i++)
	{
		int tempIndex;
		int tempDeposit, tempLoan;
		read >> tempIndex >> tempDeposit >> tempLoan;
		b.setDeposit(player[tempIndex], tempDeposit);
		b.setLoan(player[tempIndex], tempLoan);
	}

	float tempDepositRate, tempLoanRate;
	read >> tempDepositRate >> tempLoanRate;
	b.setDepositRate(tempDepositRate);
	b.setLoanRate(tempLoanRate);

	read.close();
}

void setBank(Bank &b) {
	for (int i = 0; i < 4; i++) {
		b.setDeposit(player[i], 0);
		b.setLoan(player[i], 0);
	}
	b.setDepositRate(0);
	b.setLoanRate(0);
}