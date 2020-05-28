#include "RedBlackTree.h"


template<class T>
void RedBlackTreeGeneral<T>::insert(RedBlackTreeGeneral::Node *refNode, RedBlackTreeGeneral::Node *elem) {
	Node* y = nullptr;
	while (refNode != nullptr) {
		y = refNode;
		if (elem->data < refNode->data) {
			refNode = refNode->left;
		} else if (elem->data == refNode->data) {
			return;
		} else
			refNode = refNode->right;
	}
	elem->parent = y;
	if (y == nullptr)
		root = elem;
	else if (elem->data < y->data)
		y->left = elem;
	else y->right = elem;

	insertFixUp(elem);

}

template<class T>
void RedBlackTreeGeneral<T>::insertFixUp(RedBlackTreeGeneral::Node *&pt) {
	Node *p_ptr = nullptr;
	Node *gp_ptr = nullptr;

	while ((pt != root) && (pt->color != BLACK) &&
		   (pt->parent->color == RED))
	{

		p_ptr = pt->parent;
		gp_ptr = pt->parent->parent;

		/*  Case : A
			Parent of pt is left child of Grand-parent of pt */
		if (p_ptr == gp_ptr->left){

			Node *uncle_ptr = gp_ptr->right;

			/* uncle is also red, only color flip is necessary */
			if (uncle_ptr != nullptr && uncle_ptr->color == RED){
				gp_ptr->color = RED;
				p_ptr->color = BLACK;
				uncle_ptr->color = BLACK;
				pt = gp_ptr;
			}

			else{

				if (pt == p_ptr->right){
					rotateLeft(p_ptr);
					pt = p_ptr;
					p_ptr = pt->parent;
				}

				rotateRight(gp_ptr);
				swapColor(p_ptr->color, gp_ptr->color);
				pt = p_ptr;
			}
		}


		else
		{
			Node *uncle_pt = gp_ptr->left;


			if ((uncle_pt != NULL) && (uncle_pt->color == RED))
			{
				gp_ptr->color = RED;
				p_ptr->color = BLACK;
				uncle_pt->color = BLACK;
				pt = gp_ptr;
			}
			else{

				if (pt == p_ptr->left){
					rotateRight( p_ptr);
					pt = p_ptr;
					p_ptr = pt->parent;
				}


				rotateLeft(gp_ptr);
				swapColor(p_ptr->color, gp_ptr->color);
				pt = p_ptr;
			}
		}
	}

	root->color = BLACK;
}

template<class T>
int RedBlackTreeGeneral<T>::jsw_rb_assert(RedBlackTreeGeneral::Node *elem) {
	int lh, rh;

	if (elem == nullptr)
	{
		return 1;
	}
	else
	{
		struct Node *ln = elem->left;
		struct Node *rn = elem->right;

		/* Consecutive red links */
		if (isRed(elem))
		{
			if (isRed(ln) || isRed(rn))
			{
				std::cout<<"Red violation on node: "<<elem->data<<" left is: "<<(elem->left != nullptr? elem->left->data : 0 )
						 <<" right is: "<<(elem->right != nullptr? elem->right->data : 0 )<<std::endl;
				return 0;
			}
		}
		lh = jsw_rb_assert(ln);
		rh = jsw_rb_assert(rn);

		/* Invalid binary search tree */
		if ((ln != nullptr && ln->data >= elem->data) || (rn != nullptr && rn->data <= elem->data))
		{
			std::cout<<"Binary tree violation\n";
			return 0;
		}

		/* Black height mismatch */
		if (lh != 0 && rh != 0 && lh != rh)
		{
			std::cout<<"Black violation\n";
			return 0;
		}

		/* Only count black links */
		if (lh != 0 && rh != 0)
		{
			return isRed(elem) ? lh : lh + 1;
		}
		else
		{
			return 0;
		}
	}
}

template<class T>
void RedBlackTreeGeneral<T>::rotateLeft(RedBlackTreeGeneral::Node *&x) {
	Node* y= x->right;
	x->right =y->left;
	if (y->left != nullptr){
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr)
		root = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
}

template<class T>
void RedBlackTreeGeneral<T>::rotateRight(RedBlackTreeGeneral::Node *&x) {
	Node* y = x->left;
	x->left = y->right;
	if (y->right != nullptr) y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == nullptr) root = y;
	else if (x == x->parent->right) x->parent->right = y;
	else x->parent->left = y;
	y->right = x;
	x->parent = y;


}

template <class T>
void debug(RedBlackTreeGeneral<T>& in){
	auto a = in.search(72);
	auto b = in.search(41);
	in.transplant(a, b);
}

template<class T>
void RedBlackTreeGeneral<T>::RB_DELETE_FIXUP(RedBlackTreeGeneral::Node *&x) {
	Node* w;
	while (x != root && x->color == BLACK){
		if (x == x->parent->left){
			w = x->parent->right;
			if (w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				rotateLeft(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK){
				w->color = RED;
				x = x->parent;
			}
			else if (w->right->color == BLACK){
				w->left->color = BLACK;
				w->color = RED;
				rotateRight(w);
				w = x->parent->right;
			}
			w->color = x->parent->color;
			x->parent->color = BLACK;
			w->right->color = BLACK;
			rotateLeft(x->parent);
			x = root;
		}
		else{
			w = x->parent->left;
			if (w->color == RED){
				w->color = BLACK;
				x->parent->color = RED;
				rotateRight(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK){
				w->color = RED;
				x = x->parent;
			}
			else if (w->left->color == BLACK){
				w->right->color = BLACK;
				w->color = RED;
				rotateLeft(w);
				w = x->parent->left;
			}
			w->color = x->parent->color;
			x->parent->color = BLACK;
			w->left->color = BLACK;
			rotateRight(x->parent);
			x = root;
		}

	}
	x->color = BLACK;
}

template<class T>
void RedBlackTreeGeneral<T>::remove(RedBlackTreeGeneral::Node *&z) {
	if (z == nullptr)
		return;
	Node* y = z;
	Node* x;
	auto y_original_color = y->color;
	if (z->left == nullptr){
		x = z->right;
		transplant(z, z->right);
	}

	else if(z->right == nullptr){
		x = z->left;
		transplant(z, z->left);
	}

	else {

		y = minNode(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else {
			transplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	if (y_original_color == BLACK)
		RB_DELETE_FIXUP(x);
}