#include "distinguish.h"
#include "poker.h"

int flush(trump* card)
{
	int cnt = 0;

	for (int i = 0; i < 4; i++)
		if (strcmp(card[i].shape,  card[i + 1].shape) == 0) cnt++;

	if (cnt == 4) return 1;
	else		  return 0;
}

int straight(trump* card)
{
	int cnt = 0;

	for (int i = 0; i < 4; i++)
		if ((card[i].number + 1) == card[i + 1].number) cnt++;

	if (cnt == 4) return 1;
	else if (card[0].number == 1 &&
		card[1].number == 10 &&
		card[2].number == 11 &&
		card[3].number == 12 &&
		card[4].number == 13) return 1;
	else if (card[0].number == 1 &&
		card[1].number == 2 &&
		card[2].number == 11 &&
		card[3].number == 12 &&
		card[4].number == 13) return 1;
	else if (card[0].number == 1 &&
		card[1].number == 2 &&
		card[2].number == 3 &&
		card[3].number == 12 &&
		card[4].number == 13) return 1;
	else if (card[0].number == 1 &&
		card[1].number == 2 &&
		card[2].number == 3 &&
		card[3].number == 4 &&
		card[4].number == 13) return 1;
	else return 0;
}

int royal(trump* card)
{
	if (card[0].number == 1 && 
		card[1].number == 10 && 
		card[2].number == 11 && 
		card[3].number == 12 && 
		card[4].number == 13) 
		return 1;
	else return 0;
}

int four_of_a_kind(trump* card, trump* msFourkind)
{
	int cnt = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			if (j == i) continue;
			if (card[i].number == card[j].number) cnt++;
		}
		if (cnt == 3) {
			*msFourkind = card[i];
			return 1;
		}
		else cnt = 0;
	}
	return 0;
}

int three_of_a_kind(trump* card, trump* msThreekind)
{
	int cnt = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (j == i) continue;
			if (card[i].number == card[j].number) cnt++;
		}
		if (cnt == 2) {
			*msThreekind = card[i];
			return 1;
		}
		cnt = 0;
	}
	return 0;
}

int two_pair(trump* card, trump* msTwopair, short three_of_a_kind_flag)
{
	int cnt = 0;

	if (three_of_a_kind_flag == 1) return 0;

	for (int i = 0, flag = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (j == i) continue;
			if (card[i].number == card[j].number) cnt++;
		}
		if (cnt == 1)
		{
			if (flag == 1 && card[i].number == msTwopair[flag].number) continue;
			else msTwopair[flag++] = card[i];
		}
	}

	if (cnt == 4) return 1;
	else return 0;
}

int one_pair(trump* card, trump* msOnepair)
{
	int cnt = 0, flag = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (j == i) continue;
			if (card[i].number == card[j].number) cnt++;
		}
		if (cnt == 1)
		{
			flag++;
			if (flag == 2)
			{
				*msOnepair = card[i];
				return 1;
			}
		}
		cnt = 0;
	}
	return 0;
}

int full_house(int three_of_a_kind_flag, int one_pair_flag, trump* msFullhouse)
{
	if (three_of_a_kind_flag == 1 && one_pair_flag == 1) return 1;
	return 0;
}