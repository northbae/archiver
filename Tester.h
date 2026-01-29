#pragma once

#ifndef TESTER_H
#define TESTER_H

#include <string>
#include "BWT.h"
#include "Huffman.h"
#include "LZW.h"
#include "RLE.h"
#include "FileAccessor.h"
#include <chrono>
using namespace std;


class Tester
{
public:
	static string GetTesting(string inpPath, char method, bool useBWT);
};

#endif 