#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>
#include <Windows.h>

int fallspeed(int* speed, int* score);
void Mapline();
void PrintMap(int* P);
void RowDownMap();
int CollisionDetection(int* score, int* P, int* life);
int main();
void parachute();
void gotoxy(int x, int y);

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void parachute(void) {
	while (1) {
		int fallspeed(int* speed, int* score);
		void Mapline();
		void PrintMap(int* P);
		void RowDownMap();
		int CollisionDectection(int* score, int* P, int* life);
		int main();
	}
}