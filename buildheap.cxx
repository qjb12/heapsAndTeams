#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "json.hpp"
#include "priorityqueue.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc > 2){
        cout << "Too many files" << endl;
        return 0;
    }
    ifstream file(argv[1]);
    nlohmann::json jsonObject;
    if(file.is_open()){
        file >> jsonObject;
    } else {
        cout << "file cannot be opened" << endl;
        return 0;
    }

    nlohmann::json jsonProduct;
    int max = jsonObject["metadata"]["maxHeapSize"];
    PriorityQueue queue(max); 
    double num = 0;
    for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr){
        for(auto it = jsonObject[itr.key()].begin(); it != jsonObject[itr.key()].end(); ++it){
            if(it.key() == "key"){
                num = it.value();
            } else if(it.key() == "operation"){
                if(it.value() == "insert"){
                    queue.insert(num);
                } else if(it.value() == "removeMin"){
                    queue.removeMin();
                }
            }
        }
    }
    jsonProduct = queue.JSON();
    cout << jsonProduct.dump(2);
    return 0;
}