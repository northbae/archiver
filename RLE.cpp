#include "RLE.h"

void RLE::encode(const shared_ptr<vector<char> >& inpVect, const string& path)
{
	ofstream file;
	file.open(path, ios::binary);
	if (file.is_open() && !file.fail())
	{
		if (inpVect)
		{
			shared_ptr<vector<char>> outVect = shared_ptr<vector<char>>(new vector<char>);
			unsigned int currind = 0;
			char currchar;
			char times = 0;
			while (currind < inpVect->size()) {
				currchar = inpVect->at(currind);
				currind++;
				if (currind == inpVect->size())
				{
					outVect->push_back(times);
					outVect->push_back(currchar);
					times = 0;
				}
				else if (currchar == inpVect->at(currind) && times < SCHAR_MAX - 1) {
					times++;
				}
				else {
					outVect->push_back(times);
					outVect->push_back(currchar);
					times = 0;
				}
			}

			char serLen = 0;
			deque<char> buff;
			unsigned int ind = 0;
			while (ind < outVect->size()) {
				if (serLen == SCHAR_MIN + 1)
				{
					file.write((char*)&serLen, sizeof(char));
					while (buff.size() > 0) {
						file.write((char*)&(buff.front()), sizeof(char));
						buff.pop_front();
					}
					serLen = 0;
				}

				if (outVect->at(ind) == 0) {
					serLen--;
					buff.push_back(outVect->at(ind + 1));
				}
				else {
					if (serLen != 0) {
						file.write((char*)&serLen, sizeof(char));
						while (buff.size() > 0) {
							file.write((char*)&(buff.front()), sizeof(char));
							buff.pop_front();
						}
						serLen = 0;
					}
					file.write((char*)&(outVect->at(ind)), sizeof(char));
					file.write((char*)&(outVect->at(ind + 1)), sizeof(char));
				}
				ind += 2;
			}
			if (serLen != 0) {
				file.write((char*)&serLen, sizeof(char));
				while (buff.size() > 0) {
					file.write((char*)&(buff.front()), sizeof(char));
					buff.pop_front();
				}
			}

		}
		else {
			//error
		}
	}
}

shared_ptr<vector<char> > RLE::decode(const string& path)
{
	shared_ptr<std::vector<char>> inpVect = FileAccessor::GetSymbVectPtr(path);
	shared_ptr<vector<char>> outVect = shared_ptr<vector<char>>(new vector<char>);
	if (inpVect)
	{
		char symb;
		char count;
		unsigned int currind = 0;
		while (currind < inpVect->size() - 1)
		{
			count = inpVect->at(currind);
			currind++;
			if (count >= 0) {
				symb = inpVect->at(currind);
				currind++;
				for (char i = 0; i <= count; ++i) {
					outVect->push_back(symb);
				}
			}
			else
			{
				for (char i = 0; i > count; --i)
				{
					symb = inpVect->at(currind);
					currind++;
					outVect->push_back(symb);
				}
			}
		}
	}
	else
	{
		//error
		return nullptr;
	}
	return outVect;
}