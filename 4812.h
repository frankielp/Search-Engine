#ifndef _4812_H_
#define _4812_H_

#include "trie.h"

using namespace std;

vector<val> _INTITLE_(node* head, string word)
{
    vector<string> words = Split__(word);
    vector<val> re = search_more(head, "~" + words[0]);

    for (int i = 1; i < words.size(); i++)
    {
        vector<val> temp = search_more(head, "~" + words[i]);
        re = combine_AND_(re, temp);
    }

    return re;
}

vector<val> _SYNONYM_(node* root, string word)
{
    vector<val> result = _NOTEXACT_(root, word);
    vector<string> check;
    check.push_back(word);

    ifstream ifs("synonym/" + word + ".txt");

    if (ifs.is_open())
    {
        while (!ifs.eof())
        {
            getline(ifs, word, '\n');
            bool search = 1;
            for (int i = 0; i < check.size(); i++)
                if (check[i] == word)
                {
                    search = 0;
                    break;
                }

            if (search)
            {
                vector<val> searching = _NOTEXACT_(root, word);
                result = combine(result, searching);
                check.push_back(word);
            }
        }
    }

    ifs.close();
    result = rankSort(result);
    return result;
}

string listSynonym(string word) {
    string ans = word;
    ifstream f;
    f.open("synonym/" + word + ".txt");
    if (f.is_open()) {
        while (!f.eof()) {
            f >> word;
            if (ans.find(word) == string::npos) ans += " " + word;
        }
    }
    f.close();
    return ans;
}

#endif
