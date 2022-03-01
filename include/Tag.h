#ifndef TAG_H
#define TAG_H

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

    void writeHeaderFrame(std::fstream& file, unsigned int size);

    void writeTextFrame(std::fstream& file, const char tagID[4], char information[]);

    void writeAttachedPictureFrame(std::fstream& file, std::string fileName, const unsigned int size);

    void writeSyncSafeSize(std::fstream& file, unsigned int size);

    void writeSyncUnsafeSize(std::fstream& file, unsigned int size);

    unsigned int getID3v2TagSize(std::fstream& file);
};

void tagMP3File(std::fstream& file, ID3v2Tag tag, bool includeImage);

#endif