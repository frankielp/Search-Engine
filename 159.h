#ifndef _159_H_
#define _159_H_

#include "trie.h"
using namespace std;

vector<val> combine_AND_(vector<val> a, vector<val> b)
{
    for (int i = 0; i < a.size(); i++)
    {
        bool check = 1;
        for (int j = 0; j < b.size(); j++)
        {
            if (a[i].filename == b[j].filename)
            {
                check = 0;
                b.erase(b.begin() + j);
                j--;
            }
        }

        if (check)
        {
            a.erase(a.begin() + i);
            i--;
        }
    }

    return a;
}

string toLower(string b)
{
    for (int i = 0; i < b.length(); i++)
        if (b[i] > 64 && b[i] < 91) b[i] += 32;
    return b;
}

bool allStopWord(string data)
{
    vector<string> word = Split(data);

    for (int i = 0; i < word.size(); i++)
        if (!isStopWord(word[i])) return false;
    return true;
}

// PLUS AND
vector<val> _NOTEXACT_(node* head, string word)
{
    vector<val> re;
    string singleW;
    for (int i = 0, j = 0; i <= word.size(); i++)
    {
        if (isSplitWord(word[i]))
        {
            if (j == 0 && singleW != "")
            {
                re = search_notExact(head, singleW);
                j++;
                singleW.clear();
                continue;
            }

            if (isStopWord(singleW) || singleW == "")
            {
                singleW.clear();
                continue;
            }

            vector<val> sear = search_notExact(head, singleW);
            re = combine_AND_(re, sear);
            singleW.clear();
        }
        else singleW.push_back(word[i]);
    }

    for (int i = 0; i < re.size(); i++)
    {
        ifstream ifs(searchFolder + re[i].filename);
        string file;
        getline(ifs, file, '\0');
        file = toLower(file);
        ifs.close();

        for (int j = 0; j < re[i].pos.size(); j++)
        {
            int beg = re[i].pos[j];
            string sub = file.substr(beg, word.size() + 1);
            int found = sub.find(toLower(word));

            if (found == string::npos)
            {
                re[i].pos.erase(re[i].pos.begin() + j);
                j--;
            }
        }

        if (re[i].pos.size() == 0)
        {
            re.erase(re.begin() + i);
            i--;
        }
    }

    re = rankSort(re);
    return re;
}

vector<val> _EXACT_(node* head, string word)
{
    vector<val> re;
    string singleW;
    for (int i = 0, j = 0; i <= word.size(); i++)
    {
        if (isSplitWord(word[i]))
        {
            if (j == 0 && singleW != "")
            {
                re = search(head, singleW);
                j++;
                singleW.clear();
                continue;
            }

            if (isStopWord(singleW) || singleW == "")
            {
                singleW.clear();
                continue;
            }

            vector<val> sear = search(head, singleW);
            re = combine_AND_(re, sear);
            singleW.clear();
        }
        else singleW.push_back(word[i]);
    }

    for (int i = 0; i < re.size(); i++)
    {
        ifstream ifs(searchFolder + re[i].filename);
        string file;
        getline(ifs, file, '\0');
        ifs.close();

        for (int j = 0; j < re[i].pos.size(); j++)
        {
            int beg = re[i].pos[j];
            string sub = file.substr(beg, word.size() + 1);
            int found = sub.find(word);

            if (found == string::npos)
            {
                re[i].pos.erase(re[i].pos.begin() + j);
                j--;
            }
        }

        if (re[i].pos.size() == 0)
        {
            re.erase(re.begin() + i);
            i--;
        }
    }

    re = rankSort(re);
    return re;
}

vector<val> _AND_(node* head, string data)
{
    vector<val> result;
    int pos = 0;
    while (1)
    {
        int n = data.find(" AND ", pos);
        if (n == string::npos)
        {
            string sear = data.substr(pos);
            if (allStopWord(sear)) return vector<val>{};

            vector<val> tm = _NOTEXACT_(head, sear);
            result = combineAND(result, tm);
            break;
        }

        string sear = data.substr(pos, n - pos);
        if (allStopWord(sear)) return vector<val>{};

        vector<val> tm = _NOTEXACT_(head, sear);
        pos = n + 5;
        if (result.size() == 0) result = tm;
        else result = combineAND(result, tm);
    }

    return rankSort(result);
}

void updateBoard(node* &head)
{
    clrscr();
    int l = 10;
    int c = (137 - 65) / 2;
    string path;
    gotoXY(c,l);cout<<"Type the PATH to the data file (.txt) or 0 to back: ";
    unhidePointer();
    getline(cin,path,'\n');
    if (path=="0") return;
    insertFile(head,path);

}

#endif
