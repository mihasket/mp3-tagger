#include <iostream>
#include <fstream>
#include <string.h>
#include <filesystem>
#include "../include/Tag.h"
#include "../include/FileExtension.h"
#include "../include/FileNames.h"
#include "../include/Genre.h"

void ID3v2Tag::writeHeaderFrame(std::fstream& file, unsigned int size) const{
    file.write(headerFrame, sizeof(headerFrame));
    writeSyncSafeSize(file, size);
}

void ID3v2Tag::writeTextFrame(std::fstream& file, const char* tagID, const char* information) const{
    // Identifier
    file.write(tagID, 4);

    // Size descriptor
    writeSyncUnsafeSize(file, strlen(information)+1);
        
    // Flags
    file.write(flags, sizeof(flags));

    // Text encoding
    file.write(textEncoding, sizeof(textEncoding));

    // Information text
    file.write(information, strlen(information));
}

void ID3v2Tag::writeAttachedPictureFrame(std::fstream& file, std::string fileName, const unsigned int size) const {
    std::fstream picture("images/" + fileName, std::ios::in | std::ios::binary);
        
    // Frame ID
    file.write(attachedPictureID, 4);

    // Size descriptor
    writeSyncUnsafeSize(file, size);

    // Flags
    file.write(flags, sizeof(flags));

    // Text encoding
    file.write(textEncoding, sizeof(textEncoding));

    // MIME type
    if(isJpeg(fileName)) {
        file.write(mimeTypeJpeg, strlen(mimeTypeJpeg));
    }
    else if(isPng(fileName)) {
        file.write(mimeTypePng, strlen(mimeTypePng));
    }

    file.write(null, sizeof(null));

    // Picture type
    file.write(pictureType, sizeof(pictureType));

    // Description
    file.write(null, sizeof(null));
        
    // Picture data
    char byte;

    while(picture.get(byte)) {
        file.write(&byte, 1);
    }

    picture.close();
}   

// Write tag header size
void ID3v2Tag::writeSyncSafeSize(std::fstream& file, unsigned int size) const {
    unsigned int maxSize = 268435455;
    unsigned int syncSafeMask = 254 << 24; // 4261412864

    if(size <= maxSize) {
        size <<= 4;

        for(int i = 0; i < 4; i++) {
            unsigned int byte = size & syncSafeMask;
            byte >>= 25;

            file.write(reinterpret_cast<char*>(&byte), 1);

            size <<= 7;
        }
    }
    else {
        std::cerr << "Error! Size is bigger than the maximum sync safe size.\n";
        exit(1);
    }
}

// Write frame size
void ID3v2Tag::writeSyncUnsafeSize(std::fstream& file, unsigned int size) const {
    unsigned int maxSize = 4294967295;
    unsigned int synchUnsafeMask = 255 << 24; // 4278190080

    if(size <= maxSize) {
        for(int i = 0; i < 4; i++) {
            unsigned int byte = size & synchUnsafeMask;
            byte >>= 24;

            file.write(reinterpret_cast<char*>(&byte), 1);

            size <<= 8;
        }
    }
    else {
        std::cerr << "Error! Size is bigger than the maximum sync unsafe size.\n";
        exit(1);
    }
}

void ID3v2Tag::tagMP3File(std::fstream& file) const {
    if(file.is_open()) {
        unsigned int sizeOfAllFrames = 0;
        unsigned int sizeOfAttachedPictureFrame = 0;

        // 10 = frame header size, 1 = encoding
        sizeOfAllFrames += 10 + strlen(title) + 1;
        sizeOfAllFrames += 10 + strlen(artist) + 1;
        sizeOfAllFrames += 10 + strlen(album) + 1;
        sizeOfAllFrames += 10 + strlen(track) + 1;
        sizeOfAllFrames += 10 + strlen(releaseDate) + 1;

        if(includeGenre) {
            sizeOfAllFrames += 10 + genreName.size() + 1;
        }

        if(includeImage) {
            sizeOfAttachedPictureFrame = 4  + std::filesystem::file_size("images/" + imageName);

            if(isPng(imageName)) {
                sizeOfAttachedPictureFrame += strlen(mimeTypePng);
            }
            else if(isJpeg(imageName)) {
                sizeOfAttachedPictureFrame += strlen(mimeTypeJpeg);
            }

            sizeOfAllFrames += 10 + sizeOfAttachedPictureFrame;
        }
        
        file.clear();
        file.seekg(0);

        writeHeaderFrame(file, sizeOfAllFrames);
        
        writeTextFrame(file, titleID, title);
        writeTextFrame(file, artistID, artist);
        writeTextFrame(file, albumID, album);
        writeTextFrame(file, trackID, track);
        writeTextFrame(file, releaseDateID, releaseDate);
        if(includeGenre) {
            writeTextFrame(file, contentTypeID, genreName.c_str());
        }

        if(includeImage) {
            writeAttachedPictureFrame(file, imageName, sizeOfAttachedPictureFrame);
        }
    }
}

void ID3v2Tag::inputTagDescription(std::string fileName, const unsigned int filePosition) {
    std::cout << filePosition << ". " << cutPath(fileName, fileName.size()) << '\n';
    
    std::cout << "Title: ";
    std::cin.getline(title, 100);

    std::cout << "Artist: ";
    std::cin.getline(artist, 100);

    std::cout << "Album: ";
    std::cin.getline(album, 100);

    std::cout << "Track number: ";
    std::cin.getline(track, 5);

    std::cout << "Release date: ";
    std::cin.getline(releaseDate, 5);

    char choice;
    std::cout << "Do you want to tag a genre? (y,n): ";
    std::cin >> choice;

    std::cin.clear();
    std::cin.ignore(10000, '\n');

    if(choice == 'y' || choice == 'Y') {
        int index;
        Genre::outputGenres();

        std::cout << "Input a number: ";
        std::cin >> index;
        std::cin.clear();
        std::cin.ignore(10000, '\n');

        genreName = Genre::getGenre(index);
        includeGenre = true;
    }
    else {
        includeGenre = false;
    }

    std::cout << "Do you want to tag an image? (y,n): ";
    std::cin >> choice;

    std::cin.clear();
    std::cin.ignore(10000, '\n');

    if(choice == 'y' || choice == 'Y') {
        outputImageNames();
        std::cout << "Image (file name): ";
        getline(std::cin, imageName);
        includeImage = true;
    }
    else {
        includeImage = false;
    }

    std::cout << '\n';
}

bool ID3v2Tag::hasID3v2Tag(std::fstream& file) const {
    char data[3];

    file.clear();
    file.seekg(0);

    file.read(data, 3);

    if(strcmp(data, "ID3") == 0) {
        return true;
    }
    
    return false;
}

unsigned int ID3v2Tag::getID3v2TagSize(std::fstream& file) const {
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