#include "commands.h"
#include <iostream>
#include <sstream>

using namespace std;

void ProcessCommand(const string& line, TrainManager& manager) {
    istringstream iss(line);
    string command;
    iss >> command;

    if (command == "CREATE_TRAIN") {
        string train, town;
        iss >> train;
        vector<string> towns;
        while (iss >> town) towns.push_back(town);
        manager.CreateTrain(train, towns);
    }
    else if (command == "TRAINS_FOR_TOWN") {
        string town;
        iss >> town;
        auto trains = manager.GetTrainsForTown(town);
        cout << "Trains for town " << town << ": ";
        for (const auto& t : trains) cout << t << " ";
        cout << "\n";
    }
    else if (command == "TOWNS_FOR_TRAIN") {
        string train;
        iss >> train;
        auto towns = manager.GetTownsForTrain(train);
        cout << "Towns for train " << train << ":\n";
        for (const auto& in : towns) {
            const auto& town = in.first;
            const auto& others = in.second;
            cout << "  " << town << ": ";
            if (others.empty()) cout << "no other trains";
            else for (const auto& t : others) cout << t << " ";
            cout << "\n";
        }
    }
    else if (command == "TRAINS") {
        auto trains = manager.GetAllTrains();
        cout << "All trains:\n";
        for (const auto& in : trains) {
            const auto& name = in.first;
            const auto& train = in.second;
            cout << "  " << name << ": ";
            for (const auto& town : train.GetTowns()) cout << town << " ";
            cout << "\n";
        }
    }
    else {
        cout << "Unknown command\n";
    }
}