#include <iostream>
#include<cstdio>
#include<fstream>
#include<string>
#include<list>
#include<locale>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include<sstream>

using namespace std;

struct Worker
{
    string name, surname, patronymic, post, isTeacher;
    int day, month, year, exp, wage; 
    Worker(string name, string surname, string patronymic, string post, string isTeacher, int day, int month, int year, int exp, int wage)
    {
        this->name = name;
        this->surname = surname;
        this->patronymic = patronymic;
        this->post = post;
        this->isTeacher = isTeacher;
        this->day = day;
        this->month = month;
        this->year = year;
        this->exp = exp;
        this->wage = wage;
    }
};

void add_element(list <Worker>& list_workers);
void print_list(list<Worker>& list_workers, bool wayBack);
void delete_element(list<Worker>& list_workers);
void search_element(const list<Worker>& list_workers);
void sort_elements(list<Worker>& list_workers);

bool comp_name(Worker& a, Worker& b);
bool comp_surname(Worker& a, Worker& b);
bool comp_patronymic(Worker& a, Worker& b);
bool comp_post(Worker& a, Worker& b);
bool comp_day(Worker& a, Worker& b);
bool comp_exp(Worker& a, Worker& b);
bool comp_wage(Worker& a, Worker& b);

void file_out(list<Worker>& list_workers);
void file_in(list<Worker>& list_workers);
void task(list<Worker>& list_workers);
void delete_wish(list<Worker>& list_workers);


string check_string(string message);
int check_int(string message);
void cont();

int main()
{
    setlocale(LC_ALL, "Russian");

    char menu_select, act;
    list<Worker> list_workers;
    do
    {
        do
        {
            system("cls");
            cout << "1. Добавить элемент в список\n2. Вывести весь список\n3. Удаление работника из базы\n4. Поиск сотрудника по критерию\n5. Сортировка по критерию\n6. Работа с файлами\n7. Удаление по критерию\n8. Задание\n9. Выход" << endl;
            menu_select = _getch();
        } while (menu_select < 1 && menu_select > 9);
        switch (menu_select)
        {
        case '1':
            add_element(list_workers);
            break;
        case '2':
            print_list(list_workers, true);
            cont();
            break;
        case '3':
            delete_element(list_workers);
            break;
        case '4':
            search_element(list_workers);
            break;
        case '5':
            sort_elements(list_workers);
            break;
        case '6':
            do
            {
                system("cls");
                cout << "1. Добавить элементы в файл\n2. Взять элементы из файла" << endl;
                act = _getch();
            } while (act !='1' && act != '2');
            if (act == '1')
                file_out(list_workers);
            else if (act == '2')
                file_in(list_workers);
            break;
        case '7':
            delete_wish(list_workers);
            break;
        case '8':
            task(list_workers);
            break;
        }
    } while (menu_select != '9');
    cont();
}

void add_element(list<Worker>& list_workers)
{
    Worker worker("", "", "", "", "", 0, 0, 0, 0, 0);
    char add_select; int after_element; bool catcher;
    system("cls");
    worker.name = check_string("Введите имя сотрудника");
    worker.surname = check_string("Введите фамилию сотрудника");
    worker.patronymic = check_string("Введите отчество сотрудника");
    worker.post = check_string("Введите должность сотрудника");
    do
    {
        cout << "Сотрудник является учителем(введите yes или no)" << endl;
        cin >> worker.isTeacher;
        if (worker.isTeacher != "yes" && worker.isTeacher != "no")
            cout << "Введены неверные данные, попробуйте ещё раз" << endl;
    } while (worker.isTeacher != "yes" && worker.isTeacher != "no");
    do
    {
        catcher = false;
        cout << "Введите дату рождения сотрудника" << endl;
        cin >> worker.day >> worker.month >> worker.year;
        if (worker.day > 31 || worker.day <= 0) { cout << "\nДата введена неверно, повторите попытку" << endl; catcher = true; }
        else if (worker.day > 28 && worker.month == 2) { cout<< "\nДата введена неверно, повторите попытку"<< endl; catcher = true; }
        else if (worker.day > 30 && worker.month == 4 || worker.month == 6 || worker.month == 9 || worker.month == 11) { cout << "\nДата введена неверно, повторите попытку" << endl; catcher = true; }
        else if(worker.year <= 1700 || worker.year > 2021 || worker.month <= 0 || worker.month > 12) { cout << "\nДата введена неверно, повторите попытку" << endl; catcher = true; }
    } while (catcher == true);
    worker.exp = check_int("Введите стаж сотрудника: ");
    worker.wage = check_int("Введите зарплату сотрудника: ");

    cout << "\n1. В начало списка\n2. В конец списка\n3. После элемента" << endl;
    add_select = _getch();
    if (add_select == '1') 
        list_workers.push_front(worker);
    else if (add_select == '2')
        list_workers.push_back(worker);
    else if (add_select == '3')
    {
        if (!list_workers.empty())
        {
            int counter = 1;
            print_list(list_workers, false);
            do
            {
                cout << "\nВведите номер элемента, после которого необходимо вставить новый элемент" << endl;
                cin >> after_element;
            } while (after_element <= 0 || after_element > list_workers.size());
            if (after_element == list_workers.size())
                list_workers.push_back(worker);
            else
            {
                for (list<Worker> ::iterator iter = list_workers.begin(); iter != list_workers.end(); iter++)
                {
                    if (counter == after_element+1)
                        list_workers.insert(iter, worker);
                    counter++;
                }
            }
        }
        else
            list_workers.push_back(worker);
    }
    print_list(list_workers, true);
    cont();
}

void print_list(list<Worker>& list_workers, bool wayBack)
{
    system("cls");
    if (list_workers.empty())
    {
        cout << "Список пуст";
        return cont();
    }
    
    if (wayBack)
    {
        list_workers.reverse();
    }
    int i = 0;
    cout << "Текущий список:\n" << endl ;
    cout << "№     Имя        Фамилия       Отчество       Должность      Учитель      Дата рождения     Опыт работы      Зарплата    \n";
    for (auto iter : list_workers) 
    {
        cout << left << setw(3) << ++i  << left << setw(14) << iter.name << left << setw(14) << iter.surname << left << setw(14) << iter.patronymic << left << setw(14) << iter.post << left << setw(14) << iter.isTeacher
        << iter.day << left  <<  "." << iter.month << left << "." << iter.year << right << setw(18) << iter.exp << right << setw(14) << iter.wage << endl;
    }
    if (wayBack)
    {
        list_workers.reverse();
    }
}

void delete_element(list<Worker>& list_workers)
{
    if (list_workers.empty())
    {
        system("cls");
        cout << "Список пуст";
    }
    else
    {
        int toDelete;
        bool notCorrect;
        do
        {
            print_list(list_workers, false);
            cout << "\nВведите номер сотрудника, которого необходимо удалить из базы: ";
            cin >> toDelete;
            if (toDelete <= 0 || toDelete > list_workers.size())
            {
                notCorrect = true;
                cont();
            }
            else
                notCorrect = false;
        } while (notCorrect == true);
        auto iter = list_workers.begin();
        for (int i = 0; i <= list_workers.size(); i++)
        {
            if (i == toDelete - 1)
            {
                list_workers.erase(iter);
                break;
            }
            iter++;
        }
        print_list(list_workers, true);
    }
    cont();
}

void search_element(const list<Worker>& list_workers)
{
    string s_taker; int i_taker;
    int i = 0; bool exist = false; 
    char search_select;
    do
    {
        system("cls");
        cout << "Выберете критерий для поиска:\n1. Имя\n2. Фамилия\n3. Отчество\n4. Должность работника\n5. День рождения\n6. Месяц рождения\n7. Год рождения\n8. Опыт работы\n9. Зарплата\n0. Все учителя" << endl;
        search_select = _getch();
    } while (search_select != '1' && search_select != '2' && search_select != '3' && search_select != '4' && search_select != '5' && search_select != '6' && search_select != '7' && search_select != '8' && search_select != '9' && search_select != '0');
    cout << "Введите: ";
    if (search_select == '1' || search_select == '2' || search_select == '3' || search_select == '4')
        cin >> s_taker;
    else if(search_select == '5' || search_select == '6' || search_select == '7' || search_select == '8' || search_select == '9')
        cin >> i_taker;
    for (auto iter : list_workers)
    {
        exist = false;
        switch (search_select)
        {
        case '1':
            if (s_taker == iter.name)
                exist = true;
            break;
        case '2':
            if (s_taker == iter.surname)
                exist = true;
            break;
        case '3':
            if (s_taker == iter.patronymic)
                exist = true;
            break;
        case '4':
            if (s_taker == iter.post)
                exist = true;
            break;
        case '5':
            if (i_taker == iter.day)
                exist = true;
            break;
        case '6':
            if (i_taker == iter.month)
                exist = true;
            break;
        case '7':
            if (i_taker == iter.year)
                exist = true;
            break;
        case '8':
            if (i_taker == iter.exp)
                exist = true;
            break;
        case '9':
            if (i_taker == iter.wage)
                exist = true;
            break;
        case '0':
            if (iter.isTeacher == "yes")
                exist = true;
        }
        if (exist == true)
        {
            if (i == 0)
            {
                system("cls");
                cout << "Найденые сотрудники\n" << endl;
                cout << "Имя        Фамилия       Отчество       Должность      Учитель      Дата рождения     Опыт работы      Зарплата    \n";
            }
            cout << left << setw(14) << iter.name << left << setw(14) << iter.surname << left << setw(14) << iter.patronymic << left << setw(14) << iter.post << left << setw(14) << iter.isTeacher
                << iter.day << left << "." << iter.month << left << "." << iter.year << right << setw(18) << iter.exp << right << setw(14) << iter.wage << endl;
            i++;
        }
    }
    if (i == 0)
        cout << "Работника найти не удалось";
    cont();
}

void sort_elements(list<Worker>& list_workers)
{
    char search_select;
    if (!list_workers.empty())
    {
        do
        {
            system("cls");
            print_list(list_workers, false);
            cout << "Выберете критерий для сортировки:\n1. Имя\n2. Фамилия\n3. Отчество\n4. Должность работника\n5. Дата\n6. Опыт работы\n7. Зарплата" << endl;
            search_select = _getch();
        } while (search_select != '1' && search_select != '2' && search_select != '3' && search_select != '4' && search_select != '5' && search_select != '6' && search_select != '7');
        switch (search_select)
        {
        case '1':
            list_workers.sort(comp_name);
            break;
        case '2':
            list_workers.sort(comp_surname);
            break;
        case '3':
            list_workers.sort(comp_patronymic);
            break;
        case '4':
            list_workers.sort(comp_post);
            break;
        case '5':
            list_workers.sort(comp_day);
            break;
        case '6':
            list_workers.sort(comp_exp);
            break;
        case '7':
            list_workers.sort(comp_wage);
            break;
        }
    }
    print_list(list_workers, true);
    cont();
}

bool comp_name(Worker& a, Worker& b) { return a.name < b.name; }
bool comp_surname(Worker& a, Worker& b) { return a.surname < b.surname; }
bool comp_patronymic(Worker& a, Worker& b) { return a.patronymic < b.patronymic; }
bool comp_post(Worker& a, Worker& b) { return a.post < b.post; }
bool comp_day(Worker& a, Worker& b) { return a.day + a.month * 31 + a.year * 365 < b.day + b.month * 31 + b.year * 365; }
bool comp_exp(Worker& a, Worker& b) { return a.exp < b.exp; }
bool comp_wage(Worker& a, Worker& b) { return a.wage > b.wage; }

void file_out(list<Worker>& list_workers)
{ 
    system("cls");
    if (!list_workers.empty())
    {
        ofstream fout("file_for_lab_4.txt");
        for (auto iter : list_workers)
            fout << iter.name << "  " << iter.surname << "  " << iter.patronymic << "  " << iter.post << "  " << iter.isTeacher
            << "  "<< iter.day << " " << iter.month << " " << iter.year << "  " << iter.exp << "  " << iter.wage << endl;
        fout.close();
        cout << "Данные были успешно записаны в файл";
    }
    else
        cout << "Список пуст";
    cont();
}

void file_in(list<Worker>& list_workers)
{
    ifstream fin("file_for_lab_4.txt");
    Worker worker("", "", "", "", "", 0, 0, 0, 0, 0);
    string keeper;
    while (getline(fin, keeper))
    {
        istringstream reader(keeper);
        reader >> worker.name >> worker.surname >> worker.patronymic >> worker.post >> worker.isTeacher >> worker.day >> worker.month >> worker.year >> worker.exp >> worker.wage;
        list_workers.push_back(worker);
    }
    fin.close();
    print_list(list_workers, true);
    cont();
}

void task(list<Worker>& list_workers)
{
    system("cls");
    if (!list_workers.empty())
    {
        int max_year = 1, min_year = 1, i = 1;
        list<Worker> keeper = list_workers;
        keeper.sort(comp_day);
        for (auto iter : keeper)
        {
            if (i == 1) max_year = iter.year;
            if (i == keeper.size()) min_year = iter.year;
            i++;
        }
        if (max_year - min_year == 0)
            cout << "Разницы в годах нет";
        else
            cout << "Разница между самым старшим и самым младшим составляет примерно(в годах) " << fabs(max_year - min_year);
    }
    else
        cout << "Список пуст";
    cont();
}

void delete_wish(list<Worker>& list_workers)
{
    string s_taker; int i_taker; char toDelete; bool eraser = false;
    Worker worker("", "", "", "", "", 0, 0, 0, 0, 0);
    list<Worker> keeper = list_workers;
    do
    {
        system("cls");
        cout << "Выберите критерий для удаления:\n1. Имя\n2. Фамилия\n3. Отчество\n4. Должность работника\n5. День рождения\n6. Месяц\n7. Год\n8. Опыт работы\n9. Зарплата" << endl;
        toDelete = _getch();
    } while (toDelete != '1' && toDelete != '2' && toDelete != '3' && toDelete != '4' && toDelete != '5' && toDelete != '6' && toDelete != '7' && toDelete != '8' && toDelete != '9');
    if (toDelete == '1' || toDelete == '2' || toDelete == '3' || toDelete == '4')
        s_taker = check_string("Введите данные");
    else
        i_taker = check_int("Введите данные: ");
    list_workers.clear();
    for (auto iter : keeper)
    {
        eraser = false;
        switch (toDelete)
        {
        case '1':
            if (iter.name != s_taker)
                eraser = true;
            break;
        case '2':
            if (iter.surname != s_taker)
                eraser = true;
            break;
        case '3':
            if (iter.patronymic != s_taker)
                eraser = true;
            break;
        case '4':
            if (iter.post != s_taker)
                eraser = true;
            break;
        case '5':
            if (iter.day != i_taker)
                eraser = true;
            break;
        case '6':
            if (iter.month != i_taker)
                eraser = true;
            break;
        case '7':
            if (iter.year != i_taker)
                eraser = true;
            break;
        case '8':
            if (iter.exp != i_taker)
                eraser = true;
            break;
        case '9':
            if (iter.wage != i_taker)
                eraser = true;
            break;
        }
        if (eraser)
        {
            worker.name = iter.name; worker.surname = iter.surname; worker.patronymic = iter.patronymic; worker.post = iter.post; worker.isTeacher = iter.isTeacher;
            worker.day = iter.day; worker.month = iter.month; worker.year = iter.year; worker.exp = iter.exp; worker.wage = iter.wage;
            list_workers.push_back(worker);
        }
    }
    print_list(list_workers, true);
}

string check_string(string message)
{
    string value;
    do
    {
        cout << message << " (максимум 14 символов): ";
        cin >> value;
        if (value.length() <= 0 || value.length() > 15) 
        {
            fflush(stdin);
            std::cout << "Введены неверные данные, повторите ввод" << std::endl << std::endl;
            continue;
        }
    } while (1);
    return value;
}

int check_int(string message)
{
    int value; char test[10];
    do
    {
        cout << message;
        scanf_s("%d", &value);
        fgets(test, sizeof(test), stdin);
        if (strlen(test) > 1 || value <= 0)
        {
            fflush(stdin);
            std::cout << "Введены неверные данные, повторите ввод" << std::endl << std::endl;
        }
    } while (strlen(test) > 1 || value <= 0);
    return value;
}

void cont() 
{
    cout << "\n\nДля продолжение нажмите Entre" << endl;
    char taker = _getch();
}
