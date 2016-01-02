#include <iostream>
#include <string>
#include "tree.h"

using namespace std;

void main() {
	cout << "Enter exp: ";
	string exp;
	cin >> exp;
	Tree mytree;
	mytree.create(exp);//create tree
	cout<<mytree.straight()<<endl;//direct bypass tree
	cout << mytree.print() << endl;//show tree with brakets
	mytree.del();//erase tree
	cout << mytree.print() << endl;//show tree with brakets
	system("pause");
}