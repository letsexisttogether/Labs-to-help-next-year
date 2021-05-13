#include <iostream>
#include <string>
#include <conio.h>
#include <cmath>
#include <clocale>

using namespace std;

void cont();

class vector
{
private:
    double x_start, y_start; 
	double x_end, y_end;
	double z_start, z_end;

	double x, y, z;
	void create_vector()
	{

		check_int("Введите координты начала вектора: ", this->x_start, this->y_start, this->z_start);
		check_int("Введите координты конца вектора:  ", this->x_end, this->y_end, this->z_end);
	}
	void toCoord()
	{
		x = x_end - x_start;
		y = y_end - y_start;
		z = z_end - z_start;
	}
	double range_calc()
	{
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
    // дополнительные функции
	void check_int(string message, double &x, double &y, double& z)
	{
		char test[10];
		do
		{
			cout << message;
			scanf_s("(%lf;%lf;%lf)", &x, &y, &z);
			fgets(test, sizeof(test), stdin);
			if (strlen(test) > 1)
			{
				cout << "Ошибка ввода. Введите данные ещё раз!!!\n\n";
				fflush(stdin);
			}
		} while (strlen(test) > 1);
	}

public:

	vector()
	{
		x = x_start = x_end = NULL;
		y = y_start = y_end = NULL;
		z = z_start = z_end = NULL;
	}
	vector(bool toCreate)
	{
		if (toCreate)
			create_vector();
	}
	~vector()
	{
		x = x_start = x_end = 0;
		y = y_start = y_end = 0;
		z = z_start = z_end = 0;
	}
	void print_vector()
	{
		if (x_start != NULL)
		{
			cout << "Начало:  (" << this->x_start << ";" << this->y_start << ";" << this->z_start << ")" << endl;
			cout << "Конец:   (" << this->x_end << ";" << this->y_end << ";" << this->z_end << ")" << endl;
		}
		toCoord();
		cout << "Координаты вектора: (" << this->x << ";" << this->y << ";" << this->z << ")\nЕго длинна: " << range_calc() << endl;
	}
	vector operator + (vector other)
	{
		vector keeper;
		keeper.x_start = this->x_start + other.x_start; keeper.x_end = this->x_end + other.x_end;
		keeper.y_start = this->y_start + other.y_start; keeper.y_end = this->y_end + other.y_end;
		keeper.z_start = this->z_start + other.z_start; keeper.z_end = this->z_end + other.z_end;
		return keeper;
	}
	vector operator - (vector other)
	{
		vector keeper;
		keeper.x_start = this->x_start - other.x_start; keeper.x_end = this->x_end - other.x_end;
		keeper.y_start = this->y_start - other.y_start; keeper.y_end = this->y_end - other.y_end;
		keeper.z_start = this->z_start - other.z_start; keeper.z_end = this->z_end - other.z_end;
		return keeper;
	}
	vector& operator * (vector other)
	{
		vector keeper;
		keeper.x = (this->y * other.z - this->z * other.y);
		keeper.y = (this->z * other.x - this->x * other.z);
		keeper.z = (this->x * other.y - this->y * other.x);
		cout << "(" << keeper.x << ";" << keeper.y << ";" << keeper.z << ")";
		return keeper;
	}
	vector operator * (double value)
	{
		this->x_start *= value;		this->x_end *= value;
		this->y_start *= value;		this->y_end *= value;
		this->z_start *= value;		this->z_end *= value;
		return*this;
	}
	vector operator / (double value)
	{
		this->x_start /= value;		this->x_end/= value;
		this->y_start /= value;		this->y_end /= value;
		this->z_start /= value;		this->z_end /= value;
		return* this;
	}
	vector& operator++ ()
	{
		this->x_start++; this->x_end++;
		this->y_start++; this->y_end++;
		this->z_start++; this->z_end++;
		return  *this;
	}
	vector& operator -- (int)
	{
		this->x_start--; this->x_end--;
		this->y_start--; this->y_end--;
		this->z_start--; this->z_end--;
		return *this;
	}

	bool operator || (vector other)
	{
		if (this->x / other.x == this->y / other.y && this->x / other.x == this->z / other.z && this->y / other.y == this->z / other.z)
			return true;
		return false;
	}

};

int  main()
{
	setlocale(LC_ALL, "Russian");
	vector vector_m(true), vector_h(true);
	vector vector_t, vector_r;
	for (int i = 0; i < 7; i++)
	{
		system("cls");
		vector_m.print_vector();
		if (i < 4 || i == 6)
		{
			cout << endl;
			vector_h.print_vector();
		}
		cout << endl;
		if (i == 0)
		{
			cout << "Сложение двух векторов:" << endl;
			vector_t = vector_m + vector_h;
			vector_t.print_vector();
		}
		if (i == 1)
		{
			cout << "Вычитание двух векторов:" << endl;
			vector_t = vector_h - vector_m;
			vector_t.print_vector();
		}
		if (i == 2)
		{
			cout << "Векторное произведение двух векторов:" << endl;
			vector_r = vector_m * vector_h;
		}
		if (i == 3)
		{
			cout << "Деление координат вектора на 3:" << endl;
			vector_m / 3;
			vector_m.print_vector();
			vector_m * 3;
		}
		if (i == 4)
		{
			cout << "\nПрефиксное увеличение координат вектора на 1" << endl;
			++vector_m;
			vector_m.print_vector();
		}
		if (i == 5)
		{
			cout << "Постфиксное уменьшение координат вектора на 1:" << endl;
			vector_m--;
			vector_m.print_vector();
		}
		if (i == 6)
		{
			cout << "Провека коллинеарности:" << endl;
			if (vector_m || vector_h)
				cout << "Вектора коллинеарны";
			else
				cout << "Вектора не коллинеарны";
		}
		cont();
	}
	return 0;
}

void cont()
{
	char taker;
	cout << "\n\nДля продолжение нажмите Enter" << endl;
	taker = _getch();
	system("cls");
}