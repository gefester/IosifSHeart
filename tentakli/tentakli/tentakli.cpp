#include <iostream>;
#include <conio.h>;

using namespace std;

bool gameOver, pause;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tallX[100], tallY[100];
int nTall;
enum eDirection { STOP = 0, LEFT, UP, RIGHT, DOWN };
eDirection dir;

void Setup()  // Функция, отвечающая за установку необходимых координат и начисления очков
{
	gameOver = false;    // Задание начальных координат змейки и фрукта, и запись о том, что игра не проиграна
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()    // Функция отвечает за рисование игрового поля
{
	system("cls");
	for (int i = 0; i < width + 1; i++)   // Ограничение игрового поля
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)  // Цикл для вертикального анализа
	{
		for (int j = 0; j < width; j++)  // Цикл для горизонтального анализа
		{
			if (j == 0 || j == width - 1)  // Ограничение игрового поля по вертикали
				cout << "#";
			if (i == y && j == x)  // Обозначение головы змеи
				cout << "0";
			else if (i == fruitY && j == fruitX)  // Обозначение фруктов
				cout << "$";
			else
			{
				bool print = false;
				for (int k = 0; k < nTall; k++)  // Цикл, в котором будет обеспечиваться рост змейки при поедании фруктов
				{
					if (tallX[k] == j && tallY[k] == i)  // Условие, при котором хвост будет увеличиваться
					{
						print = true;
						cout << "O";
					}
				}
				if (!print)  // Условие, при котором хвост расти не будет
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)  // Ограничение игрового поля
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;  // Ввывод текущего количества очков
}

void Input()  // Функция, отвечающая за входные данные
{
	if (_kbhit())  // Условие для задания клавиш управления змеёй
	{
		switch (_getch ())  // Задание параметров управления змейкой, какие клавиши за что отвечают
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case'z':
			gameOver = true;
			break;
		}
	}
}

void Logic()  // Функция, отвечающая за логику в игре
{
	int prevX = tallX[0];
	int prevY = tallY[0];
	int prev2X, prev2Y;
	tallX[0] = x;
	tallY[0] = y;
	for (int i = 1; i < nTall; i++)  // Цикл для правильного роста хвоста у змеи
	{
		prev2X = tallX[i];
		prev2Y = tallY[i];
		tallX[i] = prevX;
		tallY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)  // Обеспечение изменения координат при движении змеи
	{
	case LEFT:
		x--;
		break;
	case UP:
		y--;
		break;
	case RIGHT:
		x++;
		break;
	case DOWN:
		y++;
		break;
	}

	//if (x > width || x < 0 || y > height || y < 0)  // Условие, при котором змейка не будет проходить сквозь стену
	//	gameOver = true;
	if (x >= width - 1)  // Условия, прикоторых змейка будет проходить сквозь стену
		x = 0;
	else if (x < 0)
		x = width - 2;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < nTall; i++)  // Цикл для проверки условия, при котором игра будет проиграна
	{
		if (tallX[i] == x && tallY[i] == y)  // Условие, при котором игра будет проиграна, в случае поедания собственного хвоста
			gameOver = true;
	}

	if (x == fruitX && y == fruitY)  // Условие для определения координат фруктов
	{
		score += 8;  // Добавление к текущему количеству 8 очков
		fruitX = rand() % width;  // Случайное появление фруктов
		fruitY = rand() % height;
		nTall++;
	}
}

int main()
{
	Setup();  // Вызов функции
	while (!gameOver)  // Пока игра не проиграна вызываются следующие функции
	{
		Draw();
		Input();
		Logic();
	}
	return 0;
}