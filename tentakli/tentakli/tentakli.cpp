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

void Setup()  // �������, ���������� �� ��������� ����������� ��������� � ���������� �����
{
	gameOver = false;    // ������� ��������� ��������� ������ � ������, � ������ � ���, ��� ���� �� ���������
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw()    // ������� �������� �� ��������� �������� ����
{
	system("cls");
	for (int i = 0; i < width + 1; i++)   // ����������� �������� ����
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)  // ���� ��� ������������� �������
	{
		for (int j = 0; j < width; j++)  // ���� ��� ��������������� �������
		{
			if (j == 0 || j == width - 1)  // ����������� �������� ���� �� ���������
				cout << "#";
			if (i == y && j == x)  // ����������� ������ ����
				cout << "0";
			else if (i == fruitY && j == fruitX)  // ����������� �������
				cout << "$";
			else
			{
				bool print = false;
				for (int k = 0; k < nTall; k++)  // ����, � ������� ����� �������������� ���� ������ ��� �������� �������
				{
					if (tallX[k] == j && tallY[k] == i)  // �������, ��� ������� ����� ����� �������������
					{
						print = true;
						cout << "O";
					}
				}
				if (!print)  // �������, ��� ������� ����� ����� �� �����
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++)  // ����������� �������� ����
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;  // ������ �������� ���������� �����
}

void Input()  // �������, ���������� �� ������� ������
{
	if (_kbhit())  // ������� ��� ������� ������ ���������� ����
	{
		switch (_getch ())  // ������� ���������� ���������� �������, ����� ������� �� ��� ��������
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

void Logic()  // �������, ���������� �� ������ � ����
{
	int prevX = tallX[0];
	int prevY = tallY[0];
	int prev2X, prev2Y;
	tallX[0] = x;
	tallY[0] = y;
	for (int i = 1; i < nTall; i++)  // ���� ��� ����������� ����� ������ � ����
	{
		prev2X = tallX[i];
		prev2Y = tallY[i];
		tallX[i] = prevX;
		tallY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)  // ����������� ��������� ��������� ��� �������� ����
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

	//if (x > width || x < 0 || y > height || y < 0)  // �������, ��� ������� ������ �� ����� ��������� ������ �����
	//	gameOver = true;
	if (x >= width - 1)  // �������, ���������� ������ ����� ��������� ������ �����
		x = 0;
	else if (x < 0)
		x = width - 2;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < nTall; i++)  // ���� ��� �������� �������, ��� ������� ���� ����� ���������
	{
		if (tallX[i] == x && tallY[i] == y)  // �������, ��� ������� ���� ����� ���������, � ������ �������� ������������ ������
			gameOver = true;
	}

	if (x == fruitX && y == fruitY)  // ������� ��� ����������� ��������� �������
	{
		score += 8;  // ���������� � �������� ���������� 8 �����
		fruitX = rand() % width;  // ��������� ��������� �������
		fruitY = rand() % height;
		nTall++;
	}
}

int main()
{
	Setup();  // ����� �������
	while (!gameOver)  // ���� ���� �� ��������� ���������� ��������� �������
	{
		Draw();
		Input();
		Logic();
	}
	return 0;
}