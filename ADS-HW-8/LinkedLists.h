//
// Created by Jose Ignacio Biehl on 28.03.20.
//

#ifndef STACKSANDQUEUES_LINKEDLISTS_H
#define STACKSANDQUEUES_LINKEDLISTS_H
#include <iostream>
template <class T> class LinkedList;
template <class T> class RedBlackTreeGeneral;

template <class T> class BST{
	friend class BST;
private:
	struct Node{
		T data;
		struct Node* left;
		struct Node* right;
		struct Node* parent;
	} typedef Node;
	Node* root;

	//private insertion method to avoid recursive new calls
	 void insert( Node* refNode, Node* elem){
	 	//sift down
	 	using namespace std;
	 	if (elem->data < refNode->data) {
	 		if (refNode->left == nullptr){
	 			refNode->left = elem;
	 			elem->parent = refNode;
	 			//cout<<"inserting element: "<<elem->data<<"  as  left child of: "<<refNode->data<<"\n";
	 			return;
	 		}
			insert(refNode->left, elem);
		}
	 	else if (elem->data > refNode->data) {
			if (refNode->right == nullptr) {
				refNode->right = elem;
				elem->parent = refNode;
				//cout<<"inserting element: "<<elem->data<<"  as right  child of: "<<refNode->data<<"\n";
				return;
			}
			insert(refNode->right, elem);
		}
	 		return;

	}
	void destroyRecursive(Node* start){
	 	if (start){
	 		destroyRecursive(start->left);
			destroyRecursive(start->right);
	 	}
	 	delete start;
	 }
public:
	friend class LinkedList<T>;
	BST(){
		root = nullptr;
	}
	void insert(const T elem){
		Node* newel = new Node();
		newel->data = elem;
		newel->left = newel->right = nullptr;
		newel->parent = nullptr;

		if (root == nullptr){
		//	std::cout<<"setting root: root is: "<<newel->data<<std::endl;
			root = newel;
			return;
		}
		insert(root, newel);

	}

	Node* minNode(Node* ref){

		Node* cursor;
		//std::cout<<"cursor left is: "<<ref->left->data<<std::endl;
		for( cursor = ref; cursor->left != nullptr; cursor = cursor->left){}
		return cursor;
	}

	 Node* successor(Node* ref){
		if (ref == nullptr)
			return nullptr;
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

	 	for (Node* cursor = minNode(root); cursor != nullptr; cursor = successor(cursor) ){
	 		std::cout<<cursor->data<<"\n";
	 	}
	 }

	 ~BST(){
		destroyRecursive(root);
	}

};



//glorified queue
template <class T> class LinkedList{
private:
	struct Node{
		T data;
		Node* prev;
	}typedef Node;
	Node* start;
	Node* end;
	int size;
public:
	friend class RedBlackTreeGeneral<T>;
	void insertStart(T elem){
		Node* newel = new Node;
		newel->data = elem;
		newel->prev = nullptr;
		if ( start == nullptr){
			start = end = newel;
			return;
		}
		start->prev = newel;
		start = newel;
	}

	LinkedList(){
		start = end = nullptr;
		size = 0;
	}

	LinkedList(BST<T>& inp) {
		size = 0;
		start = end = nullptr;
		for (typename BST<T>::Node* cursor = inp.minNode(inp.root); cursor != nullptr; cursor = inp.successor(cursor) ) {
			size++;
			T a = cursor->data;
			//std::cout<<a<<std::endl;
			insertStart(a);
		}
	}


	bool removeEnd(T& res){
		if (end != nullptr) {
			auto cursor = end->prev;
			T res = end->data;
			delete end;
			end = cursor;
			return true;
		}
		return false;
	}

	void print(){
		for(auto it = end; it != nullptr; it = it->prev)
			std::cout<<it->data<<std::endl;
	}
};
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
protected:
	inline bool isRed(Node* r){
		return r == nullptr? false : (r->color == RED);
	}
	inline void invert(Node* ref){
		if (ref->color == RED) {
			ref->color = BLACK;
		} else ref->color = RED;

	}
	inline void colorFlip(Node* ref){
		invert(ref);
		invert(ref->left);
		invert(ref->right);
	}


	void rotateLeft(Node *& h){
		Node* x = h->right;
//		if (x == nullptr)
//			throw std::logic_error("error detected nullpointer\n");

		h->right =x->left;
		h-> right = x->left;
		if (x->left != nullptr){
			x->left->parent = h;
		}
		x->left = h;
		x->color = x->left->color;
		x->left->color = RED;
		Node* temp = h->parent;
		h->parent = x;
		x->parent = temp;
		if (x->parent == nullptr)
			root = x;
		else if (x->parent->left == h)
			x->parent->left = x;
		else
			x->parent->right = x;
	}

	void rotateRight(Node *& h){
		Node* x= h->left;
		h->left = x->right;
		if (x->right != nullptr)
			x->right->parent = h;
		x->right = h;
		x->color = x->right->color;
		x->right->color = RED;
		Node* temp = h->parent;
		h->parent = x;
		x->parent = temp;
		if (x->parent == nullptr)
			root = x;
		else if (x->parent->left == h)
			x->parent->left = x;
		else
			x->parent->right = x;
	}

	void insert(Node* refNode, Node* elem){
		/// split 4-nodes on the way down - Sedgewick
		if (isRed(refNode->left) && isRed(refNode->right))
			colorFlip(refNode);

		if (elem->data < refNode->data) {
			if (refNode->left == nullptr){
				refNode->left = elem;
				elem->parent = refNode;
				//cout<<"inserting element: "<<elem->data<<"  as  left child of: "<<refNode->data<<"\n";
				return;
			}
			else
				insert(refNode->left, elem);
		}
		else if (elem->data > refNode->data) {
			if (refNode->right == nullptr) {
				refNode->right = elem;
				elem->parent = refNode;
				//cout<<"inserting element: "<<elem->data<<"  as right  child of: "<<refNode->data<<"\n";
				return;
			}
			else
				insert(refNode->right, elem);
		}
		/// Balancing the tree to maintain RB- conditions, recursive calls ensure that we fix it on the way up too
		///
		if (isRed(refNode->right))
			rotateLeft(refNode);
		if (isRed(refNode->left) && isRed(refNode->left->left))
			rotateRight(refNode);

		return;
	}

public:

	RedBlackTreeGeneral(){
		root =nullptr;
	}
	RedBlackTreeGeneral(LinkedList<T>& a){
		root = nullptr;
		for(auto cursor = a.end; cursor != nullptr; cursor = cursor->prev)
			insert(cursor->data);

	}
	void insert(T in){
		Node* newel = new Node;
		newel->data = in;
		newel->left = newel->right = nullptr;
		if (root == nullptr){
			newel->color = BLACK;
			root = newel;
			return;
		}
		else {
			newel->color = RED;
			insert(root, newel);
		}

	}
	void  remove(Node *& a){


	}
	Node* minNode(Node *& arg){
		Node* cursor;
		for (cursor = arg; cursor->left != nullptr; cursor = cursor->left){}
		return cursor;
	}
	Node * predecessor(const Node *&);

	Node * successor(Node *& a) {
		Node* ref = a;
		if (ref == nullptr)
			return nullptr;
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

		for (Node* cursor = minNode(root); cursor != nullptr; cursor = successor(cursor) ){
			std::cout<<cursor->data<<"\n";
		}
	}
	Node * getMinimum();
	Node * getMaximum();
	Node * search(int);
};

#endif //STACKSANDQUEUES_LINKEDLISTS_H
