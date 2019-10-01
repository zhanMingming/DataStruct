#include <iostream>
#include <cstring>
#include <limits>
#include "BTree.h"
using namespace std;
using namespace zhanmm;

void Menu() {
	cout << "--Data Struct-BTree--" << endl;
	cout << "instruction:" << endl;
	cout << "1.install B-Tree" << endl;
	cout << "2.Print  B-Tree" << endl;
	cout << "3.Delete Element" << endl;
	cout << "4.Insert Element" << endl;
	cout << "5.quit" << endl;
}



int main()
{
	Menu();
	BTree<int>* bt = nullptr;
	bool flag = true;
	while (flag) {
		cout << "Input operation number:";
		int n;
		cin.clear();cin.sync();
		cin >> n;
		switch (n) {
		case 1:
			if (bt != nullptr) {
				cout << "already exist BTree" << endl;
				continue;
			}
			else {
				cout << "Input degree and number of element:";
				int m, n;
				cin >> m >> n;
				if (m < 2) {
					cout << "need greater than two" << endl;
					continue;
				}
				bt = new BTree<int>(m);
				cout << "Input" << n << " elements:" << endl;
				for (int i = 0;i < n;++i) {
					int c;
					cin >> c;
					bt->Insert(c);
				}
			}
			break;
		case 2:
			if (bt == nullptr) {
				cout << "Need to install Btree" << endl;
			}
			else if (bt->TotalSize() <= 0) {
				cout << "No  elements in Btree" << endl;
			}
			else {
				bt->Print();
			}
			break;
		case 3:
			if (bt == nullptr) {
				cout << "Need to install Btree" << endl;
			}
			else if (bt->TotalSize() <= 0) {
				cout << "No  elements in Btree" << endl;
			}
			else {
				cout << "Enter element to be deleted";
				int k;
				cin >> k;
				bt->Delete(k);
			}
			break;
		case 4:
			if (bt != nullptr) {
				cout << "Enter element to be inserted";
				int c;
				cin >> c;
				bt->Insert(c);
			}
			else {
				cout << "Need to install Btree" << endl;
			}
			break;
		case 5:
			delete bt;
			bt = nullptr;
			flag = false;
			break;
		default:
			cout << "input invaild" << endl;
			cin.clear();            //clear bad input flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
			
		}
	}
	return 0;
}
