#include <iostream>
#include <locale>
#include "Tree.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	vector<dataType> vec = { 12, 0.1, 10, 14, 1245, 1.1, 0.8, 11, 5, 0.009, 13, 0.05, 124, 17, 600, 1450, 13000, 2756 };
	
	Tree tree(4);
	cout << "������� ������ ������ � ����� ���������:" << endl;
	tree.print();
	cout << endl;

	cout << endl << "������� �������� �� ������� vec:" << endl;
	tree.loadFromArray(vec);
	cout << tree;
	cout << endl;

	Tree tree2;
	cout << endl << "������� ������, ������ ������ � �������� ��� ������� 3, 4, 2:" << endl;
	tree2.add(3);
	tree2.add(4);
	tree2.add(2);
	tree2.printByTree();

	cout << endl << "�������� ��� ������:" << endl;
	tree2.clear();
	tree2.print();

	cout << endl << "��������� � ���� ������ ������:" << endl;
	tree2.copy(tree);
	tree2.printByTree();
	cout << endl;

	cout << endl << "������ �� ���� ����� 1450:" << endl;
	tree2.erase(1450);
	cout << tree2;
	cout << endl;

	cout << endl << "�������� ������ ������ - ����� �������:" << endl;
	Tree tree3(tree2);
	tree3.printByTree();
	cout << endl;

	cout << endl << "������� ������, ��������� ���� �������:" << endl;
	for each (dataType elem in tree3.toArray())
		cout << elem << " ";
	cout << endl << endl;

	cout << "����� ���������: " << tree3.count() << endl;
	cout << "����������� ��������: " << tree3.min() << endl;
	cout << "������������ ��������: " << tree3.max() << endl << endl;
	
	int findItem = 600;
	if (tree3.isExist(findItem))
		cout << "������� " << findItem << " ���������� � ������" << endl;
	else
		cout << "������� " << findItem << " �� ���������� � ������" << endl;

	cout << "������ " << findItem << " �� ������:" << endl;
	tree3.erase(findItem);
	if (tree3.isExist(findItem))
		cout << "������� " << findItem << " ���������� � ������" << endl;
	else
		cout << "������� " << findItem << " �� ���������� � ������" << endl;

	cout << endl << "�������� �� ������ ������:" << endl;
	tree3.clear();

	findItem = 13;
	if (tree3.isExist(findItem))
		cout << "������� " << findItem << " ���������� � ������" << endl;
	else
		cout << "������� " << findItem << " �� ���������� � ������" << endl;

	cout << "������ " << findItem << " �� ������:" << endl;
	tree3.erase(findItem);
	if (tree3.isExist(findItem))
		cout << "������� " << findItem << " ���������� � ������" << endl << endl;
	else
		cout << "������� " << findItem << " �� ���������� � ������" << endl << endl;

	cout << "����� ���������: " << tree3.count() << endl;
	cout << "����������� ��������: " << tree3.min() << endl;
	cout << "������������ ��������: " << tree3.max() << endl << endl;

	system("pause");
}