#include "playerUI.h"
#include "mapUI.h"
#include "loadMap.h"
#include "Estates.h"
#include "Bank.h"
#include <conio.h>
#include "Character.h"
#include "stock.h"
#include "stateMachine.h"
#include"bankUI.h"
#include"win.h"

void Inst();
void Warn(string sentence, int time);

char key;
int playRound = 0; //回合
int lastPlay = 0;	//利率用
int turn = state; //換人玩
bool 剛開 = true; //繼續遊戲有兩種狀況 
//1.在遊戲內繼續 -> 不用重load圖
//2.剛開遊戲 > 重load圖		

// 內部階段
int walk = 0;  // 移動
int itemUsed = 0; // 道具
int goBank = 0; // 銀行(貸款)
int action = 1; //買房or升級

Bank newBank(4);
vector<bankUI> inBank(4);

int main()
{
	srand(time(NULL));
	/*map<int, Estates> info;
	getInformation(info);
	cout << info[1].buy;*/
	//std::cout << "a";gotoxy(posX + 2, posY + 1);
	//system("pause");
	map<string, stock> stock;

	for (int i = 0; i < 4; i++) {
		string buf = to_string(i);
		inBank[i] = bankUI(player[i]);
	}

	ConsoleFullScreen();
	loadMap("basemap.txt");
	loadUI("menu");

	while (key = _getch()) //讀取
	{
		if (stateMachine == 0)
		{
			int ctr = selecterU(3, 0); //開新遊戲
			if (ctr == 0)
			{
				setStock(stock);
				setBank(newBank);
				剛開 = false;
				stateMachine = 1;
				Clr();
				drawMap();
				fillData();
				for (int i = 0; i < 4; i++)
				{
					playerUI(i);
					setBank(i, newBank);
				}
				StructBelong();
				informationBlock(0, 0);
			}
			else if (ctr == 1) //繼續遊戲
			{
				fstream test;
				test.open("saveMap.txt");
				if (test.is_open() && 剛開 == true)
				{
					test.close();
					loadMap("saveMap.txt");
					readStock(stock);
					readBank(newBank);
					readItem();
				}
				test.close();
				stateMachine = 1;
				Clr();
				drawMap();
				fillData();
				for (int i = 0; i < 4; i++)
				{
					playerUI(i);
					setBank(i, newBank);
				}
				StructBelong(); 
				informationBlock(playRound, turn);
			}
			else if (ctr == 2) //離開遊戲
			{
				//saveStock(stock);
				saveMap();
				exit(1);
			}
		}
		else if (stateMachine == 1)
		{
			if (player[turn].died == false) //如果你沒死 繼續玩
			{
				if (key == 32) //按空白骰
				{
					if (walk == 0)
					{
						int point = player[turn].throwDice();
						gotoxy(100, 20);
						SetColor(5);
						printf("您骰到了 %d 點", point);
						SetColor(0);
						playerPlace(turn);
						gotoxy(100, 20);
						cout << "                 ";
						walk = 1;
						action = 0;
						Sleep(1000);
						//路過別人家
						if (buildingList[player[turn].getPlace()].getBelongs() != turn && buildingList[player[turn].getPlace()].getBelongs() != -1)
						{
							action = 1;
							int pay = buildingList[player[turn].getPlace()].getPay()[buildingList[player[turn].getPlace()].getLevel()];
							int owner = buildingList[player[turn].getPlace()].getBelongs();
							gotoxy(100, 20);
							printf("走到別人家罰款 %d", pay);
							Sleep(1300);
							gotoxy(100, 20);
							cout << "                     ";
							if (pay < player[turn].getCash())//給得起
							{
								//給錢
								player[turn].sendMoney(pay);
								player[owner].getMoney(pay);
								//UI更新
								playerUI(turn);
								setBank(turn, newBank);
								setMoney(turn);
								setMoney(owner);
							}
							else
							{
								playerdied(turn);
								Inst(); //內部階段
								turn = (turn + 1) % 4;
								while (player[turn].died == true || player[turn].sleep == true)
								{
									if (player[turn].sleep == true)
									{
										player[turn].sleep = false; //休息一回合
									}
									turn = (turn + 1) % 4;
								}

								if (turn == 0) {
									for (size_t i = 0; i < 10; i++)
									{
										randProbability(stock, stock::allName[i]);
										updatePrice(stock, stock::allName[i]);
									}
									playRound += 1;
									for (int id = 0; id <= 3; id++) {
										newBank.depositRate(player[id], newBank.getDepositRate());
										newBank.loanRate(player[id], newBank.getLoanRate());
									}
									for (int i = 0; i < 4; i++)
									{
										setBank(i, newBank);
									}
								}
								informationBlock(playRound, turn);
							}
						}
						if (buildingList[player[turn].getPlace()].block == true)
						{
							Warn("撞牆摟 下去休息一回合", 1000);
							player[turn].sleep = true;
							StructBelong();
							informationBlock(playRound, turn);
						}

						if (buildingList[player[turn].getPlace()].getName() == "命運") {

							Warn("命運", 1000);

							int destiny = (rand() % 3 + 1);
							int finalPlace;

							if (destiny == 0) {
								//輸出遇上土石流，後退三格
								finalPlace = player[turn].getPlace() - 3;
								player[turn].setPlace(finalPlace);
								//執行玩家的ui移動，但我不確定要在哪一行實做
							}
							else if (destiny == 1) {
								//遇到大神帶路，移動至想要的地區
								//顯示想前往的地點代號，不能是命運(玩家目前的位置)，如果是命運就跳出錯誤訊息
								cout << "請輸入想去的地點代號(0~27)";
								cin >> finalPlace;
								while (finalPlace < 0 || finalPlace > 27 || finalPlace == player[turn].getPlace()) {
									if (finalPlace < 0 || finalPlace > 27) {
										cout << "該地點不存在";
									}
									else if (finalPlace == player[turn].getPlace()) {
										cout << "地點不能選擇命運";
									}
									cin >> finalPlace;
								}

								player[turn].setPlace(finalPlace);
								//執行玩家的ui移動，但我不確定要在哪一行實做
							}
							else if (destiny == 2) {
								//撞上時空門，隨機傳送
								//顯示最終到達的地點，不能是命運，如果是命運就重新選取

								finalPlace = (rand() % 27 + 1);

								while (finalPlace == player[turn].getPlace()) {
									finalPlace = (rand() % 27 + 1);
								}

								player[turn].setPlace(finalPlace);
								//執行玩家的ui移動，但我不確定要在哪一行實做
							}

						}
					}
					else if (walk == 1)
					{
						Warn(" 骰過了無法使用", 1000);
					}
				}
				else if (key == 'z' || key == 'Z') //道具判斷階段
				{
					if (itemUsed == 0)
					{
						int used; //道具編號
						used = selectItem(showItem(player[turn].ownItem));
						if (used == 0 && player[turn].ownItem[0] > 0)
						{
							if (walk == 1) //骰過不能再骰
							{
								Warn(" 骰過了無法使用", 1000);
							}
							else
							{

								/*if (player[turn].ownItem[0]<=0)
								{
									map<int, int>::iterator itr;
									itr = player[turn].ownItem.find(0);
									player[turn].ownItem.erase(itr);

								}*///刪除道具
								int step;
								gotoxy(100, 20);
								cout << "輸入欲走步數: ";
								if (cin >> step)
								{
									gotoxy(100, 20);
									cout << "                               ";
								}
								if (player[turn].throwDice(step) == 0)
								{
									player[turn].ownItem[0] -= 1;
									playerPlace(turn);
									itemUsed = 1;
									walk = 1;
									action = 0;

									if (buildingList[player[turn].getPlace()].getBelongs() != turn && buildingList[player[turn].getPlace()].getBelongs() != -1)
									{
										action = 1;
										int pay = buildingList[player[turn].getPlace()].getPay()[buildingList[player[turn].getPlace()].getLevel()];
										int owner = buildingList[player[turn].getPlace()].getBelongs();
										gotoxy(100, 20);
										printf("走到別人家罰款 %d", pay);
										Sleep(1300);
										gotoxy(100, 20);
										cout << "                     ";
										if (pay < player[turn].getCash())//給得起
										{
											//給錢
											player[turn].sendMoney(pay);
											player[owner].getMoney(pay);
											//UI更新
											playerUI(turn);
											setBank(turn, newBank);
											setMoney(turn);
											setMoney(owner);
										}
										else
										{
											playerdied(turn);
											Inst(); //內部階段
											turn = (turn + 1) % 4;
											while (player[turn].died == true || player[turn].sleep == true)
											{
												if (player[turn].sleep == true)
												{
													player[turn].sleep = false; //休息一回合
												}
												turn = (turn + 1) % 4;
											}

											if (turn == 0) {
												for (size_t i = 0; i < 10; i++)
												{
													randProbability(stock, stock::allName[i]);
													updatePrice(stock, stock::allName[i]);
												}
												playRound += 1;
												for (int id = 0; id <= 3; id++) {
													newBank.depositRate(player[id], newBank.getDepositRate());
													newBank.loanRate(player[id], newBank.getLoanRate());
												}
												for (int i = 0; i < 4; i++)
												{
													setBank(i, newBank);
												}
											}
											informationBlock(playRound, turn);

										}
									}
									if (buildingList[player[turn].getPlace()].block == true)
									{
										Warn("撞牆摟 下去休息一回合", 1000);
										player[turn].sleep = true;
										StructBelong();
										informationBlock(playRound, turn);

									}
									if (buildingList[player[turn].getPlace()].getName() == "命運") {

										Warn("命運", 1000);

										int destiny = (rand() % 3 + 1);
										int finalPlace;

										if (destiny == 0) {
											//輸出遇上土石流，後退三格
											finalPlace = player[turn].getPlace() - 3;
											player[turn].setPlace(finalPlace);
											//執行玩家的ui移動，但我不確定要在哪一行實做
										}
										else if (destiny == 1) {
											//遇到大神帶路，移動至想要的地區
											//顯示想前往的地點代號，不能是命運(玩家目前的位置)，如果是命運就跳出錯誤訊息
											cout << "請輸入想去的地點代號(0~27)";
											cin >> finalPlace;
											while (finalPlace < 0 || finalPlace > 27 || finalPlace == player[turn].getPlace()) {
												if (finalPlace < 0 || finalPlace > 27) {
													cout << "該地點不存在";
												}
												else if (finalPlace == player[turn].getPlace()) {
													cout << "地點不能選擇命運";
												}
												cin >> finalPlace;
											}

											player[turn].setPlace(finalPlace);
											//執行玩家的ui移動，但我不確定要在哪一行實做
										}
										else if (destiny == 2) {
											//撞上時空門，隨機傳送
											//顯示最終到達的地點，不能是命運，如果是命運就重新選取

											finalPlace = (rand() % 27 + 1);

											while (finalPlace == player[turn].getPlace()) {
												finalPlace = (rand() % 27 + 1);
											}

											player[turn].setPlace(finalPlace);
											//執行玩家的ui移動，但我不確定要在哪一行實做
										}

									}
								}

							}
						}
						else if (used == 1 && player[turn].ownItem[1] > 0)
						{

							int step;
							gotoxy(100, 20);
							cout << "選擇欲放置道具位置: ";
							step = blockplace();
							if (buildingList[step].block == false)
							{
								player[turn].ownItem[1] -= 1;
								itemUsed = 1;
								buildingList[step].block = true;
								StructBelong();
							}
							else
							{
								Warn("這個位置已經被放置過", 1000);
							}
						}
					}
					else if (itemUsed == 1)
					{
						Warn("已經使用過道具了", 1000);
					}


				}
				else if (key == 27) //exc 跳選單
				{
					stateMachine = 2;
					loadUI("option");
				}
				else if (key == 'x' || key == 'X') //地產判斷階段
				{
					if (action == 0 && walk == 0) //還沒走
					{
						Warn("先走才能動作", 1000);
					}
					else if (action == 0 && walk == 1)
					{
						if (buildingList[player[turn].getPlace()].getType() == 1)
						{
							if (buildingList[player[turn].getPlace()].getBelongs() == -1) //這塊地沒人
							{
								if (buildingList[player[turn].getPlace()].getPay()[0] <= player[turn].getCash())
								{
									loadUI("buy");
									if (selecterLeft() == 0) //要買
									{
										//扣玩家的錢
										player[turn].sendMoney(buildingList[player[turn].getPlace()].getPay()[0]);
										//提升房屋等級
										buildingList[player[turn].getPlace()].setLevel(buildingList[player[turn].getPlace()].getLevel() + 1);
										//改變所有權
										buildingList[player[turn].getPlace()].setBelongs(turn);
										//改變玩家自身訊息
										player[turn].resetStruct();
										//UI更新
										playerUI(turn);
										setBank(turn, newBank);
										setMoney(turn);
										StructBelong();
										action = 1;
									}

									loadUI("clean");
								}
								else
								{
									Warn("錢不夠還想買阿 窮逼", 1000);
								}
							}
							else if (buildingList[player[turn].getPlace()].getBelongs() == turn) //這塊地是自己的
							{
								if (buildingList[player[turn].getPlace()].getLevel() <= 3) //房屋等級不夠
								{
									loadUI("upgrade");
									if (selecterLeft() == 0) //要升級
									{
										//升得起
										if (buildingList[player[turn].getPlace()].getPay()[0] <= player[turn].getCash())
										{
											player[turn].sendMoney(buildingList[player[turn].getPlace()].getPay()[0]);
											//提升房屋等級
											buildingList[player[turn].getPlace()].setLevel(buildingList[player[turn].getPlace()].getLevel() + 1);
											//改變玩家自身訊息
											player[turn].resetStruct();
											//UI更新
											playerUI(turn);
											setBank(turn, newBank);
											setMoney(turn);
											StructBelong();
											action = 1;

										}
										else
										{
											Warn("錢不夠升級", 400);
										}
									}
									loadUI("clean");
								}
							}
						}
					}
				}
				else if (key == 'b') //進入銀行
				{
					if (lastPlay == 0) {
						double dIn = newBank.getDepositRate();
						double lIn = newBank.getLoanRate();
					}
					if (playRound != lastPlay || lastPlay == 0) {
						double dIn = newBank.getDepositRate();
						double lIn = newBank.getLoanRate();
						for (int i = 0; i < 4; i++) {
							inBank[i].setRate(dIn, lIn);
						}
						lastPlay = playRound;
					}

					bool leave = false;
					inBank[turn].loadAll(player[turn], newBank);

					while (key = _getch()) {

						inBank[turn].move(key, player[turn], newBank, stock, leave);
						if (leave == true) {
							SetColor(-1);
							Clr();
							drawMap();
							fillData();
							for (int i = 0; i < 4; i++)
							{
								playerUI(i);
								setBank(i, newBank);
							}
							StructBelong();
							informationBlock(playRound, turn);
							break;
						}
					}
					//回到地圖
				}
				else if (key == 'c') //結束回合
				{
					if (walk == 0)
					{
						Warn("先骰過骰子才能結束", 1000);
					}
					else if (walk == 1)
					{
						Inst(); //內部階段
						turn = (turn + 1) % 4;
						while (player[turn].died == true || player[turn].sleep == true)
						{
							if (player[turn].sleep == true)
							{
								player[turn].sleep = false; //休息一回合
							}
							turn = (turn + 1) % 4;
						}

						if (turn == 0) {
							for (size_t i = 0; i < 10; i++)
							{
								randProbability(stock, stock::allName[i]);
								updatePrice(stock, stock::allName[i]);
							}
							playRound += 1;
							for (int id = 0; id <= 3; id++) {
								newBank.depositRate(player[id], newBank.getDepositRate());
								newBank.loanRate(player[id], newBank.getLoanRate());
							}
							for (int i = 0; i < 4; i++)
							{
								setBank(i, newBank);
							}
						}
						informationBlock(playRound, turn);
					}
				}
			}
		}
		else if (stateMachine == 2)
		{
			int ctr = selecterU(4, 1);
			if (ctr == 0)
			{
				stateMachine = 1;
				Clr();
				drawMap();
				fillData();
				for (int i = 0; i < 4; i++)
				{
					playerUI(i);
					setBank(i, newBank);
				}
				StructBelong();
				informationBlock(playRound, turn);
			}
			else if (ctr == 1)
			{
				Inst();
				stateMachine = 1;
				Clr();
				drawMap();
				loadMap("basemap.txt"); //重load圖
				fillData();
				for (int i = 0; i < 4; i++)
				{
					player[i].resetStruct();
					player[i].died = false;
					setStruct(i);
					setMoney(i);
					playerUI(i);
					setBank(i, newBank);
				}
				StructBelong();
				informationBlock(playRound = 0, turn = 0);
			}
			else if (ctr == 2) //主選單
			{
				stateMachine = 0;
				Clr();
				loadUI("menu");
			}
			else if (ctr == 3)
			{
				saveItem();
				saveMap();
				saveStock(stock);
				saveBank(newBank);
				exit(1);

				//hsuSave
			}


		}


		if (playRound >= 20 || victory() || key == 'p') //勝利畫面
		{
			stateMachine = 5;
			Clr();
			win winUI(to_string(turn));
			winUI.type = 0;
			winUI.loadWin();
			while (key = _getch()) {
				if (key == 72 || key == 80) {
					Clr();
					winUI.loadWin();
				}
				else if (key == 13) {
					if (winUI.type == 1) {
						stateMachine = 0;
						Clr();
						//loadMap("basemap.txt");
						loadUI("menu");
						//回主畫面
					}
					else {
						exit(0);
					}
					break;
				}
			}


			//Warn("贏了", 2000);
			//stateMachine = 5;
		}

	}


}

void Inst()
{
	walk = 0;  // 移動
	itemUsed = 0; // 道具
	goBank = 0; // 銀行(貸款)
	action = 0; //買房or升級
}

void Warn(string sentence, int time)
{
	gotoxy(100, 20);
	cout << sentence;
	Sleep(time);
	gotoxy(100, 20);
	cout << "                           ";
}