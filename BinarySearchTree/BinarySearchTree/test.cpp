#include "BinarySearchTree.h"

void BSTtest1()
{
	BSTree<int> bt;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	for (auto e : a)
	{
		bt.Insert(e);
	}

	bt.InOrder();

	cout << bt.Find(3) << endl;
	cout << bt.Find(0) << endl;
}

void BSTtest2()
{
	BSTree<int> bt;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	for (auto e : a)
	{
		bt.Insert(e);
	}
	bt.InOrder();

	bt.Erase(7);
	bt.InOrder();
	bt.Erase(14);
	bt.InOrder();
	bt.Erase(3);
	bt.InOrder();
	bt.Erase(8);
	bt.InOrder();
	bt.Erase(1);
	bt.Erase(4);
	bt.Erase(6);
	bt.Erase(10);
	bt.InOrder();
	cout << bt.Erase(13) << endl;
	
	cout << bt.Erase(13) << endl;
}

int main()
{
	BSTtest2();
	return 0;
}