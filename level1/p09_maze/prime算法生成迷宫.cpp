#include <iostream>
using namespace std;
#include <graphics.h>
#include <Windows.h>
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

#define WIDTH 1080//�ֱ���
#define HEIGHT 720
#define BLOCK_XY 10//С����߳�
const int BLOCK_WIDTH = WIDTH / (BLOCK_XY);//С����x������
const int BLOCK_HEIGHT = HEIGHT / (BLOCK_XY);//С����y������

#define kongqi COLORREF RGB(50,50,50)//������ɫ
#define qiangbi COLORREF RGB(255,255,255)//ǽ����ɫ
#define daixuan COLORREF RGB(0,255,0)//��ѡ��ɫ
#define xuanzhong COLORREF RGB(255,0,0)//ѡ����ɫ

#define ROAD 0//·��������
#define WALL 1//ǽ��
#define WAIT 2//��ѡ·��

struct block {
public:
	int x;
	int y;
	block(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

int map[BLOCK_WIDTH][BLOCK_HEIGHT];//0���������1����ǽ�ڣ�2�����ѡ·�㣬3����ѡ��·�㣨���ǲ�û���õ���
vector<block*> openlist;//��ѡ�б�
vector<block*> list;

/*��������*/
void clearscreen(COLORREF RGB);//��յ�ͼΪRGB��ɫ(��������)
void gamedrawpixal(int x, int y, COLORREF RGB);//��x��yλ�û���ɫΪRGB�ķ���
void init();//��ʼ��
void join(int x, int y);//��x,y������ǽ�ڵ�·������ѡ�б�
void display();//ˢ����Ļ
void prim_main();//prim��ѭ��
void through(int x, int y);//��x,y��������һ������Ѿ����·��·���ͨ
/*********/

void init() {
	openlist.clear();
	/*��ͼ��ʼ��Ϊǽ*/
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			map[x][y] = WALL;
		}
	}
	/*���ѡһ��·�㣬�������·*/
	map[0][0] = ROAD;
	/*��·�����ܲ���·��·������ѡ�б�*/
	join(0, 0);
	prim_main();
}
void prim_main() {
	while (openlist.size() > 0) {
		/*�Ӵ�ѡ·�����ѡһ��·��A*/
		int AIndexea = rand() % openlist.size();
		block* A = openlist[AIndexea];
		/*��A��������һ������Ѿ����·��·���ͨ*/
		through(A->x, A->y);
		/*��A���·*/
		map[A->x][A->y] = ROAD;
		/*��A���ܲ���·��·������ѡ�б�*///(ע�⣬��Ҫ�ظ����·�㣡)
		join(A->x, A->y);
		/*�Ӵ�ѡ·�����Ƴ�A*/
		openlist.erase(openlist.begin() + AIndexea);

		gamedrawpixal(A->x, A->y, xuanzhong);
		FlushBatchDraw();
		display();
	}
	openlist.clear();
}
void through(int x, int y) {
	list.clear();
	//��
	if (y - 2 >= 0 && map[x][y - 2] == ROAD) {
		block* a = new block(x, y - 1);
		list.push_back(a);
	}
	//��
	if (y + 2 <= BLOCK_HEIGHT - 1 && map[x][y + 2] == ROAD) {
		block* b = new block(x, y + 1);
		list.push_back(b);
	}
	//��
	if (x - 2 >= 0 && map[x - 2][y] == ROAD) {
		block* c = new block(x - 1, y);
		list.push_back(c);
	}
	//��
	if (x + 2 <= BLOCK_WIDTH - 1 && map[x + 2][y] == ROAD) {
		block* d = new block(x + 1, y);
		list.push_back(d);
	}
	int BIndexea = rand() % list.size();
	block* B = list[BIndexea];
	/*��x��y��B��ͨ*/
	map[B->x][B->y] = ROAD;
}
void join(int x, int y) {
	//��
	if (y - 2 >= 0 && map[x][y - 2] == WALL) {
		block* a = new block(x, y - 2);
		openlist.push_back(a);
		map[x][y - 2] = WAIT;
	}
	//��
	if (y + 2 <= BLOCK_HEIGHT - 1 && map[x][y + 2] == WALL) {
		block* b = new block(x, y + 2);
		openlist.push_back(b);
		map[x][y + 2] = WAIT;
	}
	//��
	if (x - 2 >= 0 && map[x - 2][y] == WALL) {
		block* c = new block(x - 2, y);
		openlist.push_back(c);
		map[x - 2][y] = WAIT;
	}
	//��
	if (x + 2 <= BLOCK_WIDTH - 1 && map[x + 2][y] == WALL) {
		block* d = new block(x + 2, y);
		openlist.push_back(d);
		map[x + 2][y] = WAIT;
	}
}
void display() {
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			if (map[x][y] == WALL) {
				gamedrawpixal(x, y, qiangbi);
			}
			else if (map[x][y] == ROAD) {
				gamedrawpixal(x, y, kongqi);
			}
			else if (map[x][y] == WAIT) {
				gamedrawpixal(x, y, daixuan);
			}
		}
	}
	FlushBatchDraw();
}
void clearscreen(COLORREF RGB) {
	for (int y = 0; y < BLOCK_HEIGHT; y++) {
		for (int x = 0; x < BLOCK_WIDTH; x++) {
			gamedrawpixal(x, y, RGB);
		}
	}
}
void gamedrawpixal(int x, int y, COLORREF RGB) {
	setfillcolor(RGB); setlinecolor(COLORREF RGB(0, 0, 0));
	fillrectangle(x * BLOCK_XY, y * BLOCK_XY, BLOCK_XY + x * BLOCK_XY, BLOCK_XY + y * BLOCK_XY);
}
int main() {
	srand((unsigned)time(NULL));//���������
	initgraph(WIDTH, HEIGHT);//������ͼ����
	BeginBatchDraw();//��ʼ������ͼ
	cleardevice();//�����ʾ

	init();

	display();
	FlushBatchDraw();//�������������Ļ

	while (1);
}
