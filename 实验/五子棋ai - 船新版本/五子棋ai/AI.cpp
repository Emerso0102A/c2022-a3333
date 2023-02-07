#include "AI.h"
#include"chess.h"
#include<windows.h>

void AI::init(Chess *chess)
{
	this->chess = chess;
	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++)
	{
		vector<int>row;
		for (int j = 0; j < size; j++)
		{
			row.push_back(0);
			
		}
		scoreMap.push_back(row);
	
	}
}

void AI::move()
{
	ChessPos aipos = consider();
	Sleep(400);
	chess->chessDown(&aipos, CHESS_WHITE);
}

ChessPos AI::consider()
{
	
	calculateScore();
	int size;
	size = chess->getGradeSize();
	int maxscore = 0;
	
	vector<ChessPos>maxscorepos;
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (maxscore < scoreMap[row][col])
			{
				maxscore = scoreMap[row][col];
				maxscorepos.clear();
				maxscorepos.push_back(ChessPos(row, col));

			}
			else if (maxscore == scoreMap[row][col])
			{
				maxscorepos.push_back(ChessPos(row, col));

			}
			else
			{
				continue;
			}
		}
	}
	//��ͬ���÷ֵĸ������ѡһ������Ϊ��ߵ÷ֵ�
	int random = rand() % (maxscorepos.size());
	return maxscorepos[random];
	
}

void AI::calculateScore()
{
	int personNum;// (�����м���������һ��
	int aiNum;
	int emptyNum = 0;//�÷����м����հ�
	for (int i = 0; i < scoreMap.size(); i++)//�����������
	{
		for (int j = 0; j < scoreMap[i].size(); j++)
		{
			scoreMap[i][j] = 0;
		}
	}
	scoreMap[7][7] = 1;
	int size = chess->getGradeSize();//��ȡ���̴�С
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			//����ÿ�����ļ�ֵ
			if (chess->getChessData(row, col) == 0)
			{
				for (int y = -1; y <= 0; y++)
				{
					for (int x = -1; x <= 1; x++)
					{
						//����
						personNum = 0;
						aiNum = 0;
						emptyNum = 0;

						if ((!(y == 0 && x == 0))
							&& (!(y == 0 && x == 1)))
						{
							//������壨���֣��ڸ�λ������
							for (int i = 1; i <= 4; i++)
							{
								int curRow = row + i * x;
								int curCol = col + i * y;
								if (curRow >= 0 && 
									curRow < size &&
									curCol >= 0 && 
									curCol < size && 
									chess->getChessData(curRow, curCol) == 1)
								{
									personNum++;
								}
								else if (curRow >= 0 && 
									curRow < size && 
									curCol >= 0 && 
									curCol < size && 
									chess->getChessData(curRow, curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else
								{
									break;
								}

							}

							//����ļ���
							for (int i = 1; i <= 4; i++)
							{
								int curRow = row - i * x;
								int curCol = col - i * y;
								if (curRow >= 0 &&
									curRow < size && 
									curCol >= 0 && 
									curCol < size &&
									chess->getChessData(curRow, curCol) == 1)
								{
									personNum++;
								}
								else if (curRow >= 0 && 
									curRow < size && curCol >= 0 &&
									curCol < size && 
									chess->getChessData(curRow, curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else
								{
									break;
								}

							}

							//����������ӵ÷�
							if (personNum == 1)//����
							{
								scoreMap[row][col] += 10;

							}
							else if (personNum == 2)//����
							{
								if (emptyNum == 0)
								{
									scoreMap[row][col] += 0;//ûɶ��
								}
								else if (emptyNum == 1)
								{
									scoreMap[row][col] += 30;//������
								}
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 40;//����
								}
							}
							else if (personNum == 3)//����
							{
								if (emptyNum == 0)
								{
									scoreMap[row][col] += 0;
								}
								else if (emptyNum == 1)
								{
									scoreMap[row][col] += 60;//����
								}
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 200;//����
								}
							}
							else if (personNum >= 4)//����
							{
								scoreMap[row][col] += 20000;
							}

							//����������ӣ�����÷�
							
							emptyNum = 0;//��տհ׸���

							for (int i = 1; i <= 4; i++)
							{
								int curRow = row + i * x;
								int curCol = col + i * y;
								if (curRow >= 0 && 
									curRow < size &&
									curCol >= 0 && curCol < size &&
									chess->getChessData(curRow, curCol) == -1)
								{
									aiNum++;
								}
								else if (curRow >= 0 &&
									curRow < size && 
									curCol >= 0 && curCol < size && 
									chess->getChessData(curRow, curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else
								{
									break;
								}

							}

							//����ļ���
							for (int i = 1; i <= 4; i++)
							{
								int curRow = row - i * x;
								int curCol= col - i * y;
								if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == -1)
								{
									aiNum++;
								}
								else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size && chess->getChessData(curRow, curCol) == 0)
								{
									emptyNum++;
									break;
								}
								else
								{
									break;
								}

							}

							//�������÷�
							if (aiNum == 0)
								scoreMap[row][col] += 5;
							else if (aiNum == 1)//����
							{
								scoreMap[row][col] += 10;

							}
							else if (aiNum == 2)
							{
								if (emptyNum == 0)//����
								{
									scoreMap[row][col] += 0;
								}
								else if (emptyNum == 1)//����
								{
									scoreMap[row][col] += 25;
								}
								else if (emptyNum == 2)//˫ͷ����
								{
									scoreMap[row][col] += 50;
								}
							}
							else if (aiNum == 3)
							{
								if (emptyNum == 0)
								{
									scoreMap[row][col] += 0;
								}
								else if (emptyNum == 1)
								{
									scoreMap[row][col] += 55;
								}
								else if (emptyNum == 2)
								{
									scoreMap[row][col] += 1000;
								}
							}
							else if (aiNum >= 4)
							{
								scoreMap[row][col] += 30000;
							}
						}
					}
				}
			}
		}
	}
}

