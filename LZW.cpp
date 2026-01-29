#include "LZW.h"

map<string, unsigned short int> LZW::GetInitDic()
{
	map<string, unsigned short int> res;
	for (char i = CHAR_MIN; i != CHAR_MAX; ++i)
	{
		res[string(1, i)] = res.size();
	}
	return res;
}


string LZW::GetStrByCode(const map<string, unsigned short int>& dict, unsigned short int code)
{
	for (auto &i : dict)
	{
		if (i.second == code)
			return i.first;
	}
	return "";
}

void LZW::encode(const shared_ptr<vector<char>>& inpVect, const string& path)
{
	map<string, unsigned short int> dict = GetInitDic();
	ofstream out;
	out.open(path, ios::binary);
	if (out.is_open()) {
		string curr;
		string priv;
		for (unsigned int i = 0; i < inpVect->size(); ++i)
		{
			curr = std::string(1, inpVect->at(i));
			if (dict.count(priv + curr))
			{
				priv += curr;
			}
			else
			{
				out.write((char*)&dict[priv], sizeof(unsigned short int));
				if (dict.size() < USHRT_MAX - 1)
					dict[priv + curr] = dict.size() + 1;
				priv = curr;
			}
		}
		out.write((char*)&dict[priv], sizeof(unsigned short int));
		out.close();
	}
	else {
		//error
	}
}

shared_ptr<vector<char>> LZW::decode(const string& path)
{
	ifstream fin;
	fin.open(path, ios::binary);
	shared_ptr<vector<char>> outVect = shared_ptr<vector<char>>(new vector<char>);
	if (fin.is_open())
	{
		map<string, unsigned short int> dict = GetInitDic();

		unsigned short int currCode;
		unsigned short int privCode;
		string currStr;
		string privStr;
		string S;

		fin.read((char*)&privCode, sizeof(unsigned short int));
		privStr = GetStrByCode(dict, privCode);
		for (char k : privStr)
			outVect->push_back(k);
		char C = privStr[0];
		while (!fin.eof())
		{
			fin.read((char*)&currCode, sizeof(unsigned short int));
			privStr = GetStrByCode(dict, privCode);
			currStr = GetStrByCode(dict, currCode);

			if (dict.count(currStr))
			{
				S = currStr;
			}
			else
			{
				S = privStr;
				S = S + string(1, C);
			}

			for (char k : S)
				outVect->push_back(k);
			C = S[0];
			if (dict.size() < USHRT_MAX - 1)
				dict[privStr + string(1, C)] = dict.size() + 1;
			privCode = currCode;
		}
    string ft = "";
		for (char k : S) {
			outVect->pop_back();
      ft += k;
      }
		fin.close();
		return outVect;
	}
	else {
		//error
	}

  return nullptr;
}