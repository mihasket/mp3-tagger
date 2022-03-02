#include <iostream>
#include <fstream>
#include <string.h>
#include <filesystem>
#include "../include/FileExtension.h"
#include "../include/Tag.h"

using std::filesystem::directory_iterator;

bool hasID3v2Tag(std::fstream& file) {
    char data[3];

    file.clear();
    file.seekg(0);

    file.read(data, 3);

    if(strcmp(data, "ID3") == 0) return true;
    else return false;
}

unsigned int getNumberOfMp3Files() {
    std::string path = "mp3files/";
    unsigned int numberOfFiles = 0;

    for(const auto& entry : directory_iterator(path)) {
        std::string fileName = std::string(entry.path());

        if(isMp3(fileName)) numberOfFiles++;
    }

    return numberOfFiles;
}

unsigned int getID3v2TagSize(std::fstream& file) {
    char data[4];
    unsigned int size = 0;

    file.clear();
    file.seekg(6);
    // Get the tag header size
    file.read(data, 4);
    // Calculate the tag header size in to a number
    size = data[0] << 21;
    size += data[1] << 14;
    size += data[2] << 7;
    size += data[3];

    return size;
}

void copyMP3DataToFile(std::fstream& taggedFile, std::fstream& originalFile) {
    char byte;
    unsigned int size = 0;
    // Check if the original file has a ID3 tag at the beggining
    if(taggedFile.is_open() && originalFile.is_open()) {
        if(hasID3v2Tag(originalFile)) {
            size = getID3v2TagSize(originalFile);
        }
        else {
            std::cerr << "No ID3v2 tag!\n";
        }

        originalFile.clear();
        originalFile.seekg(size);

        while(originalFile.get(byte)) {
            taggedFile.write(&byte, 1);
        }
    }
    else std::cerr << "Error!Cp3dtf\n";
}

void createFstreamObjects(std::fstream file[], std::string fileNames[]) {
    std::string path = "mp3files/";
    unsigned int i = 0;

    for(const auto& entry : directory_iterator(path)) {
        std::string fileName = std::string(entry.path()); 

        if(isMp3(fileName)) {
            fileNames[i] = fileName;
            file[i].open(fileName, std::ios::in | std::ios::binary);
            i++;
        }
    }
}

void createTaggedFstreamObjects(std::fstream file[], std::string fileNames[]) {
    std::string path = "mp3files/";
    unsigned int i = 0;

    for(const auto& entry : directory_iterator(path)) {
        std::string fileName = std::string(entry.path()); 

        if(isMp3(fileName)) {
            fileName.insert(fileName.size()-4, 1, '1');
            fileNames[i] = fileName;

            file[i].open(fileName, std::ios::out | std::ios::binary);
            i++;
        }
    }
}

void closeFstreamObjects(std::fstream file[], const unsigned int size) {
    for(unsigned int i = 0; i < size; i++) {
        file[i].close();
    }
}