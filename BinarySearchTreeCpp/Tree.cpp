#include "Tree.h"
using namespace BTS;
struct Node
{
	int value;
	Node *left, *right, *parent;
};
bool flag;
Node* ans;
Node *root = nullptr;

void AddN(Node *curNode, int item)
{
	if (curNode->value > item)
	{
		if (curNode->left == nullptr)
		{
			curNode->left = new Node;
			curNode->left->value = item;
			curNode->left->left = nullptr;
			curNode->left->right = nullptr;
			curNode->left->parent = curNode;
		}
		else AddN(curNode->left, item);
	}
	else if (curNode->value < item)
	{
		if (curNode->right == nullptr)
		{
			curNode->right = new Node;
			curNode->right->value = item;
			curNode->right->left = nullptr;
			curNode->right->right = nullptr;
			curNode->right->parent = curNode;
		}
		else AddN(curNode->right, item);
	}
}

void BinarySearchTree::Add(int item)
{
	if (root == nullptr)
	{
		root = new Node;
		root->value = item;
		root->left = nullptr;
		root->right = nullptr;
		root->parent = nullptr;
	}
	else AddN(root, item);
}

vector<int> rt;

void InOrderN(Node* curNode)
{
	if (curNode == nullptr)return;
	rt.push_back(curNode->value);
	InOrderN(curNode->left);
	rt.push_back(curNode->value);
	InOrderN(curNode->right);
	rt.push_back(curNode->value);
}

vector<int> BinarySearchTree::InOrder()
{
	while (!rt.empty())
		rt.pop_back();
	InOrderN(root);
	return rt;
}

void Find(Node* curNode, int item)
{
	if (curNode == nullptr)return;
	if (flag) return;
	if (curNode->value == item)
	{
		flag = true;
		ans = curNode;
		return;
	}
	if (curNode->value < item)
	{
		if (curNode->right == nullptr)
		{
			flag = true;
			ans = nullptr;
			return;
		}
		else Find(curNode->right, item);
	}
	if (curNode->value > item)
	{
		if (curNode->left == nullptr)
		{
			flag = true;
			ans = nullptr;
			return;
		}
		else Find(curNode->left, item);
	}
}

void FindSmallest(Node * curNode, Node* beg)
{
	if (curNode == nullptr)return;
	if (flag) return;
	if (curNode->left == nullptr && curNode->right == nullptr)
	{
		flag = true;
		ans = curNode;
		return;
	}
	if (curNode->left != nullptr && curNode != beg)FindSmallest(curNode->left, beg);
	else FindSmallest(curNode->right, beg);
}



int BinarySearchTree::Remove(int item)
{
	ans = nullptr;
	flag = false;
	//printf("%d n \n", root->value);
	Find(root, item);
	Node* st = ans;
	if (st == nullptr)return item;
	int val = st->value;
	if (st->left == nullptr && st->right == nullptr)
	{
		if (st->parent != nullptr)
		{
			if (st->value < st->parent->value) st->parent->left = nullptr;
			else st->parent->right = nullptr;
		}
		else root = nullptr;
		delete st;
		st = nullptr;
		return 0;
	}
	if (st->left == nullptr && st->right != nullptr)
	{
		if (st->parent != nullptr)
		{
			if (st->value < st->parent->value)
			{
				st->parent->left = st->right;
				st->right->parent = st->parent;
			}
			else
			{
				st->parent->right = st->right;
				st->right->parent = st->parent;
			}
		}
		else
		{
			root = st->right;
			st->right->parent = nullptr;
		}
		delete st;
		st = nullptr;
		return 0;
	}
	if (st->left != nullptr && st->right == nullptr)
	{
		if (st->parent != nullptr)
		{
			if (st->value < st->parent->value)
			{
				st->parent->left = st->left;
				st->left->parent = st->parent;
			}
			else
			{
				st->parent->right = st->left;
				st->left->parent = st->parent;
			}
		}
		else
		{
			root = st->left;
			st->left->parent = nullptr;
		}
		delete st;
		st = nullptr;
		return 0;
	}
	if (st->left == nullptr && st->right == nullptr)
	{
		flag = false;
		ans = nullptr;
		FindSmallest(st, st);
		Node* sm = ans;
		if (sm->parent != nullptr)
		{
			st->value = sm->value;
		}
		else
		{
			root = sm;
		}
		delete sm;
		sm = nullptr;
		return 0;
	}
	return 0;
}

void DeleteN(Node* cur)
{
	if (cur->left == nullptr && cur->right == nullptr)
	{
		delete cur;
		cur = nullptr;
		return;
	}
	if (cur->left != nullptr)DeleteN(cur->left);
	if (cur->right != nullptr)DeleteN(cur->right);
}

void BinarySearchTree::Delete()
{
	DeleteN(root);
	root = nullptr;
}