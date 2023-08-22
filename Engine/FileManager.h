#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Log.h"

class FileManager
{
private:
	std::string filePath;
public:
	FileManager(std::string path);
	FileManager(const FileManager& manager);
	~FileManager();

	void Delete();
	void Rename( std::string newPath);
	void ChangeFile(std::string newPath);
	void Clear(bool isBinary);
	//text files
	template<typename T>
	bool Write(const T data){
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
	bool WriteAppend(const T data) {
		std::ofstream file(filePath.c_str(), std::ios::app);
		if (!file.is_open()) {
			LOG("Error opening file: " + filePath);
			return false;
		}
		file << data;
		file.close();
		return true;
	}
	std::string Read();
	std::string Read(int lineID);
	//binary files
	template<typename T>
	bool WriteBinary(T data) {
		std::ofstream file(filePath.c_str(), std::ios::binary);
		if (!file.is_open()) {
			LOG("Error opening file: " + filePath);
			return false;
		}
		file.write((char*)&data, sizeof(data));
		file.close();
		return true;
	}
	template<typename T>
	bool WriteAppendBinary(T data) {
		std::ofstream file(filePath.c_str(), std::ios::binary | std::ios::app);
		if (!file.is_open()) {
			LOG("Error opening file: " + filePath);
			return false;
		}
		file.write((char*)&data, sizeof(data));
		file.close();
		return true;
	}
	template<typename T>
	bool ReadBinary(std::vector<T>& data) {
		std::ifstream file(filePath, std::ios::binary);
		if (!file.is_open()) {
			LOG("Error opening file: " + filePath);
			return false;
		}

		T object;
		while (file.read(reinterpret_cast<char*>(&object), sizeof(T))) {
			data.push_back(object);
		}
		file.close();

		return true;
	}
	template<typename T>
	bool ReadBinary(T& object, size_t recordNumber) {
		std::ifstream file(filePath, std::ios::binary);
		if (!file.is_open()) {
			LOG("Error opening file: " + filePath);
			return false;
		}

		std::streampos offset = static_cast<std::streampos>(recordNumber - 1) * static_cast<std::streampos>(sizeof(T));
		file.seekg(recordNumber, std::ios::beg);

		file.read(reinterpret_cast<char*>(&object), sizeof(T));
		if (file.gcount() != static_cast<std::streamsize>(sizeof(T))) {
			LOG("Error reading record from file: " + filePath);
			return false;
		}

		file.close();
		return true;
	}
};

