#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define GREEN  10
#define BLUE   11
#define RED    12
#define YELLOW 14
#define WHITE  15

//트럼프 카드 구조체
struct trump {
	char order;
	char shape[3];
	int number;
};

//데이터 저장을 위한 사용자 구조체
struct person {
	char name[20];
	int money;
	short best_play = 0;
	trump card[5];
};