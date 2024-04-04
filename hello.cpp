#include <iostream>
#include <windows.h>
#include <vector>
#include <stack>
#include <ctime>
#include <conio.h>




void gotoxy(int short x, short int y) {
    COORD p = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

enum ConsoleColor {
    Black = 0,
    Blue,
    Green,
    Cyan,
    Red,
    Magenta,
    Brown,
    LightGray,
    DarkGray,
    LightBlue,
    LightGreen,
    LightCyan,
    LightRed,
    LightMagenta,
    Yellow,
    White
};

void setColor(int background, int text) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)(background << 4) | text);
}

const int BORDER = 100;
const int EMPTY_CELL = 0;
const int MINE = 10;

class Map {
private:
    

    int size;
    std::vector <std::vector<int>> map;
    std::vector <std::vector<int>> mask;
public:
    Map() {
        size = 25;
    }

    int openCell(int x, int y) {
        int result = 1;
        mask[x][y] = 1;

        if (map[x][y] == MINE) {
            result = MINE;
        }
        else if (map[x][y] == EMPTY_CELL) {
            result = EMPTY_CELL;
        }
        show();
        return result;
    }
    bool isBorder(int x, int y) {
        if (x < 0 || x >= size) {
            return false;
        }
        if (y < 0 || y >= size) {
            return false;
        }
        if (map[x][y] == BORDER) {
            return true;
        }
        return false;
    }

    void initVec(std::vector <std::vector<int>>& vec) {
        for (int i = 0; i < size; i++) {
            std::vector<int> temp;
            for (int j = 0; j < size; ++j)
            {
                if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
                {
                    temp.push_back(BORDER);
                }
                else
                {
                    temp.push_back(EMPTY_CELL);
                }
            }
            vec.push_back(temp);
        }
    }

    void initMap() {
        initVec(map);
    }

    void initMask() {
        initVec(mask);
    }

    void coutColor(char ch, int color) {
        setColor(Black, color);
        std::cout << ch;
        setColor(Black, White);
    }

    void show() {
        gotoxy(0, 0);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; ++j)
            {
                 if (mask[j][i] == EMPTY_CELL)
                 {
                     std::cout << ".";
                     continue;
                 }
                if (map[j][i] == BORDER)
                {
                    coutColor('#', LightBlue);
                }
                else if (map[j][i] == EMPTY_CELL)
                {
                    std::cout << " ";
                }
                else if (map[j][i] == MINE)
                {
                    std::cout << "*";
                }
                else if (map[j][i] == 1)
                {
                    coutColor('1', Yellow);
                }
                else if (map[j][i] == 2)
                {
                    coutColor('2', Magenta);
                }
                else if (map[j][i] == 3)
                {
                    coutColor('3', Brown);
                }
                else if (map[j][i] == 4)
                {
                    coutColor('4', Red);
                }
                else if (map[j][i] == 5)
                {
                    coutColor('5', LightRed);
                }
                else if (map[j][i] == 6)
                {
                    coutColor('6', DarkGray);
                }
                else if (map[j][i] == 7)
                {
                    coutColor('7', Cyan);
                }
                else if (map[j][i] == 8)
                {
                    coutColor('8', LightMagenta);
                }
                
            }
            std::cout << std::endl;
        }
    }

    void setRandMines(int numMines) {
        if (numMines >= (size - 2) * (size - 2)) {
            std::cout << "Too many mines!" << std::endl;
            return;
        }
        for (int i = 0; i < numMines; i++)
        {
            int x, y;
            do {
                x = rand() % (size - 2) + 1;
                y = rand() % (size - 2) + 1;
            } while (map[x][y] == MINE);
            map[x][y] = MINE;
        }
    }

    void setDigits() {
        int d = 0;
        for (int i = 1; i < size - 1; i++) {
            for (int j = 1; j < size - 1; ++j)
            {
                if (map[j][i] == MINE) {
                    continue;
                }
                if (map[j][i + 1] == MINE) {
                    ++d;
                }
                if (map[j][i - 1] == MINE) {
                    ++d;
                }
                if (map[j + 1][i + 1] == MINE) {
                    ++d;
                }
                if (map[j + 1][i - 1] == MINE) {
                    ++d;
                }
                if (map[j - 1][i + 1] == MINE) {
                    ++d;
                }
                if (map[j - 1][i - 1] == MINE) {
                    ++d;
                }
                if (map[j + 1][i] == MINE) {
                    ++d;
                }
                if (map[j - 1][i] == MINE) {
                    ++d;
                }
                map[j][i] = d;
                d = 0;
            }
        }
    }
    void fill(int px, int py) {
        std::stack<int> stk;
        stk.push(px);
        stk.push(py);

        int x = 0;
        int y = 0;
        
        while (true) {
            y = stk.top();
            stk.pop();
            x = stk.top();
            stk.pop();
            if (map[x][y + 1] == EMPTY_CELL && mask[x][y+1] == 0) {
                stk.push(x);
                stk.push(y + 1);                
            }
            mask[x][y + 1] = 1;
            if (map[x][y - 1] == EMPTY_CELL && mask[x][y-1] == 0) {
                stk.push(x);
                stk.push(y - 1);                
            }
            mask[x][y - 1] = 1;
            if (map[x+1][y + 1] == EMPTY_CELL && mask[x + 1][y+1] == 0) {
                stk.push(x+1);
                stk.push(y + 1);                
            }
            mask[x + 1][y + 1] = 1;
            if (map[x+1][y - 1] == EMPTY_CELL && mask[x + 1][y-1] == 0) {
                stk.push(x+1);
                stk.push(y - 1);                
            }
            mask[x + 1][y - 1] = 1;
            if (map[x - 1][y + 1] == EMPTY_CELL && mask[x - 1][y+1] == 0) {
                stk.push(x - 1);
                stk.push(y + 1);                
            }
            mask[x - 1][y + 1] = 1;
            if (map[x - 1][y - 1] == EMPTY_CELL && mask[x - 1][y-1] == 0) {
                stk.push(x - 1);
                stk.push(y - 1);                
            }
            mask[x - 1][y - 1] = 1;
            if (map[x - 1][y] == EMPTY_CELL && mask[x - 1][y] == 0) {
                stk.push(x - 1);
                stk.push(y);                
            }
            mask[x - 1][y] = 1;
            if (map[x + 1][y] == EMPTY_CELL && mask[x+1][y]==0) {
                stk.push(x + 1);
                stk.push(y);                
            }
            mask[x + 1][y] = 1;
            if (stk.empty()) {
                break;
            }
        }
    }
};

class Keyboard {
    int ch = 0;
public:
    Keyboard() {
        ch = 0;
    }
    void waitKey() {
        ch = _getch();
    }
    int getKey() {
        return ch;
    }
};

class Cursor {
private:
    int x = 1;
    int y = 1;

    int tx = 1;
    int ty = 1;
public:
    void save() {
        tx = x;
        ty = y;
    }
    void undo() {
        x = tx;
        y = ty;
    }
    void incX() {
        ++x;
    }
    void decX() {
        --x;
    }
    void incY() {
        ++y;
    }
    void decY() {
        --y;
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    void move() {
        gotoxy(x, y);
    }
};

class Game {
private:
    void showLogo() {
        gotoxy(40, 11);
        std::cout << "Saper" << std::endl;
        Sleep(2000);
        system("cls");
    }
public:
    void gameOver() {
        gotoxy(40, 11);
        std::cout << "Game over!";
        Sleep(2000);
        gotoxy(0, 15);
        system("pause");
    }
    void run() {
        //showLogo();
        //std::cout<<"Game is running!" << std::endl;
        Map map;
        map.initMap();
        map.initMask();
        map.setRandMines(40);
        map.setDigits();
        map.show();

        Keyboard kb;
        Cursor cs;

        cs.move();

        bool exit = false;

        while (!exit) {
            kb.waitKey();
            cs.save();

            switch (kb.getKey()) {
            case 77: cs.incX(); break;
            case 80: cs.incY(); break;
            case 75: cs.decX(); break;
            case 72: cs.decY(); break;
            case 13:
                int result = map.openCell(cs.getX(), cs.getY());
                if (result == MINE)
                {
                    gameOver();
                    exit = true;
                }
                if (result == EMPTY_CELL)
                {
                    map.fill(cs.getX(), cs.getY());
                    map.show();
                }

                break;

            }

            if (map.isBorder(cs.getX(), cs.getY())) {
                cs.undo();
            }
            cs.move();
        }
    }
};

int main() {
    srand(time(0));
    Game game;
    game.run();
}