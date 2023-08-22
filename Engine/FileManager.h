#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Log.h"

class FileManager
{
private:
	std::string filePath;
public:
	FileManager(std::string path);
	FileManager(const FileManager& manager);
	~FileManager();

	//bool Delete();
	//bool Rename(std::string newPath);
	//void ChangeFile(std::string path);
	//void Write(std::string data);
	//void WriteBinary(const void* data, std::streamsize dataSize);
	//std::string ReadLines();
	//std::string ReadLine(int lineIndex);

	void Delete();
	void Rename( std::string newPath);
	void operator=(std::string newPath) {
		filePath = newPath;
		/*FileManager x(newPath);
		return x;*/
	}
	void Clear(bool isBinary);
	//text files
	template<typename T>
	bool Write(const T& data){
		std::ofstream file(filePath.c_str());
		if (!file.is_open()) {
			LOG("Error opening file: " + filePath);
			return false;
		}
		file << data;
		file.close();
		return true;
	}
	template<typename T>
	bool WriteAppend(const T& data) {

	}
	std::string Read();
	std::string Read(int lineID);
	//binary files
	template<typename T>
	bool WriteBinary(T& data) {

	}
	template<typename T>
	bool WriteAppendBinary(T& data) {

	}
	bool ReadBinary(char*& data, size_t dataSize);
	bool ReadBinary(char*& data, size_t dataSize, size_t dataRecord);
};

