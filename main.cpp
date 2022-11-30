#include "trie.h"
using namespace std;



int main()
{
    const int w = 1024;
    const int h = 896;
    string queryFile="queries.txt";
    setConsoleWindow(w, h);
    fixConsoleWindow();
    loadingBoard();
    node* head = inputInfo();
    buildStopWordTrie();
    while (1)
    {
        bool exitFlag=false;
        while (1)
        {
            clrscr();
            searchBoard();
            char option = _getch();
            if (option == ESC)
            {
                exitFlag=true; break;
            }
            else if (option == ENTER)
                break;
            else if (option == TAB)
                historyBoard();
            else if (option == SPACE)
                updateBoard(head);
            else if (option == BACKSPACE)
                timeTest(head,queryFile);
        }
        if (exitFlag) break;
        //Input
        int l=21;
        int c = (137 - 70) / 2+3;
        gotoXY(c,l);
        unhidePointer();
        string input;
        getline(cin,input,'\n');
        if (input != "")
        {
            writeHistory(input);
        }
        else continue;
        vector<val> re;
        //if (input == "") break;
        if (checkString(input))
        re = _INPUT_(head,input);
        resultGeneral(input,re);
    }
    destroy(head);

    return 0;
}
