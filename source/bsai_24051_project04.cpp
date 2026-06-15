#include<iostream>
#include<windows.h>
#include<conio.h>
#include<math.h>
#include <cstdlib>
using namespace std;
enum RUKH
{
	UP,DOWN,RIGHT,LEFT
};
struct pos
{
	int row, col;
};
struct saanp
{
	pos* p;
	int size;
	RUKH dir;
	int up, down, right, left;
};
void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
        ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState ==

            FROM_LEFT_1ST_BUTTON_PRESSED)

        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}
void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}
void color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}
void hideConsoleCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
void initialize(saanp& s,int rows,int cols)
{
    s.p = new pos[3]{ {rows / 2,cols / 2},{(rows / 2) - 1,cols / 2},{(rows / 2) - 2,cols / 2 } };
	s.size = 3;
	s.dir = UP;
}
void displaysaanp(saanp& s, char sym = 'O')
{
	for (int i = 0; i < s.size; i++)
	{
        gotoRowCol(s.p[i].row, s.p[i].col);
        color(2);
        cout << sym;
	}
}
void displaysaanp2(saanp& s, char sym = 'O')
{
    for (int i = 0; i < s.size; i++)
    {
        gotoRowCol(s.p[i].row, s.p[i].col);
        color(6);
        cout << sym;
    }
}
void movesaanp(saanp& s,int rows,int cols)
{
    for (int i = s.size-1; i-1 >=0; i--)
    {
        s.p[i] = s.p[i - 1];
    }
    switch (s.dir)
    {
    case UP:
        s.p[0].row--;
        if (s.p[0].row == -1)
            s.p[0].row = rows;
        break;
    case DOWN:
        s.p[0].row++;
        if (s.p[0].row == rows + 1)
            s.p[0].row = 0;
        break;
    case RIGHT:
        s.p[0].col++;
        if (s.p[0].col == cols + 1)
            s.p[0].col = 0;
        break;
    case LEFT:
        s.p[0].col--;
        if (s.p[0].col == -1)
            s.p[0].col = cols;
        break;
    }
}
void changeRukh(saanp &s, int key)
{
    switch (key)
    {
    case 77:
        if (s.dir == LEFT)
            return;
        s.dir = RIGHT; 
        break;
    case 75:
        if (s.dir == RIGHT)
            return;
        s.dir = LEFT;
        break;
    case 72:
        if (s.dir == DOWN)
            return;
        s.dir = UP;
        break;
    case 80:
        if (s.dir == UP)
            return;
        s.dir = DOWN;
        break;
    }
}
void changeRukh2(saanp& s, int key)
{
    switch (key)
    {
    case 100:
        if (s.dir == LEFT)
            return;
        s.dir = RIGHT;
        break;
    case 97:
        if (s.dir == RIGHT)
            return;
        s.dir = LEFT;
        break;
    case 119:
        if (s.dir == DOWN)
            return;
        s.dir = UP;
        break;
    case 115:
        if (s.dir == UP)
            return;
        s.dir = DOWN;
        break;
    }
}
bool isvalid(saanp& s, pos& f)
{
    for (int i = 0; i < s.size; i++)
    {
        if (s.p[i].col == f.col && s.p[i].row == f.row)
            return false;
    }
    return true;
}
void generatefruit(saanp& s,pos &f,int rows,int cols)
{
    do
    {
        f.row = rand() % rows;
        f.col = rand() % cols;
    } while (!isvalid(s, f));
}
void displayFruit(pos& f,char sym=3)
{
    gotoRowCol(f.row, f.col);
    color(5);
    cout <<sym;
}
bool fruitKhaliya(pos f, saanp& s)
{
    return (s.p[0].row == f.row && s.p[0].col == f.col);
}
void INSERTATEND(saanp& s, int rows, int cols)
{
    pos* p = new pos[s.size + 1];
    for (int i = 0; i < s.size; i++)
    {
        p[i] = s.p[i];
    }
    p[s.size] = s.p[s.size - 1];
    delete[]s.p;
    s.p = p;
    s.size++;
}
bool margya(saanp& s, saanp& s2)
{
    for (int i = 1; i < s.size; i++) 
    {
        if ((s.p[0].row == s2.p[i].row && s.p[0].col == s2.p[i].col) ||
            (s.p[i].row == s2.p[0].row && s.p[i].col == s2.p[0].col)) {
            return true;
        }
        if (s.p[0].row == s.p[i].row && s.p[0].col == s.p[i].col) {
            return true;
        }
    }
    for (int i = 1; i < s2.size; i++) 
    {
        if ((s2.p[0].row == s.p[i].row && s2.p[0].col == s.p[i].col) ||
            (s2.p[i].row == s2.p[0].row && s2.p[i].col == s2.p[0].col)) {
            return true;
        }
        if (s2.p[0].row == s2.p[i].row && s2.p[0].col == s2.p[i].col) {
            return true;
        }
    }
    return false; 
}
int main()
{
    int rows = 100, cols = 120; saanp snake_1,snake_2; pos fruit;
	initialize(snake_1,rows,cols);
    initialize(snake_2, rows/2, cols/2);
    displaysaanp(snake_1);
    displaysaanp(snake_2);
    generatefruit(snake_1,fruit, rows, cols);
    generatefruit(snake_2, fruit, rows, cols);
    displayFruit(fruit);
    while (true)
    {
        if (_kbhit())
        {
            int key = _getch();
            if (key == 224)
            {
                key = _getch();
                changeRukh(snake_1, key);
            }
            if (key == 119 or key == 97 or key == 115 or key == 100)
            {
                changeRukh2(snake_2, key);
            }

        }
        displaysaanp(snake_1); 
        displaysaanp2(snake_2);
        Sleep(100);
        displaysaanp2(snake_2, ' ');
        displaysaanp(snake_1, ' '); 
        movesaanp(snake_1,rows,cols);
        movesaanp(snake_2, rows, cols);
        if (fruitKhaliya(fruit, snake_1))
        {
            INSERTATEND(snake_1, rows, cols);
            generatefruit(snake_1, fruit, rows, cols);
            displayFruit(fruit);
        }
        if (fruitKhaliya(fruit, snake_2))
        {
            INSERTATEND(snake_2, rows, cols);
            generatefruit(snake_2, fruit, rows, cols);
            displayFruit(fruit);
        }
        if (snake_1.size > 3 or snake_2.size>3)
        {
            if (margya(snake_1,snake_2))
            {
                break;
            }
        }
    }
    color(4);
    cout << "snake 1 eats : " << snake_1.size - 3 << " fruit" <<"     ";
    cout << "snake 2 eats : " << snake_2.size - 3 << " fruit"; 
	return 0;
}