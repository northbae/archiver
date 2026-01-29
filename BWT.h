#pragma once

#ifndef BWT_H
#define BWT_H

#include <vector>
#include <algorithm>
#include <cstring>
#include <memory>
#include <string>
#include <climits>
using namespace std;

class BWT
{
private:
  static const unsigned char MaxBlockSize = UCHAR_MAX-1;

  static vector<char> encodeBlock(vector<char> inpVect);

  static vector<char> decodeBlock(vector<char> inpVect);
public:

  static shared_ptr<vector<char>> encode(const shared_ptr<vector<char>>& inpVect);

  static shared_ptr<vector<char>> decode(const shared_ptr<vector<char>>& inpVect);
};


#endif