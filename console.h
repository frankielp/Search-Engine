

#ifndef _console_header
#define _console_header
#include "trie.h"

#define ColorCode_Back			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7


#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_none	-1

//--------------------------------------------------------
using namespace std;
//--------------------------------------------------------
int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)	// special key
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return key_none;
	}

	return key_none;
}


//-------------------------Screen-------------------------
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void fixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void setConsoleWindow(int w, int h)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, w, h, TRUE);
}
int wherex()
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.X;
}
int wherey()
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.Y;
}
void gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void hidePointer()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void unhidePointer()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void searchBoard()
{
    hidePointer();
    clrscr();
    int l = 1;
    int c = 5;
    TextColor(ColorCode_Pink);
    for (int i = 0; i <= 44; i++)
    {
        gotoXY(i, l + 6); cout << (char)196;
    }
    for (int i = 0; i <= 6; i++)
    {
        gotoXY(c + 39, i); cout << (char)186;
    }
    gotoXY(c+39, l+6); cout << (char)189;
    gotoXY(c, l++); cout << "ESC        : EXIT";
    gotoXY(c, l++); cout << "TAB        : VIEW SEARCH HISTORY";
    gotoXY(c, l++); cout << "ENTER      : SEARCHING";
    gotoXY(c, l++); cout << "SPACE      : UPDATE DATASET";
    gotoXY(c, l++); cout << "BACKSPACE  : RUNTIME CALCULATION";
    TextColor(ColorCode_Cyan);
    l = 10;
    c = (137 - 65) / 2;
    gotoXY(c, l++); cout << "                         _                        _            ";
    gotoXY(c, l++); cout << "                        | |                      (_)           ";
    gotoXY(c, l++); cout << " ___  ___  __ _ _ __ ___| |__     ___ _ __   __ _ _ _ __   ___ ";
    gotoXY(c, l++); cout << "/ __|/ _ \\/ _` | '__/ __| '_ \\   / _ \\ '_ \\ / _` | | '_ \\ / _ \\";
    gotoXY(c, l++); cout << "\\__ \\  __/ (_| | | | (__| | | | |  __/ | | | (_| | | | | |  __/";
    gotoXY(c, l++); cout << "|___/\\___|\\__,_|_|  \\___|_| |_|  \\___|_| |_|\\__, |_|_| |_|\\___|";
    gotoXY(c, l++); cout << "                                             __/ |             ";
    gotoXY(c, l++); cout << "                                            |___/              ";
    //search board
    l = 20;
    c = (137 - 70) / 2;
    for (int i = c; i <= c+70; i++)
    {
        gotoXY(i, l); cout << (char)196;
        gotoXY(i, l + 2); cout << (char)196;
    }
    for (int i = l; i <= l+2; i++)
    {
        gotoXY(c, i); cout << (char)186;
        gotoXY(c+70, i); cout << (char)186;
    }
    gotoXY(c, l); cout << (char)214;
    gotoXY(c, l+2); cout << (char)211;
    gotoXY(c+70, l); cout << (char)183;
    gotoXY(c+70, l+2); cout << (char)189;
    TextColor(ColorCode_White);
    gotoXY(c+21, l+4); cout << "Press ENTER to start searching";
    //instruction board
    l = 30;
    c = (137 - 75) / 2;
    for (int i = c; i <= c+75; i++)
    {
        gotoXY(i, l); cout << (char)196;
        gotoXY(i, l + 2); cout << (char)196;
        gotoXY(i, l + 9); cout << (char)196;
    }
    for (int i = l; i <= l+9; i++)
    {
        gotoXY(c, i); cout << (char)186;
        gotoXY(c+75, i); cout << (char)186;
    }
    gotoXY(c, l); cout << (char)214;
    gotoXY(c, l+9); cout << (char)211;
    gotoXY(c+75, l); cout << (char)183;
    gotoXY(c+75, l+9); cout << (char)189;
    //Instruction
    gotoXY(c+33, l+1); cout << "INSTRUCTION";
    l=33;
    gotoXY(c+4, l++); cout << "1. AND       : all chosen words";
    gotoXY(c+4, l++); cout << "2. OR        : one of chosen words";
    gotoXY(c+4, l++); cout << "3. A-B       : adjacent words";
    gotoXY(c+4, l++); cout << "4. IN TITLE: : name of file";
    gotoXY(c+4, l++); cout << "5. +         : search sentence";
    gotoXY(c+4, l++); cout << "6. FILETYPE: : type of file";
    l=33;
    gotoXY(c+40, l++); cout << "7.  $        : price";
    gotoXY(c+40, l++); cout << "8.  #        : hashtag";
    gotoXY(c+40, l++); cout << "9.  \"\"       : exact words";
    gotoXY(c+40, l++); cout << "10. *        : unknown words";
    gotoXY(c+40, l++); cout << "11. A..B     : range of numbers";
    gotoXY(c+40, l++); cout << "12. ~        : synonyms";
    
}
void resultBoard(string input)
{
    clrscr();
    hidePointer();
    int l = 1;
    int c = 5;
    for (int i = 5; i <= 103; i++)
    {
        gotoXY(i, l); cout << (char)196;
        gotoXY(i, l + 2); cout << (char)196;
    }
    for (int i = l; i <= l+2; i++)
    {
        gotoXY(5, i); cout << (char)186;
        gotoXY(103, i); cout << (char)186;
    }
    gotoXY(5, l); cout << (char)214;
    gotoXY(5, l+2); cout << (char)211;
    gotoXY(103, l); cout << (char)183;
    gotoXY(103, l+2); cout << (char)189;
    gotoXY(8, l+3); cout << "Press ESC to turn back or press the number of document order to read data";
    l = 1;
    c = 5;
    int width=95;
    int i,t;
    gotoXY(c+3,l+1);
    for(i=0;i<min((int)input.size(),90);i++) cout<<input[i];
    if (i!=input.size()) cout<<"...";
}

void historyBoard()
{
    clrscr();
    hidePointer();
    int l = 4;
    int c = (137 - 75) / 2;
    for (int i = c; i <= c + 75; i++)
    {
        gotoXY(i, l); cout << (char)196;
        gotoXY(i, l + 2); cout << (char)196;
        gotoXY(i, l + 40); cout << (char)196;
    }
    for (int i = l; i <= l + 40; i++)
    {
        gotoXY(c, i); cout << (char)186;
        gotoXY(c + 75, i); cout << (char)186;
    }
    gotoXY(c, l); cout << (char)214;
    gotoXY(c, l + 40); cout << (char)211;
    gotoXY(c + 75, l); cout << (char)183;
    gotoXY(c + 75, l + 40); cout << (char)189;
    gotoXY(c + 35, l + 1); cout << "HISTORY";
    ifstream ifs;
    ifs.open("history.txt");
    int line=l+3;
    while (!ifs.eof()&&line<l+40)
    {
        string str;
        getline(ifs,str,'\n');
        gotoXY(c + 10, line); cout << str;
        line++;
    }
    ifs.close();
    if (line==l+3)
    {gotoXY(c + 10, l + 3); cout << "No search history found!";}
    TextColor(ColorCode_Cyan);
    gotoXY(1, 1); cout << "ESC: BACK";
     while (1)
        {
            char BACK = _getch();
            if (BACK == ESC)
                return;
        }
}
void loadingBoard()
{
    clrscr();
    int l = 10;
    int c = (137 - 12) / 2;
    string path;
    gotoXY(c,l);cout<<"Loading.....";
}
#endif
