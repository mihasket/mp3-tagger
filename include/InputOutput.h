#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

std::string cutPath(std::string filePath, const unsigned int size);
void outputMp3FileNames();
void outputImageNames();
void inputTagDescription(ID3v2Tag& tag, const unsigned int filePosition, std::string fileName);

#endif