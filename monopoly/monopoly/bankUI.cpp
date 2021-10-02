#include "bankUI.h"

bankUI::bankUI()
{
	playerID = 0;
	stateC = 'L';
	stateI = 0;
}

bankUI::bankUI(character & player)
{
	playerID = player.getID();
	stateC = 'L';
	stateI = 0;

	//loadBank();
	//loadRate();
	//loadData(player, bank);
}

void bankUI::loadBank()
{
	wstring out;
	Clr();
	gotoxy(0, 0);
	bankIn.open("bank.txt");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 115);
	while (getline(bankIn, out)) {
		wcout << out << endl;
	}
	bankIn.close();
}

void bankUI::loadRate()
{
	int line = 0;
	wstring out;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 63);
	rateIn.open("bankRate.txt");
	while (getline(rateIn, out))
	{
		gotoxy(5, 23 + line);
		wcout << out << endl;
		line++;
	}
	rateIn.close();


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 63);
	gotoxy(24, 24);  //rateD
	cout << rateD * 100 << " %";
	gotoxy(24, 26);  //rateL
	cout << rateL * 100 << " %";
}

void bankUI::loadData(character & player, Bank &bank)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 63);
	gotoxy(76, 4);  //name
	cout << player.getID();
	gotoxy(76, 6);
	cout << bank.getDeposit(player);
	gotoxy(76, 8);
	cout << bank.getLoan(player);
	gotoxy(76, 10);
	cout << player.getCash();
}

void bankUI::loadOption()
{
	int line = 0;
	wstring out;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 63);
	gotoxy(62, 15);
	optionIn.open("bankOption.txt");
	while (getline(optionIn, out))
	{
		gotoxy(62, 15 + line);
		wcout << out << endl;
		line++;
	}
	optionIn.close();

}

void bankUI::switchOption()
{
	if (stateC == 'L') {
		switch (stateI) {
		case 0:
		{
			loadOption();
			gotoxy(71, 17);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			cout << "存款";
			break;
		}
		case 1:
		{
			loadOption();
			gotoxy(71, 21);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			cout << "貸款";
			break;
		}
		case 2:
		{
			loadOption();
			gotoxy(69, 25);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			cout << "股市交易";
			break;
		}
		case 3:
		{
			loadOption();
			gotoxy(69, 29);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			cout << "離開銀行";
			break;
		}
		}
	}
	else {
		switch (stateI) {
		case 0:
		{
			loadOption();
			gotoxy(94, 17);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			cout << "提款";
			break;
		}
		case 1:
		{
			loadOption();
			gotoxy(94, 21);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			cout << "還款";
			break;
		}
		case 2:
		{
			loadOption();
			gotoxy(92, 25);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			cout << "道具購買";
			break;
		}
		case 3:
		{
			loadOption();
			gotoxy(92, 29);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
			cout << "離開銀行";
			break;
		}
		}
	}
}

void bankUI::showKey()
{
	wstring out;
	int line = 0;
	keyIn.open("bankKeyin.txt");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	while (getline(keyIn, out))
	{
		gotoxy(32, 13 + line);
		wcout << out << endl;
		line++;
	}
	keyIn.close();
}

void bankUI::loadAll(character & player, Bank &bank)
{
	loadBank();
	loadRate();
	loadData(player, bank);
	loadOption();
	switchOption();
}

void bankUI::move(int key, character & player, Bank &bank, map<string, stock> &Stock, bool & leave)
{
	switch (key) {
	case 72://up
	{
		if (stateI > 0) {
			stateI -= 1;
		}
		else {
			stateI = 3;
		}
		switchOption();
		break;
	}
	case 80://down
	{
		if (stateI < 3) {
			stateI += 1;
		}
		else {
			stateI = 0;
		}
		switchOption();
		break;
	}
	case 77: //right
	{
		if (stateC == 'L') stateC = 'R';
		else stateC = 'L';
		switchOption();
		break;
	}
	case 75: //left
	{
		if (stateC == 'L') stateC = 'R';
		else stateC = 'L';
		switchOption();
		break;
	}
	case 13:
	{
		if (stateC == 'L') {
			switch (stateI) {
			case 0:
			{
				showKey();
				gotoxy(46, 16);

				int num;
				cin >> num;

				if (num >= 0) {
					bool check = false;
					check = bank.deposit(player, num, check);
					if (check == true) {
						player.sendMoney(num);
					}
					else {
						gotoxy(35, 14);
						cout << "身上現金不足，無法存款";
						stateC = 'L';
						stateI = 0;
						Sleep(1000);
					}
					loadAll(player, bank);
				}
				else {
					gotoxy(35, 14);
					cout << "輸入需為正數";
					gotoxy(46, 16);
					cout << "按ENTER以繼續";
				}

				break;
			}
			case 1:
			{
				showKey();
				gotoxy(46, 16);

				int num;
				cin >> num;

				if (num >= 0) {
					bool check = false;
					bank.loan(player, num, check);
					player.getMoney(num);
					loadAll(player, bank);
				}
				else {
					gotoxy(35, 14);
					cout << "輸入需為正數";
					gotoxy(46, 16);
					cout << "按ENTER以繼續";
				}

				break;
			}
			case 2:
			{
				bool check = true;
				loadStock(Stock, player);
				stockState = 0;
				key = 0;
				switchStock();
				while (key = _getch()) {
					if (check == true) {
						check = moveStock(key, player, bank, Stock, check);
					}
					else {
						loadAll(player, bank);
						break;
					}
				}
				break;
			}
			case 3:
			{
				leave = true;
				break;
			}
			}
		}
		else {
			switch (stateI) {
			case 0:
			{
				showKey();
				gotoxy(46, 16);

				int num;
				cin >> num;

				if (num >= 0) {
					bool check = false;
					check = bank.withdraw(player, num, check);
					if (check == true) {
						player.getMoney(num);
					}
					else {
						gotoxy(35, 14);
						cout << "帳戶金額不足，無法提款";
						stateC = 'L';
						stateI = 0;
						Sleep(1000);
					}
					loadAll(player, bank);
				}
				else {
					gotoxy(35, 14);
					cout << "輸入需為正數";
					gotoxy(46, 16);
					cout << "按ENTER以繼續";
				}

				break;
			}
			case 1:
			{
				showKey();
				gotoxy(46, 16);

				int num;
				cin >> num;

				if (num >= 0) {
					bool check = false;
					if (bank.getLoan(player) <= num) {
						check = bank.giveBack(player, num, check);
						if (check == true) {
							player.sendMoney(num);
						}
						else {
							gotoxy(35, 14);
							cout << "身上現金不足，無法還款";
						}
					}
					else {
						bank.giveBack(player, bank.getLoan(player), check);
						gotoxy(35, 14);
						cout << "超過需還款金額，剩下返回";
					}
					stateC = 'L';
					stateI = 0;
					Sleep(1000);
					loadAll(player, bank);
				}
				else {
					gotoxy(35, 14);
					cout << "輸入需為正數";
					gotoxy(46, 16);
					cout << "按ENTER以繼續";
				}

				break;
			}
			case 2:
			{
				wstring out;
				int line = 0;
				itemOp.open("item.txt");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				while (getline(itemOp, out))
				{
					gotoxy(36, 13 + line);
					wcout << out << endl;
					line++;
				}
				itemOp.close();
				key = 0;
				itemType = 0;
				switchItem();
				while (key = _getch()) {
					if (key == 75 || key == 77) {
						if (itemType == 0) itemType = 1;
						else itemType = 0;
						switchItem();
					}
					else if (key == 13) {
						if (player.getCash() >= 100) {
							player.sendMoney(100);
							player.ownItem[itemType] += 1;
						}
						else {
							gotoxy(41, 15);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							cout << "身上現金不足，無法購買!(道具每個100元)";
							Sleep(1000);
						}
						break;
					}
				}
				loadAll(player, bank);
				break;
			}
			case 3:
			{
				leave = true;
				break;
			}
			}
		}
		break;
	}

	}
}

void bankUI::setRate(double &dIn, double &lIn)
{
	rateD = dIn;
	rateL = lIn;
}

void bankUI::switchItem()
{
	if (itemType == 0) {
		gotoxy(45, 15);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		cout << "骰子";
		gotoxy(68, 15);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "路障";
	}
	else {
		gotoxy(45, 15);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "骰子";
		gotoxy(68, 15);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
		cout << "路障";
	}
}

void bankUI::loadStock(map<string, stock> & stock, character & player)
{
	wstring out;
	Clr();
	gotoxy(0, 0);
	stockIn.open("stock.txt");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	while (getline(stockIn, out)) {
		wcout << out << endl;
	}
	stockIn.close();

	loadStockOp();
	showStockKey();
	loadPrice(stock, player);

}

void bankUI::loadStockOp()
{
	int line = 0;
	wstring out;
	stockOption.open("stockOption.txt");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 245);
	while (getline(stockOption, out))
	{
		gotoxy(116, 7 + line);
		wcout << out << endl;
		line++;
	}
	stockOption.close();
}

void bankUI::showStockKey()
{
	int line = 0;
	wstring out;
	stockKeyin.open("stockKeyin.txt");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 245);
	while (getline(stockKeyin, out))
	{
		gotoxy(111, 21 + line);
		wcout << out << endl;
		line++;
	}
	stockKeyin.close();
}

void bankUI::loadPrice(map<string, stock>& stock, character & player)
{
	int line = 0;
	for (int i = 0; i < 5; i++) {
		if (stock[stock::allName[i]].gap >= 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		gotoxy(29, 11 + (line * 4));
		cout << stock[stock::allName[i]].value;
		gotoxy(39, 11 + (line * 4));
		cout << stock[stock::allName[i]].gap;
		gotoxy(50, 11 + (line * 4));
		cout << player.holdStock[i];
		line++;
	}
	line = 0;
	for (int i = 5; i < 10; i++) {
		if (stock[stock::allName[i]].gap >= 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		gotoxy(82, 11 + (line * 4));
		cout << stock[stock::allName[i]].value;
		gotoxy(93, 11 + (line * 4));
		cout << stock[stock::allName[i]].gap;
		gotoxy(103, 11 + (line * 4));
		cout << player.holdStock[i];
		line++;
	}
}

bool bankUI::moveStock(int key, character & player, Bank & bank, map<string, stock> & Stock, bool &check)
{
	switch (key) {
	case 72:
	{
		if (stockState > 0) {
			stockState -= 1;
		}
		else {
			stockState = 2;
		}
		switchStock();
		break;
	}
	case 80:
	{
		if (stockState < 2) {
			stockState += 1;
		}
		else {
			stockState = 2;
		}
		switchStock();
		break;
	}
	case 13:
	{
		switch (stockState) {
		case 0:
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			if (bank.getDeposit(player) > 0) {
				gotoxy(113, 22);
				cout << "您目前有" << bank.getDeposit(player) << " 元可以投資";
				gotoxy(113, 23);
				cout << "請輸入編號及張數:";
				gotoxy(123, 24);
				int num, share;
				cin >> num >> share;
				bool checkBuy = true;
				if (num >= 0 && num < 10) {
					buyStock(player, num, share, Stock, bank, checkBuy);
					if (checkBuy == false) {
						showStockKey();
						gotoxy(113, 22);
						cout << "存款不足";
					}
					else {
						bank.withdraw(player, Stock[stock::allName[num]].value * 1000 * share, checkBuy);
						showStockKey();
						gotoxy(113, 22);
						cout << "購買成功";
						loadPrice(Stock, player);
					}
					Sleep(1000);
					stockState = 0;
					showStockKey();
					switchStock();
				}
				else {
					showStockKey();
					gotoxy(113, 22);
					cout << "沒有這檔股票";
					gotoxy(113, 23);
					cout << "按ENTER以繼續";
				}

			}
			else {
				gotoxy(113, 22);
				cout << "您目前沒有存款可供投資";
				Sleep(1000);
				stockState = 0;
				switchStock();
			}

			break;
		}
		case 1:
		{
			int num, share;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			gotoxy(113, 22);
			cout << "請輸入編號:";
			gotoxy(123, 24);
			cin >> num;

			if (num >= 0 && num < 10) {
				if (player.holdStock[num] > 0) {
					showStockKey();
					gotoxy(113, 22);
					cout << "請輸入張數:";
					cin >> share;
					if (player.holdStock[num] < share) {
						showStockKey();
						gotoxy(113, 22);
						cout << "超過擁有張數";
					}
					else {
						bool checkSell = true;
						sellStock(player, num, share, Stock, bank);
						bank.deposit(player, Stock[stock::allName[num]].value * 1000 * share, checkSell);
						showStockKey();
						gotoxy(113, 22);
						cout << "交易成功";
						loadPrice(Stock, player);
					}
					Sleep(1000);
					stockState = 0;
					showStockKey();
					switchStock();
				}
				else {
					showStockKey();
					gotoxy(113, 22);
					cout << "您沒有這檔股票";
					Sleep(1000);
					stockState = 0;
					showStockKey();
					switchStock();
				}

			}
			else {
				showStockKey();
				gotoxy(113, 22);
				cout << "沒有這檔股票";
				gotoxy(113, 23);
				cout << "按ENTER以繼續";
			}
			break;
		}
		case 2:
		{
			check = false;
		}
		}
		break;
	}
	}

	return check;
}

void bankUI::switchStock()
{
	switch (stockState) {
	case 0:
	{
		loadStockOp();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
		gotoxy(125, 8);
		cout << "買入";
		break;
	}
	case 1:
	{
		loadStockOp();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
		gotoxy(125, 10);
		cout << "賣出";
		break;
	}
	case 2:
	{
		loadStockOp();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 125);
		gotoxy(125, 12);
		cout << "離開";
		break;
	}
	}
}