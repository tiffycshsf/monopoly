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
int playRound = 0; //�^�X
int lastPlay = 0;	//�Q�v��
int turn = state; //���H��
bool ��} = true; //�~��C������ت��p 
//1.�b�C�����~�� -> ���έ�load��
//2.��}�C�� > ��load��		

// �������q
int walk = 0;  // ����
int itemUsed = 0; // �D��
int goBank = 0; // �Ȧ�(�U��)
int action = 1; //�R��or�ɯ�

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

	while (key = _getch()) //Ū��
	{
		if (stateMachine == 0)
		{
			int ctr = selecterU(3, 0); //�}�s�C��
			if (ctr == 0)
			{
				setStock(stock);
				setBank(newBank);
				��} = false;
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
			else if (ctr == 1) //�~��C��
			{
				fstream test;
				test.open("saveMap.txt");
				if (test.is_open() && ��} == true)
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
			else if (ctr == 2) //���}�C��
			{
				//saveStock(stock);
				saveMap();
				exit(1);
			}
		}
		else if (stateMachine == 1)
		{
			if (player[turn].died == false) //�p�G�A�S�� �~��
			{
				if (key == 32) //���ťջ�
				{
					if (walk == 0)
					{
						int point = player[turn].throwDice();
						gotoxy(100, 20);
						SetColor(5);
						printf("�z���F %d �I", point);
						SetColor(0);
						playerPlace(turn);
						gotoxy(100, 20);
						cout << "                 ";
						walk = 1;
						action = 0;
						Sleep(1000);
						//���L�O�H�a
						if (buildingList[player[turn].getPlace()].getBelongs() != turn && buildingList[player[turn].getPlace()].getBelongs() != -1)
						{
							action = 1;
							int pay = buildingList[player[turn].getPlace()].getPay()[buildingList[player[turn].getPlace()].getLevel()];
							int owner = buildingList[player[turn].getPlace()].getBelongs();
							gotoxy(100, 20);
							printf("����O�H�a�@�� %d", pay);
							Sleep(1300);
							gotoxy(100, 20);
							cout << "                     ";
							if (pay < player[turn].getCash())//���o�_
							{
								//����
								player[turn].sendMoney(pay);
								player[owner].getMoney(pay);
								//UI��s
								playerUI(turn);
								setBank(turn, newBank);
								setMoney(turn);
								setMoney(owner);
							}
							else
							{
								playerdied(turn);
								Inst(); //�������q
								turn = (turn + 1) % 4;
								while (player[turn].died == true || player[turn].sleep == true)
								{
									if (player[turn].sleep == true)
									{
										player[turn].sleep = false; //�𮧤@�^�X
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
							Warn("����O �U�h�𮧤@�^�X", 1000);
							player[turn].sleep = true;
							StructBelong();
							informationBlock(playRound, turn);
						}

						if (buildingList[player[turn].getPlace()].getName() == "�R�B") {

							Warn("�R�B", 1000);

							int destiny = (rand() % 3 + 1);
							int finalPlace;

							if (destiny == 0) {
								//��X�J�W�g�۬y�A��h�T��
								finalPlace = player[turn].getPlace() - 3;
								player[turn].setPlace(finalPlace);
								//���檱�a��ui���ʡA���ڤ��T�w�n�b���@��갵
							}
							else if (destiny == 1) {
								//�J��j���a���A���ʦܷQ�n���a��
								//��ܷQ�e�����a�I�N���A����O�R�B(���a�ثe����m)�A�p�G�O�R�B�N���X���~�T��
								cout << "�п�J�Q�h���a�I�N��(0~27)";
								cin >> finalPlace;
								while (finalPlace < 0 || finalPlace > 27 || finalPlace == player[turn].getPlace()) {
									if (finalPlace < 0 || finalPlace > 27) {
										cout << "�Ӧa�I���s�b";
									}
									else if (finalPlace == player[turn].getPlace()) {
										cout << "�a�I�����ܩR�B";
									}
									cin >> finalPlace;
								}

								player[turn].setPlace(finalPlace);
								//���檱�a��ui���ʡA���ڤ��T�w�n�b���@��갵
							}
							else if (destiny == 2) {
								//���W�ɪŪ��A�H���ǰe
								//��̲ܳר�F���a�I�A����O�R�B�A�p�G�O�R�B�N���s���

								finalPlace = (rand() % 27 + 1);

								while (finalPlace == player[turn].getPlace()) {
									finalPlace = (rand() % 27 + 1);
								}

								player[turn].setPlace(finalPlace);
								//���檱�a��ui���ʡA���ڤ��T�w�n�b���@��갵
							}

						}
					}
					else if (walk == 1)
					{
						Warn(" ��L�F�L�k�ϥ�", 1000);
					}
				}
				else if (key == 'z' || key == 'Z') //�D��P�_���q
				{
					if (itemUsed == 0)
					{
						int used; //�D��s��
						used = selectItem(showItem(player[turn].ownItem));
						if (used == 0 && player[turn].ownItem[0] > 0)
						{
							if (walk == 1) //��L����A��
							{
								Warn(" ��L�F�L�k�ϥ�", 1000);
							}
							else
							{

								/*if (player[turn].ownItem[0]<=0)
								{
									map<int, int>::iterator itr;
									itr = player[turn].ownItem.find(0);
									player[turn].ownItem.erase(itr);

								}*///�R���D��
								int step;
								gotoxy(100, 20);
								cout << "��J�����B��: ";
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
										printf("����O�H�a�@�� %d", pay);
										Sleep(1300);
										gotoxy(100, 20);
										cout << "                     ";
										if (pay < player[turn].getCash())//���o�_
										{
											//����
											player[turn].sendMoney(pay);
											player[owner].getMoney(pay);
											//UI��s
											playerUI(turn);
											setBank(turn, newBank);
											setMoney(turn);
											setMoney(owner);
										}
										else
										{
											playerdied(turn);
											Inst(); //�������q
											turn = (turn + 1) % 4;
											while (player[turn].died == true || player[turn].sleep == true)
											{
												if (player[turn].sleep == true)
												{
													player[turn].sleep = false; //�𮧤@�^�X
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
										Warn("����O �U�h�𮧤@�^�X", 1000);
										player[turn].sleep = true;
										StructBelong();
										informationBlock(playRound, turn);

									}
									if (buildingList[player[turn].getPlace()].getName() == "�R�B") {

										Warn("�R�B", 1000);

										int destiny = (rand() % 3 + 1);
										int finalPlace;

										if (destiny == 0) {
											//��X�J�W�g�۬y�A��h�T��
											finalPlace = player[turn].getPlace() - 3;
											player[turn].setPlace(finalPlace);
											//���檱�a��ui���ʡA���ڤ��T�w�n�b���@��갵
										}
										else if (destiny == 1) {
											//�J��j���a���A���ʦܷQ�n���a��
											//��ܷQ�e�����a�I�N���A����O�R�B(���a�ثe����m)�A�p�G�O�R�B�N���X���~�T��
											cout << "�п�J�Q�h���a�I�N��(0~27)";
											cin >> finalPlace;
											while (finalPlace < 0 || finalPlace > 27 || finalPlace == player[turn].getPlace()) {
												if (finalPlace < 0 || finalPlace > 27) {
													cout << "�Ӧa�I���s�b";
												}
												else if (finalPlace == player[turn].getPlace()) {
													cout << "�a�I�����ܩR�B";
												}
												cin >> finalPlace;
											}

											player[turn].setPlace(finalPlace);
											//���檱�a��ui���ʡA���ڤ��T�w�n�b���@��갵
										}
										else if (destiny == 2) {
											//���W�ɪŪ��A�H���ǰe
											//��̲ܳר�F���a�I�A����O�R�B�A�p�G�O�R�B�N���s���

											finalPlace = (rand() % 27 + 1);

											while (finalPlace == player[turn].getPlace()) {
												finalPlace = (rand() % 27 + 1);
											}

											player[turn].setPlace(finalPlace);
											//���檱�a��ui���ʡA���ڤ��T�w�n�b���@��갵
										}

									}
								}

							}
						}
						else if (used == 1 && player[turn].ownItem[1] > 0)
						{

							int step;
							gotoxy(100, 20);
							cout << "��ܱ���m�D���m: ";
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
								Warn("�o�Ӧ�m�w�g�Q��m�L", 1000);
							}
						}
					}
					else if (itemUsed == 1)
					{
						Warn("�w�g�ϥιL�D��F", 1000);
					}


				}
				else if (key == 27) //exc �����
				{
					stateMachine = 2;
					loadUI("option");
				}
				else if (key == 'x' || key == 'X') //�a���P�_���q
				{
					if (action == 0 && walk == 0) //�٨S��
					{
						Warn("�����~��ʧ@", 1000);
					}
					else if (action == 0 && walk == 1)
					{
						if (buildingList[player[turn].getPlace()].getType() == 1)
						{
							if (buildingList[player[turn].getPlace()].getBelongs() == -1) //�o���a�S�H
							{
								if (buildingList[player[turn].getPlace()].getPay()[0] <= player[turn].getCash())
								{
									loadUI("buy");
									if (selecterLeft() == 0) //�n�R
									{
										//�����a����
										player[turn].sendMoney(buildingList[player[turn].getPlace()].getPay()[0]);
										//���ɩЫε���
										buildingList[player[turn].getPlace()].setLevel(buildingList[player[turn].getPlace()].getLevel() + 1);
										//���ܩҦ��v
										buildingList[player[turn].getPlace()].setBelongs(turn);
										//���ܪ��a�ۨ��T��
										player[turn].resetStruct();
										//UI��s
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
									Warn("�������ٷQ�R�� �a�G", 1000);
								}
							}
							else if (buildingList[player[turn].getPlace()].getBelongs() == turn) //�o���a�O�ۤv��
							{
								if (buildingList[player[turn].getPlace()].getLevel() <= 3) //�Ыε��Ť���
								{
									loadUI("upgrade");
									if (selecterLeft() == 0) //�n�ɯ�
									{
										//�ɱo�_
										if (buildingList[player[turn].getPlace()].getPay()[0] <= player[turn].getCash())
										{
											player[turn].sendMoney(buildingList[player[turn].getPlace()].getPay()[0]);
											//���ɩЫε���
											buildingList[player[turn].getPlace()].setLevel(buildingList[player[turn].getPlace()].getLevel() + 1);
											//���ܪ��a�ۨ��T��
											player[turn].resetStruct();
											//UI��s
											playerUI(turn);
											setBank(turn, newBank);
											setMoney(turn);
											StructBelong();
											action = 1;

										}
										else
										{
											Warn("�������ɯ�", 400);
										}
									}
									loadUI("clean");
								}
							}
						}
					}
				}
				else if (key == 'b') //�i�J�Ȧ�
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
					//�^��a��
				}
				else if (key == 'c') //�����^�X
				{
					if (walk == 0)
					{
						Warn("����L��l�~�൲��", 1000);
					}
					else if (walk == 1)
					{
						Inst(); //�������q
						turn = (turn + 1) % 4;
						while (player[turn].died == true || player[turn].sleep == true)
						{
							if (player[turn].sleep == true)
							{
								player[turn].sleep = false; //�𮧤@�^�X
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
				loadMap("basemap.txt"); //��load��
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
			else if (ctr == 2) //�D���
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


		if (playRound >= 20 || victory() || key == 'p') //�ӧQ�e��
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
						//�^�D�e��
					}
					else {
						exit(0);
					}
					break;
				}
			}


			//Warn("Ĺ�F", 2000);
			//stateMachine = 5;
		}

	}


}

void Inst()
{
	walk = 0;  // ����
	itemUsed = 0; // �D��
	goBank = 0; // �Ȧ�(�U��)
	action = 0; //�R��or�ɯ�
}

void Warn(string sentence, int time)
{
	gotoxy(100, 20);
	cout << sentence;
	Sleep(time);
	gotoxy(100, 20);
	cout << "                           ";
}