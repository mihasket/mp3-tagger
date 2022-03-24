#ifndef FILES_H
#define FILES_H

bool hasID3v2Tag(std::fstream& file);
unsigned int getNumberOfMp3Files();
void copyMP3DataToFile(std::fstream& taggedFile, std::fstream& originalFile, ID3v2Tag& tag);
void createFstreamObjects(std::fstream file[], std::string fileNames[]);
void createTaggedFstreamObjects(std::fstream file[], std::string fileNames[]);
void closeFstreamObjects(std::fstream file[], const unsigned int size);

#endif