#include <vector>

namespace CG {
	template<typename T>
	struct BSTNode {
		BSTNode *left, *right, *parent;
		float key;
		T* data;

		BSTNode(float k, T *d) : key{k}, data{d}, left{nullptr},
			right{nullptr}, parent{nullptr} {};
		//std::vector<T> inorder();
		T* search(float);
		BSTNode* min();
		BSTNode* max();
		BSTNode* pred();
		BSTNode* succ();
	};

	template<typename T>
	struct BSTree {
		BSTNode<T> *root;
		BSTree() : root{nullptr} {};
		BSTree(BSTNode<T> *p) : root{p} {};
		void insert(BSTNode<T> *);
		void transplant(BSTNode<T> *, BSTNode<T> *);
		void del(BSTNode<T> *);
	};

	template<typename T>
	T* BSTNode<T>::search(float k)
	{
		BSTNode<T> *curr = this;
		while (k != curr->key) {
			if (k < curr->key && curr->left != nullptr) {
				curr = curr->left;
			} else if (curr->right != nullptr) {
				curr = curr->right;
			}
		}
		if (curr->key == k) return curr->data;
		return nullptr;
	}

	template<typename T>
	BSTNode<T>* BSTNode<T>::min()
	{
		BSTNode<T> *curr = this;
		while (curr->left != nullptr)
			curr = curr->left;
		return curr;
	}

	template<typename T>
	BSTNode<T>* BSTNode<T>::max()
	{
		BSTNode<T> *curr = this;
		while (curr->right != nullptr)
			curr = curr->right;
		return curr;
	}

	template<typename T>
	BSTNode<T>* BSTNode<T>::succ()
	{
		if (right != nullptr)
			return right->min();
		BSTNode<T> *x = this;
		BSTNode<T> *y = parent;
		while (y != nullptr && y->right == x) {
			x = y;
			y = y->parent;
		}
	}

	template<typename T>
	BSTNode<T>* BSTNode<T>::pred()
	{
		if (left != nullptr)
			return left->max();
		BSTNode<T> *x = this;
		BSTNode<T> *y = parent;
		while (y != nullptr && y->left == x) {
			x = y;
			y = y->parent;
		}
	}

	template<typename T>
	void BSTree<T>::insert(BSTNode<T> *n)
	{
		BSTNode<T> *curr = root;
		BSTNode<T> *p = nullptr;
		while (curr != nullptr) {
			p = curr;
			if (n->key < curr->key) {
				curr = curr->left;
			} else {
				curr = curr->right;
			}
		}
		n->parent = p;
		if (p == nullptr) {
			root = n;
		} else if (n->key < p->key) {
			p->left = n;
		} else {
			p->right = n;
		}
	}

	template<typename T>
	void BSTree<T>::transplant(BSTNode<T> *u, BSTNode<T> *v)
	{
		if (u->parent == nullptr) {
			root = v;
		} else if (u == u->parent->left) {
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		if (v != nullptr)
			v->parent = v->parent;
	}

	template<typename T>
	void BSTree<T>::del(BSTNode<T> *n)
	{
		if (n->left == nullptr) {
			transplant(n, n->right);
		} else if (n->right == nullptr) {
			transplant(n, n->left);
		} else {
			BSTNode<T> *y = n->right->min();
			if (y->parent != n) {
				transplant(y, y->right);
				y->right = n->right;
				y->right->parent = y;
			}
			transplant(n, y);
			y->left = n->left;
			y->left->parent = y;
		}
	}
}
