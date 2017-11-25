////////////////////////////////////////////
// �������ƣ�̰����
// ���뻷����Visual Studio 2015  ����easyͼ�ο�
// �����д��dawu
//
// �����£�2017��10��21��11:12:41
//

#pragma warning(disable:4996)
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>			// ��ͼ��ͷ�ļ�����ͼ�����Ҫ
#define WIDTH 640				//��ͼ���
#define HEIGHT 480				//��ͼ�߶�
#define SNAKER  12				//�߿�뾶
#define FOODR 15				//ʳ��뾶
#define SNAKELEN  1024			//�ߵ���󳤶�

//λ�ýṹ��
struct Pos
{
	int x;
	int y;
};

//�ߵĽṹ��
struct Snake
{
	int size;
	Pos pos[SNAKELEN];
};

//����ö��
enum Direction { UP, RIGHT, DOWN, LEFT };

void init();//��ʼ���ߵ�λ�ú�ʵ���λ��
void updateFoodPos();//����ʳ��λ��
void displaySnake();//����
void displayFood();//��ʳ��
void updateSnake();//�����ߵ�λ�úͳ���
void run(int speed);//����
void keyOperator();//�жϼ�λ���ı䷽��
bool isImpact();//�ж��Ƿ���ײ
bool isEat();//�ж��Ƿ�Ե�ʳ��


			 //�ⲿ�����Եľ�̬������ȫ�ֱ�����
struct Snake snake;//�߶���
Pos food;//ʳ�����
Direction dir;//��ǰ���ķ���


int main()
{
	//��ʼ�����������
	srand((unsigned)time(NULL));
	//��ʼ������
	initgraph(WIDTH, HEIGHT);
	char c;
	//��ʾ����
	outtextxy(WIDTH / 2, HEIGHT / 2, _T("��Y��ʼ��Ϸ,�������˳�..."));
	c = _getch();
	//�Ѷȼ���ѡ��
	int speed, in;
	outtextxy(WIDTH / 2, HEIGHT / 2, _T("��ѡ��1-8���Ѷ�"));
	errors:
	scanf("%d", &in);
	switch (in)
	{
	case 1:
		speed = 300;
		break;
	case 2:
		speed = 200;
		break;
	case 3:
		speed = 100;
		break;
	case 4:
		speed = 70;
		break;
	case 5:
		speed = 50;
		break;
	case 6:
		speed = 25;
		break;
	case 7:
		speed = 20;
		break;
	case 8:
		speed = 10;
		break;
	default:
		outtextxy(WIDTH / 2, HEIGHT / 2, _T("������������������"));
		goto errors;
		break;
	}
	while (c == 'y' || c == 'Y')
	{
		//����
		run(speed);
		outtextxy(WIDTH / 2, HEIGHT / 2, _T("ʧ�ܣ�������Y��ʼ��Ϸ,�������˳�..."));
		_getch();
	}
	//�رմ���
	closegraph();
	return 0;
}


void init()
{
	updateFoodPos();
	snake.size = 1;
	snake.pos[0].x = rand() % (WIDTH - SNAKER * 2) + SNAKER;		//��ʼ����ͷλ��
	snake.pos[0].y = rand() % (HEIGHT - SNAKER * 2) + SNAKER;		//��Χ0 -- HEIGHT-SNAKER
}

//1
void updateFoodPos()
{
	food.x = rand() % (WIDTH - FOODR * 2) + FOODR;		//��ʼ��ʳ��λ��
	food.y = rand() % (HEIGHT - FOODR * 2) + FOODR;		//��Χ0 -- HEIGHT-FOODR
}

//������
void displaySnake()
{
	int i;
	setfillcolor(RGB(255, 0, 0));		//������ɫ
	fillcircle(snake.pos[0].x, snake.pos[0].y, SNAKER);	//����ͷ
	setfillcolor(RGB(0, 255, 0));
	for (i = 1; i < snake.size; ++i){
		fillcircle(snake.pos[i].x, snake.pos[i].y, SNAKER);	
	}
}

//��ʳ��
void displayFood()
{
	setfillcolor(RGB(255, 255, 255));
	fillcircle(food.x, food.y, FOODR);		
}

//������
void updateSnake()
{
	int i;
	if (isEat()){
		snake.size++;
		updateFoodPos();
	}
	//����λ�ø���
	for (i = snake.size - 1; i > 0; --i) {
		snake.pos[i] = snake.pos[i - 1];
	}
	//��ͷ��λ�ø���
	switch (dir)
	{
	case UP:
		snake.pos[0].y -= SNAKER;
		break;
	case RIGHT:
		snake.pos[0].x += SNAKER;
		break;
	case DOWN:
		snake.pos[0].y += SNAKER;
		break;
	case LEFT:
		snake.pos[0].x -= SNAKER;
		break;
	default:
		break;
	}
}

void run(int speed)
{
	init();
	while (1)
	{
		cleardevice();//�������
		displaySnake();//��ʾ��
		displayFood();//��ʾʳ��
		keyOperator();//�жϼ�λ
		updateSnake();//�ı���λ��
		if (isImpact())//��ײ���
			return;
		Sleep(speed);
	}
}

//4 ��
void keyOperator()
{
	char k = -1;
	if (_kbhit())
		k = _getch();
	switch (k)
	{
	case 'w':
		if (dir != DOWN)
			dir = UP;
		break;
	case 'W':
		if (dir != DOWN)
			dir = UP;
		break;
	case 'd':
	case 'D':
		if (dir != LEFT)
			dir = RIGHT;
		break;
	case 's':
	case 'S':
		if (dir != UP)
			dir = DOWN;
		break;
	case 'a':
	case 'A':
		if (dir != RIGHT)
			dir = LEFT;
		break;
	default:
		break;
	}
}


bool isImpact()
{
	if (snake.pos[0].x <= 0 || snake.pos[0].x >= WIDTH || snake.pos[0].y <= 0 || snake.pos[0].y >= HEIGHT)
		return true;
	int i;
	for (i = 1; i < snake.size; ++i)
	{
		//�ж��Ƿ�����Բ�ڣ�������ײ��x1-x0��2 +��y1-y0��2 <= r2 
		if (((snake.pos[0].x - snake.pos[i].x)*(snake.pos[0].x - snake.pos[i].x) + (snake.pos[0].y - snake.pos[i].y)*(snake.pos[0].y - snake.pos[i].y)) < SNAKER*SNAKER)
			return true;
	}

	return false;
}
//�Ƿ�Ե�ʳ��
bool isEat()
{
	if (((snake.pos[0].x - food.x)*(snake.pos[0].x - food.x) + (snake.pos[0].y - food.y)*(snake.pos[0].y - food.y)) <= FOODR*FOODR)
		return true;
	return false;
}