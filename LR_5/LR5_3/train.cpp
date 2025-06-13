#include "train.h"

Train::Train() : name(""), towns() {}

Train::Train(const string& name, const vector<string>& towns)
    : name(name), towns(towns) {
}

string Train::GetName() const {
    return name;
}

const vector<string>& Train::GetTowns() const {
    return towns;
}
