#include "../../include/v1/ID3v1.h"

// ------------------------------------- Tags ------------------------------------- //

std::string ID3v1::readTitle(){
    int findNull = 0;
    while(title[findNull] != '\0' && findNull < 30){
        findNull++;
    }

    return ch2str(title, findNull);
}

std::string ID3v1::readArtist(){
    int findNull = 0;
    while(artist[findNull] != '\0' && findNull < 30){
        findNull++;
    }
    
    return ch2str(artist, findNull);
}

std::string ID3v1::readAlbum(){
    int findNull = 0;
    while(album[findNull] != '\0' && findNull < 30){
        findNull++;
    }

    return ch2str(album, findNull);
}

std::string ID3v1::readComment(){
    int findNull = 0;
    while(comment[findNull] != '\0' && findNull < 30){
        findNull++;
    }
    
    return ch2str(comment, findNull);
}

std::string ID3v1::readYear(){
    return ch2str(year, 4);
}

std::string ID3v1::readGenre(){
    // --ALERT-- LONG LIST
    switch(genre){
        case 0:  return "Blues";
        case 1:  return "Classic Rock";
        case 2:  return "Country";
        case 3:  return "Dance";
        case 4:  return "Disco";
        case 5:  return "Funk";
        case 6:  return "Grunge";
        case 7:  return "Hip-Hop";
        case 8:  return "Jazz";
        case 9:  return "Metal";
        case 10: return "New Age";
        case 11: return "Oldies";
        case 12: return "Other";
        case 13: return "Pop";
        case 14: return "Rhythm & Blues";
        case 15: return "Rap";
        case 16: return "Reggae";
        case 17: return "Rock";
        case 18: return "Techno";
        case 19: return "Industrial";
        case 20: return "Alternative";
        case 21: return "Ska";
        case 22: return "Death Metal";
        case 24: return "Pranks";
        case 25: return "Soundtrack";
        case 26: return "Ambient";
        case 27: return "Trip-Hop";
        case 28: return "Vocal";
        case 29: return "Jazz & Funk";
        case 30: return "Fusion";
        case 31: return "Trance";
        case 32: return "Classical";
        case 33: return "Instrumental";
        case 34: return "Acid";
        case 35: return "House";
        case 36: return "Game";
        case 37: return "Sound clip";
        case 38: return "Gospel";
        case 39: return "Noise";
        case 40: return "Alternative Rock";
        case 41: return "Bass";
        case 42: return "Soul";
        case 43: return "Punk";
        case 44: return "Space";
        case 45: return "Meditative";
        case 46: return "Instrumental Pop";
        case 47: return "Instrumental Rock";
        case 48: return "Ethnic";
        case 49: return "Gothic";
        case 50: return "Darkwave";
        case 51: return "Techno-Industrial";
        case 52: return "Electronic";
        case 53: return "Pop-Folk";
        case 54: return "Eurodance";
        case 55: return "Dream";
        case 56: return "Southern Rock";
        case 57: return "Comedy";
        case 58: return "Cult";
        case 59: return "Gangsta";
        case 60: return "Top 40";
        case 61: return "Christian Rap";
        case 62: return "Pop/Funk";
        case 63: return "Jungle music";
        case 64: return "Native US";
        case 65: return "Cabaret";
        case 66: return "New Wave";
        case 67: return "Psychedelic";
        case 68: return "Rave";
        case 69: return "Showtunes";
        case 70: return "Trailer";
        case 71: return "Lo-Fi";
        case 72: return "Tribal";
        case 73: return "Acid Punk";
        case 74: return "Acid Jazz";
        case 75: return "Polka";
        case 76: return "Retro";
        case 77: return "Musical";
        case 78: return "Rock 'n' Roll";
        case 79: return "Hard Rock";

        default: return "";                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
    }
}


// ------------------------------------- Return ------------------------------------- //

std::string ID3v1::get(const std::string &whatID){
    // Check if file exists
    if(!fileExists) return "File Error";

    // Check if tag exists
    if(!tagExists) return "ID3 Missing";
    
    // Search for tag
    if(whatID == "TITLE")         return readTitle();
    else if(whatID == "ARTIST")   return readArtist();
    else if(whatID == "ALBUM")    return readAlbum();
    else if(whatID == "COMMENT")  return readComment();
    else if(whatID == "YEAR")     return readYear();
    else if(whatID == "GENRE")    return readGenre();  // Does not include Winamp's extensions

    return "Invalid tag";
}