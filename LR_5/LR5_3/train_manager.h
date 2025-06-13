#pragma once
#include <string>
#include <vector>
#include <map>
#include "train.h"

using namespace std;

class TrainManager {
public:
    TrainManager(int min_stops = 2);

    void CreateTrain(const string& name, const vector<string>& towns);
    vector<string> GetTrainsForTown(const string& town) const;
    map<string, vector<string>> GetTownsForTrain(const string& train) const;
    map<string, Train> GetAllTrains() const;

private:
    map<string, Train> trains;
    map<string, vector<string>> town_to_trains;
    int min_stops;
};