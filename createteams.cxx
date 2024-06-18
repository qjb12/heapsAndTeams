#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>
#include "json.hpp"
#include "teamdata.h"

using namespace std;

pair<int, int> findFifty(TeamData data){
    double min = 50;
    double diff = 0;
    pair<int, int> lowest;
    int num = data.numPlayers();
    for(int x = 0; x < num; ++x){
        for(int y = 0; y < num; ++y){
            double winP = data.winPercentages(x, y);
            if(winP == -1){
                continue;
            }
            else if(winP < 50){
                diff = 50 - winP;
                if(diff < min){
                    min = diff;
                    lowest.first = x;
                    lowest.second = y;
                }
            } else {
                diff = winP - 50;
                if(diff < min){
                    min = diff;
                    lowest.first = x;
                    lowest.second = y;
                }
            }
        }
    }
    return lowest;
}

int main(int argc, char** argv){
    if(argc > 2){
        cout << "Too many files" << endl;
        return 0;
    }
    ifstream file(argv[1]);
    nlohmann::json jsonObject;
    if(!file.is_open()){
        cout << "file cannot be opened" << endl;
        return 0;
    }
    TeamData data(argv[1]);
    vector<pair<int, int>> teams;
    int numTeams = data.numPlayers() / 2;
    int teamsMade = 0;
    while(teamsMade < numTeams){
        pair<int, int> players = findFifty(data);
        data.removePlayers(players);
        teams.push_back(players);
        ++teamsMade;
    }

    nlohmann::json jsonProduct;
    jsonProduct["teams"] = teams;
    cout << jsonProduct.dump(2);
}