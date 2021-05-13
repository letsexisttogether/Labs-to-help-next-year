#include <iostream>
#include<list>
#include<clocale>
#include<conio.h>
#include<iomanip>
#include<vector>

using namespace std;

class path
{
private:
	int start = 0, finish = 0, infinity = 1000;
	int a[6][6] = { 0, 5, 3, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 2, 5, 0, 0, 0, 0, 7, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
	// главные алгоритмы
	void flouyd(int fArray[6][6])
	{
		for (int k = 0; k < 6; k++)
			for (int i = 0; i < 6; i++)
				for (int j = 0; j < 6; j++)
					if (fArray[i][k] != 0 && fArray[k][j] != 0 && i != j)
						if (fArray[i][k] + fArray[k][j] < fArray[i][j] || fArray[i][j] == 0)
							fArray[i][j] = fArray[i][k] + fArray[k][j];
		system("cls");
		cout << "Алгоритм Флойда-Уоршелла\n   a  b  c  d  f  g" << endl;
		for (int i = 0; i < 6; i++)
		{
			cout << symb_ret(i) << " ";
			for (int j = 0; j < 6; j++)
				i == j ? cout << " 0 " : fArray[i][j] == 0 ? cout << " - " : cout << setw(2) << fArray[i][j] << " ";
			cout << endl;
		}
		cont();
	}
	void dijkstra(int dArray[6][6])
	{
		vector <int> range(6, infinity), p(6, -1), v;
		vector <bool> visited(6);
		int path, u;
		system("cls");
		cout << "Алгоритм Дейкстры\n";
		start = num_ret(check_char("Введите начальную вершину: "));
		finish = num_ret(check_char("Введите конечную вершину: "));
		range[start] = 0;
		for (int i = 0; i < 6; i++)
		{
			path = infinity; 
			u = -1;
			for (int j = 0; j < 6; j++)
				if (!visited[j] && range[j] < path)
				{
					path = range[i];
					u = j;
				}
			if (u == -1) break;
			visited[u] = true;
			for (int j = 0; j < 6; ++j)
				if (range[j] > range[u] + dArray[u][j] && dArray[u][j] > 0)
				{
					range[j] = range[u] + dArray[u][j]; 
					p[j] = u;
				}
		}
		if (p[finish] != -1)
		{
			for (u = finish; u != -1; u = p[u]) 
				v.push_back(u);
			reverse(v.begin(), v.end());
			cout << "Кратчайшее расстояние от вершины " << symb_ret(start) << " до вершины " << symb_ret(finish) << " составляет: " << range[finish] << endl;
			cout << "Путь: ";
			for (int i = 0; i < v.size(); i++)
			{
				if (i != 0)
					cout << " ---> ";
				cout << symb_ret(v[i]);
			}
		}
		else
			cout << "\nС вершины " << symb_ret(start) << " к вершине " << symb_ret(finish) << " пройти нельзя" << std::endl;
		cont();
	}
	// переходы
	char symb_ret(int i)
	{
		if (i == 0) return 'a';
		if (i == 1) return 'b';
		if (i == 2) return 'c';
		if (i == 3) return 'd';
		if (i == 4) return 'f';
		if (i == 5) return 'g';
	}
	int num_ret(char c)
	{
		if (c == 'a') return 0;
		if (c == 'b') return 1;
		if (c == 'c') return 2;
		if (c == 'd') return 3;
		if (c == 'f') return 4;
		if (c == 'g') return 5;
	}
	// вспомагательные фукнции
	char check_char(string message)
	{
		char value;
		char test[10];
		do
		{
			cout << message;
			cin >> value;
		} while (value != 'a' && value != 'b' && value != 'c' && value != 'd' && value != 'f' && value != 'g');
		return value;
	}
	void cont()
	{
		char taker;
		cout << "\n\nДля продолжения нажмите Enter" << endl;
		taker = _getch();
	}
public:
	void menu()
	{
		char select;
		do
		{
			do
			{
				system("cls");
				cout << "Выберите действие:\n1. Алгоритм Дейкстры\n2. Алгоритм Флойда-Воршелла\n3. Выход" << endl;
				select = _getch();
			} while (select != '1' && select != '2' && select != '3');
			switch (select)
			{
			case '1':
				dijkstra(a);
				break;
			case '2':
				flouyd(a);
				break;
			}
		} while (select != '3');
	}
}g;

int main()
{
	setlocale(LC_ALL, "Rus"); 
	g.menu();
	return 0;
}

