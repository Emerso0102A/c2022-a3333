#pragma once
#include"Chess.h"

class AI
{
public:
	void init(Chess *chess);
	void move();
	
	
	//ʵ�ֶԾ��ϸ���÷�ֵ�ļ��㣬˼���ĸ����÷����
	ChessPos consider();

private:
	Chess* chess;
	vector<vector<int>> scoreMap;

private:
	void calculateScore();
	
	
};

