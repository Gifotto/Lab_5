#include "train_manager.h"
#include <iostream>
#include <unordered_set>

using namespace std;

TrainManager::TrainManager(int min_stops)
    : min_stops(min_stops) {
}

void TrainManager::CreateTrain(const string& name, const vector<string>& towns) {
    // Проверка минимального количества остановок
    if (towns.size() < static_cast<size_t>(min_stops)) {
        cout << "Train \"" << name << "\" not created: requires at least "
            << min_stops << " stops\n";
        return;
    }

    // Проверка на повторяющиеся станции
    unordered_set<string> unique_towns(towns.begin(), towns.end());
    if (unique_towns.size() != towns.size()) {
        cout << "Train \"" << name << "\" not created: duplicate stations in route\n";
        return;
    }

    // Добавление поезда
    Train train(name, towns);
    trains[name] = train;

    for (const string& town : towns) {
        town_to_trains[town].push_back(name);
    }
}

vector<string> TrainManager::GetTrainsForTown(const string& town) const {
    if (town_to_trains.count(town)) {
        return town_to_trains.at(town);
    }
    return {};
}

map<string, vector<string>> TrainManager::GetTownsForTrain(const string& name) const {
    map<string, vector<string>> result;
    if (!trains.count(name)) return result;

    const auto& towns = trains.at(name).GetTowns();
    for (const string& town : towns) {
        vector<string> others;
        for (const string& other : town_to_trains.at(town)) {
            if (other != name) {
                others.push_back(other);
            }
        }
        result[town] = others;
    }
    return result;
}

map<string, Train> TrainManager::GetAllTrains() const {
    return trains;
}
