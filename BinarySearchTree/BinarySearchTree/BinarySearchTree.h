#pragma once
#include<iostream>
using namespace std;

template<class K>
struct BSTreeNode
{
	K _val;
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;

	BSTreeNode(const K& key)
		:_val(key)
		,_left(nullptr)
		,_right(nullptr)
	{}
};

template<class K>
class BSTree
{
	typedef BSTreeNode<K> BSTNode;
public:
	// 插入
	bool Insert(const K& key)
	{
		// 如果为空树，直接插入
		if (_root == nullptr)
		{
			_root = new BSTNode(key);
			return true;
		}

		BSTNode* cur = _root;
		BSTNode* parent = nullptr;
		// 当cur为空停下
		while (cur)
		{
			parent = cur;
			// 如果要插入的值大于当前节点的值则向右走
			if (key > cur->_val)
			{
				cur = cur->_right;
			}
			else if (key < cur->_val)// 向左走
			{
				cur = cur->_left;
			}
			else // 相等报错
			{
				return false;
			}
		}
		cur = new BSTNode(key);
		if (key > parent->_val)
		{
			parent->_right = cur;
		}
		else if (key < parent->_val)
		{
			parent->_left = cur;
		}

		return true;
	}

	// 查找
	bool Find(const K& key)
	{
		if (_root == nullptr)
			return false;

		BSTNode* cur = _root;
		while (cur)
		{
			// key大向右走
			if (key > cur->_val)
			{
				cur = cur->_right;
			}
			else if (key < cur->_val)// key小向左走
			{
				cur = cur->_left;
			}
			else // 找到了
			{
				return true;
			}
		}

		return false;
	}
	
	// 删除
	bool Erase(const K& key)
	{
		BSTNode* cur = _root;
		BSTNode* parent = nullptr;
		while (cur)
		{
			// key大向右走
			if (key > cur->_val)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_val)// key小向左走
			{
				parent = cur;
				cur = cur->_left;
			}
			else // 删除
			{
				// 1.左为空
				if (cur->_left == nullptr)
				{
					// 如果所要删除的节点就是根节点
					if (cur == _root)
					{
						_root = cur->_right;
						delete cur;
						return true;
					}
					if (parent->_left == cur)
					{
						parent->_left = cur->_right;
					}
					else
					{
						parent->_right = cur->_right;
					}
					delete cur;
					return true;
				}
				else if (cur->_right == nullptr) // 2.右为空
				{
					// 如果所要删除的节点就是根节点
					if (cur == _root)
					{
						_root = cur->_left;
						delete cur;
						return true;
					}
					if (parent->_left == cur)
					{
						parent->_left = cur->_left;
					}
					else
					{
						parent->_right = cur->_left;
					}
					delete cur;
					return true;
				}
				else // 3.左右都不为空
				{
					// 找右子树的最小节点(最左节点)
					BSTNode* subLeft = cur->_right;
					BSTNode* subParent = cur;
					while (subLeft->_left)
					{
						subParent = subLeft;
						subLeft = subLeft->_left;
					}
					// 交换节点的值
					swap(cur->_val, subLeft->_val);
					if (subParent->_left == subLeft)
					{
						subParent->_left = subLeft->_right;
					}
					else
					{
						subParent->_right = subLeft->_right;
					}
					delete subLeft;
					return true;
				}
			}
		}
		return false;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	// 中序
	void _InOrder(BSTNode* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_val << " ";
		_InOrder(root->_right);
	}

private:
	BSTNode* _root = nullptr;
};