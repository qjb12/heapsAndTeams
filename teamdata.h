#ifndef _TEAMDATA_H_
#define _TEAMDATA_H_
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <utility>
#include "json.hpp"

typedef std::pair<int, int> Value;
typedef std::vector<std::vector<double>> Array;
class TeamData {
 public:
  TeamData(std::string filename);
  int numPlayers() const;
  double winPercentages(int i, int j) const { return winPercentages_[i][j]; }
  void removePlayers(Value players);
 private:
// TODO: decide the type of this variable.
// winPercentages_;
    Array winPercentages_;
    int numPlayers_;
};  // class TeamData
#endif  // _TEAMDATA_H_