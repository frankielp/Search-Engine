#ifndef _2610_H_
#define _2610_H_

#include "trie.h"
using namespace std;

vector<val> _UNKNOW_(node* head, string word)
{
    vector<string> wordList;
    string w;
    stringstream ss(word);
    vector<val> re;

    for (int i = 0; getline(ss, w, '*'); i++)
    {
        if (w == "") continue;
        if (i == 0)
        {
            re = _NOTEXACT_(head, w);
            wordList.push_back(w);
        }
        else
        {
            for (int j = 0; j < w.size(); j++)
            {
                if (w[j] == ' ') 
                {
                    w.erase(w.begin());
                    j--;
                }
                else break;
            }

            re = combine_AND_(re, _NOTEXACT_(head, w));
            wordList.push_back(w);
        }
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
            string sub = file.substr(beg);
            int found = sub.find(toLower(wordList[wordList.size() - 1]));

            if (found == string::npos)
            {
                re[i].pos.erase(re[i].pos.begin() + j);
                j--;
            }
            else
            {
                sub = file.substr(beg, found);
                beg = 0;
                for (int k = 1; k < wordList.size() - 1; k++)
                {
                    int present = sub.find(toLower(wordList[k]));
                    if (present == string::npos || present < beg)
                    {
                        re[i].pos.erase(re[i].pos.begin() + j);
                        j--;
                        break;
                    }

                    beg = present;
                }
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

vector<val> _FILETYPE_(node* head, string type)
{
    return search(head, "~" + type);
}

vector<val> _OR_(node* head, string data)
{
    vector<val> result;
    int pos = 0;
    while (1)
    {
        int n = data.find(" OR ", pos);
        if (n == string::npos)
        {
            string sear = data.substr(pos);
            vector<val> tm;

            if (!allStopWord(sear))
                tm = _NOTEXACT_(head, sear);

            result = combine(result, tm);
            break;
        }

        string sear = data.substr(pos, n - pos);
        vector<val> tm;

        if (!allStopWord(sear))
            tm = _NOTEXACT_(head, sear);

        pos = n + 4;
        if (result.size() == 0) result = tm;
        else result = combine(result, tm);
    }

    return rankSort(result);
}

#endif
