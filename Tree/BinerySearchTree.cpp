#include <iostream>

using namespace std;

struct tree {
	tree *left;
	tree *right;
	int key;
};
tree* getNode() {
	tree* newNode = (tree*)malloc(sizeof(tree));
	return newNode;
}
void insert(tree* &T, int newKey) {
	tree *q = NULL;
	tree *p = T;
	while (p != NULL) {
		if (newKey == p->key) return;
		q = p;
		if (newKey < p->key) p = p->left;
		else p = p->right;
	}
	tree* newNode = getNode();
	newNode->key = newKey;
	newNode->right = NULL;
	newNode->left = NULL;
	if (T == NULL) {
		T = newNode;
	}
	else if (newKey < q->key) {
		q->left = newNode;
	}
	else {
		q->right = newNode;
	}
}

bool searchParentBST(tree *&T, int searchKey, tree *&q, tree *&p) {
	q = NULL;
	p = T;
	while (p != NULL) {
		if (searchKey == p->key) return true;
		q = p;
		if (searchKey < p->key) p = p->left;
		else p = p->right;
	}
	return false;
}

int height(tree *T) {
	int L = 0;
	int R = 0;
	if (T->left == NULL && T->right == NULL) return 1;
	if (T->right != NULL) {
		R = height(T->right);
	}
	if (T->left !=NULL){
		L = height(T->left);
	}
	if (L > R) return L + 1;
	else return R + 1;
}

tree* maxNode(tree *T) {
	if (T->right == NULL) return T;
	return maxNode(T->right);
}
tree* minNode(tree *T) {
	if (T->left == NULL) return T;
	return minNode(T->left);
}

int noNodes(tree *T) {
	if (T == NULL) return 0;
	return noNodes(T->left) + noNodes(T->right) + 1;
}

void deleteBST(tree *&T, int deleteKey) {
	tree *p, *q;
	searchParentBST(T, deleteKey, q, p);
	if (p == NULL) return;
	if (q == NULL && p->left == NULL && p->right==NULL) { T = NULL; return; }
	if (p->left == NULL && p->right == NULL) {//삭제할 노드의 차수가 0인경우
		if (q->left == p) q->left = NULL;
		else q->right = NULL;
	}
	else if (p->left == NULL || p->right == NULL) {//삭제할 노드의 차수가 1인경우
		if (p->left != NULL) {
			if (q == NULL) {
				p->key = p->left->key;
				p->right = p->left->right;
				p->left = p->left->left;
			}
			else if (q->left == p) q->left = p->left;
			else q->right = p->left;
		}
		else {
			if (q == NULL) {
				p->key = p->right->key;
				p->left = p->right->left;
				p->right = p->right->right;
			}
			else if (q->left == p) q->left = p->right;
			else q->right = p->right;
		}
	}
	else {//if (p->left != NULL && p->right != NULL) {삭제할 노드의 차수가 2인경우
		tree *r;
		bool flag;//0 is LEFT, 1 is RIGHT
		if (height(p->left) > height(p->right)) { r = maxNode(p->left); flag = 0; }
		else if (height(p->left) < height(p->right)) { r = minNode(p->right); flag = 1; }
		else {//높이가 동일
			if (noNodes(p->left) >= noNodes(p->right)) {
				r = maxNode(p->left);
				flag = 0;
			}
			else {
				r = minNode(p->right);
				flag = 1;
			}
		}
		if (flag == 0) deleteBST(p, r->key);
		else deleteBST(p, r->key);
		p->key = r->key;
	}
}

void inorder(tree *T) {
	if (T != NULL) {
		inorder(T->left);
		cout << T->key<<" ";
		inorder(T->right);
	}
}

void inorderBST(tree *T) {
	inorder(T);
	cout << "\n";
}

int main() {
	tree *T = NULL;
	//삽입
	insert(T, 40); inorderBST(T);
	insert(T, 11); inorderBST(T);
	insert(T, 77); inorderBST(T);
	insert(T, 33); inorderBST(T);
	insert(T, 20); inorderBST(T);
	insert(T, 90); inorderBST(T);
	insert(T, 99); inorderBST(T);
	insert(T, 70); inorderBST(T);
	insert(T, 88); inorderBST(T);
	insert(T, 80); inorderBST(T);
	insert(T, 66); inorderBST(T);
	insert(T, 10); inorderBST(T);
	insert(T, 22); inorderBST(T);
	insert(T, 30); inorderBST(T);
	insert(T, 44); inorderBST(T);
	insert(T, 55); inorderBST(T);
	insert(T, 50); inorderBST(T);
	insert(T, 60); inorderBST(T);
	insert(T, 100); inorderBST(T);
	// 삭제 1
	deleteBST(T, 40); inorderBST(T);
	deleteBST(T, 11); inorderBST(T);
	deleteBST(T, 77); inorderBST(T);
	deleteBST(T, 33); inorderBST(T);
	deleteBST(T, 20); inorderBST(T);
	deleteBST(T, 90); inorderBST(T);
	deleteBST(T, 99); inorderBST(T);
	deleteBST(T, 70); inorderBST(T);
	deleteBST(T, 88); inorderBST(T);
	deleteBST(T, 80); inorderBST(T);
	deleteBST(T, 66); inorderBST(T);
	deleteBST(T, 10); inorderBST(T);
	deleteBST(T, 22); inorderBST(T);
	deleteBST(T, 30); inorderBST(T);
	deleteBST(T, 44); inorderBST(T);
	deleteBST(T, 55); inorderBST(T);
	deleteBST(T, 50); inorderBST(T);
	deleteBST(T, 60); inorderBST(T);
	deleteBST(T, 100); inorderBST(T);
	// 재삽입
	insert(T, 40); inorderBST(T);
	insert(T, 11); inorderBST(T);
	insert(T, 77); inorderBST(T);
	insert(T, 33); inorderBST(T);
	insert(T, 20); inorderBST(T);
	insert(T, 90); inorderBST(T);
	insert(T, 99); inorderBST(T);
	insert(T, 70); inorderBST(T);
	insert(T, 88); inorderBST(T);
	insert(T, 80); inorderBST(T);
	insert(T, 66); inorderBST(T);
	insert(T, 10); inorderBST(T);
	insert(T, 22); inorderBST(T);
	insert(T, 30); inorderBST(T);
	insert(T, 44); inorderBST(T);
	insert(T, 55); inorderBST(T);
	insert(T, 50); inorderBST(T);
	insert(T, 60); inorderBST(T);
	insert(T, 100); inorderBST(T);
	//삭제2
	deleteBST(T, 100); inorderBST(T);
	deleteBST(T, 60); inorderBST(T);
	deleteBST(T, 50); inorderBST(T);
	deleteBST(T, 55); inorderBST(T);
	deleteBST(T, 44); inorderBST(T);
	deleteBST(T, 30); inorderBST(T);
	deleteBST(T, 22); inorderBST(T);
	deleteBST(T, 10); inorderBST(T);
	deleteBST(T, 66); inorderBST(T);
	deleteBST(T, 80); inorderBST(T);
	deleteBST(T, 88); inorderBST(T);
	deleteBST(T, 70); inorderBST(T);
	deleteBST(T, 99); inorderBST(T);
	deleteBST(T, 90); inorderBST(T);
	deleteBST(T, 20); inorderBST(T);
	deleteBST(T, 33); inorderBST(T);
	deleteBST(T, 77); inorderBST(T);
	deleteBST(T, 11); inorderBST(T);
	deleteBST(T, 40); inorderBST(T);
	return 0;
}
