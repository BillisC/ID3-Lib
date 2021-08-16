#include <iostream>
#include <memory>

#include "../include/v2/ID3v2.h"

int main(){
    std::cout << "Insert song's path: \n";

    std::string path = "";
    std::getline(std::cin, path);

    std::unique_ptr<ID3v2> id2 = std::make_unique<ID3v2>(path);

    if(id2->processTags()){
        // ID3v2.2
        if(id2->retMVersion() == 2){
            std::cout << "\nTitle: ";
            id2->get("TT2");
            std::cout << "\nArtist: ";
            id2->get("TP1");
            std::cout << "\nAlbum: ";
            id2->get("TAL");
            std::cout << "\nYear: ";
            id2->get("TYE");
        }

        // ID3v2.3+
        else {
            std::cout << "\nTitle: ";
            id2->get("TIT2");
            std::cout << "\nArtist: ";
            id2->get("TPE1");
            std::cout << "\nAlbum: ";
            id2->get("TALB");
            std::cout << "\nComment: ";
            id2->get("COMM");
            if(id2->retMVersion() == 3){
                std::cout << "\nYear: ";
                id2->get("TYER");
            }
            if(id2->retMVersion() == 4){
                std::cout << "\nYear: ";
                id2->get("TDRC");
            }
            
            // Extract image to file
            std::ofstream img;
            img.open("album_art.jpg", std::ios::binary);
            if(img.is_open()){
                int imageSize = 0;
                char *imgCh = id2->getImage(imageSize);

                img.write(imgCh, imageSize);
                img.close();
                
                delete[] imgCh;
            }
            if(!id2->set("COMM", "New Comment")) std::cout << "\nSet failed";
            if(!id2->remove("TIT2")) std::cout << "\nRemove failed";
            if(!id2->removeAll()) std::cout << "\nRemove failed";
        }
    }
    else {
        std::cout << "\nNo ID3 tags detected";
        // Automatically creates ID3 tag with the specified frame
        if(!id2->set("TIT2", "New Title")) std::cout << "\nSet failed";
    }

    return 0;
}