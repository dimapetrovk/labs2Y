#pragma once
#include <iostream>
#include <list>
#include <string>

using namespace std;

template <class T>
class List {//list class
	struct Node1 {//list node
	public:
		T val;//node value
		Node1* next=nullptr;
	};
	int siz = 0;//size of list
private: Node1* fron;//front of list
public:	void push_back(T a);//push into list

		int size();//size of list
		T get(int i);//get node value

};

class Tree {
	class Node {//node of tree
	public:	char val;//value
			Node* parent;//parend node
			List<Node*> sons;
	public: Node(int a, Node* parent);//constructor
	};
	Node* root = NULL;//tree root

public: void create(string exp);//fill out the tree

		string print();//show tree with brakets

		void del();//erase tree

		string straight();//direct bypass tree

private:	void add(string exp, Node* &cur, Node* parent);//fill out the subtree

			void deleteTree(Node* cur);//erase subtree

			void show(string &exp, Node* cur);//show subtree with brakets

			void strai(string &exp, Node* cur);//direct bypass subtree
};


