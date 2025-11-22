#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#define NOMINMAX
#include <windows.h>

using namespace std;

// Клас Transportation (Перевезення)
class Transportation {
public:
    // 7 полів різних типів
    string DriverName;      // Ім'я водія
    string VehicleModel;    // Модель авто
    char Category;          // Категорія прав 
    int CargoWeight;        // Вага вантажу (кг)
    double Distance;        // Відстань (км)
    float PricePerKm;       // Ціна за км
    bool IsExpress;         // Чи це експрес доставка

    Transportation()
        : DriverName(""), VehicleModel(""), Category('B'), CargoWeight(0),
        Distance(0.0), PricePerKm(0.0f), IsExpress(false) {}

    // Метод розрахунку вартості
    double CalculateTotalCost() const {
        if (Distance < 0 || PricePerKm < 0) {
            throw runtime_error("Відстань або ціна не можуть бути від'ємними.");
        }
        double total = Distance * PricePerKm;
        return IsExpress ? total * 1.2 : total; // +20% за експрес
    }
};

// Функція для показу помилки (Windows API)
void ShowError(const string& msg) {
    MessageBoxA(NULL, msg.c_str(), "Помилка вводу", MB_OK | MB_ICONERROR);
}

// Універсальна функція для безпечного вводу чисел (int, double, float)
template <typename T>
T GetInput(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ShowError("Невірний формат! Введіть число.");
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// Спеціалізація для char (один символ)
char GetInputChar(const string& prompt) {
    char value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            ShowError("Помилка вводу символу.");
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return toupper(value);
        }
    }
}

// Спеціалізація для bool (1 або 0)
bool GetInputBool(const string& prompt) {
    int val;
    while (true) {
        val = GetInput<int>(prompt);
        if (val == 1 || val == 0) return static_cast<bool>(val);
        ShowError("Введіть 1 (Так) або 0 (Ні).");
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Transportation trip;

    cout << "--- ВВЕДЕННЯ ДАНИХ ПРО ПЕРЕВЕЗЕННЯ ---\n";
    cout << " Введіть ім'я водія: ";
    getline(cin, trip.DriverName);

    cout << " Введіть модель авто: ";
    getline(cin, trip.VehicleModel);

    trip.Category = GetInputChar(" Категорія прав (один символ): ");
    trip.CargoWeight = GetInput<int>(" Вага вантажу (кг): ");
    trip.Distance = GetInput<double>(" Відстань (км): ");
    trip.PricePerKm = GetInput<float>(" Ціна за км (грн): ");
    trip.IsExpress = GetInputBool(" Експрес доставка? (1-Так, 0-Ні): ");

    cout << "\n------------------------------------------------\n";
    cout << " РЕЗУЛЬТАТИ:\n";
    cout << "------------------------------------------------\n";
    cout << " Водій: " << trip.DriverName << "\n";
    cout << " Авто: " << trip.VehicleModel << "\n";
    cout << " Категорія: " << trip.Category << "\n";
    cout << " Вага: " << trip.CargoWeight << " кг\n";
    cout << " Відстань: " << fixed << setprecision(2) << trip.Distance << " км\n";
    cout << " Тариф: " << trip.PricePerKm << " грн/км\n";
    cout << " Тип: " << (trip.IsExpress ? "Експрес" : "Звичайний") << "\n";

    try {
        cout << " ЗАГАЛЬНА ВАРТІСТЬ: " << trip.CalculateTotalCost() << " грн.\n";
    }
    catch (const runtime_error& e) {
        ShowError(e.what());
    }

    return 0;
}