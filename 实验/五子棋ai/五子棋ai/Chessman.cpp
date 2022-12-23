#include "Chess.h"
#include "Chessman.h"



void Chessman::init(Chess* chess)
{
	this->chess = chess;
}

void Chessman::move()
{
	//�����Ϣ�洢���������λ��
	ChessPos pos;

	//�����Ϣ�洢λ��
	MOUSEMSG msg;
	
	
	while (1)
	{
		//��ȡ�������Ϣ
		msg=GetMouseMsg();
		
		//ͨ��chess�������ж������Ƿ���Ч
	
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos))
		{
			
			printf("%d %d", pos.x, pos.y);
			break;
		}		
	}

	

	//����
	chess->chessDown(&pos, CHESS_BLACK);
}
