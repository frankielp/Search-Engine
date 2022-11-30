#ifndef TRIEFUNC
#define TRIEFUNC

#include "trie.h"
using namespace std;

bool isStopWord(string word);

/*
    ASCII TABLE (-32)
    space (' ') = 0;
    ~ = 94
*/
int convert(char a)
{
    return a - 32;
}

/*
    ASCII TABLE (+32)
    space (' ') = 0;
    ~ = 94
*/
char convert(int num)
{
    return num + 32;
}

char proper(char a)
{
    if (a > 64 && a < 91)
        return a + 32;
    else if (a > 96 && a < 123)
        return a - 32;
    
    return a;
}

void replaceErrorChar(string& text)
{
    for (int i = 0; i < text.length(); i++)
        if (text[i] > 253 || text[i] < 0) text[i] = '?';
}

void replaceErrorChar(char& text)
{
    if (text > 253 || text < 0) text = '?';
}

bool isSplitWord(char a)
{
    if (a < 35 || a > 122) return true;
    switch (a)
    {
    case ',':
    case '.':
    case ';':
    case ':':
    case '\'':
    case '(':
    case ')':
    case '[':
    case ']':
    case '/':
    case '\\':
    case '?':
    case '\n':
    case '\t':
        return true;
        break;
    
    default:
        return false;
        break;
    }
}

vector<string> Split__(string data)
{
    vector<string> re;
    string words;
    for (int i = 0; i < data.length() + 1; i++)
    {
        if (isSplitWord(data[i]))
        {
            if ( words != "") re.push_back(words);
            words.clear();
        }
        else words.push_back(data[i]);
    }
    return re;
}

vector<val> combine(vector<val> a, vector<val> b)
{
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < b.size(); j++)
        {
            if (a[i].filename == b[j].filename)
            {
                a[i].pos.insert(a[i].pos.end(), b[j].pos.begin(), b[j].pos.end());
                b.erase(b.begin() + j);
                j--;
            }
        }
    }

    a.insert(a.end(), b.begin(), b.end());

    return a;
}

vector<string> Split(string data)
{
    vector<string> re;
    string words;
    for (int i = 0; i < data.length() + 1; i++)
    {
        if (isSplitWord(data[i]))
        {
            if (!isStopWord(words) && words != "") re.push_back(words);
            words.clear();
        }
        else words.push_back(data[i]);
    }
    return re;
}

void destroy(node* head)
{
    delete head;
    head = nullptr;
}


//              MAIN FUNCTIONS

vector<val> search(node* root, string word)
{
    for (int i = 0; i < word.size(); i++)
    {
        if (root == nullptr)
        {
            vector<val> data;
            return data;
        }
        root = root->elements[convert((char)word[i])];
    }
    
    if (root == nullptr)
        {
            vector<val> data;
            return data;
        }

    return root->data;
}

vector<val> search_notExact(node* root, string word, int beg = 0)
{   
    if (root == nullptr) return vector<val>();

    if (beg == word.size())
        return root->data;

    if (proper(word[beg]) != word[beg])
    {
        vector<val> up = search_notExact(root->elements[convert(word[beg])], word, beg + 1);
        vector<val> down = search_notExact(root->elements[convert(proper(word[beg]))], word, beg + 1);
        return combine(up, down);
    }
    else{
        return search_notExact(root->elements[convert(word[beg])], word, beg + 1);
    }
}

vector<val> search_more(node* root, string word, int beg = 0, vector<val> tm = {})
{
    if (root == nullptr) return vector<val>();

    if (beg >= word.size())
    {
        vector<val> re = root->data;
        if (re.size() + tm.size() >= topSearch) return combine(re, tm);

        for (int i = 0; i < characterUsed; i++)
        {
            word.push_back(convert(i));
            vector<val> ex = search_more(root->elements[convert(word[beg])], word, beg + 1, re);
            re = combine(re, ex);
            word.pop_back();
        }

        return re;
    }
    if (proper(word[beg]) != word[beg])
    {
        vector<val> re1 = search_more(root->elements[convert(word[beg])], word, beg + 1);
        vector<val> re2 = search_more(root->elements[convert(proper(word[beg]))], word, beg + 1);

        return combine(re1, re2);
    }
    return search_more(root->elements[convert(word[beg])], word, beg + 1);
}

void insert(node*& head, string word, string filename, int pos, int beg = 0)
{
    if (head == nullptr)
    {
        head = new node;
        head->elements = new node*[characterUsed];
        for (int i = 0; i < characterUsed; i++)
            head->elements[i] = nullptr;
    }

    if (beg == word.length())
    {
        for (int i = 0; i < head->data.size(); i++)
        {
            if (filename == head->data[i].filename)
            {
                head->data[i].pos.push_back(pos);
                return;
            }
        }

        val ndata;
        ndata.filename = filename;
        ndata.pos.push_back(pos);
        head->data.push_back(ndata);
        return;
    }

    insert(head->elements[convert(word[beg])], word, filename, pos, beg + 1);
}

bool isStopWord(string word)
{
    if (search_notExact(stopWordls, word).size() > 0) return true;
    return false;
}

void buildStopWordTrie(){
    ifstream ifs(stopWordFile);
    if(!ifs.is_open()) return;
    
    stopWordls = nullptr;
    string word;

    while (!ifs.eof()){
        ifs >> word;
        insert(stopWordls, word, "", 0);
    }

    ifs.close();
}

node* inputInfo()
{
    node* head = nullptr;
    ifstream ifs(fileList);
    if (ifs.fail())
    {
        ifs.close();
        cout << "files cant be opened!!";
        ifs.close();
        return nullptr;
    }

    while (!ifs.eof())
    {
        string filename;
        getline(ifs, filename, '\n');
        replaceErrorChar(filename);

        stringstream ss(filename);// input filename
        string splitWord;
        while (getline(ss, splitWord, ' '))
            insert(head, "~" + splitWord, filename, -1);
        
        int dotPos = filename.find(".");
        insert(head, "~" + filename.substr(dotPos), filename, -1);
        
        // insert words
        ifstream datafile(searchFolder + filename);

        if (!datafile.fail())
        {
            string data;
            getline(datafile, data, '\0');           
            replaceErrorChar(data);
            
            string words;
            for (int i = 0; i < data.length() + 1; i++)
            {
                if (isSplitWord(data[i]))
                {
                    if (!isStopWord(words) && words != "") insert(head, words, filename, i - words.length());
                    words.clear();
                }
                else words.push_back(data[i]);
            }
        }
        
        datafile.close();
    }
    
    ifs.close();
    
    return head;
}

vector<val> rankSort(vector<val> data)
{
    bool check = 1;
    for (int i = 1; i < data.size(); i++)
        if (data[0].pos.size() != data[i].pos.size())
        {
            check = 0;
            break;
        }
        
    if (check) return data;

    float arv = 0;
    for (int i = 0; i < data.size(); i++) arv += data[i].pos.size();
    arv /= data.size();

    vector<val> min, max;

    for (int i = 0; i < data.size(); i++)
        if (data[i].pos.size() < arv) min.push_back(data[i]);
        else max.push_back(data[i]);
    
    min = rankSort(min);
    max = rankSort(max);
    data.clear();

    int i = max.size() - 1;
    while (i >= 0)
    {
        data.push_back(max[0]);
        max.erase(max.begin());
        i--;
    }

    i = min.size() - 1;
    while (i >= 0)
    {
        data.push_back(min[0]);
        min.erase(min.begin());
        i--;
    }

    return data;
}


#endif
