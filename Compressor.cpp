#include "Compressor.h"

int Compressor::compress(const string& inpPath, const string& outPath, char method, bool useBWT)
{
  shared_ptr<vector<char>> inpData = FileAccessor::GetSymbVectPtr(inpPath);
  if (!inpData) return -1;
  shared_ptr<vector<char>> outData;
  shared_ptr<vector<char>> BWTData;

  switch (method)
  {
  case 'R':
  {
    if (useBWT)
    {
      BWTData = BWT::encode(inpData);
    }
    else
      BWTData = inpData;
    RLE::encode(BWTData, outPath);
    return 0;
    break;
  }
  case 'H':
  {
    if (useBWT)
    {
      BWTData = BWT::encode(inpData);
    }
    else
      BWTData = inpData;
    Huffman::encode(BWTData, outPath);
    return 0;
    break;
  }
  case 'L':
  {
    if (useBWT)
    {
      BWTData = BWT::encode(inpData);
    }
    else
      BWTData = inpData;
    LZW::encode(BWTData, outPath);
    return 0;
    break;
  }
  default:
    return -1;
  }
}

int Compressor::decompress(const string& inpPath, const string& outPath, char method, bool useBWT)
{
  //std::shared_ptr<std::vector<char>> inpData = FileAccessor::GetSymbVectPtr(inpPath);
  shared_ptr<vector<char>> outData;
  shared_ptr<vector<char>> BWTData;

  switch (method)
  {
  case 'R':
  {
    if (useBWT)
    {
      outData = BWT::decode(RLE::decode(inpPath));
    }
    else
    {
      outData = RLE::decode(inpPath);
    }
    FileAccessor::WriteSymbVectToFile(outData, outPath);
    return 0;
    break;
  }
  case 'H':
  {
    if (useBWT)
    {
      outData = BWT::decode(Huffman::decode(inpPath));
    }
    else
    {
      outData = Huffman::decode(inpPath);
    }
    FileAccessor::WriteSymbVectToFile(outData, outPath);
    return 0;
    break;
  }
  case 'L':
  {
    if (useBWT)
    {
      outData = BWT::decode(LZW::decode(inpPath));
    }
    else
    {
      outData = LZW::decode(inpPath);
    }
    FileAccessor::WriteSymbVectToFile(outData, outPath);
    return 0;
    break;
  }
  default:
    return -1;
  }
}