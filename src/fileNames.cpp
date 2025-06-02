#include <iostream>
#include <fstream>
#include <filesystem>
#include "../include/fileExtension.h"

using std::filesystem::directory_iterator;

std::string cutPath(std::string filePath, const unsigned int size) {
    std::string temp = "";
    bool isSecondSlash = false;

    for(unsigned int i = 3; i < size; i++) {
        if(filePath[i] == '/') isSecondSlash = true;

        if(isSecondSlash) temp += filePath[i+1];
    }

    return temp;
}

void outputMp3FileNames() {
    std::string path = "mp3files/";
    unsigned int i = 1;

    std::cout << "MP3 files: \n";

    for(const auto& entry : directory_iterator(path)) {
        std::string fileName = std::string(entry.path());
        
        if(isMp3(fileName)) {
            fileName = cutPath(fileName, fileName.size());

            std::cout << i << ". " << fileName << '\n';
            i++;
        }
    }

    std::cout << '\n';
}

void outputImageNames() {
    std::string path = "images/";
    unsigned int i = 1;

    std::cout << "\nJPEG/PNG images: \n";

    for(const auto& entry : directory_iterator(path)) {
        std::string fileName = std::string(entry.path());

        if(isPng(fileName) || isJpeg(fileName)) {
            fileName = cutPath(fileName, fileName.size());

            std::cout << i << ". " << fileName << '\n';
            i++;
        }
    }
}
