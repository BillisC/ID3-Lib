#include <iostream>
#include <memory>

#include "../include/v1/ID3v1.h"

int main(){
    std::cout << "Insert song's path: \n";

    std::string path = "";
    std::getline(std::cin, path);

    std::unique_ptr<ID3v1> id1 = std::make_unique<ID3v1>(path);

    if(id1->processTags()){
        std::cout << "\nTitle: ";
        id1->get("TITLE");
        std::cout << "\nArtist: ";
        id1->get("ARTIST");
        std::cout << "\nAlbum: ";
        id1->get("ALBUM");
        std::cout << "\nYear: ";
        id1->get("YEAR");

        if(!id1->set("TITLE", "New Title")) std::cout << "\nSet failed";
        if(!id1->remove("TITLE")) std::cout << "\nRemove failed";
        if(!id1->removeAll()) std::cout << "\nRemove failed";
    }
    else {
        std::cout << "\nNo ID3 tags detected";
        // Automatically creates ID3 tag with the specified tag name
        if(!id1->set("TITLE", "New Title")) std::cout << "\nSet failed";
    }
}