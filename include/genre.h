#ifndef GENRE_H
#define GENRE_H
#include <iostream>

class Genre {
private:
    static const std::string genres[80];
    Genre() = default;

public:
    static std::string getGenre(const unsigned int index);
    static void outputGenres();
};

#endif