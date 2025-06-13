#pragma once
#include <string>
#include <vector>

using namespace std;

class Train {
public:
    Train(); // Конструктор по умолчанию
    Train(const string& name, const vector<string>& towns);

    string GetName() const;
    const vector<string>& GetTowns() const;

private:
    string name;
    vector<string> towns;
};
