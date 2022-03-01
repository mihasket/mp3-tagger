#include <iostream>
#include <fstream>
#include "../include/Tag.h"
#include "../include/Files.h"
#include "../include/FileExtension.h"
#include "../include/InputOutput.h"

int main() {
    const unsigned int size = getNumberOfMp3Files();
    unsigned int filePosition = 0;
    bool includeImage;
    ID3v2Tag tag[size];
    std::string fileNames[size];
    std::string taggedFileNames[size];
    std::fstream mp3Files[size];

    // Fstream objects where i write the tagged data
    std::fstream taggedMp3Files[size];

    outputMp3FileNames();

    createFstreamObjects(mp3Files, fileNames);
    createTaggedFstreamObjects(taggedMp3Files, taggedFileNames);

    // Input file stream data
    for(unsigned int i = 0; i < size; i++) {
        ++filePosition;
        inputTagDescription(tag[i], filePosition, includeImage);
    }

    // Tagging
    for(unsigned int i = 0; i < size; i++) {
        tagMP3File(taggedMp3Files[i], tag[i], includeImage);
    }

    // Copy information to new file
    for(unsigned int i = 0; i < size; i++) {
        copyMP3DataToFile(taggedMp3Files[i], mp3Files[i]);
    }

    // Remove old files
    for(unsigned int i = 0; i < size; i++) {
        // Convert std::string fileNames to const char pointer
        const char* file = fileNames[i].c_str();

        remove(file);
    }

    // Rename the new files to the old ones
    for(unsigned int i = 0; i < size; i++) {
        const char* oldName = taggedFileNames[i].c_str();
        const char* newName = fileNames[i].c_str();

        rename(oldName, newName);
    }

    closeFstreamObjects(mp3Files, size);
    closeFstreamObjects(taggedMp3Files, size);

    return 0;
}