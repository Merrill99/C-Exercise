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
	// ����
	bool Insert(const K& key)
	{
		// ���Ϊ������ֱ�Ӳ���
		if (_root == nullptr)
		{
			_root = new BSTNode(key);
			return true;
		}

		BSTNode* cur = _root;
		BSTNode* parent = nullptr;
		// ��curΪ��ͣ��
		while (cur)
		{
			parent = cur;
			// ���Ҫ�����ֵ���ڵ�ǰ�ڵ��ֵ��������
			if (key > cur->_val)
			{
				cur = cur->_right;
			}
			else if (key < cur->_val)// ������
			{
				cur = cur->_left;
			}
			else // ��ȱ���
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

	// ����
	bool Find(const K& key)
	{
		if (_root == nullptr)
			return false;

		BSTNode* cur = _root;
		while (cur)
		{
			// key��������
			if (key > cur->_val)
			{
				cur = cur->_right;
			}
			else if (key < cur->_val)// keyС������
			{
				cur = cur->_left;
			}
			else // �ҵ���
			{
				return true;
			}
		}

		return false;
	}
	
	// ɾ��
	bool Erase(const K& key)
	{
		BSTNode* cur = _root;
		BSTNode* parent = nullptr;
		while (cur)
		{
			// key��������
			if (key > cur->_val)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_val)// keyС������
			{
				parent = cur;
				cur = cur->_left;
			}
			else // ɾ��
			{
				// 1.��Ϊ��
				if (cur->_left == nullptr)
				{
					// �����Ҫɾ���Ľڵ���Ǹ��ڵ�
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
				else if (cur->_right == nullptr) // 2.��Ϊ��
				{
					// �����Ҫɾ���Ľڵ���Ǹ��ڵ�
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
				else // 3.���Ҷ���Ϊ��
				{
					// ������������С�ڵ�(����ڵ�)
					BSTNode* subLeft = cur->_right;
					BSTNode* subParent = cur;
					while (subLeft->_left)
					{
						subParent = subLeft;
						subLeft = subLeft->_left;
					}
					// �����ڵ��ֵ
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

	// ����
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