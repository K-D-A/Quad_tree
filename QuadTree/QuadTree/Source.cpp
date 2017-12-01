#include <iostream>
#include <locale>
#include "Tree.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	vector<dataType> vec = { 12, 0.1, 10, 14, 1245, 1.1, 0.8, 11, 5, 0.009, 13, 0.05, 124, 17, 600, 1450, 13000, 2756 };
	
	Tree tree(4);
	cout << "Создали пустое дерево с одним элементом:" << endl;
	tree.print();
	cout << endl;

	cout << endl << "Возьмем значения из вектора vec:" << endl;
	tree.loadFromArray(vec);
	cout << tree;
	cout << endl;

	Tree tree2;
	cout << endl << "Создали второе, пустое дерево и заполним его числами 3, 4, 2:" << endl;
	tree2.add(3);
	tree2.add(4);
	tree2.add(2);
	tree2.printByTree();

	cout << endl << "Очистили это дерево:" << endl;
	tree2.clear();
	tree2.print();

	cout << endl << "Скопируем в него первое дерево:" << endl;
	tree2.copy(tree);
	tree2.printByTree();
	cout << endl;

	cout << endl << "Удалим из него число 1450:" << endl;
	tree2.erase(1450);
	cout << tree2;
	cout << endl;

	cout << endl << "Создадим третье дерево - копию второго:" << endl;
	Tree tree3(tree2);
	tree3.printByTree();
	cout << endl;

	cout << endl << "Выведем массив, созданный этим деревом:" << endl;
	for each (dataType elem in tree3.toArray())
		cout << elem << " ";
	cout << endl << endl;

	cout << "Число элементов: " << tree3.count() << endl;
	cout << "Минимальное значение: " << tree3.min() << endl;
	cout << "Максимальное значение: " << tree3.max() << endl << endl;
	
	int findItem = 600;
	if (tree3.isExist(findItem))
		cout << "Элемент " << findItem << " содержится в дереве" << endl;
	else
		cout << "Элемент " << findItem << " не содержится в дереве" << endl;

	cout << "Удалим " << findItem << " из дерева:" << endl;
	tree3.erase(findItem);
	if (tree3.isExist(findItem))
		cout << "Элемент " << findItem << " содержится в дереве" << endl;
	else
		cout << "Элемент " << findItem << " не содержится в дереве" << endl;

	cout << endl << "Проверим на пустом дереве:" << endl;
	tree3.clear();

	findItem = 13;
	if (tree3.isExist(findItem))
		cout << "Элемент " << findItem << " содержится в дереве" << endl;
	else
		cout << "Элемент " << findItem << " не содержится в дереве" << endl;

	cout << "Удалим " << findItem << " из дерева:" << endl;
	tree3.erase(findItem);
	if (tree3.isExist(findItem))
		cout << "Элемент " << findItem << " содержится в дереве" << endl << endl;
	else
		cout << "Элемент " << findItem << " не содержится в дереве" << endl << endl;

	cout << "Число элементов: " << tree3.count() << endl;
	cout << "Минимальное значение: " << tree3.min() << endl;
	cout << "Максимальное значение: " << tree3.max() << endl << endl;

	system("pause");
}