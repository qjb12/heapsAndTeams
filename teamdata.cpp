#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>
#include "json.hpp"
#include "teamdata.h"

using namespace std;

TeamData::TeamData(string filename){
    ifstream file(filename);
    nlohmann::json jsonObject;
    file >> jsonObject;
    int num = jsonObject["metadata"]["numPlayers"];
    numPlayers_ = num;
    winPercentages_.resize(num, vector<double>(num));
    for(int x = 0; x < num; ++x){
        for(int y = 0; y < num; ++y){
            winPercentages_[x][y] = -1;
        }
    }
    int size = jsonObject["teamStats"].size();
    for(int x = 0; x < size; ++x){
        int indexOne = jsonObject["teamStats"][x]["playerOne"];
        int indexTwo = jsonObject["teamStats"][x]["playerTwo"];
        winPercentages_[indexOne][indexTwo] = jsonObject["teamStats"][x]["winPercentage"];
        winPercentages_[indexTwo][indexOne] = jsonObject["teamStats"][x]["winPercentage"];
    }
}

int TeamData::numPlayers() const {
    return this->numPlayers_;
}

void TeamData::removePlayers(pair<int, int> players){
    int num = this->numPlayers_;
    for(int x = 0; x < num; ++x){
        for(int y = 0; y < num; ++y){
            if(x == players.first || y == players.second || y == players.first || x == players.second){
                this->winPercentages_[x][y] = -1;
            }
        }
    }
}