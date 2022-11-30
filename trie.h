#ifndef ___HELPER___
#define ___HELPER___
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>  
#include <iomanip>
using namespace std;

const string searchFolder = "Search Engine-Data/";
const string fileList = searchFolder + "___index.txt";
const int characterUsed = 95;
const string stopWordFile = "stopWordFile.txt";
const int topSearch = 5;

struct val
{
    string filename;
    vector<int> pos;

    val(){}
};

struct node
{
    node** elements = nullptr;
    vector<val> data;

    ~node()
    {
        if (elements != nullptr)
        {
            for (int i = 0; i < characterUsed; i++)
                delete elements[i];
            delete[] elements;
        }
    }
};
#define ESC     27
#define ENTER   13
#define TAB     9
#define SPACE   32
#define BACKSPACE 8
node* stopWordls = nullptr;
#include "console.h"
#include "trieFunc.h"
#include "utils.h"
#include "3711.h"
#include "159.h"
#include "2610.h"
#include "4812.h"
#include "inout.h"
#endif
