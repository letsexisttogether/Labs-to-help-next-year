#include <iostream>
#include<deque>
#include<string>
#include<locale>
#include<conio.h>
#include<cmath>
#include<stack>
#include<cctype>
#include<cstdio>

using namespace std;

void deque_act(deque<int>& deque);
void print_deque(deque<int>& deque);
int first_event();
int palindrom();
void polish_notation();
int prior(char oper);
bool check_number(char toCheck);
bool check_oper(char c);

int check_int(string message);
void cont();

int main()
{
    setlocale(LC_ALL, "Russian");
    char select; deque<int> deque;
    do
    {   
        do
        {
            system("cls");
            cout << "Выберете дейстиве:\n1. Двухсторонняя очередь\n2. Проверка скобок\n3. Палиндром\n4. Постфиксная форма\n5. Выход" << endl;
            select = _getch();
        } while (select != '1' && select != '2' && select != '3' && select != '4' && select != '5');
        switch (select)
        {
        case '1':
            deque_act(deque);
            break;
        case '2':
            first_event();
            break;
        case '3':
            palindrom();
            break;
        case '4':
            polish_notation();
            cont();
            break;
        }
    } while (select != '5');
    return 0;
}

void deque_act(deque<int>& deque)
{
    char act, select; int number, value;
    do
    {
        do
        {
            print_deque(deque);
            cout << "Выберете дейстиве:\n1. Добавить элементы в очередь\n2. Удалить элемент в очереди\n3. Выход" << endl;
            act = _getch();
        } while (act != '1' && act != '2' && act != '3');
        switch (act)
        {
        case '1':
            do
            {   
                print_deque(deque);
                cout << "Выберете дейстиве:\n1. Добавить элемент в начало\n2. Добавить элемент в конец" << endl;
                select = _getch();
            } while (select != '1' && select != '2');
            value = check_int("Введите элемента: ");
            if (select == '1')
                deque.push_front(value);
            else
                deque.push_back(value);
            break;
        case '2':
            if (deque.empty())
            {
                cout << "\nВыполнить действие не удалось, очередь пустая";
                cont();
            }
            else
            {
                if (deque.size() != 1)
                {
                    do
                    {
                        cout << "\nВыберете дейстиве:\n1. Удалить первый элемент\n2. Удалить последний элемент" << endl;
                        select = _getch();
                    } while (select != '1' && select != '2');
                    if (select == '1')
                        deque.pop_front();
                    else if (select == '2')
                        deque.pop_back();
                }
                else
                    deque.pop_back();
            }
            break;
        }
    } while (act != '3');
}

void print_deque(deque<int>& deque)
{
    system("cls");
    if (deque.size() == 0)
        cout << "Двухстороння очередь пустая\n\n";
    else
    {
        cout << "Ваша двухсторонняя очередь: ";
        for (int i = 0; i != deque.size(); i++)
            cout << deque[i] << " ";
        cout << endl << endl;
    }
}

int first_event()
{
    system("cls");
    string keeper;
    deque<char> deque;
    cout << "Введите строку: ";
    cin >> keeper;
    for (auto iter = keeper.begin(); iter != keeper.end(); iter++)
    {
        if (*iter != ')' && *iter != '(' && *iter != '}' && *iter != '{' && *iter != ']' && *iter != '[')
        {
            deque.push_back(*iter);
            deque.pop_back();
        }
        else if (*iter == ')' && deque.size() == 0 || *iter == '}' && deque.size() == 0 || *iter == ']' && deque.size() == 0)
        {
            cout << "\nПоследовательность не верная";
            cont();
            return 0;
        }
        else if (*iter == ')' && deque.front() == '(' || *iter == '}' && deque.front() == '{' || *iter == ']' && deque.front() == '[')
            deque.pop_front();
        else if (*iter == ')' || *iter == '}' || *iter == ']')
        {
            cout << "\nПоследовательность не верная";
            cont();
            return 0;
        }
        else
            deque.push_front(*iter);
    }
    deque.empty() ? cout << "\nПоследовательность верная" : cout << "\nПоследовательность не верная";
    cont();
    return 0;
}

int palindrom()
{
    system("cls");
    string keeper;
    double collector, counter;
    cout << "Введите строку(без пробелов): ";
    cin >> keeper;
    collector = modf(keeper.size() / 2, &counter);
    auto biter = keeper.begin(); auto eiter = keeper.rbegin();
    for (int i = 0; i < counter; i++)
    {
        if (tolower(*biter) != tolower(*eiter))
        {
            cout << "\nСтрока не является палиндромом";
            cont();
            return 0;
        }
        biter++; eiter++;
    }
    cout << "\nСтрока является палиндромом";
    cont();
    return 0; 
}

void polish_notation()
{
    stack<char> s_out;
    string s_in;
    char select;
    do
    {
        system("cls");
        cout << "Выберете выражение:\n1. (A-B-C)/D-E*F\n2. (A+B)*C-(D+E)/F\n3.  A/(B-C)+D*(E-F)\n4. (A*B+C)/D-F/E\n>> ";
        cin >> select;
    } while (select != '1' && select != '2' && select != '3' && select != '4');
    switch (select) {
    case '1':
        s_in = "(A-B-C)/D-E*F";
        break;
    case '2':
        s_in = "(A+B)*C-(D+E)/F";
        break;
    case '3':
        s_in = "A/(B-C)+D*(E-F)";
        break;
    case '4':
        s_in = "(A*B+C)/D-F/E";
        break;
    }
    stack<char> oper; int i = 0;
    while (i < s_in.size())
    {
        if (s_in[i] == ')')
        {
            while (!oper.empty() && oper.top() != '(')
            {
                s_out.push(oper.top());
                oper.pop();
            }
            if (!oper.empty())
                oper.pop();
        }
        else if (s_in[i] == '(')
            oper.push(s_in[i]);
        else if (check_oper(s_in[i]))
        {
            while (!oper.empty() && check_oper(oper.top()) && prior(oper.top()) >= prior(s_in[i]))
            {
                s_out.push(oper.top());
                oper.pop();
            }
            oper.push(s_in[i]);
        }
        else if (check_number(s_in[i]))
            s_out.push(s_in[i]);
        i++;
    }
    while (!oper.empty())
    {
        s_out.push(oper.top());
        oper.pop();
    }
    cout << "\nВведённая строка в постфиксной форме: ";
    stack<char> printer;
    while (!s_out.empty())
    {
        printer.push(s_out.top());
        s_out.pop();
    }
    while (!printer.empty())
    {
        cout << printer.top();
        printer.pop();
    }
}

int prior(char oper)
{
    if (oper == '*' || oper == '/') return 2;
    if (oper == '+' || oper == '-') return 1;
}
bool check_number(char toCheck)
{
    return toCheck >= 'A' && toCheck <= 'Z';
}
bool check_oper(char c)
{
    return c == '*' || c == '/' || c == '+' || c == '-';
}

int check_int(string message)
{
    int value;
    char test[10];
    do
    {
        cout << message;
        scanf_s("%d", &value);
        fgets(test, sizeof(test), stdin);
        if (strlen(test) > 1 || value <= 0)
        {
            cout << "Ошибка ввода. Введите данные ещё раз!!!\n\n";
            fflush(stdin);
        }
    } while (strlen(test) > 1 || value <= 0);
    return value;
}

void cont()
{
    char taker;
    cout << "\n\nДля продолжение нажмите Entre" << endl;
    taker = _getch();
}