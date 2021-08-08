#ifndef ID3V2_H
#define ID3V2_H

#include <vector>
#include <memory>
#include <fstream>
#include <unordered_map>

#include "../../tools.h"

#include "ID3v2_ID.h"
#include "ID3v2_Structs.h"

// ID3v2 tags are always placed in the beginning of the file except for v2.4 which optionally
// allows you to add a footer 10 bytes before the end of it

// The frame tag IDs are seperated in three namespaces: ID3v2_1, ID3v2_3 and ID3v2_4

class ID3v2{
private:
    bool fileExists;  // Indicates file's existance
    bool tagExists;  // Indicates tag's existance

    short int totalFrames;  // Total number of frames
    unsigned int padding;  // Padding at tag's end

    ID3v2_TagHeader tagHeader;  // Tag header

    std::unique_ptr<ID3v2_3_ExtendedTagHeader> e3TagHeader;  // Extended tag header for v2.3
    std::unique_ptr<ID3v2_4_ExtendedTagHeader> e4TagHeader;  // Extended tag header for v2.4
    std::unique_ptr<ID3v2_4_Footer> t4Footer;  // Footer for v2.4

    std::vector<std::unique_ptr<ID3v2_3_4_FrameHeader>> frameHeader34Vector;  // Frame header holder for v2.3 and v2.4
    std::vector<std::unique_ptr<ID3v2_2_FrameHeader>> frameHeader2Vector;  // Frame header holder for v2.2

    std::fstream ptrSongFile;  // File
    std::string songPath;  // File path

public:
    // Constructor / Destructor
    ID3v2(const std::string &songPath);
    ~ID3v2();

    // Utilization
    bool processTags();

    // Read frames
    std::string get(const std::string &whatID);

    // Set frames
    bool set(const std::string &whatID, const std::string &content);
    bool remove(const std::string &whatID);
    bool removeAll();

    // Return tag info
    unsigned int retMVersion() { return tagHeader.ver[0]; }
    unsigned int retRVersion() { return tagHeader.ver[1]; }

    // Public settings
    static int _DefaultSetVersion;

private:
    // Utilization
    bool processTagHeader();
    void processExtendedTagHeader(); // For v2.3 and v2.4
    void processFrameHeader(); // For v2.3 and v2.4
    bool processFooter(); // For v2.4

    // Reset the class
    void Reset();

    // Check 
    std::string checkTagType(const ID3v2_2::FrameID &frameID);
    std::string checkTagType(const ID3v2_3::FrameID &frameID);
    std::string checkTagType(const ID3v2_4::FrameID &frameID);

    // Read frame content
    std::string readTIF(const unsigned int &cPos, const uint32_t &frSize);
    std::string readULF(const unsigned int &cPos, const uint32_t &frSize);
    std::string readPIC(const unsigned int &cPos, const uint32_t &frSize);
    std::string readCOM(const unsigned int &cPos, const uint32_t &frSize);

    // Write
    void writeFile(const char *bufferTagHeader, const char *bufferFrames, const uint32_t &bufferFramesSize, const char *bufferNewFrame, const uint32_t &bufferNewFrameSize, const char *bufferSongData, const uint32_t &bufferSongDataSize, const int addPadding);
    
    char *bufferSong(uint32_t &bufferSongSize);
    char *newTagHeader(const short int &version, const uint32_t &newTagSize);
    char *bufferFrame(const std::unique_ptr<ID3v2_3_4_FrameHeader> &frHeader);

    char *newFrameTIF(const std::string &newFrameID, const std::string &content, uint32_t &newFullFrameSize, const short int &tagVersion);
    char *newFrameULF(const std::string &newFrameID, const std::string &content, uint32_t &newFullFrameSize, const short int &tagVersion);
    char *newFramePIC(const std::string &newFrameID, const std::string &imagePath, uint32_t &newFullFrameSize, const short int &tagVersion);
    char *newFrameCOM(const std::string &newFrameID, const std::string &content, uint32_t &newFullFrameSize, const short int &tagVersion);
    
};

inline int ID3v2::_DefaultSetVersion = 3;

#endif