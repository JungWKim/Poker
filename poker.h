#pragma once
#include "lib.h"

void gotoxy(short x, short y);
void move_arrow_key_modified(char curPos, short* x, short* y, short y_max, short y_min);
void decoration();
void setTextColor(short color, short x, short y, const char* shape, int number);

void name();
int menu();
int game_select();
void record();
void close();

void show_boundary();
void create_card(trump* card);
void shuffle_card(trump* card);
void shuffle_one_by_one(trump* card1, trump* card2);
void sort(trump* card);
void display_card(short x, short y, const char* shape, int color);
void save();
short numberShapeCompare(trump* opponent_card, trump* user_card, short opponent_point);

void omaha_holdem(int* opponent_choice, int* user_choice);
void omaha_holdem_betting(int* opponent_choice, int* user_choice, short* betting);
short omaha_holdem_result(int* opponent_choice, int* user_choice, short y1);
int omaha_combinations(trump* card);
void seven_card_stud();
