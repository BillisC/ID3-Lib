#include "../../../include/ID3/v2/ID3v2.h"

// ------------------------------------- Frames ------------------------------------- //

std::string ID3v2::readTIF(const unsigned int &cPos, const uint32_t &frSize){
    ptrSongFile.seekg(cPos, std::ios::beg);

    unsigned int contentSize = 0;

    // Text encoding
    // If it's unicode then another 2 bytes follow to indicate the byte order (BOM)
    char encoding;
    ptrSongFile.read(reinterpret_cast<char *>(&encoding), 1);
    if(encoding == 0x01 || encoding == 0x02){
        char opt_unicode[2];
        ptrSongFile.read(reinterpret_cast<char *>(&opt_unicode), 2);

        contentSize = frSize - 3;
    }
    else{
        contentSize = frSize - 1;
    }

    // The requested content acoording to encoding
    unsigned int count = 0;
    char frameContent[contentSize];
    if(encoding == 0x01 || encoding == 0x02){
        for(; count < contentSize; count++){
            ptrSongFile.read(reinterpret_cast<char *>(&frameContent[count]), 1);
            ptrSongFile.seekg(1, std::ios::cur);
            if(frameContent[count] == '\0') break;
        }
    }
    else{
        count = contentSize;
        ptrSongFile.read(reinterpret_cast<char *>(frameContent), count);
    }


    // Return data converted to string
    if(frameContent[count - 1] == '\0') return ch2str(frameContent, count - 1);
    else return ch2str(frameContent, count);
}

std::string ID3v2::readULF(const unsigned int &cPos, const uint32_t &frSize){
    ptrSongFile.seekg(cPos, std::ios::beg);

    // The requested URL
    char frameContent[frSize];
    ptrSongFile.read(reinterpret_cast<char *>(frameContent), frSize);

    // Return data converted to string
    if(frameContent[frSize - 1] == '\0') return ch2str(frameContent, frSize - 1);
    else return ch2str(frameContent, frSize);
}

std::string ID3v2::readPIC(const unsigned int &cPos, const uint32_t &frSize){
    ptrSongFile.seekg(cPos, std::ios::beg);

    // Text encoding
    char encoding;
    ptrSongFile.read(reinterpret_cast<char *>(&encoding), 1);

    // MIME type
    int mimeCount = 0;
    char mimeType[15];
    mimeType[0] = '1';
    
    while(mimeType[mimeCount] != '\0' && mimeCount < 15){
        mimeCount++;
        ptrSongFile.read(reinterpret_cast<char *>(&mimeType[mimeCount]), 1);
    }
    for(int i = 1; i <= mimeCount; i++){
        mimeType[i - 1] = mimeType[i];
    }

    // Picture type
    char picType;
    ptrSongFile.read(reinterpret_cast<char *>(&picType), 1);

    // Description
    int descCount = 0;
    char description[64];
    description[0] = '1';

    while(description[descCount] != '\0' && descCount < 64){
        descCount++;
        ptrSongFile.read(reinterpret_cast<char *>(&description[descCount]), 1);
    }
    for(int i = 1; i <= descCount; i++){
        description[i - 1] = description[i];
    }

    // Update image size
    unsigned int contentSize = frSize - 1 - mimeCount - 1 - descCount;

    // The requested image
    char frameContent[contentSize];
    ptrSongFile.read(reinterpret_cast<char *>(frameContent), contentSize);

    // Return requested image data converted to string
    return ch2str(frameContent, contentSize);
}

std::string ID3v2::readCOM(const unsigned int &cPos, const uint32_t &frSize){
    ptrSongFile.seekg(cPos, std::ios::beg);

    unsigned int contentSize = 0;

    // Text encoding
    // If it's unicode then another 2 bytes follow to indicate the byte order (BOM)
    char encoding;
    ptrSongFile.read(reinterpret_cast<char *>(&encoding), 1);
    if(encoding == 0x01 || encoding == 0x02){
        char opt_unicode[2];
        ptrSongFile.read(reinterpret_cast<char *>(&opt_unicode), 2);

        contentSize = frSize - 3;
    }
    else{
        contentSize = frSize - 1;
    }

    char language[3];
    ptrSongFile.read(reinterpret_cast<char *>(language), 3);

    // Short description
    int sDescCount = 0;
    char sDescription[30];
    sDescription[0] = '1';

    while(sDescription[sDescCount] != '\0' && sDescCount < 30){
        sDescCount++;
        ptrSongFile.read(reinterpret_cast<char *>(&sDescription[sDescCount]), 1);
    }
    for(int i = 1; i <= sDescCount; i++){
        sDescription[i - 1] = sDescription[i];
    }

    contentSize = contentSize - 3 - sDescCount;

    // The requested content acoording to encoding
    unsigned int count = 0;
    char frameContent[contentSize];
    if(encoding == 0x01 || encoding == 0x02){
        for(; count < contentSize; count++){
            ptrSongFile.read(reinterpret_cast<char *>(&frameContent[count]), 1);
            ptrSongFile.seekg(1, std::ios::cur);
            if(frameContent[count] == '\0') break;
        }
    }
    else{
        count = contentSize;
        ptrSongFile.read(reinterpret_cast<char *>(frameContent), count);
    }


    // Return data converted to string
    if(frameContent[count - 1] == '\0') return ch2str(frameContent, count - 1);
    else return ch2str(frameContent, count);
}


// ------------------------------------- Return ------------------------------------- //

std::string ID3v2::get(const std::string &whatID){
    // Check if file exists
    if(!fileExists) return "File Error";
    
    // Check if tag exists
    if(!tagExists)  return "ID3 Missing";

    // Search for requested tag
    if(tagHeader.ver[0] == 0x02){
        for(auto it = frameHeader2Vector.begin(); it != frameHeader2Vector.end(); it++){
            std::string id_tmp = ch2str((*it)->frID, 3);

            if(id_tmp == whatID){
                if(checkTagType(ID3v2_2::str2FrameID[whatID]) == "TIF")       return readTIF((*it)->cPos, (*it)->frSize);
                else if(checkTagType(ID3v2_2::str2FrameID[whatID]) == "ULF")  return readULF((*it)->cPos, (*it)->frSize);
                else if(checkTagType(ID3v2_2::str2FrameID[whatID]) == "PIC")  return readPIC((*it)->cPos, (*it)->frSize);
                else if(checkTagType(ID3v2_2::str2FrameID[whatID]) == "COM")  return readCOM((*it)->cPos, (*it)->frSize);
                break;
            }
        }
    }
    
    else if(tagHeader.ver[0] == 0x03 || tagHeader.ver[0] == 0x04){
        for(auto it = frameHeader34Vector.begin(); it != frameHeader34Vector.end(); it++){
            std::string id_tmp = ch2str((*it)->frID, 4);

            if(id_tmp == whatID){
                switch(tagHeader.ver[0]){
                    case 0x03:
                        if(checkTagType(ID3v2_3::str2FrameID[whatID]) == "TIF")       return readTIF((*it)->cPos, (*it)->frSize);
                        else if(checkTagType(ID3v2_3::str2FrameID[whatID]) == "ULF")  return readULF((*it)->cPos, (*it)->frSize);
                        else if(checkTagType(ID3v2_3::str2FrameID[whatID]) == "PIC")  return readPIC((*it)->cPos, (*it)->frSize);
                        else if(checkTagType(ID3v2_3::str2FrameID[whatID]) == "COM")  return readCOM((*it)->cPos, (*it)->frSize);
                        break;

                    case 0x04:
                        if(checkTagType(ID3v2_4::str2FrameID[whatID]) == "TIF")       return readTIF((*it)->cPos, (*it)->frSize);
                        else if(checkTagType(ID3v2_4::str2FrameID[whatID]) == "ULF")  return readULF((*it)->cPos, (*it)->frSize);
                        else if(checkTagType(ID3v2_4::str2FrameID[whatID]) == "PIC")  return readPIC((*it)->cPos, (*it)->frSize);
                        else if(checkTagType(ID3v2_4::str2FrameID[whatID]) == "COM")  return readCOM((*it)->cPos, (*it)->frSize);
                        break;    
                }
            }
        }
    }

    return "Frame not found";
}
