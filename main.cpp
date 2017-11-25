////////////////////////////////////////////
// 程序名称：贪吃蛇
// 编译环境：Visual Studio 2015  基于easy图形库
// 程序编写：dawu
//
// 最后更新：2017年10月21日11:12:41
//

#pragma warning(disable:4996)
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <graphics.h>			// 绘图库头文件，绘图语句需要
#define WIDTH 640				//地图宽度
#define HEIGHT 480				//地图高度
#define SNAKER  12				//蛇块半径
#define FOODR 15				//食物半径
#define SNAKELEN  1024			//蛇的最大长度

//位置结构体
struct Pos
{
	int x;
	int y;
};

//蛇的结构体
struct Snake
{
	int size;
	Pos pos[SNAKELEN];
};

//方向枚举
enum Direction { UP, RIGHT, DOWN, LEFT };

void init();//初始化蛇的位置和实物的位置
void updateFoodPos();//更新食物位置
void displaySnake();//画蛇
void displayFood();//画食物
void updateSnake();//更新蛇的位置和长度
void run(int speed);//运行
void keyOperator();//判断键位并改变方向
bool isImpact();//判断是否碰撞
bool isEat();//判断是否吃到食物


			 //外部连接性的静态变量（全局变量）
struct Snake snake;//蛇对象
Pos food;//食物对象
Direction dir;//蛇前进的方向


int main()
{
	//初始化随机数种子
	srand((unsigned)time(NULL));
	//初始化窗口
	initgraph(WIDTH, HEIGHT);
	char c;
	//显示字体
	outtextxy(WIDTH / 2, HEIGHT / 2, _T("按Y开始游戏,其他键退出..."));
	c = _getch();
	//难度级别选择
	int speed, in;
	outtextxy(WIDTH / 2, HEIGHT / 2, _T("请选择1-8级难度"));
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
		outtextxy(WIDTH / 2, HEIGHT / 2, _T("输入有误，请重新输入"));
		goto errors;
		break;
	}
	while (c == 'y' || c == 'Y')
	{
		//运行
		run(speed);
		outtextxy(WIDTH / 2, HEIGHT / 2, _T("失败！！！按Y开始游戏,其他键退出..."));
		_getch();
	}
	//关闭窗口
	closegraph();
	return 0;
}


void init()
{
	updateFoodPos();
	snake.size = 1;
	snake.pos[0].x = rand() % (WIDTH - SNAKER * 2) + SNAKER;		//初始化蛇头位置
	snake.pos[0].y = rand() % (HEIGHT - SNAKER * 2) + SNAKER;		//范围0 -- HEIGHT-SNAKER
}

//1
void updateFoodPos()
{
	food.x = rand() % (WIDTH - FOODR * 2) + FOODR;		//初始化食物位置
	food.y = rand() % (HEIGHT - FOODR * 2) + FOODR;		//范围0 -- HEIGHT-FOODR
}

//画蛇身
void displaySnake()
{
	int i;
	setfillcolor(RGB(255, 0, 0));		//设置颜色
	fillcircle(snake.pos[0].x, snake.pos[0].y, SNAKER);	//画蛇头
	setfillcolor(RGB(0, 255, 0));
	for (i = 1; i < snake.size; ++i){
		fillcircle(snake.pos[i].x, snake.pos[i].y, SNAKER);	
	}
}

//画食物
void displayFood()
{
	setfillcolor(RGB(255, 255, 255));
	fillcircle(food.x, food.y, FOODR);		
}

//更新蛇
void updateSnake()
{
	int i;
	if (isEat()){
		snake.size++;
		updateFoodPos();
	}
	//蛇身位置更新
	for (i = snake.size - 1; i > 0; --i) {
		snake.pos[i] = snake.pos[i - 1];
	}
	//蛇头的位置更新
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
		cleardevice();//清除背景
		displaySnake();//显示蛇
		displayFood();//显示食物
		keyOperator();//判断键位
		updateSnake();//改变蛇位置
		if (isImpact())//碰撞检测
			return;
		Sleep(speed);
	}
}

//4 宏
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
		//判断是否落在圆内，是则碰撞（x1-x0）2 +（y1-y0）2 <= r2 
		if (((snake.pos[0].x - snake.pos[i].x)*(snake.pos[0].x - snake.pos[i].x) + (snake.pos[0].y - snake.pos[i].y)*(snake.pos[0].y - snake.pos[i].y)) < SNAKER*SNAKER)
			return true;
	}

	return false;
}
//是否吃到食物
bool isEat()
{
	if (((snake.pos[0].x - food.x)*(snake.pos[0].x - food.x) + (snake.pos[0].y - food.y)*(snake.pos[0].y - food.y)) <= FOODR*FOODR)
		return true;
	return false;
}