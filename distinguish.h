#pragma once
#include "lib.h"

int flush(trump* card);
int straight(trump* card);
int royal(trump* card);
int four_of_a_kind(trump* card, trump* msFourkind);
int three_of_a_kind(trump* card, trump* msThreekind);
int two_pair(trump* card, trump* msTwopair, short three_of_a_kind_flag);
int one_pair(trump* card, trump* msOnepair);
int full_house(int three_of_a_kind_flag, int one_pair_flag, trump* msFullhouse);