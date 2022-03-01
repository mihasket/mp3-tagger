#include <iostream>
#include <fstream>
#include <string.h>
#include <filesystem>
#include "../include/FileExtension.h"

struct ID3v2Tag {
    //ID3, then version (0x03, 0x00)
    const char headerFrame[6] = { 0x49, 0x44, 0x33, 0x03, 0x00, 0x00};

    // TIT2 ID for song titles
    const char titleID[4] = { 0x54, 0x49, 0x54, 0x32};

    // TPE1 ID for artist name
    const char artistID[4] = { 0x54, 0x50, 0x45, 0x31};

    // TALB ID for album name
    const char albumID[4] = { 0x54, 0x41, 0x4C, 0x42};

    // TRCK ID for track number
    const char trackID[4] = { 0x54, 0x52, 0x43, 0x4B};

    // TYER ID for release date
    const char releaseDateID[4] = { 0x54, 0x59, 0x45, 0x52};

    // APIC ID for attached pictures
    const char attachedPictureID[4] { 0x41, 0x50, 0x49, 0x43};

    const char flags[2] = { 0x00, 0x00};

    // Text encoding UTF-8
    const char textEncoding[1] = {0x03};

    // MIME type for png
    char mimeTypePng[10] = "image/png";

    // MIME type for jpeg
    char mimeTypeJpeg[11] = "image/jpeg";

    // Picture type for attached pictures, 0x03 = Front album cover
    const char pictureType[1] = {0x03};

    // Null byte
    const char null[1] = {0x00};

    char title[100], artist[100], album[100], track[5], releaseDate[5];

    std::string imageName;

    void writeHeaderFrame(std::fstream& file, unsigned int size) {
        file.write(headerFrame, sizeof(headerFrame));
        writeSyncSafeSize(file, size);
    }

    void writeTextFrame(std::fstream& file, const char tagID[4], char information[]) {
        // Identifier
        file.write(tagID, 4);

        // Size descriptor
        writeSyncUnsafeSize(file, strlen(information)+1);
        
        // Flags
        file.write(flags, sizeof(flags));

        // Text encoding
        file.write(textEncoding, sizeof(textEncoding));

        // Information text
        file.write(information, sizeof(char) * strlen(information));
    }

    void writeAttachedPictureFrame(std::fstream& file, std::string fileName, const unsigned int size) {
        std::fstream picture("../images/" + fileName, std::ios::in | std::ios::binary);
        
        // Frame ID
        file.write(attachedPictureID, sizeof(attachedPictureID));

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

    void writeSyncSafeSize(std::fstream& file, unsigned int size) {
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
        }
    }

    void writeSyncUnsafeSize(std::fstream& file, unsigned int size) {
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
        }
    }
};

void tagMP3File(std::fstream& file, ID3v2Tag tag, bool includeImage) {
    if(file.is_open()) {
        unsigned int sizeOfAllFrames = 0;
        unsigned int sizeOfAttachedPictureFrame;

        // 10 = frame header size, 1 = encoding
        sizeOfAllFrames += 10 + strlen(tag.title) + 1;
        sizeOfAllFrames += 10 + strlen(tag.artist) + 1;
        sizeOfAllFrames += 10 + strlen(tag.album) + 1;
        sizeOfAllFrames += 10 + strlen(tag.track) + 1;
        sizeOfAllFrames += 10 + strlen(tag.releaseDate) + 1;

        if(includeImage) {
            sizeOfAttachedPictureFrame = 4  + std::filesystem::file_size("../images/" + tag.imageName);

            if(isPng(tag.imageName)) sizeOfAttachedPictureFrame += strlen(tag.mimeTypePng);
            else if(isJpeg(tag.imageName)) sizeOfAttachedPictureFrame += strlen(tag.mimeTypeJpeg);

            sizeOfAllFrames += 10 + sizeOfAttachedPictureFrame;
        }
        
        file.clear();
        file.seekg(0);

        tag.writeHeaderFrame(file, sizeOfAllFrames);

        tag.writeTextFrame(file, tag.titleID, tag.title);

        tag.writeTextFrame(file, tag.artistID, tag.artist);

        tag.writeTextFrame(file, tag.albumID, tag.album);

        tag.writeTextFrame(file, tag.trackID, tag.track);

        tag.writeTextFrame(file, tag.releaseDateID, tag.releaseDate);

        if(includeImage) tag.writeAttachedPictureFrame(file, tag.imageName, sizeOfAttachedPictureFrame);
    }
}