#ifndef RBTREE
#define RBTREE
#include "DynamicSearchTable.hpp"

template <typename elemType, typename Key>
class RBTree : public dynamicSearchTable
{
private:
	struct RBNode
	{
		elemType data;
		Key key;
		RBNode *left;
		RBNode *right;
		int colour; // 1 represents red, 0 represents black
		RBNode() = default;
		RBNode(const elemType &x, const Key &k, int c, RBNode *l = nullptr, RBNode *r = nullptr)
			: data(x), key(k), left(l), right(r), colour(c){};
	};
	elemType *find(const Key &, RBNode *&) const;
	bool remove(const Key &, RBNode *&);
	bool insert(const elemType &, const Key &, RBNode *&);
	void Inorder(RBNode *t)
	{
		if (t == nullptr)
			return;
		Inorder(t->left);
		std::cout << t->data << ' ';
		Inorder(t->right);
	}
	RBNode *root;
	void delTree(RBNode *t)
	{
		if (t == nullptr)
			return;
		delTree(t->left);
		delTree(t->right);
		delete t;
	}

public:
	elemType *find(const Key &k) const
	{
		return find(k, root);
	}
	void remove(const Key &k)
	{
		remove(k, root);
	}
	void insert(const elemType &x, const Key &k)
	{
		insert(x, k, root);
	}
	RBTree()
	{
		root = nullptr;
	}
	~RBTree()
	{
		delTree(root);
		root = nullptr;
	}
	void Inorder() const
	{
		Inorder(root);
	}
};

template <typename elemType, typename Key>
elemType *RBTree<elemType, Key>::find(const Key &k, RBNode *&t) const
{
	if (t == nullptr)
		return nullptr;
	if (k == t->key)
		return &(t->data) else if (k < t->key) return find(t->left);
	else
		return find(t->right);
}

template <typename elemType, typename Key>
bool RBTree<elemType, Key>::insert(const elemType &x, const Key &k, RBNode *&t)
{
	if (t == nullptr)
	{
		t = new RBNode{x, k, 1};
		return false;
	}
	if (t->colour == 0)
	{
		if (k < t->key)
		{
			insert(x, k, t->left);
			return true;
		}
		else
		{
			insert(t->right);
			return true;
		}
	}
	else
	{
		if (k < t->key)
		{
			if (insert(x, k, t->left))
				return true;
			else
			{
				if (t->right->colour == 1)
				{
					t->colour =
						return false;
				}
				else
				{
					return true;
				}
			}
		}
		else
		{
		}
	}
}

#endif
