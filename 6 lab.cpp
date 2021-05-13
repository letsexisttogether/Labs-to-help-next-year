#include <iostream>
#include<string>
#include<clocale>
#include<iomanip>
#include<conio.h>
#include<cstdio>

using namespace std;

void cont();

struct DATA
{
	int number = 0, age = 0, exp = 0, wage = 0;
	string surname;
};
struct NODE {
	DATA data;
	NODE* left = nullptr;
	NODE* right = nullptr;
};

class TREE
{
private:
	int count = 0;
	NODE* root = nullptr;
	void insert(NODE*& node, DATA& data)
	{
		if (node == nullptr)
		{
			node = new NODE;
			node->data = data;
			node->left = nullptr;
			node->right = nullptr;
			count++;
			return;
		}
		else if (data.number < node->data.number)
		{
			count++;
			insert(node->left, data);
		}
		else
		{
			count++;
			insert(node->right, data);
		}
	}
	void insert_to_pour(NODE*& node, DATA& data)
	{
		if (node == nullptr)
		{
			node = new NODE;
			node->data = data;
			node->left = nullptr;
			node->right = nullptr;
			count++;
			return;
		}
		else if (data.exp < node->data.exp)
			insert_to_pour(node->left, data);
		else
			insert(node->right, data);
	}

public:
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
	void add(DATA& data)
	{
		insert(root, data);
	}
	void add_to_pour(DATA& data)
	{
		insert_to_pour(root, data);
	}
	double middle_age(NODE* node = nullptr)
	{
		if (node == nullptr) node = root;
		double sum = 0;
		int count = 0;

		if (node->left) {
			sum += middle_age(node->left);
			count++;
		}
		if (node->right) {
			sum += middle_age(node->right);
			count++;
		}
		count++;

		return (sum + node->data.age) / (double)count;
	}
	void print(NODE* node = nullptr) {
		if (node == nullptr)
			node = root;
		if (root == nullptr)
		{
			cout << "Дерево пустое" << endl;
			return;
		}
		else
		{
			if (node->left)
			{
				cout << "+1 левый потомок" << endl;
				print(node->left);
			}
			cout << "Личный номер: " << node->data.number << endl << "Фамилия: " << node->data.surname << endl << "Возраст: " << node->data.age << endl << "Стаж: " << node->data.exp << endl << "Зарплата" << node->data.wage << endl << endl;
			if (node->right)
			{
				cout << "+1 Правый потомок" << endl;
				print(node->right);
			}
		}
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
	void pour(TREE* Tree, NODE* node = nullptr)
	{
		if (node == nullptr)
			node = root;
		if (node->left)
			pour(Tree, node->left);
		if (node->right)
			pour(Tree, node->right);
		Tree->add_to_pour(node->data);
	}
} tree;


int main()
{
	DATA toRead;
	TREE tree;
	setlocale(LC_ALL, "Russian");
	int exit = 0;
	char choice, take;
	do
	{
		do
		{
			cout << "If you want enter data press 1, if you does not enter data press 2\n>>";
			choice = _getch();
			system("cls");
		} while (choice != '1' && choice != '2');
		if (choice == '1')
		{
			cout << "Enter surname of a worker:";
			cin >> toRead.surname;
			toRead.number = tree.check_numbers("Enter personal number of a worker: ");
			toRead.age = tree.check_numbers("Enter age of a worker: ");
			toRead.exp = tree.check_numbers("Enter experience of a worker: ");
			toRead.wage = tree.check_numbers("Enter salary of a worker:  ");
			tree.add(toRead);
			cout << choice;
		}
		else if (choice == '2')
		{
			exit = 1;
		}
	} while (exit != 1);
	cout << "First tree:" << endl;
	tree.print();
	cout << "\nAverage age: " << tree.middle_age() << endl;
	tree.print();
	TREE toPour;
	tree.pour(&toPour);
	tree.delete_tree();
	tree.print();
	cout << "\n\nSecond tree:" << endl;
	toPour.print();
	cout << "\n\nPress ESCAPE to exit\n" << endl;
	do
	{
		take = _getch();
	} while (take != 27);
	return 0;
}
