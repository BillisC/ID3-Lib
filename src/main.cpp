#include <filesystem>
#include <iostream>

#include "../include/ID3/v1/ID3v1.h"
#include "../include/ID3/v2/ID3v2.h"

int main(){

    std::vector<std::unique_ptr<ID3v2>> filesV2;
    std::vector<std::unique_ptr<ID3v1>> filesV1;

    // Scan for songs inside of the folder
    std::string path = "C:/Users/gamer/Music/Electronic/";

    for(const auto & entry : std::filesystem::directory_iterator(path)){
        if(entry.path().extension() == ".mp3"){
            auto id2 = std::make_unique<ID3v2>(entry.path().string());
            if(id2->processTags()){
                filesV2.push_back(std::move(id2));
            }
        }
    }

    std::vector<std::string> showWhat = { "TIT2", "TPE2", "TALB", "COMM"};
    int linePos[showWhat.size()] = { 0 };

    int num;
    for(auto it = filesV2.begin(); it != filesV2.end(); it++){
        num = 0;
        for(int i = 0; i < (int)showWhat.size(); i++){
            std::string text = (*it)->get(showWhat[num]);
            if(linePos[num] < (int)text.length()) linePos[num] = text.length();

            num++;
        }
    }

    for(auto it = filesV2.begin(); it != filesV2.end(); it++){
        num = 0;
        for(int i = 0; i < (int)showWhat.size(); i++){
            std::string text = (*it)->get(showWhat[num]);
            std::cout << text;
            for(int i = text.length(); i < linePos[num]; i++){
                std::cout << " ";
            }
            std::cout << " | ";

            num++;
        }

        std::cout << "\n";
    }

    return 0;
}