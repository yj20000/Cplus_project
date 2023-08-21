#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>    
#pragma comment(lib,"winmm.lib")

#define Map_X 35
#define Map_Y 22

int map[Map_Y][Map_X];

void gotoxy(int x, int y)
{
    COORD Cur = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int fallspeed(int* speed, int* score) {
    if (*score > 30) *speed = 170;
    if (*score > 60) *speed = 150;
    if (*score > 90) *speed = 100;
    if (*score > 150) *speed = 50;
    if (*score > 300)*speed = 20;
    return *speed;
}

void Mapline() {
    for (int i = 0; i < Map_Y + 1; i++) {
        gotoxy(Map_X, i);
        printf("□\n");
    }
    gotoxy(0, Map_Y);
    for (int i = 0; i < Map_X / 2; i++)
        printf("□");
}

void PrintMap(int* P) {
    for (int i = 0; i < Map_Y - 1; i++) {
        for (int j = 0; j < Map_X; j++) {
            if (map[i][j] == 0)
                printf(" ");
            else if (map[i][j] == 1)
                printf("#");
            else printf("♡");
        }
        printf("\n");
    }


    for (int j = 0; j < Map_X; j++) {
        if (P[j] == 0)
            printf(" ");
        else if (P[j] == 1)
            printf("@");
    }
}

void RowDownMap() {
    for (int i = Map_Y - 1; i > 0; i--) {
        for (int j = 0; j < Map_X; j++) {
            map[i][j] = map[i - 1][j];
        }
    }

    for (int j = 0; j < Map_X; j++) {
        map[0][j] = 0;
    }
}

int CollisionDetection(int* score, int* P, int* life) {
    for (int i = 0; i < Map_X; i++) {
        if (map[Map_Y - 1][i] == 1 && P[i] == 1) {
            printf("\a");
            *life -= 1;
        }
        else if (map[Map_Y - 1][i] == 1 && P[i] != 1) {
            *score += 1;
        }
        else if (map[Map_Y - 1][i] == 2 && P[i] == 1) {
            *life += 1;
        }
    }

    if (*life < 0) {
        return 1;
    }
    return 0;
}

int main() {
    system("mode con: cols=40 lines=25");

    gotoxy(13, 2);
    printf("낙하물 피하기");
    gotoxy(9, 14);
    printf("!아무키나 누르면 시작!");

    _getch();

    system("cls");
    time_t start, end;
    double result;
    start = time(NULL);
    int Char[Map_X] = { 0, };
    int Location;
    int input;
    int stage = 1;
    int score = 0;
    int life = 3;
    int speed = 300;
    int CharLoc = (int)(Map_X / 2.0);

    Mapline();

    srand((unsigned)time(NULL));

    Char[CharLoc] = 1;
    for (;;) {
        RowDownMap();
        for (int i = 0; i < rand() % 4; i++) {
            Location = rand() % Map_X;
            map[0][Location] = 1;
        }

        if ((score + 8) % 7 == 0) {
            for (int j = 0; j < rand() % 2; j++) {
                Location = rand() % Map_X;
                map[0][Location] = 2;
            }
        }

        if (_kbhit()) {
            input = _getch();
            if (input == 75 && CharLoc > 0) {
                Char[CharLoc] = 0;
                CharLoc--;
                Char[CharLoc] = 1;
            }
            else if (input == 77 && CharLoc < Map_X - 1) {
                Char[CharLoc] = 0;
                CharLoc++;
                Char[CharLoc] = 1;
            }
        }

        gotoxy(0, 0);
        PrintMap(Char);
        if (CollisionDetection(&score, Char, &life))
            break;
        fallspeed(&speed, &score);
        Sleep(speed);

        gotoxy(0, Map_Y + 1);
        printf("Life:%d", life);
        gotoxy(0, Map_Y + 2);
        printf("score:%d", score);
    }
    end = time(NULL);
    result = (double)(end - start);

    system("cls");
    printf("[Game Over]\n");
    printf("점수 : %d\n", score);
    printf("버틴 시간 :%f\n\n\n", result);
}