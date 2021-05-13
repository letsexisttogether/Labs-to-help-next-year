#include <iostream>
#include <cmath>
#include <conio.h>
#include <iomanip> 
#include <cstring>
#include <limits>

using namespace std;

double arcctg(double x);
double check_value();
void cont();

int main(){
    setlocale(LC_ALL, "Russian");

    double x1, x2, x, value, sum, n; int exit;
    double M_PI = 3.14159265358979323846;
    cout << "Данная программа предназначена для расчёта arcctg на заданном Вами отрезке\n\nОтрезок задаётся двумя точками и разбивается на равных 10 частей\n\n"
        "Точки начала и конца отрезка вводятся в радианах\n\n"
        "Пожалуйста не вводите отрезок, которого не существует, например (a = 2 и b = 2)\n" << endl;
    do
    {
        cout << "Для продолжения нажмите Entre" << endl;
    } while (_getch() == 27);
    do 
    {
        system("cls");
        do {
            do {
                cout << "Введите значение начала отрезка (строго больше 1 и не превышающее 5000): ";
                x1 = check_value();
            } while (x1 == -1);

            do {
                system("cls");
                cout << "Введите значение начала отрезка (строго больше 1 и не превышающее 5000): " << x1 << endl;
                cout << "Введите значние конца отрезка (строго больше начального значния и не превышающее 5000): ";
                x2 = check_value();
            } while (x2 == -1);

            if (x2 <= x1) {
                cout << "Вы ввели конечное значение x меньшее, чем начальное значение x\nПопробуйте ввести точки снова\n" << endl;
                cont();
                x2 = -1;
            }
        } while (x2 <= x1);
        system("cls");
        cout << "Начальное значение x = " << x1 << "\tКонечное значение x = " << x2 << endl << endl;

        cout << setw(5) << "x" << "               Примерное значение" << "            Точное значение" << "          Кол-во ряда" <<"           Погрешность\n" << endl;

        for (x = x1; x <= x2; x += (x2 - x1) / 10) {
            n = 0; sum = 0;
            do {
                value = pow(-1, n) / ((2 * n + 1) * pow(x, 2 * n + 1));
                sum += value;
                n++;
            } while (fabs(arcctg(x) - sum) > 0.001);
    
            cout << left << setprecision(5) << fixed << " " << setw(25) << x << setw(25) << sum << setw(25) << arcctg(x) 
                << setw(25) << n << setw(25) << (fabs(arcctg(x) - sum)) << endl;
        }
        if (fabs(x - (x2 - x1) / 10 - x2) >= 0.00001) {
            n = 0; sum = 0;
            do {
                value = pow(-1, n) / ((2 * n + 1) * pow(x2, 2 * n + 1));
                sum += value;
                n++;
            } while (fabs(arcctg(x2) - sum) > 0.001);
            cout << left << setprecision(5) << fixed << " " << setw(25) << x2 << setw(25) << sum << setw(25) << arcctg(x2)
                << setw(25) << n << setw(25) << (fabs(arcctg(x2) - sum)) << endl;
        }

        cout << "\nЖелаете продолжить - нажмите любую клавишу\nЖелаете выйти - нажмите ESC" << endl;
    } while (_getch() != 27);

    return 0;
}

double arcctg(double x){
    double M_PI = 3.14159265358979323846;
    return (M_PI/2 - atan(x));
}

double check_value() {
    double check_value; 
    char array[5];
    cin >> check_value;
    fgets(array, sizeof(array), stdin);
    if (strlen(array) > 1) {
        system("cls");
        cout << "Вы ввели данные не численного типа(букву, символ или знак)\nПожалуйста, повторите свой ввод\n" << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cont();
        return -1;
    }
    else if (check_value <= 1)
    {
        cout << "Вы ввели значение, которое числено равное или меньше 1\nПопробуйте снова\n" << endl;
        cont();
        return -1;
    }
    else if (check_value > 5000) {
        cout << "Вы ввели значение, числено больше 5000 \nПопробуйте снова\n" << endl;
        cont();
        return -1;
    }
    else 
        return check_value;
}

void cont() {
    do
    {
        cout << "Для продолжения нажмите Entre" << endl;
    } while (_getch() == 27);
    system("cls");
}