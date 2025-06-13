#include <iostream>
#include <string>
#include <cstdlib>
#include "train_manager.h"
#include "commands.h"

using namespace std;

void PrintMenu() {
    cout << "\n--- Train Manager Menu ---\n";
    cout << "Available commands:\n";
    cout << "  CREATE_TRAIN <name> <town1> <town2> ... <townN>\n";
    cout << "  TRAINS_FOR_TOWN <town>\n";
    cout << "  TOWNS_FOR_TRAIN <train>\n";
    cout << "  TRAINS\n";
    cout << "  EXIT\n";
    cout << "----------------------------\n";
}

int main(int argc, char* argv[]) {
    int min_stops = 2;
    if (argc > 1) {
        min_stops = atoi(argv[1]);
        if (min_stops < 1) min_stops = 2;
    }
    //cin.ignore();

    TrainManager manager(min_stops);
    string line;

    PrintMenu();

    while (true) {
        cout << "\nEnter command: ";
        if (!getline(cin, line) || line == "EXIT") break;
        if (line.empty()) continue;
        ProcessCommand(line, manager);
    }

    return 0;
}