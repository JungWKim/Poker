#include "poker.h"
#include "distinguish.h"

extern trump card[52];
extern trump neutral_card[3];
extern person player;

trump msFourkind, msThreekind, msFullhouse, msOnepair, msTwopair[2];

//좌표 이동함수
void gotoxy(short x, short y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void move_arrow_key_modified(char curPos, short* x, short* y, short y_max, short y_min)
{
	switch (curPos)
	{
	case 72://up
		*y = *y - 2;
		if (*y < y_min) *y = y_min;
		break;
	case 80://down
		*y = *y + 2;
		if (*y > y_max) *y = y_max;
		break;
	}
}

//초반에 화면을 꾸미는 함수
void decoration()
{
	system("cls");
	printf("=================================================================================================\n");
	printf("=                                                                                               =\n");
	printf("=  *       *       *  ******  *        *****   *****      *       *     ******   *******  ****  =\n");
	printf("=   *     * *     *   *       *       *       *     *    * *     * *    *           *    *    * =\n");
	printf("=    *   *   *   *    ******  *      *        *     *   *   *   *   *   ******      *    *    * =\n");
	printf("=     * *     * *     *       *       *       *     *  *     * *     *  *           *    *    * =\n");
	printf("=      *       *      ******  ******   *****   *****  *       *       * ******      *     ****  =\n");
	printf("=                                                                                               =\n");
	printf("=        *******           *            ********      *******    **        *       *******      =\n");
	printf("=      *                  * *          *                 *       * *       *      *       *     =\n");
	printf("=     *                  *   *        *                  *       *  *      *     *         *    =\n");
	printf("=    *                  *     *       *                  *       *   *     *     *         *    =\n");
	printf("=    *                 *********       **********        *       *    *    *     *         *    =\n");
	printf("=    *                *         *                *       *       *     *   *     *         *    =\n");
	printf("=     *              *           *                *      *       *      *  *     *         *    =\n");
	printf("=      *            *             *               *      *       *       * *      *       *     =\n");
	printf("=        *******   *               *    **********    *******    *        **       *******      =\n");
	printf("=                                                                                               =\n");
	printf("=================================================================================================\n");
}

void setCardColor(short color, short x, short y, const char* shape, int number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	display_card(x, y, shape, number);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
}

//이름을 적는 화면
void name() {
	int rewrite = 0;
	char user_name[20];

	while (1)
	{
		decoration();
		if(rewrite == 1)
		{
			gotoxy(40, 24);
			printf("Please Enter your name!!");
		}
		gotoxy(40, 30);
		printf("Exit[Q]");
		gotoxy(40, 22);
		printf("What is your name? ");
		gotoxy(40, 23);
		printf(">> ");
		gets_s(user_name, sizeof(user_name)); //visual studio컴파일러에서 gets는 지원안함
		if (strlen(user_name) < 1)
		{
			rewrite = 1;
			continue;
		}
		strcpy_s(player.name, sizeof(player.name), user_name);
		player.money = 10;

		if (user_name[0] == 81 || user_name[0] == 113)
		{
			gotoxy(40, 25);
			printf("Exiting program.....");
			exit(0);
		}
		break;
	}
}

//1. 게임을 시작할지 2. 저장된 기록을 볼 것인지
int menu()
{
	short x = 40, y = 22;
	char input;

	while (1)
	{
		decoration();
		gotoxy(x, y);
		printf("▶");
		gotoxy(43, 22);
		printf("Game start");
		gotoxy(43, 24);
		printf("record");
		gotoxy(43, 26);
		printf("exit");

		input = _getch();

		if (input == 72 || input == 80)
			move_arrow_key_modified(input, &x, &y, 26, 22);

		else if (input == 13) { //엔터의 아스키값은 13과 10이 결합한 형태, 즉 엔터 = \r(커서를 맨 앞으로 -- 13) + \n(커서를 다음 행으로 -- 10)
			if (y == 22)		return 1;
			else if (y == 24)	return 2;
			else				return 3;
		}

		else continue;
	}
}

//1. 오마하 홀덤을 할지 2. 세븐카드를 할지
int game_select()
{
	short x = 40, y = 25;
	char input;

	while (1)
	{
		decoration();
		gotoxy(40, 22);
		printf("Which game do you wannt play?");
		gotoxy(x, y);
		printf("▶");
		gotoxy(43, 25);
		printf("Omaha Holdem");
		gotoxy(43, 27);
		printf("Go Back");

		input = _getch();
		if (input == 72 || input == 80)
			move_arrow_key_modified(input, &x, &y, 27, 25);

		else if (input == 13) {
			switch (y)
			{
			//case 23: return 2; break;
			case 25: return 1; break;
			case 27: return -1; break;
			}
		}

		else continue;
	}
}

//저장된 기록들을 보여주는 함수
void record() {

	char input[50];
	char exit_code;
	int i, error = 0;;
	int line = 0;
	FILE* fp;

	while(1)
	{
		i = 5;
		system("cls");

		if (error == 1)
		{
			gotoxy(40, 27);
			printf("Input Error!");
		}

		if (fopen_s(&fp, "user_data.txt", "r"))
		{
			perror("[failed] poker.cpp >> record() >> fopen_s() : ");
			fclose(fp);
			exit(-1);
		}

		while(fgets(input, sizeof(input), fp) != NULL)
		{
			gotoxy(40, i++);
			printf("%s", input);
			memset(input, 0, sizeof(input));
		}

		gotoxy(40, 25);
		printf("Do you want to go back?(b/B) ");
		gotoxy(40, 26);
		printf(">> ");
		scanf_s(" %c", &exit_code, sizeof(exit_code));
		if(exit_code == 'b' || exit_code == 'B')
		{
			fclose(fp);
			break;
		}
		else {
			error = 1;
			continue;
		}
	}
}

void close()
{
	short x = 33, y = 24;
	char input;

	while (1)
	{
		decoration();
		gotoxy(30, 22);
		printf("Do you really want to exit?");
		gotoxy(x, y);
		printf("▶");
		gotoxy(37, 24);
		printf("yes");
		gotoxy(37, 26);
		printf("no");

		input = _getch();

		if (input == 72 || input == 80)
			move_arrow_key_modified(input, &x, &y, 26, 22);

		else if (input == 13) { //엔터의 아스키값은 13과 10이 결합한 형태, 즉 엔터 = \r(커서를 맨 앞으로 -- 13) + \n(커서를 다음 행으로 -- 10)
			if (y == 24)	exit(1);
			else        	break;
		}

		else continue;
	}
}

void show_boundary()
{
	gotoxy(18, 7);
	printf("*******************************************");
	gotoxy(16, 8);
	printf("*                                             *");
	gotoxy(15, 9);
	printf("*                                               *");
	gotoxy(14, 10);
	printf("*                                                 *");
	gotoxy(13, 11);
	printf("*                                                   *");
	gotoxy(12, 12);
	printf("*                                                     *");
	gotoxy(13, 13);
	printf("*                                                   *");
	gotoxy(14, 14);
	printf("*                                                 *");
	gotoxy(15, 15);
	printf("*                                               *");
	gotoxy(16, 16);
	printf("*                                             *");
	gotoxy(18, 17);
	printf("*******************************************");
}


//카드 변수들을 생성
void create_card(trump* card)
{
	int i, j;
	char shape[4][3] = { "♠", "♥", "♣", "◆" };

	for (i = 0; i < 4; i++)
	{
		for (j = i * 13; j < i * 13 + 13; j++)
		{
			card[j].order = i;
			strcpy_s(card[j].shape, shape[i]);
			card[j].number = j % 13 + 1;
		}
	}
}

//create_card함수로 생성된 카드들 섞기
void shuffle_card(trump* card)
{
	int i, rnd;

	srand((signed int)time(NULL));

	for (i = 0; i < 52; i++)
	{
		rnd = rand() % 52;
		shuffle_one_by_one(&card[rnd], &card[i]);
	}
}

//카드 두장을 바꾸는 swap함수
void shuffle_one_by_one(trump* card1, trump* card2)
{
	trump temp;

	temp = *card1;
	*card1 = *card2;
	*card2 = temp;
}

//카드 한장을 표시하는 함수
void display_card(short x, short y, const char* shape, int number)
{
	gotoxy(x, y);
	//omaha_holdem()내에서 조합할 카드를 선택할때 printf의 마지막 문자가 표시되지 않는 문제가 있었는데 뒤에 띄어쓰기를 더 쓰니 마지막 문자가 표시됨.
	printf("┌────┐ ");
	gotoxy(x, y + 1);
	printf("│%2s  │ ", shape);
	gotoxy(x, y + 2);
	printf("│    │ ");
	gotoxy(x, y + 3);
	if (number > 1 && number < 11) printf("│  %2d│ ", number);
	else if (number == 45) printf("│   -│ ");
	else if (number == 63) printf("│   ?│ ");
	else {
		switch (number)
		{
		case 1:
			printf("│   A│ ");
			break;
		case 11:
			printf("│   J│ ");
			break;
		case 12:
			printf("│   Q│ ");
			break;
		case 13:
			printf("│   K│ ");
			break;
		}
	}
	gotoxy(x, y + 4);
	printf("└────┘ ");
}

//숫자가 큰 순서대로 정렬하는 함수
void sort(trump* card)
{
	int i, j;

	for (i = 4; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (card[j].number > card[j + 1].number) shuffle_one_by_one(&card[j], &card[j + 1]);
		}
	}
}


//프로젝트 디렉토리에 파일을 생성하고 데이터 저장
void save()
{
	FILE* fp;
	time_t t = time(NULL);
	struct tm tm;

	//fopen_s는 오류값을 반환하고 0이면 성공, 다른 것은 실패
	if (fopen_s(&fp, "user_data.txt", "a")) {
		perror("[failed] fopen_s : ");
		fclose(fp);
		exit(-1);
	}

	localtime_s(&tm, &t); // 초 단위의 시간을 분리하여 구조체에 넣기

	fprintf(fp, "%d %d %d %s %d %hd\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, player.name, player.money, player.best_play);

	fclose(fp);
}

short numberShapeCompare(trump* opponent_card, trump* user_card, short opponent_point)
{
	switch (opponent_point)
	{
	case 8:
		if (opponent_card[4].number > user_card[4].number)
			return -1;
		else if (opponent_card[4].number < user_card[4].number)
			return 1;
		else
			return 0;
	}
}

//오마하 홀덤을 진행하는 함수
void omaha_holdem(int* opponent_choice, int* user_choice)
{
	int i, x;

	//trump구조체를 이용해서  카드구조체 배열생성
	create_card(card);

	//rnd는 상대가 선택할 카드를 랜덤으로 설정한 것을 저장하는 변수
	srand((signed int)time(NULL));
	while (1)
	{
		opponent_choice[0] = rand() % 4;
		opponent_choice[1] = rand() % 4;

		if (opponent_choice[0] != opponent_choice[1])
			break;
	}

	//카드 섞기
	shuffle_card(card);

	system("cls");

	//opponent card display
	for (i = 0, x = 20; i < 4; i++, x += 10)
		display_card(x, 1, "?", 63);

	//user card display
	for (i = 4, x = 20; i < 8; i++, x += 10)
	{
		gotoxy(x + 3, 19);
		printf("(%d)", i - 3);
		display_card(x, 20, card[i].shape, card[i].number);
	}

	gotoxy(70, 10);
	printf("Player money : %3d$", player.money);

	//중립카드와 상대방이 선택할 카드를 보일 때까지 남은 시간 출력
	for (i = 5; i >= 0; i--) {
		gotoxy(70, 13);
		printf("wait up to %d", i);
		Sleep(1000);
	}

	//중립카드 주변의 테두리 표시
	show_boundary();

	neutral_card[0] = card[8];
	neutral_card[1] = card[9];
	neutral_card[2] = card[10];

	//neutral card display
	for (i = 8, x = 25; i < 11; i++, x+=10)
		display_card(x, 10, card[i].shape, card[i].number);

	//opponent card display(2 of them visible, the rest invisible)
	for (i = 0, x = 20; i < 4; i++, x+=10)
	{
		if (opponent_choice[0] == i || opponent_choice[1] == i)
			setCardColor(RED, x, 1, "?", '?');
		else
			display_card(x, 1, card[i].shape, card[i].number);
	}

	gotoxy(65, 2);
	printf("<-- red cards are chosen ones!!!");

	while(1) {
		//첫 번째 카드 선택
		gotoxy(5, 25);
		printf("Write the number of your first card you want to use(1, 2, 3, 4) : ");
		scanf_s("%d", &user_choice[0]);

		//1~4의 범위를 벗어났을 때
		if (user_choice[0] < 1 || user_choice[0] > 4) {
			gotoxy(5, 26);
			printf("Range error occured!");
			continue;
		}

		//선택된 카드를 노란색으로 표현
		else {
			setCardColor(YELLOW, 20 + 10 * (user_choice[0] - 1), 20, card[user_choice[0] + 3].shape, card[user_choice[0] + 3].number);
			break;
		}
	}

	//두 번째 카드 선택
	while (1) {
		gotoxy(5, 27);
		printf("Write the number of your second card you want to use(1, 2, 3, 4) : ");
		scanf_s("%d", &user_choice[1]);

		if (user_choice[1] < 1 || user_choice[1] > 4) {
			gotoxy(5, 28);
			printf("<<range>> error occured!");
			continue;
		}

		if (user_choice[0] == user_choice[1]) {
			gotoxy(5, 28);
			printf("Redundancy error occured!");
			continue;
		}

		else {
			//선택한 두번째 카드를 노란색으로 표시
			setCardColor(YELLOW, 20 + 10 * (user_choice[1] - 1), 20, card[user_choice[1] + 3].shape, card[user_choice[1] + 3].number);
			return;
		}
	}
}

void omaha_holdem_betting(int* opponent_choice, int* user_choice, short* betting)
{
	int i, x;
	short x1 = 34, y1 = 26;
	char input;

	while (1)
	{
		system("cls");

		//user card display
		for (i = 4, x = 20; i < 8; i++, x+=10)
		{
			gotoxy(x + 3, 19);
			printf("(%d)", i - 3);
			display_card(x, 20, card[i].shape, card[i].number);
			if ((user_choice[0] + 1) == i || (user_choice[1] + 3) == i) {
				setCardColor(YELLOW, 20 + 10 * (user_choice[0] - 1), 20, card[user_choice[0] + 3].shape, card[user_choice[0] + 3].number);
				setCardColor(YELLOW, 20 + 10 * (user_choice[1] - 1), 20, card[user_choice[1] + 3].shape, card[user_choice[1] + 3].number);
			}
		}

		show_boundary();

		//neutral card display
		for (i = 8, x = 25; i < 11; i++, x+=10)
			display_card(x, 10, card[i].shape, card[i].number);

		//opponent card display(2 of them visible, the rest invisible)
		for (i = 0, x = 20; i < 4; i++, x+=10)
		{
			if (opponent_choice[0] == i || opponent_choice[1] == i)
				setCardColor(RED, x, 1, "?", '?');
			else
				display_card(x, 1, card[i].shape, card[i].number);
		}
		
		gotoxy(65, 2);
		printf("<-- red cards are chosen ones!!!");

		//사용자가 보유한 금액을 표시
		gotoxy(70, 10);
		printf("Player money : %3d$", player.money);

		//배팅할지 포기할지 선택
		gotoxy(25, 25);
		printf("Are you gonna bet or die?");
		gotoxy(37, 26);
		printf("bet");
		gotoxy(45, 26);
		printf("<-- (1) win : plus 1$ (2) draw : no change (3) lose : minus 1$");
		gotoxy(37, 28);
		printf("die");
		gotoxy(45, 28);
		printf("<-- if you choose die, you'll definitely lose 1$");
		gotoxy(49, 29);
		printf("unless both of you draws");
		gotoxy(x1, y1);
		printf("▶");

		input = _getch();
		if (input == 72 || input == 80)
			move_arrow_key_modified(input, &x1, &y1, 28, 26);

		else if (input == 13) //엔터의 아스키값은 13과 10이 결합한 형태, 즉 엔터 = \r(커서를 맨 앞으로 -- 13) + \n(커서를 다음 행으로 -- 10)
		{
			*betting = y1;
			return;
		}
	}
}

short omaha_holdem_result(int* opponent_choice, int* user_choice, trump* neutral_card, short y1)
{
	short opponent_point, user_point;
	trump opponent_card[5], user_card[5];
	char input;

	for (int i = 0; i < 2; i++)
	{
		opponent_card[i] = card[opponent_choice[i]];
		user_card[i] = card[user_choice[i] + 3];
		opponent_card[i] = card[opponent_choice[i]];
		user_card[i] = card[user_choice[i] + 3];
	}

	for (int i = 2; i < 5; i++)
	{
		opponent_card[i] = card[i + 6];
		user_card[i] = card[i + 6];
	}

	opponent_point = omaha_combinations(opponent_card);
	user_point = omaha_combinations(user_card);

	system("cls");

	//user card display
	for (int i = 4, x = 20; i < 8; i++, x+=10)
	{
		gotoxy(x + 3, 19);
		printf("(%d)", i - 3);
		display_card(x, 20, card[i].shape, card[i].number);
		if ((user_choice[0] + 1) == i || (user_choice[1] + 3) == i) {
			setCardColor(YELLOW, 20 + 10 * (user_choice[0] - 1), 20, card[user_choice[0] + 3].shape, card[user_choice[0] + 3].number);
			setCardColor(YELLOW, 20 + 10 * (user_choice[1] - 1), 20, card[user_choice[1] + 3].shape, card[user_choice[1] + 3].number);
		}
	}

	show_boundary();

	//neutral card display
	for (int i = 8, x = 15; i < 11; i++, x+=10)
		display_card(x, 10, card[i].shape, card[i].number);

	//opponent card display(2 of them visible, the others invisible)
	for (int i = 0, x = 20; i < 4; i++, x+=10)
	{
		if (opponent_choice[0] == i || opponent_choice[1] == i)
			setCardColor(RED, x, 1, card[i].shape, card[i].number);
		else
			display_card(x, 1, card[i].shape, card[i].number);
	}
	
	gotoxy(65, 2);
	printf("<-- red cards are chosen ones!!!");

	gotoxy(35, 30);
	printf("Go back[B]");

	gotoxy(25, 25);
	switch (opponent_point)
	{
	case 9:
		printf("Opponent >> Royal straight flush");
		break;
	case 8:
		printf("Opponent >> Straight flush");
		break;
	case 7:
		printf("Opponent >> Four of a kind");
		break;
	case 6:
		printf("Opponent >> Full house");
		break;
	case 5:
		printf("Opponent >> Flush");
		break;
	case 4:
		printf("Opponent >> Straight");
		break;
	case 3:
		printf("Opponent >> Three of a kind");
		break;
	case 2:
		printf("Opponent >> Two pair");
		break;
	case 1:
		printf("Opponent >> One pair");
		break;
	case 0:
		printf("Opponent >> High card(Nothing)");
		break;
	}

	gotoxy(25, 26);
	switch (user_point)
	{
	case 9:
		printf("User >> Royal straight flush");
		break;
	case 8:
		printf("User >> Straight flush");
		break;
	case 7:
		printf("User >> Four of a kind");
		break;
	case 6:
		printf("User >> Full house");
		break;
	case 5:
		printf("User >> Flush");
		break;
	case 4:
		printf("User >> Straight");
		break;
	case 3:
		printf("User >> Three of a kind");
		break;
	case 2:
		printf("User >> Two pair");
		break;
	case 1:
		printf("User >> One pair");
		break;
	case 0:
		printf("User >> High card(Nothing)");
		break;
	}
	
	gotoxy(25, 27);
	//상대방이 이길 경우
	if (opponent_point > user_point) {
		printf("Winner is \"computer\"!");
		setCardColor(BLUE, 45, 10, card[opponent_choice[0]].shape, card[opponent_choice[0]].number);
		setCardColor(BLUE, 55, 10, card[opponent_choice[1]].shape, card[opponent_choice[1]].number);

		//보유 금액 감소
		if (y1 == 26) player.money--;
	}

	//플레이어가 이길 경우
	else if (opponent_point < user_point) {
		printf("Winner is \"%s\"!", player.name);
		setCardColor(BLUE, 45, 10, card[user_choice[0] + 3].shape, card[user_choice[0] + 3].number);
		setCardColor(BLUE, 55, 10, card[user_choice[1] + 3].shape, card[user_choice[1] + 3].number);

		//보유 금액 증가
		if (y1 == 26) player.money++;
	}

	//양 플레이어가 비길 경우
	else if(opponent_point == user_point) {
		printf("Draw!!!");

		setCardColor(BLUE, 45, 10, "-", 45);
		setCardColor(BLUE, 55, 10, "-", 45);
	}

	player.best_play = user_point > player.best_play ? user_point:player.best_play;
	gotoxy(70, 10);
	printf("Player money : %3d$", player.money);

	//사용자 정보 저장(날짜, 시각, 이름, 금액)
	gotoxy(25, 28);
	printf("You wanna save?(y/n)");
	while (1) {
		scanf_s(" %c", &input, sizeof(input));
		if (input == 'y' || input == 'Y') {
			save();
			break;
		}

		else if (input == 'n' || input == 'N')
			break;

		else if (input == 'b' || input == 'B')
			return -1;

		else {
			gotoxy(40, 29);
			printf("Input Error!");
			continue;
		}
	}
	return 0;
}

//user는 +3해야함
int omaha_combinations(trump* card)
{
	short flush_flag = 0, straight_flag = 0, royal_flag = 0, three_of_a_kind_flag = 0;
	short four_of_a_kind_flag = 0, two_pair_flag = 0, one_pair_flag = 0, full_house_flag = 0;

	sort(card);

	flush_flag = flush(card);
	straight_flag = straight(card);
	royal_flag = royal(card);
	four_of_a_kind_flag = four_of_a_kind(card, &msFourkind);
	three_of_a_kind_flag = three_of_a_kind(card, &msThreekind);
	two_pair_flag = two_pair(card, msTwopair, three_of_a_kind_flag);
	one_pair_flag = one_pair(card, &msOnepair);
	full_house_flag = full_house(three_of_a_kind_flag, one_pair_flag, &msFullhouse);

	if (royal_flag && straight_flag && flush_flag) return 9;
	else if (straight_flag && flush_flag)		   return 8;
	else if (four_of_a_kind_flag)				   return 7;
	else if (full_house_flag)					   return 6;
	else if (flush_flag)						   return 5;
	else if (straight_flag)						   return 4;
	else if (three_of_a_kind_flag)				   return 3;
	else if (two_pair_flag)						   return 2;
	else if (one_pair_flag)						   return 1;
	else										   return 0;
}

void seven_card_stud()
{
	decoration();
	gotoxy(43, 22);
	printf("준비 중입니다.....");
	for (int i = 10; i >= 0; i--)
	{
		gotoxy(43, 24);
		printf("go back to menu until %2d", i);
		Sleep(1000);
	}
}

