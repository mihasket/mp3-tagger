#include <iostream>
#include <filesystem>

bool isMp3(std::string fileName) {
    std::filesystem::path filePath = fileName;

    if(filePath.extension() == ".mp3") return true;
    
    return false;
}

bool isPng(std::string fileName) {
    std::filesystem::path filePath = fileName;

    if(filePath.extension() == ".png") return true;
    
    return false;
}

bool isJpeg(std::string fileName) {
    std::filesystem::path filePath = fileName;

    if(filePath.extension() == ".jpg") return true;
    else if(filePath.extension() == ".jpeg") return true;

    return false;
}