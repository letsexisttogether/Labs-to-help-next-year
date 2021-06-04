#include <iostream>
#include<string>
#include<clocale>
#include<iomanip>
#include<conio.h>
#include<cstdio>

using namespace std;

int check_int(string message);
void cont();

struct DATA
{
	int code = 0, suitCount = 0, weight = 0;
	string surname;
};
struct NODE {
	DATA data;
	NODE* left = nullptr;
	NODE* right = nullptr;
};

class tree
{
private:
	NODE* root = nullptr;
	void insert(NODE*& node, DATA& data)
	{
		if (node == nullptr)
		{
			node = new NODE;
			node->data = data;
			node->left = nullptr;
			node->right = nullptr;
			return;
		}
		else if (data.surname < node->data.surname)
			insert(node->left, data);
		else
			insert(node->right, data);
	}
	void pInsert(NODE*& node, DATA& data)
	{
		if (node == nullptr)
		{
			node = new NODE;
			node->data = data;
			node->left = nullptr;
			node->right = nullptr;
			return;
		}
		else if (data.code < node->data.code)
			pInsert(node->left, data);
		else
			pInsert(node->right, data);
	}

public:
	void add(DATA& data)
	{
		insert(root, data);
	}
	void pAdd(DATA& data)
	{
		pInsert(root, data);
	}
	void print_the_tree(NODE* node) {
		if (node == nullptr)
			node = root;
		if (root == nullptr) {
			cout << "Дерево пустое" << endl;
			return;
		}
		else
		{
			if (node->left)
			{
				print_the_tree(node->left);
			}
			cout << "Код билета: " << node->data.code << endl << "Фамилия: " << node->data.surname << endl << "Колличество багажа: " << node->data.suitCount << endl << "Вес багажа: " << node->data.weight << endl << endl;
			if (node->right)
			{
				print_the_tree(node->right);
			}
		}
	}
	double middle_count(NODE* node) 
	{
		if (node == nullptr) 
			node = root;
		double sum = 0;
		if (node->left) 
		{
			sum += middle_count(node->left);
		}
		if (node->right) 
		{
			sum += middle_count(node->right);
		}
		return double(sum + node->data.suitCount);
	}
	double middle_weight(NODE* node)
	{
		if (node == nullptr)
			node = root;
		double sum = 0;
		if (node->left)
		{
			sum += middle_count(node->left);
		}
		if (node->right)
		{
			sum += middle_count(node->right);
		}
		return double(sum + node->data.weight);
	}
	void delete_tree(NODE* node = nullptr)
	{
		if (node == nullptr)
		{
			node = root;
			root = nullptr;
		}
		if (node->left)
			delete_tree(node->left);
		if (node->right)
			delete_tree(node->right);
		if (node != root)
			delete node;
	}
	void pour(tree* Tree, NODE* node = nullptr)
	{
		if (node == nullptr)
			node = root;
		if (node->left)
			pour(Tree, node->left);
		if (node->right)
			pour(Tree, node->right);
		Tree->pAdd(node->data);
	}
};

int check_numbers(std::string message)
{
	char test[10];
	int numbers;
	do
	{
		std::cout << message;
		scanf_s("%d", &numbers);
		fgets(test, sizeof(test), stdin);
		if (numbers <= 0 || strlen(test) > 1)
		{
			fflush(stdin);
			std::cout << "Entered invalide data!!!\nTry again!!!\n\n";
		}
	} while (numbers <= 0 || strlen(test) > 1);
	return numbers;
}



int main()
{
	DATA d;
	tree Tree;
	setlocale(LC_ALL, "Russian");
	int size;
	size = check_int("Введите колличество вводимых величин: ");
	for (int i = 0; i < size; i++)
	{
		system("cls");
		cout << "Введите имя: ";
		cin >> d.surname;
		d.code = check_int("Введите код билета данного пассажира: ");
		d.suitCount = check_int("Введите колличество багажа: ");
		d.weight = check_int("Введите общий вес багажа: ");
		Tree.add(d);
	}

	system("cls");
	cout << "Первое дерево:" << endl;
	Tree.print_the_tree(nullptr);
	cout << "\nСреднее колличество багажа на человека: " << Tree.middle_count(nullptr)/size << endl;
	cout << "\nСреднее вес багажа: " << Tree.middle_weight(nullptr) / size << endl;
	cont();
	system("cls");
	tree toPour;
	Tree.pour(&toPour);
	Tree.delete_tree();
	cout << "Первое дерево: " << endl;
	Tree.print_the_tree(nullptr);
	cout << "\n\nВторое дерево:" << endl;
	toPour.print_the_tree(nullptr);
	cont();
	return 0;
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
	cout << "\n\nДля продолжение нажмите Enter" << endl;
	taker = _getch();
}
