#include <iostream>
#include <fstream>
#include <filesystem>
#include "../include/FileExtension.h"
#include "../include/Tag.h"

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

void inputTagDescription(ID3v2Tag& tag, const unsigned int filePosition, std::string fileName) {
    std::cout << filePosition << ". " << cutPath(fileName, fileName.size()) << '\n';
    
    std::cout << "Title: ";
    std::cin.getline(tag.title, 100);

    std::cout << "Artist: ";
    std::cin.getline(tag.artist, 100);

    std::cout << "Album: ";
    std::cin.getline(tag.album, 100);

    std::cout << "Track number: ";
    std::cin.getline(tag.track, 5);

    std::cout << "Release date: ";
    std::cin.getline(tag.releaseDate, 5);

    char choice;
    std::cout << "Do you want to tag an image? (y,n): ";
    std::cin >> choice;

    std::cin.clear();
    std::cin.ignore(10000, '\n');

    if(choice == 'y' || choice == 'Y') {
        outputImageNames();
        std::cout << "Image (file name): ";
        getline(std::cin, tag.imageName);
        tag.includeImage = true;
    }
    else {
        tag.includeImage = false;
    }

    std::cout << '\n';
}