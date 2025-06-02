# MP3 Tagger
A C++ program for ID3v2.3 MP3 tagging.
A work in progress.

# Installation
Clone this repository
```bash
git clone https://github.com/mihasket/mp3-tagger.git
cd mp3-tagger
make install
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
make compile
make run
```
You only have to run make compile for the first time.

# Example

![](/screenshot/mp3-tagger-example.png)

![](/screenshot/mp3-tagger-spotify.png)
