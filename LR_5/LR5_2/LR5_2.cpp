#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <random>
#include <unordered_set>
#include <algorithm>
#include <map>
//#include <Windows.h>

using namespace std;

// Структура посетителя очереди
struct Visitor {
    string ticket;   // номер талона
    int duration;    // длительность посещения
};

// Структура окна для обработки посетителей
struct Window {
    int id;                      // номер окна
    int total_time = 0;          // суммарное время, которое уже занято
    vector<string> tickets;      // список талонов, обслуженных в этом окне

    // Приоритет в очереди по наименьшему total_time
    bool operator<(const Window& other) const {
        return total_time > other.total_time; // обратный порядок для min-heap
    }
};

// Генератор уникальных номеров талонов
string generate_ticket(unordered_set<string>& used_tickets) {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 999);

    string ticket;
    do {
        stringstream ss;
        ss << "T" << setfill('0') << setw(3) << dis(gen); // формат T001, T034 и т.д.
        ticket = ss.str();
    } while (used_tickets.count(ticket)); // гарантируем уникальность

    used_tickets.insert(ticket); // добавляем в множество использованных
    return ticket;
}

// Преобразование команды в числовой код для использования switch-case
int get_command_code(const string& command) {
    if (command == "ENQUEUE") return 1;
    if (command == "DISTRIBUTE") return 2;
    return 0; // неизвестная команда
}

int main() {
    /*
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    */
    int num_windows;
    cout << ">>> Введите кол-во окон" << endl;
    cout << "<<< ";
    cin >> num_windows;

    vector<Visitor> visitors;             // список всех посетителей
    unordered_set<string> used_tickets;   // множество уже выданных талонов

    cout << "\nКоманды: ENQUEUE — команда принимает продолжительность посещения и выдает номер талона;\nDISTRIBUTE — распределяет посетителей на окна\n\n";

    // Основной цикл ввода команд
    while (true) {
        cout << "<<< ";
        string command;
        cin >> command;

        switch (get_command_code(command)) {
        case 1: { // ENQUEUE
            int duration;
            cin >> duration;
            string ticket = generate_ticket(used_tickets); // создать уникальный талон
            visitors.push_back({ ticket, duration });        // добавить в очередь
            cout << ">>> " << ticket << endl;              // вывести номер талона
            break;
        }
        case 2: { // DISTRIBUTE
            priority_queue<Window> window_queue;

            // Инициализируем все окна
            for (int i = 1; i <= num_windows; ++i) {
                window_queue.push(Window{ i });
            }

            // Распределяем каждого посетителя в наименее загруженное окно
            for (const auto& visitor : visitors) {
                Window win = window_queue.top();  // получаем окно с минимальной загрузкой
                window_queue.pop();               // удаляем его из очереди
                win.total_time += visitor.duration;      // увеличиваем общее время
                win.tickets.push_back(visitor.ticket);   // добавляем талон в список
                window_queue.push(win);           // возвращаем окно обратно
            }

            // Собираем все окна из очереди в вектор
            vector<Window> result;
            while (!window_queue.empty()) {
                result.push_back(window_queue.top());
                window_queue.pop();
            }

            // Сортируем по номеру окна (от меньшего к большему)
            sort(result.begin(), result.end(), [](const Window& a, const Window& b) {
                return a.id < b.id;
                });

            // Выводим результат распределения
            for (const auto& win : result) {
                cout << ">>> Окно " << win.id << " (" << win.total_time << " минут): ";
                for (size_t i = 0; i < win.tickets.size(); ++i) {
                    cout << win.tickets[i];
                    if (i + 1 < win.tickets.size()) cout << ", ";
                }
                cout << endl;
            }

            return 0; // Завершаем программу после распределения
        }
        default:
            cout << ">>> Неизвестная команда" << endl;
        }
    }

    return 0;
}
