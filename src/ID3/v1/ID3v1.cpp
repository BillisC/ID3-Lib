#include "../../../include/ID3/v1/ID3v1.h"

ID3v1::ID3v1(const std::string &songPath){
    this->songPath = songPath;
    
    ptrSongFile.open(songPath, std::ios::in | std::ios::out | std::ios::binary);
    if(ptrSongFile.is_open()) fileExists = true;
    else fileExists = false;
}

ID3v1::~ID3v1(){
    ptrSongFile.close();
    ptrSongFile = nullptr;
}

// Utilization
bool ID3v1::processTags(){
    // Check if file exists
    if(!fileExists) return false;

    ptrSongFile.seekg(-128, std::ios::end);
    
    // Read tag
    ptrSongFile.read(reinterpret_cast<char *>(tag), 3);
    if( !(tag[0] == 'T' && tag[1] == 'A' && tag[2] == 'G') ){
        tagExists = false;
        return false;
    } 

    // Read Title
    ptrSongFile.read(reinterpret_cast<char *>(title), 30);
    // Read Artist
    ptrSongFile.read(reinterpret_cast<char *>(artist), 30);
    // Read Album
    ptrSongFile.read(reinterpret_cast<char *>(album), 30);
    // Read Year
    ptrSongFile.read(reinterpret_cast<char *>(year), 4);
    // Read Comment
    ptrSongFile.read(reinterpret_cast<char *>(comment), 30);
    // Read Genre
    ptrSongFile.read(reinterpret_cast<char *>(&genre), 1);
    
    tagExists = true;

    return true;
}
