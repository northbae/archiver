#pragma once

#ifndef FILEACCESSOR_H
#define FILEACCESSOR_H

#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <climits>
using namespace std;


class FileAccessor
{
public:
  static shared_ptr<vector<char>> GetSymbVectPtr(const string& path);

  static void WriteSymbVectToFile(const shared_ptr<vector<char>>& inpVect, const string& path);

  static long int GetFileSize(const string& path);
};

#endif