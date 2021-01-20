/*

	developer : Jung Woo Kim
	Company : Sungkyul Univ.
	Project name : Poker game

*/

#include "poker.h"

//windows.h >> gotoxy
//conio.h >> _getch

trump card[52];
trump neutral_card[3];
person player, opponent;
int opponent_choice[2], user_choice[2];
short betting;

int main()
{
	// create data record file
	FILE* fp;
	if (fopen_s(&fp, "user_data.txt", "a"))
	{
		perror("[failed] fopen_s in main() : ");
		fclose(fp);
	}
	fclose(fp);
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
	name();
	while (1)
	{
		int which_menu = menu();
		if (which_menu == 1)
		{
			while (1)
			{
				int which_game = game_select();
				if (which_game == 1)
				{
					while (1)
					{
						omaha_holdem(opponent_choice, user_choice);
						omaha_holdem_betting(opponent_choice, user_choice, &betting);
						if (omaha_holdem_result(opponent_choice, user_choice, neutral_card, betting) < 0) break;
					}
				}
				else if (which_game == 2)
					seven_card_stud();
				else break;
			}
		}
		else if (which_menu == 2)
			record();
		else
			close();
	}
	return 0;
}