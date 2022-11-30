#ifndef utils_h
#define utils_h
#include "trie.h"
void copyFile (string inputPath, string outputPath)
{
    ifstream infile(inputPath);
    ofstream outfile(outputPath);
    string content = "";
    int i;

    for(i=0 ; infile.eof()!=true ; i++) 
        content += infile.get();
    infile.close();
    outfile << content;                 
    outfile.close();
}

void insertFile(node*& head, string filePath)
{
    string filename="";
    for(int i=filePath.size()-1;i>=0;i--)
    {
        if (filePath[i]=='/')
        break;
        filename=filePath[i]+filename;
    }
    ifstream ifs(filePath);
    int l = 10;
    int c = (137 - 65) / 2;
    if (!ifs.fail())
    {
        ofstream f;
        f.open(fileList,ios::app);
        f<<filename<<endl;
        f.close();
        copyFile(filePath,searchFolder+filename);
        string data;
        getline(ifs, data, '\0');
        replaceErrorChar(data);
        
        string words;
        for (int i = 0; i < data.length() + 1; i++)
        {
            if (isSplitWord(data[i]))
            {
                if (!isStopWord(words) && words != "") insert(head, words, filePath, i - words.length());
                words.clear();
            }
            else words.push_back(data[i]);
        }
        gotoXY(c,l+1);cout<<"Succeed!";

    }
    else 
    {
        gotoXY(c,l+1);cout<<"File cannot be found!";
        }
    Sleep(500);
    ifs.close();
}

void writeHistory(string input)
{
    ofstream ofs;
    ofs.open("History.txt",ios::app);
    ofs<<input<<"\n";
    ofs.close();
}
bool isNumber(string s) {
	char* p;
	strtol(s.c_str(), &p, 10);
	return *p == 0;
}

bool checkString(string s) {
	if (s[0] == '"') {
		int k = 1;
		for (k; k < s.length() && s[k] != '"'; ++k);
		if (k < s.length() - 1) return 0;
	}
	else if (s[0] == '#' || s[0] == '~' || s[0] == '+') {
		if (s.length() <= 1) return 0;
	}
	else if (s.find("FILETYPE: ") == 0) {
		int k = 9;
		while (k < s.length() && isSplitWord(s[k])) ++k;
		if (k >= s.length()) return 0;
	}
	else if (s.find("IN TITLE: ") != string::npos)
	{
		int k = 9;
		while (k < s.length() && isSplitWord(s[k])) ++k;
		if (k >= s.length()) return 0;
	}
	else if (s.find(" AND") != string::npos)// washing machine AND cellphone op1
	{
		int l = 0;
		while (l <s.length()) {
			auto rtmp = s.find(" AND", l);
			if (rtmp == string::npos) break;
			if (rtmp == s.length() - 4 || !rtmp) return 0;
			if (rtmp + 4 < s.length() && !isSplitWord(s[rtmp+4])) {
				l = rtmp+1;
				continue;
			}
			int r = min(rtmp, s.length()-1);
			while (l < r && isSplitWord(s.at(l)))++l;
			if (l == r) return 0;
			l = r+4;
		}
	}
	else if (s.find(" OR") != string::npos)// washing machine OR cellphone op2
	{
		int l = 0;
		while (l < s.length()) {
			auto rtmp = s.find(" OR", l);
			if (rtmp == string::npos) break;
			if (rtmp == s.length() - 3 || !rtmp) return 0;
			if (rtmp + 3 < s.length() && !isSplitWord(s[rtmp + 3])) {
				l = rtmp + 1;
				continue;
			}
			int r = min(rtmp, s.length() - 1);
			while (l < r && isSplitWord(s.at(l)))++l;
			if (l == r) return 0;
			l = r + 3;
		}
	}
	else if (s.find("-") != string::npos)// adjacent op4
	{
		if (s[0] == '-' || s[s.size() - 1] == '-') return 0;
		if (Split(s).size() > 1) return 0;
	}
	else if (s.find("..") != string::npos)// range
	{
		vector<string> pr = Split(s);

		if (pr.size() < 2) return 0;
		else
		{
			string nstr = pr[pr.size() - 1];
			nstr.erase(nstr.begin());

			if (!isNumber(nstr)) return 0;

			nstr = pr[pr.size() - 2];
			nstr.erase(nstr.begin());

			return isNumber(nstr);
		}

		/*int i = 0;
		string tmp = "";
		while (s[i] != '.' && s[i + 1] != '.') {
			tmp += s[i];
			++i;
		}
		if (!isNumber(tmp)) return 0;
		i += 2;
		tmp = "";
		for (i; i < s.length(); ++i) tmp += s[i];
		return isNumber(tmp);*/
	}
	else if (s.find("$") != string::npos)// search price
	{
		vector<string> pr = Split(s);
		pr[pr.size() - 1].replace(0, 1, "");
		return isNumber(pr[pr.size() - 1]);
	}
	return 1;
}

#endif
