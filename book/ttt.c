#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* rudimentary tic-tac-toe game in C */
int main()
{
	void init_game(void);
	void draw_game(void);
	void get_input(void);

	init_game();
	while (1) {
		draw_game();
		get_input();
	}
	return 0;
}

#define BOARD_HEIGHT 5
#define BOARD_WIDTH  5

char game_board[BOARD_HEIGHT][BOARD_WIDTH];
char game_status[BOARD_HEIGHT][BOARD_WIDTH];
int win;

/* init_game:  initializes game board and state */
void init_game(void)
{
	extern char game_board[][BOARD_WIDTH];
	extern char game_status[][BOARD_WIDTH];
	extern int win;
	int x,y;

	srand((unsigned int)time(NULL));
	for (y=0;y<BOARD_HEIGHT;y++)
		for (x=0;x<BOARD_WIDTH;x++)
			if (((x+1)%2) == 0)
				game_board[y][x] = '|';
			else if (((y+1)%2) == 0)
				game_board[y][x] = '-';
			else
				game_board[y][x] = ' ';

	for (y=0;y<BOARD_HEIGHT;y++)
		for (x=0;x<BOARD_WIDTH;x++)
			game_status[y][x] = 0;

	win = 0;
}

/* draw_game:  draws the game screen */
void draw_game(void)
{
	extern char game_board[][BOARD_WIDTH];
	extern char game_status[][BOARD_WIDTH];
	int x,y;

	for (y=0;y<BOARD_HEIGHT;y++) {
		for (x=0;x<BOARD_WIDTH;x++)
			if (game_status[y][x] == 1)
				putchar('X');
			else if (game_status[y][x] == 2)
				putchar('O');
			else
				putchar(game_board[y][x]);
		putchar('\n');
	}
}

/* set_game:  randomly generated game map */
void set_game(void)
{
	extern char game_status[][BOARD_WIDTH];
	int x,y;

	for (y=0;y<BOARD_HEIGHT;y++)
		for (x=0;x<BOARD_WIDTH;x++)
			if ((x%2) == 0 && (y%2) == 0)
				game_status[y][x] = (rand()%2)+1;
}

/* get_input:  used to get input from user; change game state */
void get_input(void)
{
	extern char game_status[][BOARD_WIDTH];
	int choice;
	int pos;
	int x,y;

	printf("1. X's\n2. O's\n"
			"Enter your choice: ");
	if (scanf("%d",&choice) != 1)
		return;
	if (choice == 0)
		exit(0);
	printf("Valid positions: 1, 2, 3, 4, 5, 6, 7, 8, 9.\n"
			"Enter choice: ");
	if (scanf("%d",&pos) != 1)
		return;
	if (pos == 0)
		exit(0);
	switch(pos) {
		case 1:
			x = 0;
			y = 0;
			break;
		case 2:
			x = 2;
			y = 0;
			break;
		case 3:
			x = 4;
			y = 0;
			break;
		case 4:
			x = 0;
			y = 2;
			break;
		case 5:
			x = 2;
			y = 2;
			break;
		case 6:
			x = 4;
			y = 2;
			break;
		case 7:
			x = 0;
			y = 4;
			break;
		case 8:
			x = 2;
			y = 4;
			break;
		case 9:
			x = 4;
			y = 4;
			break;
		default:
			printf("Invalid input... try again.\n");
	}
	if (game_status[y][x] == 0)
		game_status[y][x] = choice;
	else
		printf("That was already selected.\n");
	for (y=0;y<BOARD_HEIGHT;y++)
		for (x=0;x<BOARD_WIDTH;x++)
			if ((x%2) == 0 && (y%2) == 0)
				if ((x%2) == 0 && y == 0)
					if (game_status[y][x] == 1)
						win = 1;
					else if (game_status[y][x] == 2)
						win = 2;
					else
						win = 0;
	if (win == 1) {
		printf("X's won!\n");
		exit(0);
	} else if (win == 2) {
		printf("O's won!\n");
		exit(0);
	}
}
