#include <iostream>
#include <cmath>
#include <fstream>
#include <locale>
#include <iomanip>
#include <cstdio>
#include <string>
#include <forward_list>
#include <conio.h>

double function(double value);

using namespace std;

void print(forward_list<double> list_x, forward_list<double> list_y);
int check();

int main()
{
    setlocale(LC_ALL, "Russian");
    double M_PI = 3.141592653589793238462643;
    double x, y, *array_x; int i, first_element, second_element;
    do 
    {
        system("cls");
        forward_list<double> list_x, list_y;
        forward_list<double>::iterator for_x = list_x.before_begin(), for_y = list_y.before_begin();
        ofstream fout("file_for_lab_3.txt");
        array_x = new double[11];
        for (i = 0, x = 0; x <= M_PI / 4; x += M_PI / 40, i++) {
            array_x[i] = x;
            y = function(x);
            fout << fixed << setprecision(10) << x << "\t" << fixed << setprecision(10) << y << endl;
        }
        fout.close();

        ifstream fin("file_for_lab_3.txt");
        for (int counter = 0; counter < 11; counter++) {
            fin >> x >> y;
            list_x.insert_after(for_x, x); for_x++;
            list_y.insert_after(for_y, y); for_y++;
        }
        fin.close();

        cout << "Список до добавления элементов:\n" << endl;
        print(list_x, list_y);

        cout << endl;

        for_x = list_x.begin(); for_y = list_y.begin();

        for (int counter = 0; counter < 10; counter++)
        {
            x = (array_x[counter] + array_x[counter + 1]) / 2;
            for_x = list_x.emplace_after(for_x, x);
            for_y = list_y.emplace_after(for_y, function(x));
            for_x++; for_y++;
        }

        delete[] array_x;

        cout << "Список после добавления элементов:\n" << endl;
        print(list_x, list_y);

        cout << endl;
        do
        {
            cout << "От какого элемента удалять: " << endl;
            first_element = check();
            cout << "До какого элемента удалять: " << endl;
            second_element = check();
            if (second_element <= first_element || first_element <= 0 || second_element > 21)
                cout << "Проверьте пожалуйста ввод ещё раз" << endl;
        } while (second_element <= first_element || first_element <= 0 || second_element > 21);

        if (first_element == 1 && second_element == 21) 
        { 
            list_x.clear(); list_y.clear();
            cout << "\nТеперь список пуст" << endl;
        }
        else
        {
            forward_list<double>::iterator interator_x_1 = list_x.before_begin(), iterator_y_1 = list_y.before_begin();
            forward_list<double>::iterator interator_x_2 = list_x.before_begin(), iterator_y_2 = list_y.before_begin();

            for (int i = 0; i < first_element - 1; i++) { interator_x_1++, iterator_y_1++; }
            for (int i = 0; i <= second_element; i++) { interator_x_2++, iterator_y_2++; }
            list_x.erase_after(interator_x_1++, interator_x_2++); list_y.erase_after(iterator_y_1++, iterator_y_2++);
         
            print(list_x, list_y);
        }
       

        cout << "\nНажмите любую клавишу, чтобы продолжить или ESC, чтобы выйти" << endl;
    }while (_getch() != 27);
    return 0;
}

double function(double value) {
    return sin(cos(value));
}

void print(forward_list<double> list_x, forward_list<double> list_y)
{
    forward_list<double>::iterator for_x = list_x.begin(), for_y = list_y.begin();

    cout <<"№" << setw(12) << "X" << "\t" << setw(14) << "Y" << endl;
    int i = 1;
    while (for_x != list_x.end() && for_y != list_y.end())
    {   
        cout << fixed << setprecision(2) << i << "\t" <<  fixed << setprecision(10) << *for_x << "\t" << fixed << setprecision(10) << *for_y << endl;
        *for_x++; *for_y++; i++;
    }
}
int check() 
{
    char array[5]; int end, value;
    do
    {
        scanf_s("%d", &value);
        fgets(array, sizeof(array), stdin);
        if (strlen(array) > 1)
        {
            fflush(stdin);
            cout << "Вы ввели данные не численного типа(букву, символ или знак)\nПожалуйста, повторите свой ввод\n" << endl;
            return -1;
        }
        else
            return value;
    } while (end != 1);

    return value;
}