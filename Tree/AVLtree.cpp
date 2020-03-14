#include <iostream>
#include <string>

using namespace std;

int h;
string Rtype;

struct tree {
	tree *left;
	tree *right;
	int key;
	int bf;
};

tree* getNode() {
	tree* newNode = (tree*)malloc(sizeof(tree));
	return newNode;
}

bool insertAVL(tree* &T, int newKey) {
	tree* y;
	if (T == NULL) {
		y = getNode();
		y->key = newKey;
		y->left = NULL;
		y->right = NULL;
		y->bf = 0;
		T = y;
		h = 1;
		return true;
	}
	int th=1;
	tree* p = T;
	tree* q = NULL;
	tree* f = NULL;
	tree* a = NULL;
	tree* b = NULL;
	//tree* f=NULL;
	tree* c = NULL;
	int d;
	bool found = false;
	while (p != NULL && found == false) {
		if (newKey < p->key) { q = p; p = p->left; }
		else if (newKey > p->key) { q = p; p = p->right; }
		else { found = true; }
		th++;
	}
	if (found == false) {
		y = getNode();
		y->key = newKey;
		y->left = NULL;
		y->right = NULL;
		y->bf = 0;
		if (newKey < q->key) q->left = y;//insert newKey
		else q->right = y;
		if (th>h) {//높이에 변화가 생긴경우
			p = T;
			q = NULL;
			while (p->key != newKey) {
				if (newKey < p->key) {
					p->bf += 1;
					//cout << p->key;
					if (p->bf == 2) { f = q; a = p; }
					q = p;
					p = p->left;
				}
				else if(newKey > p->key){
					p->bf -= 1;
					if (p->bf == -2) { f = q; a = p; }
					q = p;
					p = p->right;
				}
			}
			
			Rtype = "NO";
			if (a!=NULL && (a->bf == 2 || a->bf == -2)) {//불균형의 존재경우
				if (newKey<a->key) {
					b = a->left;
					if (newKey < b->key) {
						Rtype = "LL";
						a->bf = 0;
						b->bf = 0;
						if (f==NULL) {
							a->left = b->right;
							b->right = a;
							T = b;
						}
						else if (f->left == a) {
							a->left = b->right;
							b->right = a;
							f->left = b;
						}
						else {
							a->left = b->right;
							b->right = a;
							f->right = b;
						}
					}
					else {
						Rtype = "LR";
						c = b->right;
						if (newKey == c->key) {
							a->bf = 0;
							b->bf = 0;
						}
						else if (newKey<c->key) {
							a->bf = -1;
							b->bf = 0;
							c->bf = 0;
						}
						else {
							a->bf = 0;
							b->bf = 1;
							c->bf = 0;
						}
						if (f == NULL) {
							b->right = c->left;
							a->left = c->right;
							c->left = b;
							c->right = a;
							T = c;
						}
						else if (f->left == a) {
							b->right = c->left;
							a->left = c->right;
							c->left = b;
							c->right = a;
							f->left = c;
						}
						else {
							b->right = c->left;
							a->left = c->right;
							c->left = b;
							c->right = a;
							f->right = c;
						}
					}
				}
				else if (newKey > a->key) {
					b = a->right;
					if (newKey < b->key) {
						Rtype = "RL";
						c = b->left;
						if (newKey == c->key) {
							a->bf = 0;
							b->bf = 0;
							c->bf = 0;
						}
						else if (newKey < c->key) {
							a->bf = 0;
							b->bf = -1;
							c->bf = 0;
						}
						else {
							a->bf = 1;
							b->bf = 0;
							c->bf = 0;
						}
						if (f == NULL) {
							a->right = c->left;
							b->left = c->right;
							c->left = a;
							c->right = b;
							T = c;
						}
						else if (f->left==a) {
							a->right = c->left;
							b->left = c->right;
							c->left = a;
							c->right = b;
							f->left = c;
						}
						else {
							a->right = c->left;
							b->left = c->right;
							c->left = a;
							c->right = b;
							f->right = c;
						}

					}
					else {
						Rtype = "RR";
						a->bf = 0;
						b->bf = 0;
						if (f==NULL) {
							a->right = b->left;
							b->left = a;
							T = b;
						}
						else if (f->left==a) {
							a->right = b->left;
							b->left = a;
							f->left = b;
						}
						else {
							a->right = b->left;
							b->left = a;
							f->right = b;
						}
					}
				}
				th--;
			}

			h = th;
		}

	}
	return false;
}

void print() {
	cout << Rtype << endl;
}

void inorder(tree *T) {
	if (T != NULL) {
		inorder(T->left);
		cout << T->key << " ";
		inorder(T->right);
	}
}

void inorderBST(tree *T) {
	inorder(T);
	cout << "\n";
}

int main() {
	tree *T = NULL;
	insertAVL(T, 40); print(); inorderBST(T);
	insertAVL(T, 11); print(); inorderBST(T);
	insertAVL(T, 77); print(); inorderBST(T);
	insertAVL(T, 33); print(); inorderBST(T);
	insertAVL(T, 20); print(); inorderBST(T);
	insertAVL(T, 90); print(); inorderBST(T);
	insertAVL(T, 99); print(); inorderBST(T);
	insertAVL(T, 70); print(); inorderBST(T);
	insertAVL(T, 88); print(); inorderBST(T);
	insertAVL(T, 80); print(); inorderBST(T);
	insertAVL(T, 66); print(); inorderBST(T);
	insertAVL(T, 10); print(); inorderBST(T);
	insertAVL(T, 22); print(); inorderBST(T);
	insertAVL(T, 30); print(); inorderBST(T);
	insertAVL(T, 44); print(); inorderBST(T);
	insertAVL(T, 55); print(); inorderBST(T);
	insertAVL(T, 50); print(); inorderBST(T);
	insertAVL(T, 60); print(); inorderBST(T);
	insertAVL(T, 100); print(); inorderBST(T);
	insertAVL(T, 28); print(); inorderBST(T);
	insertAVL(T, 18); print(); inorderBST(T);
	insertAVL(T, 9); print(); inorderBST(T);
	insertAVL(T, 5); print(); inorderBST(T);
	insertAVL(T, 17); print(); inorderBST(T);
	insertAVL(T, 6); print(); inorderBST(T);
	insertAVL(T, 3); print(); inorderBST(T);
	insertAVL(T, 1); print(); inorderBST(T);
	insertAVL(T, 4); print(); inorderBST(T);
	insertAVL(T, 2); print(); inorderBST(T);
	insertAVL(T, 7); print(); inorderBST(T);
	insertAVL(T, 8); print(); inorderBST(T);
	insertAVL(T, 10); print(); inorderBST(T);
	insertAVL(T, 12); print(); inorderBST(T);
	insertAVL(T, 13); print(); inorderBST(T);
	insertAVL(T, 14); print(); inorderBST(T);
	insertAVL(T, 16); print(); inorderBST(T);
	insertAVL(T, 15); print(); inorderBST(T);
	
	return 0;
}
	