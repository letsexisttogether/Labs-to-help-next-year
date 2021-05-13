#include <iostream>
#include<utility>
#include<vector>
#include<conio.h>
#include<clocale>
#include<string>
#include<iomanip>
#include<list>
#include<queue>

using namespace std;

void cont();

class graph
{
private:
    int cont_notOriented[7][7] = { 0, 3, 2, 0, 0, 0, 0, 3, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 1, 1, 0, 0, 2, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, };
	int cont_oriented[6][6] = { 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, };

	int inc_notOriented[7][13] = { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
	int inc_oriented[7][11] = { 1, 1, -1, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, 1, 1, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, -1, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, 0, -1, 1 };

	char ribs_notOriented[26][2] = { 'a', 'b','a', 'b','a', 'b','a', 'c', 'a', 'c', 'b', 'd', 'b', 'd', 'c', 'g', 'c', 'f', 'd', 'g', 'd', 'f', 'g', 'f', 'f', 'e', };
	char ribs_oriented[11][2] = { 'a','b','a', 'c','b', 'a','b', 'd','c', 'a','c', 'g','c', 'f','d', 'b','d', 'g','d', 'f','f', 'g' };

	string list_notOriented = "a: b c\nb: a d\nc: a g f\nd: b g f\ng: c d f\nf: c d g e\ne: f\n";
	string list_oriented = "a: b c\nb: a c\nc: a g f\nd: b g f\ng:\nf: g\n";

	char symbols[7] = { 'a','b','c','d','g','f','e', };

	list<int>* C = new list<int>[7];
	bool visited[];

	//вывод графа
	void print_contiguity(int method)
	{
		int n;
		method == 1 ? n = 7 : n = 6;
		method == 1 ? cout << "Неориентированый граф: " << endl << "  a b c d g f e" << endl : cout << "Ориентированый граф: " << endl << "  a b c d g f" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << symbols[i] << " ";
			for (int j = 0; j < n; j++)
				method == 1 ? cout << cont_notOriented[i][j] << " " : cout << cont_oriented[i][j] << " ";
			cout << endl;
		}
		cout << endl;
	}
	void print_incidence(int method)
	{
		int n, m;
		method == 1 ? n = 7 : n = 6;
		method == 1 ? m = 13 : m = 11;
		method == 1 ? cout << "Неориентированый граф: " << endl << "    1   2   3   4   5   6   7   8   9   10  11  12  13" << endl : cout << "Ориентированый граф: " << endl << "    1   2   3   4   5   6   7   8   9   10  11" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << symbols[i] << " ";
			for (int j = 0; j < m; j++)
				method == 1 ? cout << setw(3) << inc_notOriented[i][j] << " " : cout << setw(3) << inc_oriented[i][j] << " ";
			cout << endl;
		}
		cout << endl;
	}
	void print_ribs(int method)
	{
		int n;
		method == 1 ? n = 13 : n = 11;
		method == 1 ? cout << "Неориентированый граф: " << endl : cout << "Ориентированый граф: " << endl;
		for (int i = 0; i < n; i++)
			method == 1 ? cout << ribs_notOriented[i][0] << "---" << ribs_notOriented[i][1] << endl : cout << ribs_oriented[i][0] << "---" << ribs_oriented[i][1] << endl;
	}
	void print_list(int method)
	{
		method == 1 ? cout << "Неориентированый граф: " << endl << list_notOriented : cout << "Ориентированый граф: " << endl << list_oriented;
	}

	//матрица смежности
	void contToIncid(int method)
	{
		int n, m, k = 0;
		method == 1 ? n = 7 : n = 6;
		method == 1 ? m = 13 : m = 11;
		method == 1 ? print_contiguity(1) : print_contiguity(2);
		int InicidNotOriented[7][13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		int InicidOriented[7][11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		if (method == 1)
		{
			for (int i = 0; i < n; i++)
				for (int j = i; j < n; j++)
					if (cont_notOriented[i][j] >= 1)
						for (int counter = 0; counter < cont_notOriented[i][j]; counter++)
						{
							InicidNotOriented[i][k] = 1;
							InicidNotOriented[j][k++] = 1;
						}

		}
		else if (method == 2)
		{
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
				{
					if (cont_oriented[i][j] == 1 && i != j)
					{
						InicidOriented[i][k] = 1;
						InicidOriented[j][k++] = -1;
					}
					else if (cont_oriented[i][j] == 1 && i == j)
						InicidOriented[i][k++] = 2;
				}
		}
		method == 1 ? cout << "    1   2   3   4   5   6   7   8   9   10  11  12  13" << endl : cout << "    1   2   3   4   5   6   7   8   9   10  11" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << symbols[i] << " ";
			for (int j = 0; j < m; j++)
				method == 1 ? cout << setw(3) << InicidNotOriented[i][j] << " " : cout << setw(3) << InicidOriented[i][j] << " ";
			cout << endl;
		}
		cout << endl;
	}
	void contToContList(int method)
	{
		int n;
		method == 1 ? n = 7 : n = 6;
		method == 1 ? print_contiguity(1) : print_contiguity(2);
		char ListNotOriented[7][7] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
		char ListOriented[6][6] = { NULL, NULL, NULL, NULL, NULL, NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
		for (int i = 0; i < n; i++)
		{
			cout << symbols[i] << " ";
			for (int j = 0; j < n; j++)
			{
				if (method == 1 && cont_notOriented[i][j] > 0)
					ListNotOriented[i][j] = ret(j);
				else if (method == 2 && cont_oriented[i][j] != 0)
					ListOriented[i][j] = ret(j);
				method == 1 ? cout << ListNotOriented[i][j] : cout << ListOriented[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}
	void contToRibs(int method)
	{
		int n = 7, counter;
		char a, b;
		bool visited[7][7]; for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) visited[i][j] = false;
		method == 1 ? n = 7 : n = 6;
		method == 1 ? print_contiguity(1) : print_contiguity(2);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				a = ret(i);
				b = ret(j);
				if (method == 1 && cont_notOriented[i][j] > 0 && visited[j][i] == false)
				{
					counter = cont_notOriented[i][j];
					while (counter-- != 0)
					{
						cout << a << " --- " << b << endl;
					}
				}
				else if (method == 2 && cont_oriented[i][j] > 0)
					cout << a << " --- " << b << endl;
				visited[i][j] = true;
			}
		cout << endl;
	}

	//матрица инцидентности
	void incidToCont(int method)
	{
		int n, m;
		bool k;
		char a = 0, b = 0;
		method == 1 ? n = 7 : n = 6;
		method == 1 ? m = 13 : m = 11;
		method == 1 ? print_incidence(1) : print_incidence(2);
		int ContNotOriented[7][7]; for (int i = 0; i < 7; i++) for (int j = 0; j < 7; j++) ContNotOriented[i][j] = 0;
		int ContOriented[6][6]; for (int i = 0; i < 6; i++) for (int j = 0; j < 6; j++) ContOriented[i][j] = 0;
		if (method == 1)
		{
			for (int j = 0; j < m; j++)
			{
				k = false;
				for (int i = 0; i < n; i++)
				{
					if (inc_notOriented[i][j] == 1 && !k)
					{
						a = i;
						k = true;
					}
					else if (inc_notOriented[i][j] == 1 && k)
						b = i;
				}
				ContNotOriented[a][b] += 1;
				ContNotOriented[b][a] = ContNotOriented[a][b];
			}
		}
		else
		{
			for (int j = 0; j < m; j++)
			{
				for (int i = 0; i < n; i++)
				{

					if (inc_oriented[i][j] == -1)
						b = i;
					else if (inc_oriented[i][j] == 1)
						a = i;
					else if (inc_oriented[i][j] == 2)
						b = a = i;
				}
				ContOriented[a][b] += 1;
			}
		}
		method == 1 ? cout << "  a b c d g f e" << endl : cout << "  a b c d g f" << endl;
		for (int i = 0; i < n; i++)
		{
			cout << symbols[i] << " ";
			for (int j = 0; j < n; j++)
				method == 1 ? cout << ContNotOriented[i][j] << " " : cout << ContOriented[i][j] << " ";
			cout << endl;
		}
		cout << endl;
	}
	void incidToContList(int method)
	{
		int a, b, n, m;
		bool isPlus = false, isMinus = false, isConnection = false, isDone = false;
		method == 1 ? n = 7 : n = 6;
		method == 1 ? m = 13 : m = 11;
		method == 1 ? print_incidence(1) : print_incidence(2);
		list<int>* ContList = new list<int>[n];
		for (int i = 0; i < m; i++)
		{
			isDone = false;
			isConnection = false;
			for (int j = 0; j < n; j++)
			{
				if (method == 1)
				{
					if (inc_notOriented[j][i] == 1)
					{
						if (isConnection && !isDone)
						{
							ContList[j].push_back(a);
							ContList[a].push_back(j);
							isDone = true;
						}
						isConnection = true;
						a = j;
					}
				}
				else
				{
					if (inc_oriented[j][i] == 1)
					{
						if (isMinus)
						{
							ContList[j].push_back(b);
							isMinus = false;
						}
						a = j;
						isPlus = true;
					}
					if (inc_oriented[j][i] == -1 && isPlus == false)
					{
						b = j;
						isMinus = true;
					}
					if (inc_oriented[j][i] == -1 && isPlus == true)
					{
						ContList[a].push_back(j);
						isPlus = false;
					}
				}
			}
		}
		for (int i = 0; i < n; i++) 
		{
			cout << symbols[i] << " ";
			for (auto iter = ContList[i].begin(); iter != ContList[i].end(); iter++)
				cout << symbols[*iter] << " ";
			cout << endl;
		}
		cout << endl;
	}
	void incidToRibs(int method)
	{
		int n, m, k;
		char a, b;
		method == 1 ? n = 7 : n = 6;
		method == 1 ? m = 13 : m = 11;
		method == 1 ? print_incidence(1) : print_incidence(2);
		for (int j = 0; j < m; j++)
		{
			k = 0;
			for (int i = 0; i < n; i++)
			{
				if (method == 1 && inc_notOriented[i][j] != 0)
				{
					if (k == 0)
					{
						a = ret(i);
						k++;
					}
					else if (k == 1)
						b = ret(i);
				}
				else if (method == 2 && inc_oriented[i][j] == 1)
					a = ret(i);
				else if (method == 2 && inc_oriented[i][j] == -1)
					b = ret(i);
				else if (inc_oriented[i][j] == 2)
				{
					b = ret(i);
					a = b;
				}
			}
			cout << a << " --- " << b << endl;
		}
		cout << endl;
	}

	// обходы 
	void DFS(int v, bool visited[])
	{
		visited[v] = true; // отмечаем текущую першину как уже 
		cout << v << " "; // выводим эту вершину 

		list<int>::iterator i;
		// проверяем все вершины в списке
		for (i = C[v].begin(); i != C[v].end(); i++)
			if (visited[*i] == false) // если вершину не посещал, запускаем функцию заново 
				DFS(*i, visited);
	}
	void BFS(int v)
	{
		list<int> list_m;
		visited[v] = true;
		list_m.push_back(v);
		list<int>::iterator i;
		while (!list_m.empty())
		{
			int currVertex = list_m.front();
			cout << currVertex << " ";
			list_m.pop_front();

			for (i = C[currVertex].begin(); i != C[currVertex].end(); ++i)
			{
				int adjVertex = *i;
				if (!visited[adjVertex])
				{
					visited[adjVertex] = true;
					list_m.push_back(adjVertex);
				}
			}
		}
	}

	char ret(int i)
	{
		if (i == 0) return 'a';
		if (i == 1) return 'b';
		if (i == 2) return 'c';
		if (i == 3) return 'd';
		if (i == 4) return 'g';
		if (i == 5) return 'f';
		if (i == 6) return 'e';
	}
public:
	void print_menu()
	{
		char select;
		do
		{
			do
			{
				system("cls");
				cout << "Выберите действие:\n1. Матрица смежности\n2. Матрица инцидентности\n3. Список рёбер\n4. Список смежности\n5. Выход";
				select = _getch();
				system("cls");
			} while (select != '1' && select != '2' && select != '3' && select != '4' && select != '5');
			switch (select)
			{
			case '1':
				print_contiguity(1);
				print_contiguity(2);
				break;
			case '2':
				print_incidence(1);
				print_incidence(2);
				break;
			case'3':
				print_ribs(1);
				print_ribs(2);
				break;
			case '4':
				print_list(1);
				print_list(2);
				break;
			}
			if (select != '5')
				cont();
		} while (select != '5');
	}
	void print_trans()
	{
		char select;
		do
		{
			do
			{
				system("cls");
				cout << "Выберети переход:\n1. Матрица смежности в матрицу инцидентности\n2. Матрица смежности в список смежности\n3. Матрица смежности в список рёбер\n4. Матрица инцидентности в матрицу смежности\n5. Матрица инцидентности в список смежности\n6. Матрица инцидентности в список рёбер\n7. Назад";
				select = _getch();
				system("cls");
			} while (select != '1' && select != '2' && select != '3' && select != '4' && select != '5' && select != '6' && select != '7');
			switch (select)
			{
			case '1':
				contToIncid(1);
				contToIncid(2);
				break;
			case '2':
				contToContList(1);
				contToContList(2);
				break;
			case '3':
				contToRibs(1);
				contToRibs(2);
				break;
			case '4':
				incidToCont(1);
				incidToCont(2);
				break;
			case '5':
				incidToContList(1);
				incidToContList(2);
				break;
			case '6':
				incidToRibs(1);
				incidToRibs(2);
				break;
			}
			if(select != '7') 
				cont();
		} while (select != '7');
	}
	void filler(int graph_type, int method)
	{
		int n, value;
		graph_type == 1 ? n = 7 : n = 6;
		for (int i = 0; i < n; i++)
			 visited[i] = false;
		// Для неориентированого графа
		if (graph_type == 1)
		{
			cout << "Неориентированый граф: " << endl;
			C[0].push_back(1); C[0].push_back(2);
			C[1].push_back(3); C[1].push_back(0);
			C[2].push_back(0); C[2].push_back(5); C[2].push_back(6);
			C[3].push_back(1); C[3].push_back(5); C[3].push_back(6);
			C[4].push_back(5);
			C[5].push_back(2); C[5].push_back(3); C[5].push_back(6); C[5].push_back(4);
			C[6].push_back(2); C[6].push_back(3); C[6].push_back(5);
		}
		// Для неориентированго графа
		else
		{
			cout << "\nОриентированый граф: " << endl;
			C[0].push_back(1); C[0].push_back(2);
			C[1].push_back(3); C[1].push_back(0);
			C[2].push_back(0); C[2].push_back(4); C[5].push_back(2);
			C[3].push_back(1); C[3].push_back(4); C[5].push_back(3);
			C[5].push_back(4);
		}
		cout << "Введите номер вершины, с которой ноеобходимо начать обход: " << endl;
		cin >> value;
		method == 1 ? cout << "Результат выполнения поиска в губину:" << endl : cout << "Результат выполнения поиска в ширину: " << endl;
		method == 1 ? DFS(value, visited) : BFS(value);
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
    graph g;
	char select;
	do
	{
		do
		{
			system("cls");
			cout << "Выберите действие:\n1. Вывод всех графов\n2. Переход от матрицы к другому типу изображения графа\n3. DFS\n4. BFS\n5. Выход";
			select = _getch();
			system("cls");
		} while (select != '1' && select != '2' && select != '3' && select != '4' && select != '5');
		switch (select)
		{
		case '1':
			g.print_menu();
			break;
		case '2':
			g.print_trans();
			break;
		case'3':
			g.filler(1, 1);
			g.filler(2, 1);
			cont();
			break;
		case '4':
			g.filler(1, 2);
			g.filler(2, 2);
			cont();
			break;
		}
	} while (select != '5');
	cout << "\n\nДо свидания";
	cont();
    return 0;
}

void cont()
{
	char taker;
	cout << "\n\nДля продолжение нажмите Enter" << endl;
	taker = _getch();
}