#include "Tree.h"

void Tree::create(string exp) {
	add(exp, root, nullptr);
}

string Tree::print() {
	string exp;
	show(exp, root);
	return exp;
}

void Tree::del() {
	deleteTree(root);
	root = nullptr;
}

string Tree::straight() {
	string exp;
	strai(exp, root);
	return exp;
}

void Tree::add(string exp, Node *& cur, Node * parent) {
	cur = new Node(exp[0], parent);//create new node
	exp.erase(exp.begin());//erase 1-st symbol in expression

	int depth = 0;
	for (int i = 0; i < exp.size(); i++) {
		switch (exp[i])
		{
		case '(': depth++;
			break;
		case ')': depth--;
			if (depth == 0) {
				Node* tmp;
				add(string(exp.substr(1, i - 1)), tmp, cur);//create subtree with son subroot
				cur->sons.push_back(tmp);//add son
				exp.erase(0, i + 1);//erase used values
				i = -1;
			}
			break;
		default:
			break;
		}
	}
}

void Tree::deleteTree(Node * cur) {
	for (int i = 0; i < cur->sons.size(); i++) {
		deleteTree(cur->sons.get(i));//go to sons
	}
	delete cur;//delete node
}

template<class T>
T List<T>::get(int i) {
	Node1* p = fron;
	for (int t = 0; t < i; t++) p = p->next;//move to necessary node
	return p->val;
}

template<class T>
inline void List<T>::push_back(T a) {
	Node1* p = fron;
	if (!p) {
		fron = new Node1; fron->val = a;//create front of list if does not exist
	}
	else {
		while (p->next) p = p->next;
		Node1* t;
		t = new Node1; t->val = a;//create new node
		p->next = t;
	}
	siz++;
}

template<class T>
int List<T>::size() { return siz; }

void Tree::show(string & exp, Node * cur) {
	if (cur) {
		exp += cur->val;
		for (int i = 0; i < cur->sons.size(); i++) {//go to sons
			Node* it = cur->sons.get(i);
			exp += '(';
			show(exp, it);
			exp += ')';
		}
	}
}

inline void Tree::strai(string & exp, Node * cur) {
	if (cur) {
		for (int i = 0; i < cur->sons.size(); i++) {//go to sons
			Node* it = cur->sons.get(i);
			strai(exp, it);
			exp += ',';
		}
		exp += cur->val;
	}
}

inline Tree::Node::Node(int a, Node * parent) {
	val = a;
	this->parent = parent;
}
