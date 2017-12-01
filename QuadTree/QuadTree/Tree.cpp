#include <queue>
#include "Tree.h"

using namespace std;

// �������� ������
int Tree::_numOfTree(dataType nodeVal, dataType newVal) {		// ������� ����������� ������ ���������, ���� ��������� ����� �������
	double div = (double)newVal / nodeVal;				// �����������, �� ������� ��� ������ ��� ������ ����� �������, ��� ������
	if (div > 1) {					// ���� ����� ������� ������, �� ����� ��������� � �����-�� �� ������ �����������
		if (div > 10) return 4;		// ���� ����� ������� ������ ����� �� �������, �� ����� ��������� � ������ ������ ���������
		else return 3;				
	}
	else {							// ���� ����� ������� ������, �� ����� ��������� � �����-�� �� ����� �����������
		if (div < 0.1) return 1;	// ���� ����� ������� ������ ����� �� �������, �� ����� ��������� � ������ ����� ���������
		else return 2;
	}
}

void Tree::_add(Node *&tree, dataType addValue)	// ����������� ���������� ������ ��������
{
	if (tree == NULL) {						// ���� �������� ���, �� ������� ��� � �������� � ���� ��������
		tree = new Node;					// �������� ������ ��� ����� ������
		tree->data = addValue;				// ���������� ������ � �����
		tree->farLeft = NULL;				
		tree->left = NULL;					// �������� �������� ��������
		tree->right = NULL;
		tree->farRight = NULL;
	}
	else {													// ���� ������� ����������, �� ������� � �����-�� �� �����������
		int numOfTree = _numOfTree(tree->data, addValue);	// ���������� ����� ���������, ���� ���������� ����� �������
		switch (numOfTree) {
		case 1: _add(tree->farLeft, addValue); break;
		case 2: _add(tree->left, addValue); break;
		case 3: _add(tree->right, addValue); break;			// ����������� ����� �������, ��� ���������� �������� � ���������
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

void Tree::_clear(Node *&tree) {		// ����������� ������� ������
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

void Tree::_toArray(Node *tree, vector<dataType> &vec) {	// ����������� �������� vector<dataType> �� ��������� ������ ������� ������-�����-������
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

void Tree::_count(Node *tree, int &count)	// ����������� ������� ���������� ���������
{
	if (tree != NULL) {						// ���� ������ �� ���� ������ ����������� � ��������� � �������� �������
		count++;
		_count(tree->farLeft, count);
		_count(tree->left, count);
		_count(tree->right, count);
		_count(tree->farRight, count);
	}
}

bool Tree::_isExist(Node *tree, dataType findItem) {		// ��������, ���������� �� �������� ������� � ������
	if (tree == NULL)
		return false;
	if (tree->data == findItem)
		return true;

	int numOfTree = _numOfTree(tree->data, findItem);				// ���������� ����� ���������, ��� ������� ������� ��� �� ����������
	Node *p;
	switch (numOfTree) {
	case 1: p = tree->farLeft; break;
	case 2: p = tree->left; break;
	case 3: p = tree->right; break;				// ���������� ���������, � ������� ��� �� ���������� ������� �������
	case 4: p = tree->farRight; break;
	default: p = NULL; break;
	}

	return _isExist(p, findItem);	// ���� � ������������ ���������
}

Node* Tree::_findMin(Node *head)			// ���������� ��������� �� ����������� �������� ������
{
	if (head != NULL) {
		if (head->farLeft != NULL)			// ���������� �� ����� ������ ���� �����
			return _findMin(head->farLeft);
		if (head->left != NULL)		
			return _findMin(head->left);
	}
	return head;
}

Node* Tree::_findMax(Node *head) // ���������� ��������� �� ������������ ������� ������
{
	if (head != NULL) {
		if (head->farRight != NULL)			// ���������� �� ������ ������ ���� �����
			return _findMax(head->farRight);
		if (head->right != NULL)
			return _findMax(head->right);
	}
	return head;
}

void Tree::_print(Node *tree) {		// ����������� ����� �� ����� ���� ��������� � ������� ������� �����-������-������
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

void Tree::_printByTree(Node *tree, int h) {		// ����������� ����� ������ �� ����� � ����������� ����, ���������� �� 90 �������� ������ ������� �������
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

// ������������
Tree::Tree() {		// ����������� �� ���������
	root = NULL;
}

Tree::Tree(dataType x) {		// ����������� � ����������, �������������� ������������ ����� �������� ������� ����
	root = NULL;
	_add(root, x);
}

Tree::Tree(Tree& tree) {	// ����������� �����
	root = NULL;
	vector<dataType> elements = tree.toArray();
	for each (dataType elem in elements) {
		_add(root, elem);
	}
}

Tree::~Tree() {		// ����������
	clear();
}

/* �������� ������ */
void Tree::add(dataType addValue) {	// ������� ���������� ������ ����� � ������
	return _add(root, addValue);
}

void Tree::clear() {	// ������� ������� ������
	if (root != NULL)
		_clear(root);
}

void Tree::copy(Tree &tree) {	// ������� ����������� ������
	clear();
	root = NULL;
	vector<dataType> elements = tree.toArray();
	for each (dataType elem in elements) {
		_add(root, elem);
	}
}

void Tree::erase(dataType deleteValue) {		// ������� �������� �� ������ ��������� � �������� ��������� 
	if (isExist(deleteValue)) {
		vector<dataType> newElements;
		for each (dataType elem in toArray()) {	// ��������� �� ��������, ������� �� ����� ��������� ��������
			if (elem != deleteValue)
				newElements.push_back(elem);
		}
		clear();
		for each (dataType elem in newElements) {	// ��������� ���������� ������� � ������
			add(elem);
		}
	}
}

void Tree::print() {	// ����� �� ����� ���� ��������� � ������� ������� �����-������-������
	_print(root);
}

void Tree::printByTree(int h) {	// ����� ������ �� ����� � ����������� ����, ���������� �� 90 �������� ������ ������� �������
	_printByTree(root);
}

/* ����������� ������ */
void Tree::loadFromArray(vector<dataType> vec) {	// ������� �������� ������ �� ��������� �������
	clear();
	for (unsigned int i = 0; i < vec.size(); i++) {
		add(vec[i]);
	}
}

vector<dataType> Tree::toArray() {		// ������� �������� ������� �� ��������� ������
	vector<dataType> vec;
	_toArray(root, vec);
	return vec;
}

bool Tree::isExist(dataType findItem) {		// ������� ��������, ���������� �� �������� ������� � ������
	return _isExist(root, findItem);
}

int Tree::count() {		// ������� �������� ����� ��������� ������
	int cnt = 0;
	_count(root, cnt);
	return cnt;
}

dataType Tree::min() {		// ������� ���������� ������������ �������� ��������� ������
	if (root != NULL)
		return _findMin(root)->data;
	else {
		cout << "������ ������!" << endl;
		return -999;
	}
}

dataType Tree::max() {		// ������� ���������� ������������� �������� ��������� ������
	if (root != NULL)
		return _findMax(root)->data;
	else {
		cout << "������ ������!" << endl;
		return -999;
	}
}


ostream &operator<<(ostream &out, Tree tree) {		// ������������� �������� '<<' ������ ��������� ������ � �����
	for each (dataType elem in tree.toArray())
		out << elem << " ";
	return out;
}