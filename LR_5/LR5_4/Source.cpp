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
    // �������: ��� �������� ? ��������� ��� ������
    unordered_map<string, unordered_set<string>> friends;

    // ������� ���� � ��������� ������
    cout << "\n--- ���� ������ ---\n";
    cout << "��������� �������:\n";
    cout << "  FRIENDS <���1> <���2>   � ������� <���1> � <���2> ��������\n";
    cout << "  COUNT <���>             � ������� ���������� ������ � <���>\n";
    cout << "  QUESTION <���1> <���2>  � ���������, ������ �� <���1> � <���2>\n";
    cout << "  EXIT                    � ��������� ���������\n";
    cout << "--------------------------\n";

    // �������� ���� ����� ������
    while (true) {
        cout << "\n������� �������: ";
        cin >> command;

        // ����� �� ������� EXIT
        if (command == "EXIT") break;

        // ��������� ������� FRIENDS
        if (command == "FRIENDS") {
            cin >> name1 >> name2;

            // ��������� name2 � ������ name1 � ��������
            friends[name1].insert(name2);
            friends[name2].insert(name1);
        }

        // ��������� ������� COUNT
        else if (command == "COUNT") {
            cin >> name1;

            // ������� ���������� ������ � name1
            cout << friends[name1].size() << endl;
        }

        // ��������� ������� QUESTION
        else if (command == "QUESTION") {
            cin >> name1 >> name2;

            // ���������, ���������� �� name2 � ������� name1
            if (friends[name1].count(name2)) {
                cout << "YES" << endl;
            }
            else {
                cout << "NO" << endl;
            }
        }
        // ��������� ����������� �������
        else {
            cout << "����������� �������. ��������� ����.\n";
        }
    }

    return 0; // ���������� ���������
}
