#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include"conio2.h"
#include <iostream>

#define PositionOfBoardX 80
#define PositionOfBoardY 3
#define PositionOfLegendX 6
#define PositionOfLegendY 5
#define PositionOfMenuX 45
#define PositionOfMenuY 12
#define EMPTY '*'
#define WHITEPLAYER 'W'
#define BLACKPLAYER 'B'
#define INSERT 0x69
#define EXIT 0x71
#define NEWGAME 0x6e
#define ENTER 0x0d
#define ESCAPE 0x1b
#define HANDICAP 0x68
#define LOAD 0x6c
#define SAVE 0x73
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

struct Board
{
	int size;			//the length of the arm of the square
	char** boardcp1;			//copy of board to know what how did it look like in previus turn
	char** boardcp2;			//copy of board to know what how did it look like two turns before
	char** board;			//Original board
};

void PrintLegend(int scorewhite, int scoreblack, int x, int y)			//Printing the legend during the Normal game
{
	int scorew = 0, scoreb = 0;
	char positions[12];
	char score1[16];			//array to store the text with white player score
	char score2[16];			//array to store the text with black player score
	gotoxy(PositionOfLegendX, PositionOfLegendY - 2);
	cputs("Created by Aleksander Blok s188865            ");
	gotoxy(PositionOfLegendX, PositionOfLegendY - 1);
	cputs("Points that have been done: a,b,c,d,e,f,g,h,k;");
	gotoxy(PositionOfLegendX, PositionOfLegendY);
	cputs("q:			quit the program;");
	gotoxy(PositionOfLegendX, PositionOfLegendY + 1);
	cputs("arrows:		moving the cursor over the board");
	gotoxy(PositionOfLegendX, PositionOfLegendY + 2);
	cputs("n:			start a new game");
	gotoxy(PositionOfLegendX, PositionOfLegendY + 3);
	cputs("i:			place a stone on the board");
	gotoxy(PositionOfLegendX, PositionOfLegendY + 4);
	sprintf(positions, "x: %d y: %d", x - PositionOfBoardX, y - PositionOfBoardY);
	cputs(positions);
	gotoxy(PositionOfLegendX, PositionOfLegendY + 5);
	sprintf(score1, "White score: %d", scorewhite);
	cputs(score1);
	gotoxy(PositionOfLegendX, PositionOfLegendY + 6);
	sprintf(score2, "Black score: %d", scoreblack);
	cputs(score2);
}

void PrintMenu()			//The menu which is printed at the beginning 
{
	gotoxy(PositionOfMenuX, PositionOfMenuY);
	cputs("n: Start a new game");
	gotoxy(PositionOfMenuX, PositionOfMenuY + 1);
	cputs("h: Start a new game with handicap");
	gotoxy(PositionOfMenuX, PositionOfMenuY + 2);
	cputs("l: Load the game");
}

void PrintConfirmation()			//The confiramtion to press the enter to initialize move
{
	gotoxy(PositionOfLegendX, PositionOfLegendY + 7);
	cputs("Press enter to confirm the move");
	gotoxy(PositionOfLegendX, PositionOfLegendY + 8);
	cputs("Press esc to cancel the move");
}

void PrintHandicapEnd()			//The information how to end handicap and start normal game
{
	gotoxy(PositionOfLegendX, PositionOfLegendY - 1);
	cputs("Created by Aleksander Blok s188865            ");
	gotoxy(PositionOfLegendX, PositionOfLegendY);
	cputs("Points that have been done: a,b,c,d,e,f,g,h,k;");
	gotoxy(PositionOfLegendX, PositionOfLegendY + 1);
	cputs("arrows:		moving the cursor over the board");
	gotoxy(PositionOfLegendX, PositionOfLegendY + 2);
	cputs("i:			place a stone on the board");
	gotoxy(PositionOfLegendX, PositionOfLegendY + 3);
	cputs("Press q to end the handicap");
}

void PrintMenu2()			//Menu for chossing the size of the board
{
	gotoxy(PositionOfMenuX, PositionOfMenuY);
	cputs("Chose size of the board:");
	gotoxy(PositionOfMenuX, PositionOfMenuY + 1);
	cputs("1. 9x9");
	gotoxy(PositionOfMenuX, PositionOfMenuY + 2);
	cputs("2. 13x13");
	gotoxy(PositionOfMenuX, PositionOfMenuY + 3);
	cputs("3. 19x19");
	gotoxy(PositionOfMenuX, PositionOfMenuY + 4);
	cputs("4. Your own");
}

void PrintSaveLoad()			//Asking for name of the file which sotres the data about the game or will store
{
	gotoxy(PositionOfMenuX, PositionOfMenuY);
	cputs("Please type the name of the file: ");
}

void CreateBoard(Board* b1)
{
	b1->board = new char* [b1->size];
	for (int i = 0; i < b1->size; i++)
		b1->board[i] = new char[b1->size];
}

void CreateBoardCp1(Board* b1)
{
	b1->boardcp1 = new char* [b1->size];
	for (int i = 0; i < b1->size; i++)
		b1->boardcp1[i] = new char[b1->size];
}

void CreateBoardCp2(Board* b1)
{
	b1->boardcp2 = new char* [b1->size];
	for (int i = 0; i < b1->size; i++)
		b1->boardcp2[i] = new char[b1->size];
}

void CopyBoard1(Board* b1, int turn)			//Function for copping board to execute KO rule
{
	if (turn < 1)
		return;
	if (turn == 1)			//Creating array in first turn because the copy is possible
		CreateBoardCp1(b1);
	for (int i = 0; i < b1->size; i++)
		for (int j = 0; j < b1->size; j++)
			b1->boardcp1[i][j] = b1->board[i][j];
}

void CopyBoard2(Board* b1, int turn)			//Function for copping board to execute KO rule
{
	if (turn < 2)
		return;
	if (turn == 2)			//Creating array in memory in second turn because the copy is possible
		CreateBoardCp2(b1);
	for (int i = 0; i < b1->size; i++)
		for (int j = 0; j < b1->size; j++)
			b1->boardcp2[i][j] = b1->boardcp1[i][j];
}

void LoadGame(Board* b1, int& scorewhite, int& scoreblack, int& turn)			//Loading the state of the game
{
	int l = 0;
	int turnn, size, scoreb, scorew;
	char name[100]{};
	for (int i = 0; i < 100; i++)
	{
		gotoxy(PositionOfMenuX + i, PositionOfMenuY + 1);			//getting the name of the file 
		name[i] = getch();
		if (name[i] == ENTER)			//pressing enter after typing the name of the file 
		{
			name[i] = NULL;			//attaching NULL value to enter character
			break;
		}
		putch(name[i]);
	}
	FILE* fp = fopen(name, "r");			//opening the file
	l = fscanf(fp, "%d %d %d %d ", &turn, &scorewhite, &scoreblack, &b1->size);			//getting data from the file 
	CreateBoard(b1);
	CreateBoardCp1(b1);
	CreateBoardCp2(b1);
	for (int i = 0; i < b1->size; i++)			//getting date about the board
		for (int j = 0; j < b1->size; j++)
			l = fscanf(fp, "%c", &b1->board[i][j]);
	for (int i = 0; i < b1->size; i++)
		for (int j = 0; j < b1->size; j++)
			l = fscanf(fp, "%c", &b1->boardcp1[i][j]);
	for (int i = 0; i < b1->size; i++)
		for (int j = 0; j < b1->size; j++)
			l = fscanf(fp, "%c", &b1->boardcp2[i][j]);
	fclose(fp);			//closing the file
}

void SaveGame(Board* b1, int scoreblack, int scorewhite, int turn)
{
	FILE* fp;
	char name[100]{};
	for (int i = 0; i < 100; i++)			//getting the name of the file 
	{
		gotoxy(PositionOfMenuX + i, PositionOfMenuY + 1);
		name[i] = getch();
		if (name[i] == ENTER)			//pressing enter after typing the name of the file 
		{
			name[i] = NULL;
			break;
		}
		putch(name[i]);
	}
	fp = fopen(name, "w");			//opening the file 
	fprintf(fp, "%i ", turn);			//printing data to the file 
	fprintf(fp, "%i ", scoreblack);
	fprintf(fp, "%i ", scorewhite);
	fprintf(fp, "%i ", b1->size);
	for (int i = 0; i < b1->size; i++)
		for (int j = 0; j < b1->size; j++)
			fprintf(fp, "%c", b1->board[i][j]);
	if (turn > 0)
	{
		for (int i = 0; i < b1->size; i++)
			for (int j = 0; j < b1->size; j++)
				fprintf(fp, "%c", b1->boardcp1[i][j]);
	}
	if (turn > 1)
	{
		for (int i = 0; i < b1->size; i++)
			for (int j = 0; j < b1->size; j++)
				fprintf(fp, "%c", b1->boardcp2[i][j]);
	}
	fclose(fp);			//closing the file
}

void FillBoard(Board* g1)
{
	for (int i = 0; i < g1->size; i++)
		for (int j = 0; j < g1->size; j++)
			g1->board[i][j] = EMPTY;
}

void PritnBoard(Board g1)
{
	for (int i = 0; i < g1.size; i++)
		for (int j = 0; j < g1.size; j++)
		{
			gotoxy(PositionOfBoardX + j, PositionOfBoardY + i);
			putch(g1.board[i][j]);
		}
}

void PrintBorder(Board g1)
{
	for (int i = 0; i <= g1.size + 1; i++)
		for (int j = 0; j <= g1.size + 1; j++)
		{
			gotoxy(PositionOfBoardX - 1 + i, PositionOfBoardY - 1 + j);
			if ((i == 0 || i == g1.size + 1) && j > 0 && j < g1.size + 1)
				putch('|');
			else if (j == 0 && i > 0 && i < g1.size + 1)
				putch('-');
			else if ((i == 0 || i == g1.size + 1) && (j == 0 || j == g1.size + 1))
				putch('+');
			else if (j == g1.size + 1 && i > 0 && i < g1.size + 1)
				putch('-');
		}
}

char WhoseTurn(int turn)
{
	char color;
	if (turn % 2 == 1)			//checking whose turn by modulo two 
		color = WHITEPLAYER;			//white player is second so when modulo two is one
	else
		color = BLACKPLAYER;			//black player is first so modulo two is zero
	return color;
}

char Opponent(int turn)			//contrary to previous function to establish who is opponent in particular turn
{
	char color;
	if (turn % 2 == 1)
		color = BLACKPLAYER;
	else
		color = WHITEPLAYER;
	return color;
}

char CheckRightCell(Board g1, int x, int y, int turn)			//Checking the neighbours
{
	if (x < g1.size - 1 && y < g1.size && y >= 0)
		return g1.board[y][x + 1];
	else
		return Opponent(turn);
}

char CheckLowerCell(Board g1, int x, int y, int turn)
{
	if (y < g1.size - 1 && x < g1.size && x >= 0)
		return g1.board[y + 1][x];
	else
		return Opponent(turn);
}

char CheckUpperCell(Board g1, int x, int y, int turn)
{
	if (y > 0 && x < g1.size && x >= 0)
		return g1.board[y - 1][x];
	else
		return Opponent(turn);
}

char CheckLeftCell(Board g1, int x, int y, int turn)
{
	if (x > 0 && y < g1.size && y >= 0)
		return g1.board[y][x - 1];
	else
		return Opponent(turn);
}

bool KoRulveApplication(Board b1, int x, int y ,int turn)			//Preventing the loop with KO rule
{
	if (turn < 2)
		return true;
	if (WhoseTurn(turn) == b1.boardcp2[y][x])			//checking if the player had placed in the same place in previus round
		return false;
	else
		return true;
}

bool CheckSuicide(Board g1, int x, int y, int turn)			//checking potential suicide by checking neighbours
{
	if (CheckLeftCell(g1, x, y, turn) == Opponent(turn)
		&& CheckRightCell(g1, x, y, turn) == Opponent(turn)
		&& CheckUpperCell(g1, x, y, turn) == Opponent(turn)
		&& CheckLowerCell(g1, x, y, turn) == Opponent(turn))
		return true;
	else
		return false;
}

bool CheckIfKill(Board g1, int x, int y, int turn)			//Checking if there is possibility to kill
{
	if (CheckLeftCell(g1, x, y, turn) == Opponent(turn)
		&& CheckLeftCell(g1, x - 1, y, turn) == WhoseTurn(turn)
		&& CheckUpperCell(g1, x - 1, y, turn) == WhoseTurn(turn)
		&& CheckUpperCell(g1, x - 1, y, turn) == WhoseTurn(turn)
		&& CheckLowerCell(g1, x - 1, y, turn) == WhoseTurn(turn))
		return true;

	else if (CheckRightCell(g1, x, y, turn) == Opponent(turn)
		&& CheckRightCell(g1, x + 1, y, turn) == WhoseTurn(turn)
		&& CheckUpperCell(g1, x + 1, y, turn) == WhoseTurn(turn)
		&& CheckLowerCell(g1, x + 1, y, turn) == WhoseTurn(turn))
		return true;
	else if (CheckUpperCell(g1, x, y, turn) == Opponent(turn)
		&& CheckRightCell(g1, x, y - 1, turn) == WhoseTurn(turn)
		&& CheckUpperCell(g1, x, y - 1, turn) == WhoseTurn(turn)
		&& CheckLeftCell(g1, x, y - 1, turn) == WhoseTurn(turn))
		return true;
	else if (CheckLowerCell(g1, x, y, turn) == Opponent(turn)
		&& CheckRightCell(g1, x, y + 1, turn) == WhoseTurn(turn)
		&& CheckLowerCell(g1, x, y + 1, turn) == WhoseTurn(turn)
		&& CheckLeftCell(g1, x, y + 1, turn) == WhoseTurn(turn))
		return true;
	else
		return false;
}

bool ValidationMove(Board g1, int x, int y, int turn)			//validation if the stone can be placed in the cell
{
	if (g1.board[y][x] == EMPTY
		&& (CheckSuicide(g1, x, y, turn) == false
			|| CheckIfKill(g1, x, y, turn) == true)
		&& KoRulveApplication(g1, x, y, turn) == true)
		return true;
	else
		return false;
}

void SearchKill(Board* g1, int& scorewhite, int& scoreblack, int turn)			//Searching for kills by scanning the array
{
	for (int i = 0; i < g1->size; i++)
		for (int j = 0; j < g1->size; j++)
		{
			if (g1->board[i][j] == WhoseTurn(turn)
				&& CheckSuicide(*g1, j, i, turn) == true)
			{
				g1->board[i][j] = EMPTY;
				if (WhoseTurn(turn) == WHITEPLAYER)
					scoreblack++;
				else
					scorewhite++;
			}
		}
}

bool ConfirmationOfMove()			//confirmation of the move
{
	int g = 1;
	do
	{
		g = getch();
		if (g == ENTER)			//if enter it is confirmed
			return true;
		else if (g == ESCAPE)			//if esc it is declined
			return false;
	} while (true);
}

int SetSize()			//setting the size of the board with length given by player
{
	char number[3]{};
	int boardsize;
	clrscr();
	gotoxy(PositionOfMenuX, PositionOfMenuY);
	cputs("Chose length of the board and press enter:");
	for (int i = 0; i < 3; i++)
	{
		gotoxy(PositionOfMenuX + i, PositionOfMenuY + 1);
		number[i] = getch();
		if (number[i] == ENTER)
			break;
		putch(number[i]);
	}
	boardsize = atoi(number);			//changing characters to inteagres
	return boardsize;
}

void ChoseBoardSize(Board* b1)			//chosing the board size
{
	int zn = 1;
	int boardsize = 19;
	clrscr();
	textbackground(YELLOW);
	textcolor(BLACK);
	PrintMenu2();
	zn = getch();
	if (zn == '1')			//Chosing the option from three deafults and one got from the player
		boardsize = 9;
	else if (zn == '2')
		boardsize = 13;
	else if (zn == '3')
		boardsize = 19;
	else if (zn == '4')
		boardsize = SetSize();
	b1->size = boardsize;
	CreateBoard(b1);
	for (int i = 0; i < b1->size; i++)
		for (int j = 0; j < b1->size; j++)
			b1->board[i][j] = EMPTY;
}

void DealocatingMemory(Board* g1)			//deleting all arrays
{
	for (int i = 0; i < g1->size; i++)
		delete[] g1->board[i];
	delete g1->board;
	for (int i = 0; i < g1->size; i++)
		delete[] g1->boardcp1[i];
	delete g1->boardcp1;
	for (int i = 0; i < g1->size; i++)
		delete[] g1->boardcp2[i];
	delete g1->boardcp2;
}

void Insert(Board* g1, int x, int y, int& turn)
{
	if (ValidationMove(*g1, x - PositionOfBoardX, y - PositionOfBoardY, turn) == true)				//checking if player can place his stone
	{
		PrintConfirmation();
		if (ConfirmationOfMove() == true)			//waiting for confiramtion from the player
		{
			g1->board[y - PositionOfBoardY][x - PositionOfBoardX] = WhoseTurn(turn);			//assigning the players sign to the cell
			turn++;			//incrementing turns to establish whose turn is it
			CopyBoard1(g1, turn);			//coping boards 
			CopyBoard2(g1, turn);
		}
	}
	else
		return;
}

void NormalGame(Board g1, int x, int y, int scoreblack, int scorewhite, int& turn)
{
	int zn = 1;
	do
	{
		clrscr();
		textbackground(YELLOW);			//setting background color
		textcolor(BLACK);			//setting the color of the text
		SearchKill(&g1, scorewhite, scoreblack, turn);
		PrintLegend(scorewhite, scoreblack, x, y);
		PritnBoard(g1);
		PrintBorder(g1);
		gotoxy(x, y);
		putch(WhoseTurn(turn));
		zn = getch();

		if (zn == UP && y > PositionOfBoardY)
			y--;
		else if (zn == DOWN && y < PositionOfBoardY + g1.size - 1)
			y++;
		else if (zn == LEFT && x > PositionOfBoardX)
			x--;
		else if (zn == RIGHT && x < PositionOfBoardX + g1.size - 1)
			x++;
		else if (zn == INSERT)
			Insert(&g1, x, y, turn);
		else if (zn == NEWGAME)			//restarting the game
		{
			FillBoard(&g1);
			turn = 0;
		}
		else if (zn == SAVE)			//saving the game
		{
			clrscr();
			PrintSaveLoad();
			SaveGame(&g1, scorewhite, scoreblack, turn);
		}
	} while (zn != EXIT);
	DealocatingMemory(&g1);
	clrscr();
	_setcursortype(_NORMALCURSOR);
}

void LoadedGame(Board g1, int x, int y, int& scoreblack, int& scorewhite, int& turn)			//the game when it is loaded from the file
{
	clrscr();
	PrintSaveLoad();
	LoadGame(&g1, scorewhite, scoreblack, turn);
	NormalGame(g1, x, y, scoreblack, scorewhite, turn);
}

void GameWithHandicap(Board g1, int x, int y, int scorewhite, int scoreblack, int turn)
{
	_setcursortype(_NOCURSOR);
	int zn = 1;
	do
	{
		clrscr();
		textbackground(YELLOW);
		textcolor(BLACK);
		PritnBoard(g1);
		PrintBorder(g1);
		PrintHandicapEnd();
		gotoxy(x, y);
		putch(BLACKPLAYER);
		zn = getch();

		if (zn == UP && y > PositionOfBoardY)
			y--;
		else if (zn == DOWN && y < PositionOfBoardY + g1.size - 1)
			y++;
		else if (zn == LEFT && x > PositionOfBoardX)
			x--;
		else if (zn == RIGHT && x < PositionOfBoardX + g1.size - 1)
			x++;
		else if (zn == INSERT)
		{
			PrintConfirmation();
			if (ConfirmationOfMove() == true)			//waitiing for confirmation from the player
				g1.board[y - PositionOfBoardY][x - PositionOfBoardX] = BLACKPLAYER;
		}
	} while (zn != EXIT);			//the handicap mode will be lopping until player will press e
	NormalGame(g1, x, y, scoreblack, scorewhite, turn);
	_setcursortype(_NORMALCURSOR);
}

int main() {
	Board g1{};
	int scorewhite = 0;			//Score for white player
	int scoreblack = 0;			//Score for black player
	int turn = 0;			//moves for black and white player that were done so far
	int zn = 1, x = PositionOfBoardX, y = PositionOfBoardY;
	settitle("Aleksander, Blok, 188865");
	textbackground(YELLOW);
	clrscr();
	textcolor(BLACK);
	PrintMenu();
	zn = getch();
	_setcursortype(_NOCURSOR);
	if (zn == HANDICAP)
	{
		ChoseBoardSize(&g1);
		GameWithHandicap(g1, x, y, scorewhite, scoreblack, turn);
	}
	else if (zn == NEWGAME)
	{
		ChoseBoardSize(&g1);
		NormalGame(g1, x, y, scoreblack, scorewhite, turn);
	}
	else if (zn == LOAD)
	{
		LoadedGame(g1, x, y, scorewhite, scoreblack, turn);
	}
	return 0;
}
