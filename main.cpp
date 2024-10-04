#include<iostream>
#include<windows.h>
#include<random>
using namespace std;
void HideCursor();
void cursor(short x, short y);
bool flag = true;

struct Map {
private:
	int width = 20;
	int length = 20;
public:
	void print() {
		cursor(0, 0);
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < width; j++) {
				if (i == 0 || i == (length - 1) || j == 0 || j == (width - 1))
					if (j == (width - 1)) {
						cout << "w" << endl;
					}
					else {
						cout << "w";
					}
				else
					cout << " ";
			}
		}
	}
};

class food {
public:
	random_device rd;
	mt19937 g{ random_device{}() };
	int x;
	int y;
	food() {
		x = 1 + rd() % 18;
		y = 1 + rd() % 18;
	}
	void show() {
		cursor(x, y);
		cout << '*';
	}
	void reproduce() {
		x = 1 + rd() % 18;
		y = 1 + rd() % 18;
	}
};
food f;

class SnakeNode {
public:
	int x;
	int y;
	char theme;
	SnakeNode* next;
	SnakeNode(char s, int x = 20, int y = 20) : theme(s), next(nullptr), x(x), y(y) {}
};

class SnakeList {
	random_device rd;
	mt19937 g{ random_device{}() };
public:
	int count = 0;
	SnakeNode* head;
	SnakeNode* tail;
	SnakeList() {
		head = new SnakeNode('@');
		tail = head;
		head->x = rd() % 10;
		head->y = 3 + rd() % 14;
	}
	void grow() {
		SnakeNode* body = new SnakeNode('+');
		body->next = tail;
		tail = body;
	}
	void print() {
		SnakeNode* current = tail;
		while (current->next != nullptr) {
			cursor(current->x, current->y);
			cout << current->theme;
			current = current->next;
		}
		cursor(current->x, current->y);
		cout << current->theme;
	}
	void move(int x1, int y1) {
		head->x += x1;
		head->y += y1;
		cursor(tail->x, tail->y);
		cout << ' ';
		SnakeNode* current = tail;
		while (current->next != nullptr) {
			if (head->x == current->x && head->y == current->y) {
				flag = false;
				break;
			}
			else if (head->x == 0 || head->x == 19 || head->y == 0 || head->y == 19) {
				flag = false;
				break;
			}
			current->x = current->next->x;
			current->y = current->next->y;
			if (current->x == f.x && current->y == f.y) {
				f.reproduce();
				f.show();
				count++;
				grow();
			}
			current = current->next;
		}
	}
};

int main() {
	int speed;
	cout << "Enter speed(1~9):";
	cin >> speed;
	HideCursor();
	Map map;
	map.print();
	SnakeList snake;
	snake.grow();
	snake.grow();
	snake.grow();
	snake.grow();
	snake.move(1, 0);
	snake.move(1, 0);
	snake.move(1, 0);
	snake.move(1, 0);

	f.show();
	int dir_x = 1;
	int dir_y = 0;
	while (flag) {
		if (GetAsyncKeyState(VK_RIGHT)) {
			dir_x = 1;
			dir_y = 0;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			dir_x = 0;
			dir_y = 1;
		}
		else if (GetAsyncKeyState(VK_LEFT)) {
			dir_x = -1;
			dir_y = 0;
		}
		else if (GetAsyncKeyState(VK_UP)) {
			dir_x = 0;
			dir_y = -1;
		}
		snake.move(dir_x, dir_y);
		snake.print();
		Sleep(500 - speed * 50);
	}
	system("cls");
	cout << "game over" << endl;
	cout << "Your score is:" << snake.count << endl;
	system("pause");
}

void HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);
}

HANDLE hOut; COORD pos;
void cursor(short x, short y) {
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	pos = { x, y };
	SetConsoleCursorPosition(hOut, pos);
}