#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
//#include <Windows.h>

using namespace std;

int main() {
    /*
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    */

    string command, name1, name2;
    // Словарь: имя человека ? множество его друзей
    unordered_map<string, unordered_set<string>> friends;

    // Выводим меню с описанием команд
    cout << "\n--- Меню команд ---\n";
    cout << "Доступные команды:\n";
    cout << "  FRIENDS <имя1> <имя2>   — сделать <имя1> и <имя2> друзьями\n";
    cout << "  COUNT <имя>             — вывести количество друзей у <имя>\n";
    cout << "  QUESTION <имя1> <имя2>  — проверить, друзья ли <имя1> и <имя2>\n";
    cout << "  EXIT                    — завершить программу\n";
    cout << "--------------------------\n";

    // Основной цикл ввода команд
    while (true) {
        cout << "\nВведите команду: ";
        cin >> command;

        // Выход по команде EXIT
        if (command == "EXIT") break;

        // Обработка команды FRIENDS
        if (command == "FRIENDS") {
            cin >> name1 >> name2;

            // Добавляем name2 в друзья name1 и наоборот
            friends[name1].insert(name2);
            friends[name2].insert(name1);
        }

        // Обработка команды COUNT
        else if (command == "COUNT") {
            cin >> name1;

            // Выводим количество друзей у name1
            cout << friends[name1].size() << endl;
        }

        // Обработка команды QUESTION
        else if (command == "QUESTION") {
            cin >> name1 >> name2;

            // Проверяем, содержится ли name2 в друзьях name1
            if (friends[name1].count(name2)) {
                cout << "YES" << endl;
            }
            else {
                cout << "NO" << endl;
            }
        }
        // Обработка неизвестной команды
        else {
            cout << "Неизвестная команда. Повторите ввод.\n";
        }
    }

    return 0; // Завершение программы
}
