#pragma once

#ifndef RLE_H
#define RLE_H

#include "FileAccessor.h"

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <climits>
#include <deque>
using namespace std;


class RLE {
public:
	static void encode(const shared_ptr<vector<char>>& inpVect, const string& path);

	static shared_ptr<vector<char>> decode(const string& path);
};

#endif 