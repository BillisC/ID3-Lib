#ifndef ID3V1_H
#define ID3V1_H

#include <fstream>
#include "../../tools.h"

// ID3v1.1 tags are always placed 128 bytes before the file's end 

// The tags are found on the namespace: ID3v1

class ID3v1{
private:
    bool fileExists;  //Indicate file's existance
    bool tagExists;  // Indicates tag's existance

    // Tags
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    char genre;

    std::fstream ptrSongFile;  // Song file
    std::string songPath;

public:
    // Constructor / Destructor
    ID3v1(const std::string &songPath);
    ~ID3v1();

    // Utilization
    bool processTags();

    // Return tags
    std::string get(const std::string &whatID);

    // Set tags
    bool set(const std::string &whatID, const std::string content);
    bool remove(const std::string &whatID);
    bool removeAll();

private:
    // Return
    std::string readTitle();  
    std::string readArtist();
    std::string readAlbum();
    std::string readComment();
    std::string readYear();
    std::string readGenre();

    // Set tags
    bool setTitle(const std::string content, const bool &remove);
    bool setArtist(const std::string content, const bool &remove);
    bool setAlbum(const std::string content, const bool &remove);
    bool setYear(const std::string content, const bool &remove);
    bool setComment(const std::string content, const bool &remove);
    bool setGenre(const std::string content, const bool &remove);
};


#endif