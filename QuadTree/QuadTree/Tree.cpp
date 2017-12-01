#include <queue>
#include "Tree.h"

using namespace std;

// Закрытые методы
int Tree::_numOfTree(dataType nodeVal, dataType newVal) {		// Функция определения номера поддерева, куда добавлять новый элемент
	double div = (double)newVal / nodeVal;				// Определение, во сколько раз больше или меньше новый элемент, чем корень
	if (div > 1) {					// Если новый элемент больше, то будет определен в какой-то из правых поддеревьев
		if (div > 10) return 4;		// Если новый элемент больше корня на порядок, то будет определен в крайне правое поддерево
		else return 3;				
	}
	else {							// Если новый элемент меньше, то будет определен в какой-то из левых поддеревьев
		if (div < 0.1) return 1;	// Если новый элемент меньше корня на порядок, то будет определен в крайне левое поддерево
		else return 2;
	}
}

void Tree::_add(Node *&tree, dataType addValue)	// Рекурсивное добавление нового элемента
{
	if (tree == NULL) {						// Если элемента нет, то создаем его и помещаем в него значение
		tree = new Node;					// Выделяем память под звено дерева
		tree->data = addValue;				// Записываем данные в звено
		tree->farLeft = NULL;				
		tree->left = NULL;					// Обнуляем значения потомков
		tree->right = NULL;
		tree->farRight = NULL;
	}
	else {													// Если элемент существует, то добавим в какое-то из поддеревьев
		int numOfTree = _numOfTree(tree->data, addValue);	// Определяем номер поддерева, куда определить новый элемент
		switch (numOfTree) {
		case 1: _add(tree->farLeft, addValue); break;
		case 2: _add(tree->left, addValue); break;
		case 3: _add(tree->right, addValue); break;			// Рекурсивный вызов функции, для добавления элемента в поддерево
		case 4: _add(tree->farRight, addValue); break;
		default: 
			tree->farLeft = NULL; 
			tree->left = NULL; 
			tree->right = NULL; 
			tree->farRight = NULL;
			break;
		}
	}
}

void Tree::_clear(Node *&tree) {		// Рекурсивная очистка дерева
	if (tree->farLeft != NULL)
		_clear(tree->farLeft);
	if (tree->left != NULL)
		_clear(tree->left);
	if (tree->right != NULL)
		_clear(tree->right);
	if (tree->farRight != NULL)
		_clear(tree->farRight);
	delete tree;
	tree = NULL;
}

void Tree::_toArray(Node *tree, vector<dataType> &vec) {	// Рекурсивное создание vector<dataType> по элементам дерева обходом Корень-Левый-Правый
	if (tree != NULL) {
		vec.push_back(tree->data);
		if (tree->farLeft != NULL)
			_toArray(tree->farLeft, vec);
		if (tree->left != NULL)
			_toArray(tree->left, vec);
		if (tree->right != NULL)
			_toArray(tree->right, vec);
		if (tree->farRight != NULL)
			_toArray(tree->farRight, vec);
	}
}

void Tree::_count(Node *tree, int &count)	// Рекурсивный подсчет количества элементов
{
	if (tree != NULL) {						// Если корень не пуст значит увеличиваем и переходим в непустые потомки
		count++;
		_count(tree->farLeft, count);
		_count(tree->left, count);
		_count(tree->right, count);
		_count(tree->farRight, count);
	}
}

bool Tree::_isExist(Node *tree, dataType findItem) {		// Проверка, содержится ли заданный элемент в дереве
	if (tree == NULL)
		return false;
	if (tree->data == findItem)
		return true;

	int numOfTree = _numOfTree(tree->data, findItem);				// Определяем номер поддерева, где искомый элемент мог бы находиться
	Node *p;
	switch (numOfTree) {
	case 1: p = tree->farLeft; break;
	case 2: p = tree->left; break;
	case 3: p = tree->right; break;				// Определили поддерево, в котором мог бы находиться искомый элемент
	case 4: p = tree->farRight; break;
	default: p = NULL; break;
	}

	return _isExist(p, findItem);	// Ищем в определенном поддереве
}

Node* Tree::_findMin(Node *head)			// Нахождение указателя на минимальный элемента дерева
{
	if (head != NULL) {
		if (head->farLeft != NULL)			// Спускаемся по левым веткам пока можем
			return _findMin(head->farLeft);
		if (head->left != NULL)		
			return _findMin(head->left);
	}
	return head;
}

Node* Tree::_findMax(Node *head) // Нахождение указателя на максимальный элемент дерева
{
	if (head != NULL) {
		if (head->farRight != NULL)			// Спускаемся по правым веткам пока можем
			return _findMax(head->farRight);
		if (head->right != NULL)
			return _findMax(head->right);
	}
	return head;
}

void Tree::_print(Node *tree) {		// Рекурсивный вывод на экран всех элементов в строчку обходом Левый-Корень-Правый
	if (tree != NULL) {
		if (tree->farLeft != NULL)
			_print(tree->farLeft);
		if (tree->left != NULL)
			_print(tree->left);
		cout << tree->data << " ";
		if (tree->right != NULL)
			_print(tree->right);
		if (tree->farRight != NULL)
			_print(tree->farRight);
	}
}

void Tree::_printByTree(Node *tree, int h) {		// Рекурсивный вывод дерева на экран в древовидном виде, повернутом на 90 градусов против часовой стрелки
	if (tree != NULL) {
		if (tree->farRight != NULL)
			_printByTree(tree->farRight, h + 4);
		if (tree->right != NULL)
			_printByTree(tree->right, h + 4);
		for (int i = 0; i < h; ++i)
			cout << " ";
		cout << tree->data << endl;
		if (tree->left != NULL)
			_printByTree(tree->left, h + 4);
		if (tree->farLeft != NULL)
			_printByTree(tree->farLeft, h + 4);
	}
}

// Конструкторы
Tree::Tree() {		// Конструктор по умолчанию
	root = NULL;
}

Tree::Tree(dataType x) {		// Конструктор с параметром, инициализирует максимальное число потомков каждого узла
	root = NULL;
	_add(root, x);
}

Tree::Tree(Tree& tree) {	// Конструктор копии
	root = NULL;
	vector<dataType> elements = tree.toArray();
	for each (dataType elem in elements) {
		_add(root, elem);
	}
}

Tree::~Tree() {		// Деструктор
	clear();
}

/* Основные методы */
void Tree::add(dataType addValue) {	// Функция добавления нового числа в дерево
	return _add(root, addValue);
}

void Tree::clear() {	// Функция очистки дерева
	if (root != NULL)
		_clear(root);
}

void Tree::copy(Tree &tree) {	// Функция копирования дерева
	clear();
	root = NULL;
	vector<dataType> elements = tree.toArray();
	for each (dataType elem in elements) {
		_add(root, elem);
	}
}

void Tree::erase(dataType deleteValue) {		// Функция удаления из дерева элементов с заданным значением 
	if (isExist(deleteValue)) {
		vector<dataType> newElements;
		for each (dataType elem in toArray()) {	// Оставляем те значения, которые не равны заданному значению
			if (elem != deleteValue)
				newElements.push_back(elem);
		}
		clear();
		for each (dataType elem in newElements) {	// Загружаем оставшееся обратно в дерево
			add(elem);
		}
	}
}

void Tree::print() {	// Вывод на экран всех элементов в строчку обходом Левый-Корень-Правый
	_print(root);
}

void Tree::printByTree(int h) {	// Вывод дерева на экран в древовидном виде, повернутом на 90 градусов против часовой стрелки
	_printByTree(root);
}

/* Дополняющие методы */
void Tree::loadFromArray(vector<dataType> vec) {	// Функция создания дерева по элементам вектора
	clear();
	for (unsigned int i = 0; i < vec.size(); i++) {
		add(vec[i]);
	}
}

vector<dataType> Tree::toArray() {		// Функция создания вектора по элементам дерева
	vector<dataType> vec;
	_toArray(root, vec);
	return vec;
}

bool Tree::isExist(dataType findItem) {		// Функция проверки, содержится ли заданный элемент в дереве
	return _isExist(root, findItem);
}

int Tree::count() {		// Функция подсчета числа элементов дерева
	int cnt = 0;
	_count(root, cnt);
	return cnt;
}

dataType Tree::min() {		// Функция нахождения минимального значения элементов дерева
	if (root != NULL)
		return _findMin(root)->data;
	else {
		cout << "Дерево пустое!" << endl;
		return -999;
	}
}

dataType Tree::max() {		// Функция нахождения максимального значения элементов дерева
	if (root != NULL)
		return _findMax(root)->data;
	else {
		cout << "Дерево пустое!" << endl;
		return -999;
	}
}


ostream &operator<<(ostream &out, Tree tree) {		// Перегруженная операция '<<' вывода элементов дерева в поток
	for each (dataType elem in tree.toArray())
		out << elem << " ";
	return out;
}