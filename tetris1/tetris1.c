﻿

#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <ctype.h>

#include <stdbool.h>

#include "ListOfFigures.h"


#define TRUE 1
#define FALSE 0

#define VerticalFrameOfPitch   177
#define BottomFrameOfPitch 176
#define TopFrameOfPitch 177
#define EmptySpace 0
#define Figure 2

#define FMAP_COUNTS 7 
#define ColumnsCount  12
#define RowsCount  22
#define SCR_OB  '\xFE' 

/*GDI +
SDL
*/
//характеристики поля

const int NewFigure = '0';
//символы заполнения (в define)
//const unsigned char VerticalFrameOfPitch = 177;
//const unsigned char BottomFrameOfPitch = 177;
//const unsigned char EmptySpace = 0;

const unsigned char LevelData0[22][13] = //поле игры
{
	"============",
	"X##########X",
	"X##########X",
	"X##########X",
	"X####0#####X",
	"X##########X",
	"X##########X",
	"X##########X",
	"X##########X",
	"X##########X",
	"X##########X",
	"X##########X",
	"X##########X",
	"X##########X",
	"X##########X",
	"X##########X",
	"X##########X",
	"X##########X",
	"X##########X",
	"X##########X",
	"X##########X",
	"============",

};

int screen[RowsCount][ColumnsCount] = { 0 }; //размер экрана
int map[4][4]; //фигура
int px, py, score, nextmap;

int fmap[FMAP_COUNTS][4][4] = // инициализация фигур тетриса
{
	{
		{ 1, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 }
	},
	{
		{ 0, 0, 1, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 1, 1, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 1, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 1, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	}
};
//условие продолжения игры
bool IsGameActive = true;
 unsigned char LevelData[22][12];
 int FigureRow = 0;
 int FigureColumn = 0;

 HANDLE consoleHandle = 0;

void SetupSystem() // общие организационные действия.Например: задание зерна генератору случайных чисел.
{
	srand(time(0));
	
	COORD scrn;
	consoleHandle = GetStdHandle (STD_OUTPUT_HANDLE);


}

void Initialise() // Инициализация вводимых данных, представленных в виде программного кода,
{

	for (int r = 0; r < RowsCount; r++)
	{
		for (int c = 0; c < ColumnsCount; c++)
		{
			unsigned char symbol = LevelData0[r][c];
			switch (symbol)
			{
			case 'X':
			{

				LevelData[r][c] = VerticalFrameOfPitch;
				break;
			}

			case '=':
			{
				LevelData[r][c] = BottomFrameOfPitch;
				break;
			}
			case '#':
			{

				LevelData[r][c] = EmptySpace;
				break;
			}
			case '0':


			{


				{
					LevelData[r][c] = Figure;
					FigureRow = r;
					FigureColumn = c;




					break;
				}

			}
			}
		}
	}
}



void MoveTo(int row, int column)

{
	unsigned char destinationCell = LevelData[row][column];
	bool canMoveToCell = true;
	switch (destinationCell)
	{
	case EmptySpace:
	{	canMoveToCell = true;
	break;
	}
	case BottomFrameOfPitch:
	{
		canMoveToCell = false;
		//CreateNewFigure(Figure);
		break;
	}
	case VerticalFrameOfPitch:
	{
		canMoveToCell = false;
		break;
	}
	}

	if (canMoveToCell)
	{
		LevelData[FigureRow][FigureColumn] = ' ';
		FigureRow = row;
		FigureColumn = column;

		LevelData[FigureRow][FigureColumn] = Figure;
	}

}

void CreateNewFigure(Newfigure)
{

}


void Render() // осуществление графического вывода основного цикла игры на экран.
{
	COORD CursorCoord;
	CursorCoord.X = 0;
	CursorCoord.Y = 0;
	SetConsoleCursorPosition(consoleHandle, CursorCoord);


	printf("\n\n\t");
	for (int r = 0; r < RowsCount; r++)
	{
		for (int c = 0; c < ColumnsCount; c++)
		{
			unsigned char symbol = LevelData[r][c];

			switch (symbol)
			{
			case VerticalFrameOfPitch:
			{
				SetConsoleTextAttribute(consoleHandle, 5);
				break;
			}
			case BottomFrameOfPitch:
			{
				SetConsoleTextAttribute(consoleHandle, 5);
				break;
			}
			case EmptySpace:
			{
				SetConsoleTextAttribute(consoleHandle, 6);
				break;
			}
			case Figure:
			{
				SetConsoleTextAttribute(consoleHandle, 7);
				break;
			}


			}

			printf("%c", symbol);
		}
		printf("\n\t");


	}
	if (Figure == BottomFrameOfPitch)
	{
		CreateNewFigure(NewFigure);
	}
}




void Update() // основная логика игры.
{
	unsigned char inputChar = _getch();
	inputChar = tolower (inputChar) ;

	switch (inputChar)
	{
	case 'w':
		{
		MoveTo(FigureRow - 1, FigureColumn);
		break;
		}
	case 'd':
	{
		MoveTo(FigureRow , FigureColumn+1);
		break;
	}
	case 's':
	{
		MoveTo(FigureRow+1, FigureColumn );
		break;
	}
	case 'a':
	{
		MoveTo(FigureRow, FigureColumn - 1);
		break;
	}
	case 'r':
	{
		
		Initialise();
		break;
	}
	case 'i':
	{
		printf("you are stupid");
		break;
	}
	}
}
void Shutdown()
{
	
	printf("\n Press any key to continue...");
	_getch();
}



int Graphics()
{
	
	return 0;
}


int main()
{
	Graphics();
	SetupSystem();

	Initialise();
	
	do
	{
		Render();
		Update();
	} 
	while (IsGameActive);

	Shutdown();

	return 0;
}