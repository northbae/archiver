#include "Tester.h"

string Tester::GetTesting(string inpPath, char method, bool useBWT)
{
	clock_t encodingTime;
	clock_t decodingTime;
	//std::string outPath = ("../Compressed/testingFileOut");
	string outPath = ("CompressedFiles/testingFile.txt");
	shared_ptr<vector<char>> inpData = FileAccessor::GetSymbVectPtr(inpPath);
	if (!inpData) return "файл не открылся:(";
	shared_ptr<vector<char>> outData;
	shared_ptr<vector<char>> BWTData;
	string result;

	switch (method)
	{
	case 'R':
	{
		encodingTime = clock();
		if (useBWT)
		{
			BWTData = BWT::encode(inpData);
		}
		else
			BWTData = inpData;
		RLE::encode(BWTData, outPath);
		encodingTime = clock() - encodingTime;
		decodingTime = clock();
		if (useBWT)
		{
			outData = BWT::decode(RLE::decode(outPath));
		}
		else
		{
			outData = RLE::decode(outPath);
		}
		decodingTime = clock() - decodingTime;
    FileAccessor::WriteSymbVectToFile(outData, "CompressedFiles/testingFileDecompressed.txt");

		result = "метод RLE";
		break;
	}
	case 'H':
	{
		encodingTime = clock();
		if (useBWT)
		{
			BWTData = BWT::encode(inpData);
		}
		else
			BWTData = inpData;
		Huffman::encode(BWTData, outPath);
		encodingTime = clock() - encodingTime;
		decodingTime = clock();
		if (useBWT)
		{
			outData = BWT::decode(Huffman::decode(outPath));
		}
		else
		{
			outData = Huffman::decode(outPath);
		}
		decodingTime = clock() - decodingTime;
    FileAccessor::WriteSymbVectToFile(outData, "CompressedFiles/testingFileDecompressed");
		result = "метод Хаффмана";
		break;
	}
	case 'L':
	{
		encodingTime = clock();
		if (useBWT)
		{
			BWTData = BWT::encode(inpData);
		}
		else
			BWTData = inpData;
		LZW::encode(BWTData, outPath);
		encodingTime = clock() - encodingTime;
		decodingTime = clock();
		if (useBWT)
		{
			outData = BWT::decode(LZW::decode(outPath));
		}
		else
		{
			outData = LZW::decode(outPath);
		}
		decodingTime = clock() - decodingTime;
    FileAccessor::WriteSymbVectToFile(outData, "CompressedFiles/testingFileDecompressed");
		result = "метод LZW";
		break;
	}/*
  case 'A':
	{
		encodingTime = clock();
		if (useBWT)
		{
			BWTData = BWT::encode(inpData);
		}
		else
			BWTData = inpData;
		AC::encode(BWTData, outPath);
		encodingTime = clock() - encodingTime;
		decodingTime = clock();
		if (useBWT)
		{
			outData = BWT::decode(AC::decode(outPath));
		}
		else
		{
			outData = AC::decode(outPath);
		}
		decodingTime = clock() - decodingTime;
    FileAccessor::WriteSymbVectToFile(outData, "CompressedFiles/testingFileDecompressed.txt");

		result = "метод AC";
		break;
	}*/
	default:
		return "такого метода нету";
	}

	if (useBWT)
		result += " + BWT";
	result += "\n";
	double compressionValue = (static_cast<double>(FileAccessor::GetFileSize(outPath)) / static_cast<double>(FileAccessor::GetFileSize(inpPath)))*100.0;
	result += " время компрессии = " + to_string(static_cast<double>(encodingTime) / (CLOCKS_PER_SEC / 1.0)) + " сек\n";
	result += " время декомпрессии = " + to_string(static_cast<double>(decodingTime) / (CLOCKS_PER_SEC / 1.0)) + "  сек\n";
	result += " размер начального файла = " + to_string(FileAccessor::GetFileSize(inpPath))  + "\n";
	result += " размер конечного файла = " + to_string(FileAccessor::GetFileSize(outPath)) + "\n";
	result += " коэффициент сжатия " + to_string(compressionValue) + "%" + "\n";
	return result;
}