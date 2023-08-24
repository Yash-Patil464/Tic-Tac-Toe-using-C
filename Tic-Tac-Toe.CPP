#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <dos.h>

#define d 35
#define s 30
#define f 200
#define mx getmaxx()
#define my getmaxy()

char grid[3][3];
int key();
void display(int, int);
int win(int, int, int);
int draw(int, int);
void end(char *);
void menu();
void loading_scr();

void main()
{
	int gd, gm, sx = 0, sy = 0, i, j, k, c = 2, player;
	char str[30], ch;
	detectgraph(&gd, &gm);
	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	menu();
	loading_scr();
	cleardevice();
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			grid[i][j] = ' ';

	printf("\n\n\nInstructions : \nPress WASD or Arrow keys to move the cursor.\nPress Spacebar or Enter key to enter X or O on the grid.\nPress E to Exit the Game.\n\n\tPress Enter to start the Game");
	getch();

	settextstyle(1, 0, 2);

	while (1)
	{
		cleardevice();
		setcolor(WHITE);
		outtextxy(200, 100, "TIC-TAC-TOE");
		outtextxy(210, 150, "Press E to Exit");
		player = c % 2;
		sprintf(str, "Player : %d (%c)", player + 1, player ? 'O' : 'X');
		setcolor(WHITE);
		outtextxy(350, 250, str);
		display(sx, sy);
		ch = key();
		switch (ch)
		{
		case 'W':
		case 'w':
		case 72: // up
			if (sy != 0)
				sy--;
			break;

		case 'S':
		case 's':
		case 80: // down
			if (sy != 2)
				sy++;
			break;

		case 'A':
		case 'a':
		case 75: // left
			if (sx != 0)
				sx--;
			break;

		case 'D':
		case 'd':
		case 77: // right
			if (sx != 2)
				sx++;
			break;

		case 13:
		case ' ':
			if (grid[sy][sx] == ' ')
			{
				if (player == 0)
					grid[sy][sx] = 'X';
				else
					grid[sy][sx] = 'O';
				c++;
			}
			break;

		case 'e':
		case 'E':
			cleardevice();
			closegraph();
			return;

		default:
			break;
		}
		if (win(sx, sy, player) == 1 || draw(sx, sy) == 1)
			break;
	}
	return;
}

int key()
{
	int ch;
	ch = getch();
	if (ch == 0)
	{
		ch = getch();
		return (ch);
	}
	return (ch);
}

void display(int sx, int sy)
{
	int i, j;
	char str[2];
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (j == sx && i == sy)
				setcolor(GREEN);
			else
				setcolor(WHITE);

			rectangle(j * d + f, i * d + f, j * d + s + f, i * d + s + f);
			sprintf(str, "%c", grid[i][j]);
			outtextxy(j * d + 8 + f, i * d + 8 + f, str);
		}
	}
}

int win(int sx, int sy, int player)
{
	char str[25];
	int i, j;
	for (i = 0; i < 3; i++)
	{
		if ((grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] && grid[i][0] != ' ') || (grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i] && grid[0][i] != ' '))
		{
			display(sx, sy);
			getch();
			sprintf(str, "Player %d (%c) You won!!!", player + 1, player ? 'O' : 'X');
			end(str);
			delay(100);
			return (1);
		}
		if ((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[2][2] != ' ') || (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[2][0] != ' '))
		{
			display(sx, sy);
			getch();
			sprintf(str, "Player %d (%c) You won!!!", player + 1, player ? 'O' : 'X');
			end(str);
			delay(100);
			return (1);
		}
	}
	return (0);
}

int draw(int sx, int sy)
{
	int i, j, k = 0;
	char str[25];
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			if (grid[i][j] != ' ')
				k++;
	if (k == 9)
	{
		display(sx, sy);
		getch();
		sprintf(str, "The game is a draw!!!");
		end(str);
		return (1);
	}
	return (0);
}

void end(char *str)
{
	int i, j;
	delay(900);
	cleardevice();
	setcolor(WHITE);
	outtextxy(mx / 2 - 150, my / 2, str);

	getch();
	closegraph();
	return;
}

void menu()
{
	cleardevice();
	setcolor(2);
	settextstyle(1, 0, 5);
	outtextxy(175, 200, " TIC-TAC-TOE ");

	setcolor(7);
	settextstyle(1, 0, 1);
	outtextxy(218, 300, "PRESS ANY KEY TO START");

	getch();
}

void loading_scr()
{
	cleardevice();
	int z;
	setcolor(WHITE);
	for (z = 35; z < 555; z++)
	{
		line(25 + z, 170, 25 + z, 200);
	}
	for (z = 35; z < 555; z++)
	{
		setcolor(GREEN);
		line(25 + z, 170, 25 + z, 200);
		delay(10);

		setcolor(WHITE);
		settextstyle(SMALL_FONT, 0, 16);
		outtextxy(220, 220, "LOADING...");
		delay(10);
	}
	getch();
}
