#pragma once

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <iostream>
#include <fstream>
#include <deque>
using namespace std;

class HuffLeaf {
public:
	char value;
	HuffLeaf* left;
	HuffLeaf* right;
	HuffLeaf* parent;
	bool isLeaf;
	unsigned long int freq;
public:
	HuffLeaf(char value_t, HuffLeaf* parent_t, int freq_t);

	HuffLeaf(HuffLeaf* right_t, HuffLeaf* left_t);

	~HuffLeaf();

	string GetCode(char inp);
};

class Huffman {
private:
	static map<char, unsigned int> GetFreqVect(shared_ptr<vector<char>> inpVect);

	static char pack_byte(bool bits[8]);

	static HuffLeaf* CreateTree(map<char, unsigned int> freqVect);

public:

	static void encode(const shared_ptr<vector<char>>& inpVect, const string& path);

	static shared_ptr<vector<char>> decode(const string& path);
};


#endif 