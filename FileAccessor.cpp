#include "FileAccessor.h"

shared_ptr<vector<char>> FileAccessor::GetSymbVectPtr(const string& path)
{
  shared_ptr<vector<char>> symbVectorPtr = shared_ptr<vector<char>>(new vector<char>);
  ifstream file(path, ios::binary);
  if (file.is_open() && !file.fail())
  {
    char t;
    while (!file.eof()) {
      file.read((char*)&t, sizeof(char));
      symbVectorPtr->push_back(t);
    }
  }
  else
  {
    return nullptr;
  }
  file.close();
  symbVectorPtr->pop_back();
  return symbVectorPtr;
};

void FileAccessor::WriteSymbVectToFile(const shared_ptr<vector<char>>& inpVect, const string& path) {
  ofstream file;
  file.open(path, ios::binary);
  if (file.is_open() && !file.fail())
  {
    unsigned int from = 0;
    char* buff = new char[UCHAR_MAX];
    while (from < inpVect->size())
    {
      if (from + UCHAR_MAX < inpVect->size())
      {
        for (int i = 0; i < UCHAR_MAX; ++i)
        {
          buff[i] = inpVect->at(from + i);
        }
        file.write(buff, sizeof(char)*UCHAR_MAX);
        from += UCHAR_MAX;
      }
      else {
        for (int i = 0; i < inpVect->size() - from; ++i)
        {
          buff[i] = inpVect->at(from + i);
        }
        file.write(buff, sizeof(char)*(inpVect->size() - from));
        from = inpVect->size();
      }
    }
  }
  else {
    //error
  }
  file.close();
}

long FileAccessor::GetFileSize(const string & path)
{
  ifstream file(path, ios::binary);
  file.seekg(0, ios::end);
  long int file_size = file.tellg();
  return file_size;
}