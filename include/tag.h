#ifndef TAG_H
#define TAG_H

class ID3v2Tag {
private:
    //ID3, then version (0x03, 0x00)
    const char headerFrame[6] = { 0x49, 0x44, 0x33, 0x03, 0x00, 0x00};

    // TIT2 ID for song titles
    const char* titleID = "TIT2";

    // TPE1 ID for artist name
    const char* artistID = "TPE1";

    // TALB ID for album name
    const char* albumID = "TALB";

    // TRCK ID for track number
    const char* trackID = "TRCK";

    // TYER ID for release date
    const char* releaseDateID = "TYER";

    // APIC ID for attached pictures
    const char* attachedPictureID = "APIC";

    // TCON ID for content type, used for tagging genres
    const char* contentTypeID = "TCON";
    
    // Two flag bytes, they are unused so they are cleared
    const char flags[2] = { 0x00, 0x00};

    // Text encoding UTF-8
    const char textEncoding[1] = {0x03};

    // MIME type for png
    const char* mimeTypePng = "image/png";

    // MIME type for jpeg
    const char* mimeTypeJpeg = "image/jpeg";

    // Picture type for attached pictures, 0x03 = Front album cover
    const char pictureType[1] = {0x03};

    // Null byte
    const char null[1] = {0x00};

    char title[100], artist[100], album[100], track[5], releaseDate[5];
    std::string imageName, genreName;
    bool includeImage, includeGenre;

    // Methods
    void writeHeaderFrame(std::fstream& file, unsigned int size) const;

    void writeTextFrame(std::fstream& file, const char* tagID, const char* information) const;

    void writeAttachedPictureFrame(std::fstream& file, std::string fileName, const unsigned int size) const;

    void writeSyncSafeSize(std::fstream& file, unsigned int size) const;

    void writeSyncUnsafeSize(std::fstream& file, unsigned int size) const;

public:
    ID3v2Tag() = default;

    void tagMP3File(std::fstream& file) const;

    void inputTagDescription(std::string fileName, const unsigned int filePosition);

    bool hasID3v2Tag(std::fstream& file) const;

    unsigned int getID3v2TagSize(std::fstream& file) const;
};

#endif