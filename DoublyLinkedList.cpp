// Doubly Linked List

#include <iostream>
using namespace std;

struct Node {
	int val;
	Node* pNext;
	Node* pPrev;
};

struct LinkedList {
	Node* Head;
	Node* Tail;
};

// Initialize linked list
void initList(LinkedList& list) {

	list.Head = list.Tail = NULL;
}

// Check linked list is empty
bool isEmpty(LinkedList list) {

	if (list.Head == NULL && list.Tail == NULL) {
		return true;
	}
	return false;
}

Node* createNode(int val) {

	Node* newNode = new Node;

	if (newNode == NULL) {
		cout << "Not enough memory!";
		return NULL;
	}

	newNode->val = val;
	newNode->pNext = newNode->pPrev = NULL;

	return newNode;
}

// Add the first element to Linked list
void pushFirstElement(LinkedList& list, int val) {

	Node* newNode = createNode(val);
	list.Head = list.Tail = newNode;
}

// Add element at the first position of linked list
void pushHead(LinkedList& list, int val) {

	if (isEmpty(list)) {
		pushFirstElement(list, val);
		return;
	}
	Node* newNode = createNode(val);
	newNode->pNext = list.Head;
	list.Head->pPrev = newNode;
	list.Head = newNode;
}

// Add element at the last position of linked list
void pushEnd(LinkedList& list, int val) {

	if (isEmpty(list)) {
		pushFirstElement(list, val);
		return;
	}

	Node* newNode = createNode(val);
	list.Tail->pNext = newNode;
	newNode->pPrev = list.Tail;
	list.Tail = newNode;
}

// Add element by position
void pushWithPosition(LinkedList& list, int val, int pos) {

	if (isEmpty(list)) {
		pushFirstElement(list, val);
		return;
	}

	Node* temp = list.Head;

	for (int i = 1; i < pos; i++) {

		if (temp == NULL) {
			cout << "Can't add element!\n";
			return;
		}
		temp = temp->pNext;
	}

	Node* newNode = createNode(val);

	// Check first element of linked list
	if (temp == list.Head) {
		newNode->pNext = list.Head;
		list.Head->pPrev = newNode;
		list.Head = newNode;
		return;
	}

	// Check last element of linked list
	if (temp == NULL) {
		list.Tail->pNext = newNode;
		newNode->pPrev = list.Tail;
		list.Tail = newNode;
		return;
	}

	newNode->pNext = temp;
	newNode->pPrev = temp->pPrev;

	(temp->pPrev)->pNext = newNode;
	temp->pPrev = newNode;
}

// Delete linked list
void deleteList(LinkedList& list) {

	Node* temp = NULL;

	while (list.Head != NULL) {
		temp = list.Head;
		list.Head = list.Head->pNext;
		delete(temp);
	}

	list.Head = list.Tail = NULL;
}

void deleteNode(LinkedList& list, Node* node) {

	// Check list has only one element
	if (list.Head == list.Tail) {
		delete list.Head;
		list.Head = list.Tail = NULL;
		return;
	}

	// Check last element of linked list
	if (list.Tail == node) {
		list.Tail = list.Tail->pPrev;
		list.Tail->pNext = NULL;
		delete node;
		return;
	}

	// Check first element of linked list
	if (list.Head == node) {
		list.Head = list.Head->pNext;
		list.Head->pPrev = NULL;
		delete node;
		return;
	}

	(node->pPrev)->pNext = node->pNext;
	delete node;
}

// Delete element with value X (only one element)
void deleteWithValue(LinkedList& list, int x) {

	if (isEmpty(list)) {
		cout << "Can't delete element with value " << x << "!\n";
		return;
	}
	Node* temp = list.Head;

	while (temp != NULL) {
		if (temp->val == x) {
			deleteNode(list, temp);
			return;
		}
		temp = temp->pNext;
	}
	cout << "Can't delete element with value " << x << "!\n";
}

// Delete element by position
void deleteWithPosition(LinkedList& list, int pos) {

	if (isEmpty(list)) {
		cout << "Can't delete element!\n";
		return;
	}
	Node* temp = list.Head;

	for (int i = 1; i < pos; i++) {

		if (temp->pNext == NULL) {
			cout << "Can't delete element!\n";
			return;
		}
		temp = temp->pNext;
	}

	deleteNode(list, temp);
}

void deleteHead(LinkedList& list) {

	deleteNode(list, list.Head);
}

void deleteTail(LinkedList& list) {

	deleteNode(list, list.Tail);
}

void reverseList(LinkedList& list) {

	for (Node* temp = list.Head; temp != NULL; temp = temp->pPrev) {
		swap(temp->pNext, temp->pPrev);
	}
	swap(list.Head, list.Tail);
}

// Print linked list
void display(LinkedList list) {

	for (Node* temp = list.Head; temp != NULL; temp = temp->pNext) {
		cout << temp->val << ' ';
	}
	cout << '\n';
}

int main() {

	LinkedList list;
	initList(list);

	pushEnd(list, 1);
	pushEnd(list, 2);
	pushEnd(list, 3);
	pushEnd(list, 4);
	pushEnd(list, 5);
	pushEnd(list, 6);
	pushEnd(list, 7);
	pushEnd(list, 8);
	pushEnd(list, 9);
	pushEnd(list, 10);

	display(list);

	reverseList(list);

	display(list);

	return 0;
}
