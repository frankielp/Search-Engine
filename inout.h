#ifndef __INOUT__
#define __INOUT__
#include "trie.h"
#include <set>

vector<val> _INPUT_(node* head, string input)
{
    if (input[0] == input[input.size() - 1] && input[0] == 34)// "VU LAN" op9   
    {
        input.erase(input.begin());
        input.pop_back();
        return _EXACT_(head, input);
    }
    else if (input[0] == '#')// #hagtag op8)
    {
        return _NOTEXACT_(head, input);
    }
    else if (input[0] == '~')// ~set op12
    {
        input.replace(0, 1, "");
        return _SYNONYM_(head, toLower(input));
    }
    else if (input[0] == '+')// +washing machine and cellphone op5
    {
        input.erase(input.begin());
        return _NOTEXACT_(head, input);
    }
    else if (input.find("FILETYPE: ") == 0)// FILETYPE: .txt op6
    {
        input.replace(0, 10, "");
        return _FILETYPE_(head, input);
    }
    else if (input.find("IN TITLE: ") != string::npos)// IN TITLE: coolest things op4
    {
        input.replace(0, 10, "");
        return _INTITLE_(head, input);
    }
    else if (input.find(" * ") != string::npos)// vu * celebration op10
    {
        return _UNKNOW_(head, input);
    }
    else if (input.find(" AND ") != string::npos)// washing machine AND cellphone op1
    {
        return _AND_(head, input);
    }
    else if (input.find(" OR ") != string::npos)// washing machine OR cellphone op2
    {
        return _OR_(head, input);
    }
    else if (input.find("-") != string::npos)// adjacent op4
    {
        while(input.find("-") != string::npos)
        {
            int pos = input.find("-");
            input.replace(pos, 1," ");
        }
        return searchAdjacent(head,input);
    }
    else if (input.find("..") != string::npos)// range
    {
        int pos = input.find("..");
        input.replace(pos, 2, " ");
        return searchRange(head,input);
    }
    else if (input.find("$") != string::npos)// search price
    {
        return searchPrice(head,input);
    }
    else// normal search
    {
        vector<string> word = Split(input);
        vector<val> re;
        for (int i = 0; i < word.size(); i++)
            re = combine(re, search_notExact(head, word[i]));
        return rankSort(re);
    }
}

void result (string input,vector<val>re)
{

    int l = 1;
    int c = 5;
    int width=95;
    int i,t;
    l=8;
    if (re.size()==0) 
    {
        gotoXY(c+3,l); cout<<"Your search did not match any documents.";
        l+=2;
        gotoXY(c+3,l); cout<<"Suggestions:";
        l+=2;
        gotoXY(c+3,l++); cout<<"- Make sure that all words are spelled correctly.";
        gotoXY(c+3,l++); cout<<"- Try different keywords.";
        gotoXY(c+3,l++); cout<<"- Try more general keywords.";
        gotoXY(c+3,l++); cout<<"- Try fewer keywords.";
        return;
    }
    for (i=0; i < min(topSearch ,(int)re.size()); i++)
    {
        TextColor(ColorCode_Blue);
        gotoXY(c+3,l++); cout<<re[i].filename;
        TextColor(ColorCode_White);
        ifstream ifs;
        ifs.open(searchFolder+re[i].filename);

        //skip words
        int current=0;
        string word;
        while(current<max((int)re[i].pos[0]-100,0))
        {
            ifs>>word;
            current+=1+word.size();
        }
        //int posData=re[i].pos[0]-current;
        //read line
        string data;
        while(current<re[i].pos[0]+100&&!ifs.eof())
        {
            ifs>>word;
            current+=1+word.size();
            data+=word+" ";
        }
        gotoXY(c+3,l++); 
        ifs.close();
        //print
        int curData=0;
        while(curData<data.length())
        {
            int curLine=0;
            gotoXY(c+3,l++); 
            for (curLine=0;curLine<width-1&&curData<data.length();curLine++)
            {   
                if (data[curData]==' '||curData==0)
                {
                    string curWord="";
                    int curPos;
                    if(curData==0) curPos=curData;
                    else curPos=curData+1;
                    while (data[curPos]!=' '&&curPos<data.length())
                    {
                        if (!isSplitWord(data[curPos]))
                        curWord+=data[curPos];
                        curPos++;
                    }
                    input=toLower(input);
                    curWord=toLower(curWord);
                    if (!isStopWord(curWord)&&input.find(curWord)!= string::npos)
                    TextColor(ColorCode_Pink);
                    else
                    TextColor(ColorCode_White);
                }
                cout<<data[curData++];
            }
                if (curData<data.length()&&data[curData]!=' ')
                    cout<<'-';
                else cout<<data[curData++];
        }
        l+=3;
        
    }
    
}

void resultNoHighlight (string input,vector<val>re)
{
    int l = 1;
    int c = 5;
    int width=95;
    int i,t;
    l=8;
    if (re.size()==0) 
    {
        gotoXY(c+3,l); cout<<"Your search did not match any documents.";
        l+=2;
        gotoXY(c+3,l); cout<<"Suggestions:";
        l+=2;
        gotoXY(c+3,l++); cout<<"- Make sure that all words are spelled correctly.";
        gotoXY(c+3,l++); cout<<"- Try different keywords.";
        gotoXY(c+3,l++); cout<<"- Try more general keywords.";
        gotoXY(c+3,l++); cout<<"- Try fewer keywords.";
        return;
    }
    for (i=0; i < min(topSearch ,(int)re.size()); i++)
    {
        TextColor(ColorCode_Blue);
        gotoXY(c+3,l++); cout<<re[i].filename;
        TextColor(ColorCode_White);
        ifstream ifs;
        ifs.open(searchFolder+re[i].filename);

        //skip words
        int current=0;
        string word;
        while(current<max((int)re[i].pos[0]-100,0))
        {
            ifs>>word;
            current+=1+word.size();
        }
        //int posData=re[i].pos[0]-current;
        //read line
        string data;
        while(current<re[i].pos[0]+100&&!ifs.eof())
        {
            ifs>>word;
            current+=1+word.size();
            data+=word+" ";
        }
        gotoXY(c+3,l++); 
        ifs.close();
        //print
        int curData=0;
        while(curData<data.length())
        {
            int curLine=0;
            gotoXY(c+3,l++); 
            for (curLine=0;curLine<width-1&&curData<data.length();curLine++)
            {   
                cout<<data[curData++];
            }
                if (curData<data.length()&&data[curData]!=' ')
                    cout<<'-';
                else cout<<data[curData++];
        }
        l+=3;
        
    }
    
}

void resultExact (string input,vector<val>re)
{
    
    int l = 1;
    int c = 5;
    int width=95;
    int i,t;
    l=8;
    if (re.size()==0) 
    {
        gotoXY(c+3,l); cout<<"Your search did not match any documents.";
        l+=2;
        gotoXY(c+3,l); cout<<"Suggestions:";
        l+=2;
        gotoXY(c+3,l++); cout<<"- Make sure that all words are spelled correctly.";
        gotoXY(c+3,l++); cout<<"- Try different keywords.";
        gotoXY(c+3,l++); cout<<"- Try more general keywords.";
        gotoXY(c+3,l++); cout<<"- Try fewer keywords.";
        return;
    }
    //REsult
    vector<string>inputWords=Split(input);
    set<string>inputSet;
    for (auto &word:inputWords)
    inputSet.insert(toLower(word));
    for (i=0; i < min(topSearch ,(int)re.size()); i++)
    {
        TextColor(ColorCode_Blue);
        gotoXY(c+3,l++); cout<<re[i].filename;
        TextColor(ColorCode_White);
        ifstream ifs;
        ifs.open(searchFolder+re[i].filename);

        //skip words
        int current=0;
        string word;
        while(current<max((int)re[i].pos[0]-100,0))
        {
            ifs>>word;
            current+=1+word.size();
        }
        int posData=re[i].pos[0]-current;
        //read line
        string data;
        while(current<re[i].pos[0]+100&&!ifs.eof())
        {
            ifs>>word;
            current+=1+word.size();
            data+=word+" ";
        }
        gotoXY(c+3,l++); 
        ifs.close();
        //print
        int curData=0;
        while(curData<data.length())
        {
            int curLine=0;
            gotoXY(c+3,l++); 
            for (curLine=0;curLine<width-1&&curData<data.length();curLine++)
            {   
                if (data[curData]==' '||curData==0)
                {
                    string curWord="";
                    int curPos;
                    if(curData==0) curPos=curData;
                    else curPos=curData+1;
                    while (data[curPos]!=' '&&curPos<data.length())
                    {
                        if (!isSplitWord(data[curPos]))
                        curWord+=data[curPos];
                        curPos++;
                    }
                    input=toLower(input);
                    curWord=toLower(curWord);
                    if (inputSet.count(curWord)||curData==posData)
                    TextColor(ColorCode_Pink);
                    else
                    TextColor(ColorCode_White);
                }
                cout<<data[curData++];
            }
                if (curData<data.length()&&data[curData]!=' ')
                    cout<<'-';
                //else cout<<data[curData++];
        }
        l+=3;
        
    }
     
}
void resultSentence (string input,vector<val>re)
{
    int l = 1;
    int c = 5;
    int width=95;
    int i,t;
    l=8;
    if (re.size()==0) 
    {
        gotoXY(c+3,l); cout<<"Your search did not match any documents.";
        l+=2;
        gotoXY(c+3,l); cout<<"Suggestions:";
        l+=2;
        gotoXY(c+3,l++); cout<<"- Make sure that all words are spelled correctly.";
        gotoXY(c+3,l++); cout<<"- Try different keywords.";
        gotoXY(c+3,l++); cout<<"- Try more general keywords.";
        gotoXY(c+3,l++); cout<<"- Try fewer keywords.";
       return;
    }

    for (i=0; i < min(topSearch ,(int)re.size()); i++)
    {
        TextColor(ColorCode_Blue);
        gotoXY(c+3,l++); cout<<re[i].filename;
        TextColor(ColorCode_White);
        ifstream ifs;
        ifs.open(searchFolder+re[i].filename);

        //skip words
        int current=0;
        string word;
        while(current<max((int)re[i].pos[0]-100,0))
        {
            ifs>>word;
            current+=1+word.size();
        }
        int posData=re[i].pos[0]-current;
        //read line
        string data;
        while(current<re[i].pos[0]+100&&!ifs.eof())
        {
            ifs>>word;
            current+=1+word.size();
            data+=word+" ";
        }
        gotoXY(c+3,l++); 
        ifs.close();
        //print
        int curData=0;
        while(curData<data.length())
        {
            int curLine=0;
            gotoXY(c+3,l++); 
            for (curLine=0;curLine<width-1&&curData<data.length();curLine++)
            {   
                
                if (curData>=posData&&curData<=posData+input.size())
                    TextColor(ColorCode_Pink);
                else
                    TextColor(ColorCode_White);
                cout<<data[curData++];
            }
                if (curData<data.length()&&data[curData]!=' ')
                    cout<<'-';
                else cout<<data[curData++];
        }
        l+=3;
        
    }
    
}
void resultAdjacent (string input,vector<val>re)
{
    for (int i=0;i<input.size();i++)
    {
         if (input[i]==' '||i==0)
                {
                    string curWord="";
                    int curPos;
                    if(i==0) curPos=i;
                    else curPos=i+1;
                    while (input[curPos]!=' '&&curPos<input.length())
                    {
                        curWord+=input[curPos];
                        curPos++;
                    }
                    if(isStopWord(toLower(curWord)))
                    {
                        while(input==curWord||input.find(curWord+" ") != string::npos||input.find(" "+curWord) != string::npos)
                        {
                            int pos;
                            if (input==curWord)
                                pos=input.find(curWord);
                            else if (input.find(curWord+" ") != string::npos)
                                {
                                    pos=input.find(curWord+" ");
                                    curWord+=" ";
                                }
                            else if (input.find(" "+curWord) != string::npos)
                                {
                                    pos=input.find(" "+curWord);
                                    curWord+=" ";
                                }
                            input.replace(pos,curWord.size(),"");
                        }
                    }
                }
    }
    int l = 1;
    int c = 5;
    int width=95;
    int i,t;
    l=8;
    if (re.size()==0) 
    {
        gotoXY(c+3,l); cout<<"Your search did not match any documents.";
        l+=2;
        gotoXY(c+3,l); cout<<"Suggestions:";
        l+=2;
        gotoXY(c+3,l++); cout<<"- Make sure that all words are spelled correctly.";
        gotoXY(c+3,l++); cout<<"- Try different keywords.";
        gotoXY(c+3,l++); cout<<"- Try more general keywords.";
        gotoXY(c+3,l++); cout<<"- Try fewer keywords.";
       return;
    }

    for (i=0; i < min(topSearch ,(int)re.size()); i++)
    {
        TextColor(ColorCode_Blue);
        gotoXY(c+3,l++); cout<<re[i].filename;
        TextColor(ColorCode_White);
        ifstream ifs;
        ifs.open(searchFolder+re[i].filename);

        //skip words
        int current=0;
        string word;
        while(current<max((int)re[i].pos[0]-100,0))
        {
            ifs>>word;
            current+=1+word.size();
        }
        int posData=re[i].pos[0]-current;
        //read line
        string data;
        while(current<re[i].pos[0]+100&&!ifs.eof())
        {
            ifs>>word;
            current+=1+word.size();
            data+=word+" ";
        }
        gotoXY(c+3,l++); 
        ifs.close();
        //print
        int curData=0;
        while(curData<data.length())
        {
            int curLine=0;
            gotoXY(c+3,l++); 
            for (curLine=0;curLine<width-1&&curData<data.length();curLine++)
            {   
                
                if (curData>=posData&&curData<=posData+input.size())
                    TextColor(ColorCode_Pink);
                else
                    TextColor(ColorCode_White);
                cout<<data[curData++];
            }
                if (curData<data.length()&&data[curData]!=' ')
                    cout<<'-';
                else cout<<data[curData++];
        }
        l+=3;
        
    }
    
}
void resultWildcard (string input,vector<val>re)
{
    
    int l = 1;
    int c = 5;
    int width=95;
    int i,t;
    l=8;
    if (re.size()==0) 
    {
        gotoXY(c+3,l); cout<<"Your search did not match any documents.";
        l+=2;
        gotoXY(c+3,l); cout<<"Suggestions:";
        l+=2;
        gotoXY(c+3,l++); cout<<"- Make sure that all words are spelled correctly.";
        gotoXY(c+3,l++); cout<<"- Try different keywords.";
        gotoXY(c+3,l++); cout<<"- Try more general keywords.";
        gotoXY(c+3,l++); cout<<"- Try fewer keywords.";
        return;
    }
    //REsult
    vector<string>inputWords=Split(toLower(input));
    for (i=0; i < min(topSearch ,(int)re.size()); i++)
    {
        TextColor(ColorCode_Blue);
        gotoXY(c+3,l++); cout<<re[i].filename;
        TextColor(ColorCode_White);
        ifstream ifs;
        ifs.open(searchFolder+re[i].filename);

        //skip words
        int current=0;
        string word;
        while(current<max((int)re[i].pos[0]-100,0))
        {
            ifs>>word;
            current+=1+word.size();
        }
        int posData=re[i].pos[0]-current;
        //read line
        string data;
        while(current<re[i].pos[0]+100&&!ifs.eof())
        {
            ifs>>word;
            current+=1+word.size();
            data+=word+" ";
        }
        gotoXY(c+3,l++); 
        ifs.close();
        //print
        int curData=0;
        bool colorFlag=false,tmpColor=false;
        while(curData<data.length())
        {
            int curLine=0;
            gotoXY(c+3,l++); 
            for (curLine=0;curLine<width-1&&curData<data.length();curLine++)
            {   
                if (data[curData]==' '||curData==0)
                {
                    string curWord="";
                    int curPos;
                    if(curData==0) curPos=curData;
                    else curPos=curData+1;
                    while (data[curPos]!=' '&&curPos<data.length())
                    {
                        if (!isSplitWord(data[curPos]))
                        curWord+=data[curPos];
                        curPos++;
                    }
                    input=toLower(input);
                    curWord=toLower(curWord);
                    if (tmpColor) tmpColor=false;
                    if (curData==posData) colorFlag=true;
                    else if (colorFlag&&curWord==inputWords[inputWords.size()-1]) {tmpColor=true;colorFlag=false;}
                    if (tmpColor||colorFlag)
                    TextColor(ColorCode_Pink);
                    else
                    TextColor(ColorCode_White);
                }
                cout<<data[curData++];
            }
                if (curData<data.length()&&data[curData]!=' ')
                    cout<<'-';
                //else cout<<data[curData++];
        }
        l+=3;
        
    }
     
}
void resultRange (string input,char moneyUnit, vector<val>re)
{
    
    int l = 1;
    int c = 5;
    int width=95;
    int i,t;
    
    l=8;
    if (re.size()==0) 
    {
        gotoXY(c+3,l); cout<<"Your search did not match any documents.";
        l+=2;
        gotoXY(c+3,l); cout<<"Suggestions:";
        l+=2;
        gotoXY(c+3,l++); cout<<"- Make sure that all words are spelled correctly.";
        gotoXY(c+3,l++); cout<<"- Try different keywords.";
        gotoXY(c+3,l++); cout<<"- Try more general keywords.";
        gotoXY(c+3,l++); cout<<"- Try fewer keywords.";
        return;
    }
    //REsult
    vector<string>str=Splitprice(input,moneyUnit);
    set<string>inputSet;
    for (auto &word:str)
    inputSet.insert(toLower(word));
        
    int lowerInt = stod(str[str.size()-2]);
    int upperInt = stod(str[str.size()-1]);
    for (i=0; i < min(topSearch ,(int)re.size()); i++)
    {
        TextColor(ColorCode_Blue);
        gotoXY(c+3,l++); cout<<re[i].filename;
        TextColor(ColorCode_White);
        ifstream ifs;
        ifs.open(searchFolder+re[i].filename);

        //skip words
        int current=0;
        string word;
        while(current<max((int)re[i].pos[0]-100,0))
        {
            ifs>>word;
            current+=1+word.size();
        }
        int posData=re[i].pos[0]-current;
        //read line
        string data;
        while(current<re[i].pos[0]+100&&!ifs.eof())
        {
            ifs>>word;
            current+=1+word.size();
            data+=word+" ";
        }
        gotoXY(c+3,l++); 
        ifs.close();
        //print
        int curData=0;
        while(curData<data.length())
        {
            int curLine=0;
            gotoXY(c+3,l++); 
            for (curLine=0;curLine<width-1&&curData<data.length();curLine++)
            {   
                if (data[curData]==' '||curData==0)
                {
                    string curWord="";
                    int curPos;
                    if(curData==0) curPos=curData;
                    else curPos=curData+1;
                    while (data[curPos]!=' '&&curPos<data.length())
                    {
                        if (!isSplitWord(data[curPos]))
                        curWord+=data[curPos];
                        curPos++;
                    }
                    input=toLower(input);
                    curWord=toLower(curWord);
                    string tmp=curWord;
                    tmp.erase(tmp.begin());
                    if (inputSet.count(curWord)||(moneyUnit!='0'&&curWord[0]==moneyUnit&&isNumber(tmp)&&stod(tmp)>=lowerInt&&stod(tmp)<=upperInt))
                    TextColor(ColorCode_Pink);
                    else
                    TextColor(ColorCode_White);
                }
                cout<<data[curData++];
            }
                if (curData<data.length()&&data[curData]!=' ')
                    cout<<'-';
                else cout<<data[curData++];
        }
        l+=3;
        
    }
   
}
void resultSynonym (string input, string synonym, vector<val>re)
{
    
    int l = 1;
    int c = 5;
    int width=95;
    int i,t;
    l=8;
    if (re.size()==0) 
    {
        gotoXY(c+3,l); cout<<"Your search did not match any documents.";
        l+=2;
        gotoXY(c+3,l); cout<<"Suggestions:";
        l+=2;
        gotoXY(c+3,l++); cout<<"- Make sure that all words are spelled correctly.";
        gotoXY(c+3,l++); cout<<"- Try different keywords.";
        gotoXY(c+3,l++); cout<<"- Try more general keywords.";
        gotoXY(c+3,l++); cout<<"- Try fewer keywords.";
        return;
    }
    //REsult
    vector<string>inputWords=Split(input);
    vector<string>symWords=Split(synonym);
    set<string>inputSet;
    for (auto &word:inputWords)
    inputSet.insert(toLower(word));
    for (auto &word:symWords)
    inputSet.insert(toLower(word));
    for (i=0; i < min(topSearch ,(int)re.size()); i++)
    {
        TextColor(ColorCode_Blue);
        gotoXY(c+3,l++); cout<<re[i].filename;
        TextColor(ColorCode_White);
        ifstream ifs;
        ifs.open(searchFolder+re[i].filename);

        //skip words
        int current=0;
        string word;
        while(current<max((int)re[i].pos[0]-100,0))
        {
            ifs>>word;
            current+=1+word.size();
        }
        int posData=re[i].pos[0]-current;
        //read line
        string data;
        while(current<re[i].pos[0]+100&&!ifs.eof())
        {
            ifs>>word;
            current+=1+word.size();
            data+=word+" ";
        }
        gotoXY(c+3,l++); 
        ifs.close();
        //print
        int curData=0;
        while(curData<data.length())
        {
            int curLine=0;
            gotoXY(c+3,l++); 
            for (curLine=0;curLine<width-1&&curData<data.length();curLine++)
            {   
                if (data[curData]==' '||curData==0)
                {
                    string curWord="";
                    int curPos;
                    if(curData==0) curPos=curData;
                    else curPos=curData+1;
                    while (data[curPos]!=' '&&curPos<data.length())
                    {
                        if (!isSplitWord(data[curPos]))
                        curWord+=data[curPos];
                        curPos++;
                    }
                    input=toLower(input);
                    curWord=toLower(curWord);
                    if (inputSet.count(curWord))
                    TextColor(ColorCode_Pink);
                    else
                    TextColor(ColorCode_White);
                }
                cout<<data[curData++];
            }
                if (curData<data.length()&&data[curData]!=' ')
                    cout<<'-';
                else cout<<data[curData++];
        }
        l+=3;
        
    }
     
}
void documentBoard(string filename)
{
    clrscr();
    TextColor(ColorCode_Yellow);
    gotoXY(10,1); cout<<"Press ESC to back";
    int l=2;
    string data="";
    int c=(137-filename.size())/2;
    TextColor(ColorCode_Cyan);
    gotoXY(c,l); cout<<filename;
    TextColor(ColorCode_White);
    c=0;
    l=l+3;
    ifstream ifs(searchFolder+filename);
    gotoXY(c,l);
    if (!ifs) {
        cout<<"File not found!";
    }
    else
    while (!ifs.eof())
    {
        string graph;
        getline(ifs,graph,'\n');
        cout<<graph<<endl<<endl;
    }
    gotoXY(0,0);
    while (1)
    {
        char BACK = _getch();
        if (BACK == ESC)
        return;
    }
}
void resultGeneral (string input,vector<val>re)
{
    while (1)
    {
        resultBoard(input);
        string tmpInput=input;
        if (input[0] == input[input.size() - 1] && input[0] == 34)// "VU LAN" op9   
        {
            input.erase(input.begin());
            input.pop_back();
            resultAdjacent(input,re);
        }
        else if (input[0] == '#')// #hagtag op8)
        {
            resultExact(input,re);
        }
        else if (input[0] == '~')// ~set op12
        {
            input.replace(0, 1, "");
            string sym=listSynonym(input);
            resultSynonym(input,sym,re);
        }
        else if (input[0] == '+')// +washing machine and cellphone op5
        {
            input.erase(input.begin());
            resultSentence(input,re);
        }
        else if (input.find("FILETYPE: ") == 0)// FILETYPE: .txt op6
        {
            input.replace(0, 10, "");
            resultNoHighlight(input,re);
        }
        else if (input.find("IN TITLE: ") != string::npos)// IN TITLE: coolest things op4
        {
            input.replace(0, 10, "");
            resultNoHighlight(input,re);
        }
        else if (input.find(" * ") != string::npos)// vu * celebration op10
        {
            while(input.find("*") != string::npos)
            {
                int pos = input.find("*");
                input.replace(pos, 1," ");
            }
            resultWildcard(input,re);
        }
        else if (input.find(" AND ") != string::npos)// washing machine AND cellphone op1
        {
            resultExact(input,re);
        }
        else if (input.find(" OR ") != string::npos)// washing machine OR cellphone op2
        {
            resultExact(input,re);
        }
        else if (input.find("-") != string::npos)// adjacent op4
        {
            while(input.find("-") != string::npos)
            {
                int pos = input.find("-");
                input.replace(pos, 1," ");
            }
            resultAdjacent(input,re);
        }
        else if (input.find("..") != string::npos)// range
        {
            int pos = input.find("..");
            input.replace(pos, 2, " ");
            char moneyUnit='0';
            resultRange(input,moneyUnit,re);
        }
        else if (input.find("$") != string::npos)// search price
        {
            resultExact(input,re);
        }
        else// normal search
        {
            result(input,re);
        }
        while (1)
            {
                char BACK = _getch();
                if (BACK == ESC)
                    return;
                else if ((int)BACK>'0'&&(int)BACK<='0'+min((int)re.size(),5))
                {
                    documentBoard(re[(int)BACK-1-'0'].filename);
                    break;
                }
            }
        input=tmpInput;
    }
}

void timeTest(node* head, string file) { // trie, file queries
    clrscr();
    int l = 15;
    int c = (137 - 45) / 2;
    ifstream f;
    f.open(file);
    if (f.is_open())
    {
        clock_t start, end;
        start = clock();
        while (!f.eof()) {
            string word;
            getline(f, word);
            if (checkString(word))
            {
                _INPUT_(head, word);
            }
        }
        end = clock();
        
        gotoXY(c,l);  cout << "Time taken with 1000 random queries: " << fixed << double(end - start) / double(CLOCKS_PER_SEC) << setprecision(5) << "sec.\n";
    }
    else {gotoXY(c,l);  cout << "Query file not found!";}
    gotoXY(c,l+1);  cout << "Press ESC to back";
    f.close();
    while (1)
        {
            char BACK = _getch();
            if (BACK == ESC)
                return;
        }
}
#endif
