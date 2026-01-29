#pragma once

#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>
#include "BWT.h"
#include "Huffman.h"
#include "LZW.h"
#include "RLE.h"
#include "FileAccessor.h"
using namespace std;

class Compressor {
public:
	static int compress(const string& inpPath, const string& outPath, char method, bool useBWT);

	static int decompress(const string& inpPath, const string& outPath, char method, bool useBWT);
};

#endif