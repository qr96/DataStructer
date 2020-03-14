#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//myIdx를 저장하는방법, 삽입시 뒤 노드들의 myIdx 값을 모두 변경해주어야하는 단점

struct node {
	vector<node*>* nodes;
	vector<int>* keys;
	int size;
	bool terminal;//단말노드인지 여부
};

node* getNode() {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->keys = new vector<int>;
	newNode->nodes = new vector<node*>;
	return newNode;
}

void deleteBT(node* &T, int deleteKey, int m) {
	node* p = T;
	node* q = NULL;
	stack<int> idxes;
	stack<node*> parents;
	bool find = 0;
	int myi=-1;//삭제할 키의 인덱스
	if (T == NULL) return;
	while (!find && p->terminal == 0) {
		if (deleteKey == p->keys->back()) {
			myi = p->size - 1;
			break;
		}
		else if (deleteKey > p->keys->back()) {
			idxes.push(p->size);
			parents.push(p);
			p = p->nodes->back();
		}
		else {
			for (int i = 0; i < p->size; i++) {
				if (deleteKey == p->keys->at(i)) {
					myi = i;
					find = 1;
					break;
				}
				else if (deleteKey < p->keys->at(i)) {
					idxes.push(i);
					parents.push(p);
					p = p->nodes->at(i);
					break;
				}
			}
		}
	}

	if (p->terminal == 0) {//현재 노드가 내부노드인 경우
		node* tmp = p;
		parents.push(p);
		idxes.push(myi + 1);
		p = p->nodes->at(myi + 1);
		while (p->terminal == 0) {
			idxes.push(0);
			parents.push(p);
			p = p->nodes->front();
		}
		swap(p->keys->front(), tmp->keys->at(myi));//후행키와 교체
		myi = 0;
	}
	else {
		for (int i = 0; i < p->size; i++) {
			if (deleteKey == p->keys->at(i)) {
				myi = i;
				break;
			}
		}
	}
	if (myi==-1 || p->keys->at(myi) != deleteKey) return; //해당하는 값이 없는 경우
	p->keys->erase(p->keys->begin() + myi);
	p->nodes->pop_back();
	p->size--;

	int si = NULL;//형제노드의 인덱스
	int pi = NULL;//현재노드의 인덱스
	node* s = NULL;//형제 노드

	while (p->size < m/2) {//언더플로우 발생
		if (parents.empty()) {//현재노드가 루트노드인 경우
			if (p->size == 0) {
				T = p->nodes->front();
				delete p;//할당된 메모리 해제??
			}
			return;
		}
		q = parents.top();
		parents.pop();
		pi = idxes.top();
		idxes.pop();
		if (pi == 0) {
			si = 1;
		}
		else if (pi == q->size) {
			si = q->size - 1;
		}
		else if (q->nodes->at(pi - 1)->size > q->nodes->at(pi + 1)->size) {
			si = pi - 1;
		}
		else if (q->nodes->at(pi - 1)->size < q->nodes->at(pi + 1)->size) {
			si = pi + 1;
		}
		else return;
		s = q->nodes->at(si);
		if (s->size + p->size + 1 < m) { //합병, 두 노드 중 좌측 노드에 합병
			if (si < pi) {
				s->keys->push_back(q->keys->at(si));
				s->keys->resize(s->size + p->size + 1);
				copy(p->keys->begin(), p->keys->end(), s->keys->begin() + s->size + 1);
				s->nodes->resize(s->size + p->size + 2);
				copy(p->nodes->begin(), p->nodes->end(), s->nodes->begin() + s->size + 1);
				s->size += p->size + 1;
				q->keys->erase(q->keys->begin() + si);
				q->nodes->erase(q->nodes->begin() + pi);
				q->size--;
				delete p;//이렇게 하는거 맞는가
			}
			else {// pi < si
				p->keys->push_back(q->keys->at(pi));
				p->keys->resize(p->size + s->size + 1);
				copy(s->keys->begin(), s->keys->end(), p->keys->begin() + p->size + 1);
				p->nodes->resize(p->size + s->size + 2);
				copy(s->nodes->begin(), s->nodes->end(), p->nodes->begin() + p->size + 1);
				p->size += s->size + 1;
				q->keys->erase(q->keys->begin() + pi);
				q->nodes->erase(q->nodes->begin() + si);
				q->size--;
				delete s;
			}
		}
		else {//재분배
			if (si < pi) {
				p->keys->insert(p->keys->begin(), q->keys->at(si));
				p->nodes->insert(p->nodes->begin(), s->nodes->back());
				p->size++;
				q->keys->at(si) = s->keys->back();
				s->keys->pop_back();
				s->nodes->pop_back();
				s->size--;
			}
			else {//pi < si
				p->keys->push_back(q->keys->at(pi));
				p->nodes->push_back(s->nodes->front());
				p->size++;
				q->keys->at(pi) = s->keys->front();
				s->keys->erase(s->keys->begin());
				s->nodes->erase(s->nodes->begin());
				s->size--;
			}
		}
		
		p = q;
	}

}

void insert(node*& T, int newKey, int m) {
	node* p = T;
	node* q = NULL;
	stack<node*> parents;
	if (T == NULL) {
		node* newNode = getNode();
		newNode->keys->push_back(newKey);
		newNode->nodes->push_back(NULL);
		newNode->nodes->push_back(NULL);
		newNode->size = 1;
		newNode->terminal = 1;
		T = newNode;
		return;
	}
	while (p->terminal==0) {
		if (newKey == p->keys->back()) {
			return;
		}
		else if (newKey > p->keys->back()) {
			parents.push(p);
			p = p->nodes->back();
		}
		else {
			for (int i = 0; i < p->size; i++) {
				if (newKey == p->keys->at(i)) return;
				else if (newKey < p->keys->at(i)) {
					parents.push(p);
					p = p->nodes->at(i);
					break;
				}
			}
		}
	}
	if (newKey == p->keys->at(p->size - 1)) return;
	else if (newKey > p->keys->at(p->size - 1)) {
		p->keys->push_back(newKey);
	}
	else {
		for (int i = 0; i < p->size; i++) {
			if (newKey == p->keys->at(i)) return;
			else if (newKey < p->keys->at(i)) {
				p->keys->insert(p->keys->begin() + i, newKey);
				break;
			}
		}
	}
	p->nodes->push_back(NULL);
	p->size++;
	while (p->size >= m) {//오버플로우 발생
		if (parents.empty()) {
			node* newNode = getNode();
			q = newNode;
			q->nodes->push_back(p);
			q->size = 0;
			q->terminal = 0;
			T = q;
		}
		else {
			q = parents.top();
			parents.pop();
		}
		node* newNode = getNode();
		int mid = p->keys->at(m / 2);
		newNode->keys->assign(p->keys->begin() + m/2 + 1, p->keys->end());
		newNode->nodes->assign(p->nodes->begin() + m/2 + 1, p->nodes->end());
		newNode->terminal = p->terminal;
		newNode->size = (m - 1) / 2;
		if (q->size == 0 || mid > q->keys->back()) {
			q->keys->push_back(mid);
			q->nodes->push_back(newNode);
		}
		else {
			for (int i = 0; i < q->size; i++) {
				if (mid < q->keys->at(i)) {
					q->keys->insert(q->keys->begin() + i, mid);
					q->nodes->insert(q->nodes->begin() + i + 1, newNode);
					break;
				}
			}
		}
		q->size++;
		p->keys->resize(m / 2);
		p->nodes->resize(m / 2 + 1);
		p->size = m / 2;//3원이면 노드당 1개 1개, 4원이면 2개 1개

		p = q;
	}
}

void inorderBT(node* tree) {
	if (tree != NULL) {
		for (int i = 0; i < tree->size; i++) {
			inorderBT(tree->nodes->at(i));
			cout << tree->keys->at(i) << " ";
		}
		inorderBT(tree->nodes->at(tree->size));
	}
}

void inorder(node* tree) {
	inorderBT(tree);
	cout << endl;
}

int main() {
	
	node* tree = NULL;

	insert(tree, 40, 4); inorder(tree);
	insert(tree, 11, 4); inorder(tree);
	insert(tree, 77, 4); inorder(tree);
	insert(tree, 33, 4); inorder(tree);
	insert(tree, 20, 4); inorder(tree);
	insert(tree, 90, 4); inorder(tree);
	insert(tree, 99, 4); inorder(tree);
	insert(tree, 70, 4); inorder(tree);
	insert(tree, 88, 4); inorder(tree);
	insert(tree, 80, 4); inorder(tree);
	insert(tree, 66, 4); inorder(tree);
	insert(tree, 10, 4); inorder(tree);
	insert(tree, 22, 4); inorder(tree);
	insert(tree, 30, 4); inorder(tree);
	insert(tree, 44, 4); inorder(tree);
	insert(tree, 55, 4); inorder(tree);
	insert(tree, 50, 4); inorder(tree);
	insert(tree, 60, 4); inorder(tree);
	insert(tree, 100, 4); inorder(tree);
	insert(tree, 28, 4); inorder(tree);
	insert(tree, 18, 4); inorder(tree);
	insert(tree, 9, 4); inorder(tree);
	insert(tree, 5, 4); inorder(tree);
	insert(tree, 17, 4); inorder(tree);
	insert(tree, 6, 4); inorder(tree);
	insert(tree, 3, 4); inorder(tree);
	insert(tree, 1, 4); inorder(tree);
	insert(tree, 4, 4); inorder(tree);
	insert(tree, 2, 4); inorder(tree);
	insert(tree, 7, 4); inorder(tree);
	insert(tree, 8, 4); inorder(tree);
	insert(tree, 10, 4); inorder(tree);
	insert(tree, 12, 4); inorder(tree);
	insert(tree, 13, 4); inorder(tree);
	insert(tree, 14, 4); inorder(tree);
	insert(tree, 16, 4); inorder(tree);
	insert(tree, 15, 4); inorder(tree);
	insert(tree, 25, 4); inorder(tree);
	insert(tree, 24, 4); inorder(tree);
	insert(tree, 28, 4); inorder(tree);

	deleteBT(tree, 66, 4); inorder(tree);
	deleteBT(tree, 10, 4); inorder(tree);
	deleteBT(tree, 22, 4); inorder(tree);
	deleteBT(tree, 30, 4); inorder(tree);
	deleteBT(tree, 44, 4); inorder(tree);
	deleteBT(tree, 55, 4); inorder(tree);
	deleteBT(tree, 50, 4); inorder(tree);
	deleteBT(tree, 60, 4); inorder(tree);
	deleteBT(tree, 100, 4); inorder(tree);
	deleteBT(tree, 28, 4); inorder(tree);
	deleteBT(tree, 18, 4); inorder(tree);
	deleteBT(tree, 9, 4); inorder(tree);
	deleteBT(tree, 5, 4); inorder(tree);
	deleteBT(tree, 17, 4); inorder(tree);
	deleteBT(tree, 6, 4); inorder(tree);
	deleteBT(tree, 3, 4); inorder(tree);
	deleteBT(tree, 1, 4); inorder(tree);
	deleteBT(tree, 4, 4); inorder(tree);
	deleteBT(tree, 2, 4); inorder(tree);
	deleteBT(tree, 7, 4); inorder(tree);
	deleteBT(tree, 8, 4); inorder(tree);
	deleteBT(tree, 10, 4); inorder(tree);
	deleteBT(tree, 12, 4); inorder(tree);
	deleteBT(tree, 13, 4); inorder(tree);
	deleteBT(tree, 14, 4); inorder(tree);
	deleteBT(tree, 16, 4); inorder(tree);
	deleteBT(tree, 15, 4); inorder(tree);
	deleteBT(tree, 25, 4); inorder(tree);
	deleteBT(tree, 24, 4); inorder(tree);
	deleteBT(tree, 28, 4); inorder(tree);
	deleteBT(tree, 40, 4); inorder(tree);
	deleteBT(tree, 11, 4); inorder(tree);
	deleteBT(tree, 77, 4); inorder(tree);
	deleteBT(tree, 33, 4); inorder(tree);
	deleteBT(tree, 20, 4); inorder(tree);
	deleteBT(tree, 90, 4); inorder(tree);
	deleteBT(tree, 99, 4); inorder(tree);
	deleteBT(tree, 70, 4); inorder(tree);
	deleteBT(tree, 88, 4); inorder(tree);
	deleteBT(tree, 80, 4); inorder(tree);

	return 0;
}

