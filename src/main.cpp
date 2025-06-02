#include <fstream>
#include "../include/tag.h"
#include "../include/files.h"
#include "../include/fileNames.h"

int main() {
    const unsigned int size = getNumberOfMp3Files();
    ID3v2Tag tag[size];
    std::string fileNames[size];
    std::string taggedFileNames[size];
    std::fstream mp3Files[size];
    std::fstream taggedMp3Files[size];

    outputMp3FileNames();

    createFstreamObjects(mp3Files, fileNames);
    createTaggedFstreamObjects(taggedMp3Files, taggedFileNames);

    // Input file stream data
    for(unsigned int i = 0; i < size; i++) {
        tag[i].inputTagDescription(fileNames[i], i+1);
    }

    // Tagging
    for(unsigned int i = 0; i < size; i++) {
        tag[i].tagMP3File(taggedMp3Files[i]);
    }

    // Copy information to new file
    for(unsigned int i = 0; i < size; i++) {
        copyMP3DataToFile(taggedMp3Files[i], mp3Files[i], tag[i]);
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
