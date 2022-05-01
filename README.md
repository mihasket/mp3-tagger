# ID3v2 Tagger
A C++ program for ID3v2.3 MP3 tagging.
A work in progress.

# Installation
Clone this repository
```bash
git clone https://github.com/mihasket/mp3-tagger.git
<<<<<<< HEAD
cd mp3-tagger
make install
=======
>>>>>>> f2a0ca48dd778f1e4a146a4a69fccaf2d68d9242
```
This will create 3 directories:
- images 
- mp3files
- obj

# Usage
Put the MP3 files into the directory mp3files. Put the PNG/JPEG files into the directory images.
The only supported image file extensions are PNG and JPG/JPEG.

After installing, run with command:
```
make run
```

# Example
```
make run

MP3 files:
1. song.mp3

1. song.mp3
Title: Apples and Oranges
Artist: Miha
Album: Github EP
Track number: 1
Release date: 2022
Do you want to tag an image? (y,n): y
0. Blues
1. Classic Rock
2. Country
.
.
.
77. Musical
78. Rock & Roll
79. Hard Rock
Input a number: 71
Do you want to tag an image? (y,n): y

JPEG/PNG images:
1. apple.jpeg
2. orange.png
Image (file name): apple.jpeg
```