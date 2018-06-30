#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	void init_game(void);
	void draw_game(void);
	void get_input(void);
/*	void set_game(void); */
	int i;

	init_game();
	i = 0;
	while (i < 3) {
		draw_game();
		get_input();
		i++;
	}
	return 0;
}

#define BOARD_HEIGHT 5
#define BOARD_WIDTH  5

char game_board[BOARD_HEIGHT][BOARD_WIDTH];
char game_status[BOARD_HEIGHT][BOARD_WIDTH];

void init_game(void)
{
	extern char game_board[][BOARD_WIDTH];
	extern char game_status[][BOARD_WIDTH];
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
}

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

void set_game(void)
{
	extern char game_status[][BOARD_WIDTH];
	int x,y;

	for (y=0;y<BOARD_HEIGHT;y++)
		for (x=0;x<BOARD_WIDTH;x++)
			if ((x%2) == 0 && (y%2) == 0)
				game_status[y][x] = (rand()%2)+1;
}

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
	printf("Valid positions: 1, 2, 3, 4, 5, 6, 7, 8, 9.\n"
			"Enter choice: ");
	if (scanf("%d",&pos) != 1)
		return;
	for (y=0;y<BOARD_HEIGHT;y++)
		for (x=0;x<BOARD_WIDTH;x++)
			if (x == (pos-1) && y == (pos-1))
				game_status[y+(pos-1)][x+(pos-1)] = choice;
}
