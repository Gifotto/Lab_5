#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

// qty — это кол-во единиц товаров которые нужно добавить или удалить

// Константы склада
const int maxPerCell = 10;                   // Максимальное количество товара в одной ячейке
const int numZones = 2;                       // Количество зон хранения
const int numShelves = 4;                     // Количество стеллажей в каждой зоне
const int numSections = 18;                   // Количество вертикальных секций в каждом стеллаже
const int numLevels = 5;                      // Количество полок в каждой секции
const int totalCapacity = numZones * numShelves * numSections * numLevels * maxPerCell;

// Типы данных
using Cell = string;                           // Тип для адреса ячейки
using Product = string;                        // Тип для наименования товара
using Warehouse = unordered_map<Cell, map<Product, int>>;  // Склад: ячейка -> товар -> количество

Warehouse warehouse;                           // Глобальное хранилище склада

// Проверка правильности адреса ячейки
bool isValidCell(const Cell& addr) {
    if (addr.size() < 5 || (addr[0] != 'А' && addr[0] != 'Б')) return false;
    int shelf = addr[1] - '0';                    // 1 цифра
    int section = stoi(addr.substr(2, 2));        // 2 цифры
    int level = addr[4] - '0';                    // 1 цифра
    
    // Проверка диапазонов
    return shelf >= 1 && shelf <= numShelves &&
           section >= 1 && section <= numSections &&
           level >= 1 && level <= numLevels;
}

// Подсчёт общего количества товара в конкретной ячейке
int cellLoad(const Cell& cell) {
    int sum = 0;
    for (const auto& entry : warehouse[cell]) {
        const auto& cell = entry.first;
        const auto& products = entry.second;
        sum += products;
    }
    return sum;
}

// Добавление товара в ячейку
void addProduct(const Product& name, int qty, const Cell& cell) {
    if (!isValidCell(cell)) {
        cout << "Неверный адрес ячейки.\n";
        return;
    }

    int current = cellLoad(cell);
    if (current + qty > maxPerCell) {
        cout << "Ошибка: Ячейка переполнена. Доступно: " << (maxPerCell - current) << "\n";
        return;
    }

    warehouse[cell][name] += qty;
    cout << "Товар добавлен.\n";
}

// Удаление товара из ячейки
void remProduct(const Product& name, int qty, const Cell& cell) {
    if (!isValidCell(cell) || warehouse.find(cell) == warehouse.end() || warehouse[cell].find(name) == warehouse[cell].end()) {
        cout << "Ошибка: Товар не найден в ячейке.\n";
        return;
    }

    if (warehouse[cell][name] < qty) {
        cout << "Ошибка: Недостаточно товара. В наличии: " << warehouse[cell][name] << "\n";
        return;
    }

    warehouse[cell][name] -= qty;

    // Если количество товара стало 0 — удаляем товар из ячейки
    if (warehouse[cell][name] == 0) {
        warehouse[cell].erase(name);
        if (warehouse[cell].empty())
            warehouse.erase(cell); // Если ячейка пуста, удаляем её
    }

    cout << "Товар удален.\n";
}

void info() {
    int totalUsed = 0; // Общее количество товара на складе
    map<char, int> zoneUsed; // Занятость по зонам (А, Б, В)

    // Подсчёт загруженности ячеек и зон
    for (const auto& entry : warehouse) {
        const auto& cell = entry.first;
        const auto& products = entry.second;

        int cellQty = 0;
        for (const auto& productEntry : products)
            cellQty += productEntry.second;

        totalUsed += cellQty;
        zoneUsed[cell[0]] += cellQty; // cell[0] — первая буква адреса — зона
    }

    // Вывод общего процента загрузки склада
    cout << fixed << setprecision(2);//вывод числа с точностью до двух знаков после запятой
    cout << "Загрузка склада: " << (totalUsed * 100.0 / totalCapacity) << "%\n";

    // Вывод загрузки по каждой зоне
    for (char zone : {'А', 'Б'}) {
        int zoneCapacity = numShelves * numSections * numLevels * maxPerCell;
        cout << "Зона " << zone << ": " << (zoneUsed[zone] * 100.0 / zoneCapacity) << "%\n";
    }

    // Содержимое занятых ячеек
    cout << "\nСодержимое ячеек:\n";
    for (const auto& entry : warehouse) {
        const auto& cell = entry.first;
        const auto& products = entry.second;

        cout << cell << ":\n";
        for (const auto& productEntry : products) {
            cout << "  " << productEntry.first << ": " << productEntry.second << "\n";
        }
    }

    // Список всех пустых ячеек
    cout << "\nПустые ячейки:\n";
    for (char zone : {'А', 'Б'}) {
        for (int shelf = 1; shelf <= numShelves; ++shelf) {
            for (int section = 1; section <= numSections; ++section) {
                for (int level = 1; level <= numLevels; ++level) {
                    string addr = string(1, zone) +
                        to_string(shelf) +
                        (section < 10 ? "0" : "") + to_string(section) +
                        to_string(level);


                    // Если ячейка не используется — выводим адрес
                    if (warehouse.find(addr) == warehouse.end())
                        cout << addr << " ";
                }
            }
        }
    }
    cout << "\n";
}


// Главная функция программы
int main() {
    
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    string command;
    cout << "Склад: команды\n ADD <*наименование товара> <количество> <адрес ячейки**>\n REMOVE <наименование товара> <количество> <**адрес ячейки>\n INFO\n EXIT\n\n";
    cout << "*Если в товаре не одно слово то через [ _ ]\n**Адресс ячейки:\n1) А, Б - зона хранения - теплый, холодный склад;"
        << "\nПредупреждение: нулевых стелажей, полок и ячеек не существует\n"
        << "2) 0 - порядковый номер стеллажа;\n"
        << "3) 00 - порядковый номер вертикальной секции стеллажа;\n"
        << "4) 0 - порядковый номер полки.\n\n";

    while (true) {
        cout << "> ";
        cin >> command;

        
        if (command == "ADD") {
            string name, cell;
            int qty;
            cin >> ws;                    // Пропуск пробелов
            getline(cin, name, ' ');     // Считываем название товара до первого пробела
            cin >> qty >> cell;         // Считываем количество и ячейку
            addProduct(name, qty, cell);

        } else if (command == "REMOVE") {
            string name, cell;
            int qty;
            cin >> ws;
            //cin.ignore();
            getline(cin, name, ' ');     // Считываем название товара до первого пробела
            cin >> qty >> cell;
            remProduct(name, qty, cell);

        } else if (command == "INFO") {
            info();

        } else if (command == "EXIT") {
            break;

        } else {
            cout << "Неизвестная команда, проверьте регистр.\n";
        }
    }

    return 0;
}
