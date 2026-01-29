#include "BWT.h"

vector<char> BWT::encodeBlock(vector<char> inpVect)
{
  int blockSize = inpVect.size();
  vector<char*> transMat;

  for (int i = 0; i < blockSize; ++i)
  {
    transMat.push_back(new char[blockSize + 1]);
  }

  for (int i = 0; i < blockSize; ++i)
  {
    for (int j = 0; j < blockSize; ++j)
    {
      transMat.at(i)[j] = inpVect.at((i + j) % blockSize);
    }
  }
  for (int i = 0; i < blockSize; ++i)
  {
    transMat.at(i)[blockSize] = '\0';
  }

  sort(transMat.begin(), transMat.end(), [](const char* lhs, const char* rhs) {
    return strcmp(lhs, rhs) < 0;
  });

  char* inpChar = new char[blockSize + 1];
  for (int i = 0; i < blockSize; ++i)
  {
    inpChar[i] = inpVect.at(i);
  }
  inpChar[blockSize] = '\0';
  unsigned char inpIndex = 0;
  while (strcmp(inpChar, transMat[inpIndex]) != 0)
    inpIndex++;

  vector<char> result;
  result.push_back(inpIndex);
  for (int i = 0; i < blockSize; ++i)
  {
    result.push_back(transMat.at(i)[blockSize - 1]);
  }

  for (int i = 0; i < blockSize; ++i)
  {
    delete[] transMat.at(i);
  }

  return result;
}

vector<char> BWT::decodeBlock(vector<char> inpVect)
{
  unsigned char lineNumber = inpVect.front();
  inpVect.erase(inpVect.begin());
  int blockSize = inpVect.size();
  vector<char*> transMat;

  for (int i = 0; i < blockSize; ++i)
  {
    transMat.push_back(new char[blockSize + 1]);
  }

  for (int i = 0; i < blockSize; ++i)
  {
    for (int j = 0; j < blockSize; ++j)
    {
      transMat.at(i)[j] = '0';
    }
  }

  for (int i = 0; i < blockSize; ++i)
  {
    transMat.at(i)[blockSize] = '\0';
  }


  for (int j = blockSize - 1; j >= 0; --j)
  {
    for (int i = 0; i < blockSize; ++i)
    {
      transMat.at(i)[j] = inpVect.at(i);
    }
    sort(transMat.begin(), transMat.end(), [](const char* lhs, const char* rhs) {
      return strcmp(lhs, rhs) < 0;
    });
  }

  vector<char> result;
  for (int i = 0; i < blockSize; ++i)
  {
    if (lineNumber >= blockSize) return result;
    result.push_back(transMat.at(lineNumber)[i]);
  }


  for (int i = 0; i < blockSize; ++i)
  {
    delete[] transMat.at(i);
  }

  return result;
}

shared_ptr<vector<char>> BWT::encode(const shared_ptr<vector<char>>& inpVect) {
  unsigned int inpVectsize = inpVect->size();
  vector<char>* vect = new vector<char>;
  shared_ptr<vector<char>> result = shared_ptr<vector<char>>(vect);
  unsigned int from = 0;
  unsigned int to = 0;
  while (from < inpVectsize)
  {
    if (inpVectsize - from >= MaxBlockSize)
    {
      to = from + MaxBlockSize;
    }
    else {
      to = inpVectsize;
    }
    vector<char> inpblock;
    vector<char> outblock;
    for (unsigned int j = from; j < to; ++j)
      inpblock.push_back(inpVect->at(j));
    outblock = encodeBlock(inpblock);
    for (auto el = outblock.begin(); el < outblock.end(); ++el)
      result->push_back(*el);
    from = to;
  }
  return result;
}

shared_ptr<vector<char> > BWT::decode(const shared_ptr<vector<char> >& inpVect) {
  unsigned int inpVectsize = inpVect->size();
  vector<char>* vect = new vector<char>;
  shared_ptr<vector<char>> result = shared_ptr<vector<char>>(vect);
  unsigned int from = 0;
  unsigned int to = 0;
  while (from < inpVectsize)
  {
    if (inpVectsize - from >= MaxBlockSize + 1)
    {
      to = from + MaxBlockSize + 1;
    }
    else {
      to = inpVectsize;
    }
    std::vector<char> inpblock;
    std::vector<char> outblock;
    for (unsigned int j = from; j < to; ++j)
      inpblock.push_back(inpVect->at(j));
    outblock = decodeBlock(inpblock);
    for (auto el = outblock.begin(); el < outblock.end(); ++el)
      result->push_back(*el);
    from = to;
  }
  return result;
}