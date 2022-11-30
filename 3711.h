#ifndef f3711_h
#define f3711_h
#include "trie.h"
#include <algorithm>

vector<val> combineAND(vector<val> a, vector<val> b)
{
    for (int i = 0; i < a.size(); i++)
    {
        bool check = true;
        for (int j = 0; j < b.size(); j++)
        {
            if (a[i].filename == b[j].filename)
            {
                check = false;
                a[i].pos.insert(a[i].pos.end(), b[j].pos.begin(), b[j].pos.end());
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

vector<val> searchPrice (node* root, string word)
{
    vector<string> words = Split(word);
    vector<val> re;

    for (int i = 0; i < words.size(); i++)
        if (i == 0) re = search_notExact(root, words[i]);
        else re = combineAND(re, search_notExact(root, words[i]));

    return rankSort(re);
}

vector<val> searchRange (node* root, string data)
{
    string str[2], moneyChr;
    vector<string> words = Split(data);
    vector<val> ans;

    for (int i = 0, j = 0; i < words.size(); i++)
    {
        if (i < words.size() - 2)
        {
            if (i == 0) ans = search_notExact(root, words[0]);
            else{
                vector<val> tm = search_notExact(root, words[i]);
                ans = combineAND(ans, tm);
            }
        }
        else{
            str[j] = words[i];
            if (j == 0) moneyChr.push_back(words[i][0]);
            str[j].erase(str[j].begin());
            j++;
        }
    }
    
    vector<val> temp, price;
    int lowerInt = stod(str[0]);
    int upperInt = stod(str[1]);

    if (upperInt < lowerInt) swap(lowerInt, upperInt);
    for (int i = lowerInt; i <= upperInt; i++)
    {
        string sear = moneyChr + to_string(i);
        temp = search(root, sear);
        price = combine(price, temp);
        temp.clear();
    }
    
    if (ans.size() > 0)
    {
        vector<val> re = combineAND(ans, price);
        return rankSort(re);
    }
    else return rankSort(price);
}

vector<string> getCommonFile (vector<string> v1,vector<string> v2){
    vector<string> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));
    return v3;
}

bool checkAdjacent(string filename, node* root, vector<string>words, int lev, int posi)
{
    //cout<<filename<<words[lev]<<lev<<"-"<<posi<<endl;
    if (lev==words.size())
    return true;
    vector<val>temp=search(root,words[lev]);
    for (auto &info:temp)
    {
        if (info.filename==filename)
        {
            for (auto &posW:info.pos)
            if (posW==posi)
            return checkAdjacent(filename,root,words,lev+1,posi+1+words[lev].size());
            return false;
        }
    }
    return true;
}

vector<val> searchAdjacent (node* root, string data)
{
    vector<string>words=Split(data);
    vector<string>commonFile;
    vector<val>ans;
    if (words.size()==0) return ans;
    vector<val>temp = search(root,words[0]);
    //Initiate
    for (auto &info:temp)
            commonFile.push_back(info.filename);
  
    //Get common file
    for (auto &word:words)
    {
        temp=search(root,word);
        vector<string>current;
        for (auto &info:temp)
        {
            current.push_back(info.filename);
        }
        
        commonFile=getCommonFile(commonFile,current);
        if (commonFile.size()==0) 
        return ans;
    }
    //Get position
    temp=search(root,words[0]);
    for (auto &file:commonFile)
    {
        for (auto &info:temp)
        {
            if (info.filename==file)
            {
                for (auto &posW:info.pos)
                if (checkAdjacent(file,root,words,0,posW))
                {
                    val a;
                    a.filename=file;
                    a.pos.push_back(posW);
                    ans.push_back(a);
                    break;
                }
                break;
            }
        }
    }
    ans=rankSort(ans);
    return ans;
}
vector<string> Splitprice(string data, char &moneyUnit)
{
    vector<string> ndata = Split(data);
    if (!isdigit(ndata[ndata.size()-1][0])) moneyUnit=ndata[ndata.size()-1][0];
    ndata[ndata.size() - 1].erase(ndata[ndata.size() - 1].begin());
    ndata[ndata.size() - 2].erase(ndata[ndata.size() - 2].begin());

    return ndata;
}
#endif
