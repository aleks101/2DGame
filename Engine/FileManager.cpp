#include "FileManager.h"

FileManager::FileManager(std::string path) : filePath(path) {

}
FileManager::FileManager(const FileManager& manager) {
	filePath = manager.filePath;
}
FileManager::~FileManager() {

}
void FileManager::Delete() {
	remove(filePath.c_str());
}
void FileManager::Rename(std::string newPath) {
	rename(filePath.c_str(), newPath.c_str());
	filePath = newPath;
}
void FileManager::Clear(bool isBinary) {
    std::ios_base::openmode mode = std::ios::out | std::ios::trunc;

    if (isBinary) {
        mode |= std::ios::binary;
    }

    std::ofstream file(filePath, mode);
    if (!file.is_open()) {
        LOG("Error opening file: " + filePath);
    }

    file.close();
}