#ifndef FILES_H
#define FILES_H

bool hasID3v2Tag(std::fstream& file);
unsigned int getNumberOfMp3Files();
unsigned int getID3v2TagSize(std::fstream& file);
void copyMP3DataToFile(std::fstream& taggedFile, std::fstream& originalFile);
void createFstreamObjects(std::fstream file[], std::string fileNames[]);
void createTaggedFstreamObjects(std::fstream file[], std::string fileNames[]);
void closeFstreamObjects(std::fstream file[], const unsigned int size);

#endif