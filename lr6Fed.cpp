#include <iostream>
#include <string>
#include <limits>
#define NOMINMAX
#include <windows.h>

using namespace std;

class Transport {
private:
    string driver;      // Ім’я водія
    float date;         // Рік прийому на роботу
    int countRace;      // Кількість поїздок 

public:
    Transport(string dr, float dt, int cr) : driver(dr), date(dt), countRace(cr) { }

    void Input() {
        // Очищення буфера перед введенням рядка
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n\nВведіть водія: ";
        getline(cin, driver);

        // Ввід року з перевіркою
        while (true) {
            cout << "Введіть рік прийому на роботу: ";
            try {
                cin >> date;
                // Перевірка на коректність вводу та діапазон (наприклад, > 1950 і <= 2025)
                if (cin.fail() || date < 1950 || date > 2025) {
                    throw runtime_error("Рік повинен бути числом від 1950 до 2025.");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            catch (const runtime_error& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                MessageBoxA(NULL, e.what(), "Помилка вводу", MB_OK | MB_ICONERROR);
            }
        }

        // Ввід кількості рейсів з перевіркою 
        while (true) {
            cout << "Введіть кількість поїздок: ";
            try {
                cin >> countRace;
                if (cin.fail() || countRace < 0) {
                    throw runtime_error("Кількість поїздок повинна бути додатнім цілим числом.");
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            catch (const runtime_error& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                MessageBoxA(NULL, e.what(), "Помилка вводу", MB_OK | MB_ICONERROR);
            }
        }
    }

    void Output() const {
        cout << "Ім'я водія - " << driver
            << ", Рік прийому - " << date << " р."
            << ", Кількість поїздок - " << countRace;
    }
};

class TransportComp : public Transport {
private:
    string company; // Назва перевізника

public:
    TransportComp(string dr, float dt, int cr, string cmp)
        : Transport(dr, dt, cr), company(cmp) {}

    void InputFull() {
        Input(); // Виклик методу базового класу (вже з валідацією)

        // Тут буфер вже чистий після останнього успішного вводу числа в Input()
        cout << "Введіть назву перевізника: ";
        getline(cin, company);
    }

    void OutputFull() const {
        Output();
        cout << ", Назва перевізника - " << company << endl;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    TransportComp obj("Тисминецький Богдан", 2014, 730, "КарпатиТранс");

    // 1. Вивід початкових даних
    obj.OutputFull();

    // 2. Ввід нових даних з перевіркою винятків
    cout << "\n--- Введіть нові дані ---";
    obj.InputFull();

    // 3. Вивід оновлених даних
    cout << "\n--- Оновлені дані ---\n";
    obj.OutputFull();

    cout << endl;
    system("pause");
    return 0;
}