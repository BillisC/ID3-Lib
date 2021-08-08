#include <filesystem>

#include "../../../include/ID3/v1/ID3v1.h"

// ------------------------------------- Tags ------------------------------------- //

bool ID3v1::setTitle(const std::string content, const bool &remove){
    // Check if the string is above the size limit of ID3v1
    if(content.length() > 30){
        return false;
    }
    // Go to title's position
    ptrSongFile.seekg(-125, std::ios::end);
    
    // Check if the tag should be removed
    if(!remove){
        char *toWrite = str2ch(content, 30, 0);

        ptrSongFile.write(toWrite, content.length());

        delete[] toWrite;
    }
    else{
        char zero[30] = { 0 };
        ptrSongFile.write(zero, 30);
    }

    return true;
}

bool ID3v1::setArtist(const std::string content, const bool &remove){
    // Check if the string is above the size limit of ID3v1
    if(content.length() > 30){
        return false;
    }
    // Go to artist's position
    ptrSongFile.seekg(-95, std::ios::end);

    // Check if the tag should be removed
    if(!remove){
        char *toWrite = str2ch(content, 30, 0);

        ptrSongFile.write(toWrite, content.length());

        delete[] toWrite;
    }
    else{
        char zero[30] = { 0 };
        ptrSongFile.write(zero, 30);
    }

    return true;
}

bool ID3v1::setAlbum(const std::string content, const bool &remove){
    // Check if the string is above the size limit of ID3v1
    if(content.length() > 30){
        return false;
    }
    // Go to album's position
    ptrSongFile.seekg(-65, std::ios::end);

    // Check if the tag should be removed
    if(!remove){
        char *toWrite = str2ch(content, 30, 0);

        ptrSongFile.write(toWrite, content.length());

        delete[] toWrite;
    }
    else{
        char zero[30] = { 0 };
        ptrSongFile.write(zero, 30);
    }

    return true;
}

bool ID3v1::setYear(const std::string content, const bool &remove){
    // Check if the string is above the size limit of ID3v1
    if(content.length() > 4){
        return false;
    }
    // Go to year's position
    ptrSongFile.seekg(-35, std::ios::end);

    // Check if the tag should be removed
    if(!remove){
        char *toWrite = str2ch(content, 4, 0);

        ptrSongFile.write(toWrite, 4);

        delete[] toWrite;
    }
    else{
        char zero[4] = { 0 };
        ptrSongFile.write(zero, 4);
    }

    return true;
}

bool ID3v1::setComment(const std::string content, const bool &remove){
    // Check if the string is above the size limit of ID3v1
    if(content.length() > 30){
        return false;
    }
    // Go to comment's position
    ptrSongFile.seekg(-31, std::ios::end);

    // Check if the tag should be removed
    if(!remove){
        char *toWrite = str2ch(content, 30, 0);

        ptrSongFile.write(toWrite, content.length());

        delete[] toWrite;
    }
    else{
        char zero[30] = { 0 };
        ptrSongFile.write(zero, 30);
    }

    return true;
}

bool ID3v1::setGenre(const std::string content, const bool &remove){
    // Go to genre's position
    ptrSongFile.seekg(-1, std::ios::end); 

    uint8_t num;

    // Check if the tag should be removed
    if(remove){
        num = 255;
        return true;
    }

    if(content == "Blues")                  num = 0;
    else if(content == "Classic Rock")      num = 1;
    else if(content == "Country")           num = 2;
    else if(content == "Dance")             num = 3;
    else if(content == "Disco")             num = 4;
    else if(content == "Funk")              num = 5;
    else if(content == "Grunge")            num = 6;
    else if(content == "Hip-Hop")           num = 7;
    else if(content == "Jazz")              num = 8;
    else if(content == "Metal")             num = 9;
    else if(content == "New Age")           num = 10;
    else if(content == "Oldies")            num = 11;
    else if(content == "Other")             num = 12;
    else if(content == "Pop")               num = 13;
    else if(content == "Rhythm & Blues")    num = 14;
    else if(content == "Rap")               num = 15;
    else if(content == "Reggae")            num = 16;
    else if(content == "Rock")              num = 17;
    else if(content == "Techno")            num = 18;
    else if(content == "Industrial")        num = 19;
    else if(content == "Alternative")       num = 20;
    else if(content == "Ska")               num = 21;
    else if(content == "Death Metal")       num = 22;
    else if(content == "Pranks")            num = 24;
    else if(content == "Soundtrack")        num = 25;
    else if(content == "Ambient")           num = 26;
    else if(content == "Trip-Hop")          num = 27;
    else if(content == "Vocal")             num = 28;
    else if(content == "Jazz & Funk")       num = 29;
    else if(content == "Fusion")            num = 30;
    else if(content == "Trance")            num = 31;
    else if(content == "Classical")         num = 32;
    else if(content == "Instrumental")      num = 33;
    else if(content == "Acid")              num = 34;
    else if(content == "House")             num = 35;
    else if(content == "Game")              num = 36;
    else if(content == "Sound clip")        num = 37;
    else if(content == "Gospel")            num = 38;
    else if(content == "Noise")             num = 39;
    else if(content == "Alternative Rock")  num = 40;
    else if(content == "Bass")              num = 41;
    else if(content == "Soul")              num = 42;
    else if(content == "Punk")              num = 43;
    else if(content == "Space")             num = 44;
    else if(content == "Meditative")        num = 45;
    else if(content == "Instrumental Pop")  num = 46;
    else if(content == "Instrumental Rock") num = 47;
    else if(content == "Ethnic")            num = 48;
    else if(content == "Gothic")            num = 49;
    else if(content == "Darkwave")          num = 50;
    else if(content == "Techno-Industrial") num = 51;
    else if(content == "Electronic")        num = 52;
    else if(content == "Pop-Folk")          num = 53;
    else if(content == "Eurodance")         num = 54;
    else if(content == "Dream")             num = 55;
    else if(content == "Southern Rock")     num = 56;
    else if(content == "Comedy")            num = 57;
    else if(content == "Cult")              num = 58;
    else if(content == "Gangsta")           num = 59;
    else if(content == "Top 40")            num = 60;
    else if(content == "Christian Rap")     num = 61;
    else if(content == "Pop/Funk")          num = 62;
    else if(content == "Jungle music")      num = 63;
    else if(content == "Native US")         num = 64;
    else if(content == "Cabaret")           num = 65;
    else if(content == "New Wave")          num = 66;
    else if(content == "Psychedelic")       num = 67;
    else if(content == "Rave")              num = 68;
    else if(content == "Showtunes")         num = 69;
    else if(content == "Trailer")           num = 70;
    else if(content == "Lo-Fi")             num = 71;
    else if(content == "Tribal")            num = 72;
    else if(content == "Acid Punk")         num = 73;
    else if(content == "Acid Jazz")         num = 74;
    else if(content == "Polka")             num = 75;
    else if(content == "Retro")             num = 76;
    else if(content == "Musical")           num = 77;
    else if(content == "Rock 'n' Roll")     num = 78;
    else if(content == "Hard Rock")         num = 79;
    else return false;

    ptrSongFile.write(reinterpret_cast<char *>((&num)), 1);

    return true;
}


// ------------------------------------- Set ------------------------------------- //

bool ID3v1::set(const std::string &whatID, const std::string content){
    // Check if file exists
    if(!fileExists) return false;
    
    // Check if tag exists
    if(!tagExists){
        ptrSongFile.seekg(-128, std::ios::end);

        // Write tag
        char tag[3] = {'T', 'A', 'G'};
        ptrSongFile.write(reinterpret_cast<char *>(tag), 3);

        // Zero out the rest
        for(int i = 0; i < 124; i++){
            char zero = 0;
            ptrSongFile.write(&zero, 1);
        }

        // This is done because if genre is set to 0 its considered as "Blues"
        char genre = 255;
        ptrSongFile.write(reinterpret_cast<char *>(&genre), 1);
    }

    if(whatID == "TITLE")         setTitle(content, false);
    else if(whatID == "ARTIST")   setArtist(content, false);
    else if(whatID == "ALBUM")    setAlbum(content, false);
    else if(whatID == "YEAR")     setYear(content, false);
    else if(whatID == "COMMENT")  setComment(content, false);
    else if(whatID == "GENRE")    setGenre(content, false);
    else return false;

    return true;
}

bool ID3v1::remove(const std::string &whatID){
    // Check if file exists
    if(!fileExists) return false;
    
    // Check if tag exists
    if(!tagExists) return false;

    if(whatID == "TITLE")         setTitle("", true);
    else if(whatID == "ARTIST")   setArtist("", true);
    else if(whatID == "ALBUM")    setAlbum("", true);
    else if(whatID == "YEAR")     setYear("", true);
    else if(whatID == "COMMENT")  setComment("", true);
    else if(whatID == "GENRE")    setGenre("", true);
    else return false;

    return true;
}

bool ID3v1::removeAll(){
    // Check if file exists
    if(!fileExists) return false;

    // Check if tag exists
    if(!tagExists) return false;

    // Resize file
    std::filesystem::resize_file(songPath, std::filesystem::file_size(songPath) - 128);

    return true;
}
