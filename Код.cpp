#include <iostream>
#include "windows.h"
#include <cmath>
#include <iomanip> // бібліотека для форматування виводу
using namespace std;

//Geom4. Дано дійсні числа (Хі, Уі), і = 1,2,...n, - координати точок на площині. Визначити кількість 
//точок, що потрапляють в фігупу червоного кольору.
void task_1(); //завдання 1, декларація функції

//Таб.2, #8. Дано дійсне число х і натуральне число n. Необхідно обчислити значення виразу
//при заданих x i n та вивести для парних варіантів значення кожного третього, для непарного - 
//кожного четвертого елемента.
void task_2(); //завдання 2, декларація функції

// Tаб.3, #6. Дослідити ряд на збіжність. 
void task_3(); // завдання 3, декларація функції

int main() {
    SetConsoleOutputCP(1251);
    int menu; // зміна для номеру завдання
    do
    { // початок циклу
        cout << "Номер завдання:"; //введення номеру завдання
        cin >> menu; // обирання номеру завдання
        cout << endl; //вільна строка
        switch (menu) {
        case 1: task_1(); break; // 1 - завдання 1
        case 2: task_2(); break; // 2 - завдання 2
        case 3: task_3(); break; // 3 - завдання 3
        case -1: cout << "Вихід..." << endl; break; // -1 - вихід
        default: cout << "Помилка! Лише 1, 2 або 3!" << endl; // інший номер - повторити
        }
        cout << endl;
    } // кінець циклу
    while (menu != -1); // умова виконання циклу
    return 0;
}

// функція перевірки входження точки в коло
bool isInCircle(int x, int y, int r, float area_yellow) {
    double distance = x * x + y * y;
    return (distance <= r * r) || (x <= 0 && y >= 0 && distance <= area_yellow) || (x <= 0 && y <= 0 && distance <= r * r) || (x >= 0 && y <= 0 && distance <= r * r);
}

void task_1() {
    double r;
    int n;

    cout << "Введіть радіус кола: "; // введення радіуса
    cin >> r;

    cout << "Введіть кількість точок: "; // введення кількості точок
    cin >> n;

    // знаходимо відрізок жовтої частини кола
    float cath_small_yell_tris = r / 4;
    float dist_2_chord = r - cath_small_yell_tris;

    // знаходимо площу повної хорди
    double zmensh = r * r * acos(dist_2_chord / r);
    double vdmk = dist_2_chord * sqrt(r * r - dist_2_chord * dist_2_chord);

    double S_chord = zmensh - vdmk;
    double area_yellow = S_chord / 2; // площа жовтої частини на колі

    int count = 0; // лічильник точок у червоній фігурі

    // цикл для введення точок
    for (int i = 0; i < n; ++i) {
        double x, y;
        cout << "Введіть координати точки " << i + 1 << " (x, y): ";
        cin >> x >> y;

        if (isInCircle(x, y, r, area_yellow)) {
            count++;
        }
    }

    cout << "Кількість точок у червоній області: " << count << endl;
}


void task_2() { // завдання 2, реалізація
    double x;
    int n;

    cout << "Введіть значення х: "; // введення числа х
    cin >> x;
    if (x < 0 || x > 2) { //перевірка на коректність
        cout << "Помилка! х має бути в діапазоні [0; 2]." << endl; // сповіщення про помилку
        return;
    }
    cout << "Введіть натуральне число n: "; // введення числа n
    cin >> n;
    if (n <= 0) { //перевірка на коректність
        cout << "Помилка! n має бути натуральним числом." << endl;
        return;
    }

    double num = 1.0; // чисельник
    double denom = 1.0; // знаменник

    for (int i = 1; i <= n; i++) {
        num *= (1 - i * x); // обчислення чисельника
        denom *= (1 + 2 * i * x); // обчислення знаменника
    }
    double result = num / denom; // розрахунок виразу
    cout << "Значення виразу: " << result << endl; // виведення результату

    cout << "Елементи послідовності: " << endl; // виведення значень елементів
    if (n % 2 == 0) {
        for (int i = 3; i <= n; i += 3) {
            cout << "Елемент " << i << ": " << (1 - i * x) << endl; // для парних виведення кожного третього елемента
        }
    }
    else {
        for (int i = 4; i <= n; i += 4) {
            cout << "Елемент " << i << ": " << (1 - i * x) << endl; // для непарних виведення кожного четвертого елемента
        }
    }
}


double term(int n) { // функція для обчислення n-го члена ряду
    return (3.0 * n * tgamma(n + 1)) / pow(n, n);  // tgamma - факторіал
}
void task_3() { // завдання 2, реалізація
    const double e = 1e-10; // мала величина для збіжності
    const double g = 1e5; // верхня межа для розбіжності ряду
    const int M = 1000; // крок виводу результатів
    const int maxIterations = 1000000; // максимальна кількість ітерацій

    double sum = 0.0; //сума ряду

    int n;
    cout << "Введіть початковий індекс n:"; // введення індекса
    cin >> n;

    cout << fixed << setprecision(15); // форматування до 15 знаків після коми
    cout << "Дослідження ряду на збіжність:\n\n";

    while (n <= maxIterations) {
        double currentTerm = term(n); // перевірка умов завершення
        if (fabs(currentTerm) < e) {
            cout << "Ряд збігається на " << n << "-й ітерації.\n";
            break;
        }
        if (fabs(currentTerm) > g) {
            cout << "Ряд розбігається на " << n << "-й ітерації.\n";
            break;
        }
        sum += currentTerm; // додавання поточного члена до суми
        if (n % M == 0) {
            cout << "Ітерація" << n << ", поточна сума: " << sum << "\n"; //
        }
        n++;
    }
    cout << "\nКінцева сума ряду: " << sum << endl; // виведення остаточного результату
    cout << "Кількість ітерацій: " << n << endl;
}
