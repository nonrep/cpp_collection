#include <iostream>
#include <random>

using namespace std;

void y1() { cout << "\nНошу маску\n"; }

void y2() { cout << "\nВызвал врача\n"; }

void y3() { cout << "\nСамоизоляция на 2 недели\n"; }

void y4() { cout << "\nСамоизоляция до выздоровления\n"; }

int main() {
    srand(time(NULL));
    int random;
    int choice;
    int s = 1;
    while (choice != 0) {
        switch (s) {
        case 1:
            cout << "\nОпишите свое самочувствие:\n1. Здоров\n3. Появились первые симптомы коронавируса\n\n";
            cin >> choice;
            if (choice == 1)
                y1();
            else if (choice == 3) {
                s = 2;
                y2();
            }
            break;
        case 2:
            random = rand() % 2 + 1;
            cout << "\n--------------------------------------";
            if (random == 1) {
                cout << "\nВрач не обнаружил коронавирус\n";
                s = 3;
                cout << "--------------------------------------\n";
                y3();
            }
            else if (random == 2) {
                s = 4;
                cout << "\nВрач обнаружил коронавирус\n";
                cout << "--------------------------------------\n";
                y4();
            }
            break;
        case 3:
            cout << "\nКаков результат самоизоляции?\n1. Здоров\n2. Болею коронавирусом\n\n";
            cin >> choice;
            if (choice == 1) {
                s = 1;
                y1();
            }
            else if (choice == 2) {
                s = 4;
                y4();
            }
            break;
        case 4:
            cout << "\nОпишите свое самочувствие:\n1. Здоров\n2. Болею коронавирусом\n\n";
            cin >> choice;
            if (choice == 1) {
                s = 1;
                y1();
            }
            else if (choice == 2) {
                y4();
            }
            break;
        }
    }
}