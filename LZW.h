#pragma once

#ifndef LZW_H
#define LZW_H

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <climits>
#include <fstream>
#include <iostream>
using namespace std;


class LZW
{
private:
	static map<string, unsigned short int> GetInitDic();

	static string GetStrByCode(const map<string, unsigned short int>& dict, unsigned short int code);
public:
	static void encode(const shared_ptr<vector<char>>& inpVect, const string& path);

	static shared_ptr<vector<char>> decode(const string& path);
};

#endif 