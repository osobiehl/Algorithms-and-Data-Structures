//
// Created by Jose Ignacio Biehl on 30.03.20.
//

#ifndef REDBLACKBST_REDBLACKTREE_H
#define REDBLACKBST_REDBLACKTREE_H
#include <iostream>

// struct Node
//{
//	int data;
//	Color color;
//	Node *left, *right, *parent;
//};
template <class T> class RedBlackTreeGeneral;
template <class T>
void debug(RedBlackTreeGeneral<T>&);


template <class T> class RedBlackTreeGeneral
{
	 enum Color {RED, BLACK};
	 struct Node
	{
		T data;
		Color color;
		Node *left, *right, *parent;
	};

private:
	Node *root;
	void destroyRecursive(Node* in){

		if (in->right != nullptr)
			destroyRecursive(in->right);
		if (in->left != nullptr)
			destroyRecursive(in->left);
		//std::cout<<"deleting element: "<<in->data<<std::endl;
		delete in;
	}
protected:

	inline bool isRed(Node* r){
		return (r != nullptr && r->color == RED);
	}


// 	based on Sedgewick's algorithms third edition for Java

	void rotateLeft(Node *& h);

	void rotateRight(Node *& h);


	void insert(Node* refNode, Node* elem);
	//helper function for deletion
	//	//dir = RIGHT


	int jsw_rb_assert(Node* elem);

	void insertFixUp(Node*& h);

	void swapColor(Color& a, Color& b){
		Color temp = a;
		a = b;
		b = temp;
	}

	void transplant(Node*&u, Node*& v){
		if (u->parent == nullptr)
			root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else u->parent->right = v;
		if (v != nullptr)
			v->parent = u->parent;
		delete u;
	}

public:
	friend void debug<T>(RedBlackTreeGeneral<T>& );
	void debug(){
		std::cout<<jsw_rb_assert(root)<<std::endl;
	}

	RedBlackTreeGeneral(){

		root =nullptr ;
	}
	void insert(T in){
		Node* newel = new Node;
		newel->data = in;
		newel->left = newel->right = newel->parent = nullptr ;
		if (root == nullptr || root == nullptr ){
			newel->color = BLACK;
			root = newel;
			return;
		}
		else {
			newel->color = RED;
			insert(root, newel);
		}

	}


	void  remove(Node *& z);
	void RB_DELETE_FIXUP(Node*& x);
	Node* minNode(Node *& arg){
		Node* cursor;
		for (cursor = arg; cursor->left != nullptr ; cursor = cursor->left){}
		return cursor;
	}
	Node* maxNode(Node*& arg){
		Node* cursor;
		for (cursor = arg; cursor ->right != nullptr; cursor = cursor->right){}
		return cursor;
	}
	Node * predecessor( Node *& a){
		Node* ref = a;
		if (ref == nullptr)
			return nullptr;
		if (ref->left != nullptr)
			return maxNode(ref->left);
		Node* x = ref;
		Node* y = ref->parent;
		while (y != nullptr && x == y->left) {
			x = y;
			y = y->parent;
		}
		return y;
	}


	Node * successor(Node *& a) {
		Node* ref = a;
		if (ref == nullptr )
			return nullptr ;
		if (ref->right != nullptr){
			//	std::cout<<"right element is :"<<ref->data<<" should return: "<<minNode(ref->right)->data<<std::endl;
			return minNode(ref->right);
		}
		Node* x = ref;
		Node* y = ref->parent;
		while (y != nullptr && x == y->right){
			x = y;
			y = y->parent;
			//std::cout<<"parent data is: "<<y->data<<"\n";
		}
		//std::cout<<"loop broken at: "<<y->data<<"\n";
		return y;
	}

	void print(){

		for (Node* cursor = getMinimum(); cursor != nullptr; cursor = successor(cursor) ){
			std::cout<<cursor->data<<"\n";
		}
	}
	Node * getMinimum(){
		Node* cursor;
		for (cursor = root; cursor->left != nullptr; cursor = cursor->left);
		return cursor;
	}
	Node * getMaximum(){
		Node* cursor;
		for (cursor = root; cursor->right != nullptr; cursor = cursor->right);
		return cursor;
	}
	Node * search(T elem){
		auto it = root;
		while (it != nullptr){
			if (elem == it->data)
				return it;
			if (elem > it->data){
				it = it->right;
			} else it = it->left;
		}
		return nullptr;
	}

	~RedBlackTreeGeneral(){
		destroyRecursive(root);
	}
	void printBackwards(){
		for (auto cursor = getMaximum(); cursor != nullptr; cursor = predecessor(cursor) )
			std::cout<<cursor->data<<std::endl;
	}
};


#endif //REDBLACKBST_REDBLACKTREE_H
