// Singly Linked List

#include <iostream>
using namespace std;

struct Node {
	int val;
	Node* pNext;
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
		cout << "not enough memory!";
		return NULL;
	}

	newNode->val = val;
	newNode->pNext = NULL;

	return newNode;
}

// Add first element to Linked list
void pushFirstElement(LinkedList& list, int val) {

	Node* newNode = createNode(val);
	list.Head = list.Tail = newNode;
}

// Add element at first position of linked list
void pushHead(LinkedList& list, int val) {

	if (isEmpty(list)) {
		pushFirstElement(list, val);
		return;
	}
	Node* newNode = createNode(val);
	newNode->pNext = list.Head;
	list.Head = newNode;
}

// Add element at last position of linked list
void pushEnd(LinkedList& list, int val) {

	if (isEmpty(list)) {
		pushFirstElement(list, val);
		return;
	}
	Node* newNode = createNode(val);
	list.Tail->pNext = newNode;
	list.Tail = newNode;
}

// Add element after element with value X
void pushWithValue(LinkedList& list, int val, int x) {

	if (isEmpty(list)) {
		pushFirstElement(list, val);
		return;
	}

	Node* temp = list.Head;
	Node* newNode = createNode(val);

	while (temp != NULL) {
		if (temp->val == x) {
			newNode->pNext = temp->pNext;
			temp->pNext = newNode;

			// Check last element of linked list
			if (temp == list.Tail) {
				list.Tail = newNode;
			}
			return;
		}
		temp = temp->pNext;
	}

	cout << "Can't add element!\n";
}

// Add element by position
void pushWithPosition(LinkedList& list, int val, int pos) {

	if (isEmpty(list)) {
		pushFirstElement(list, val);
		return;
	}
	
	// Check first element of linked list
	if (pos == 1) {
		pushHead(list, val);
		return;
	}

	Node* temp = list.Head;

	for (int i = 2; i < pos; i++) {

		if (temp->pNext == NULL) {
			cout << "Can't add element!\n";
			return;
		}
		temp = temp->pNext;
	}

	Node* newNode = createNode(val);

	newNode->pNext = temp->pNext;
	temp->pNext = newNode;

	if (temp == list.Tail) {
		list.Tail = newNode;
	}
}

// Delete first element of linked list
void deleteHead(LinkedList& list) {

	if (isEmpty(list)) {
		cout << "Can't delete element!\n";
		return;
	}

	// Check list has only one element
	if (list.Head == list.Tail) {
		delete list.Head;
		list.Head = list.Tail = NULL;
		return;
	}

	Node* temp = list.Head;
	list.Head = list.Head->pNext;
	delete temp;
	temp = NULL;
}

// Delete last element of linked list
void deleteTail(LinkedList& list) {

	if (isEmpty(list)) {
		cout << "Can't delete element!\n";
		return;
	}

	// Check list has only one element
	if (list.Head == list.Tail) {
		delete list.Head;
		list.Head = list.Tail = NULL;
		return;
	}

	Node* temp = list.Head;

	while (temp->pNext != list.Tail) {
		temp = temp->pNext;
	}

	delete list.Tail;
	list.Tail = NULL;

	list.Tail = temp;
	list.Tail->pNext = NULL;
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

// Delete element with value X (only one element)
void deleteWithValue(LinkedList& list, int x) {

	if (isEmpty(list)) {
		cout << "Can't delete element with value " << x << "!\n";
		return;
	}

	Node* temp = list.Head;

	// Check first element of linbked list
	if (list.Head->val == x) {
		deleteHead(list);
		return;
	}

	while (temp->pNext != NULL) {
		if ((temp->pNext)->val == x) {

			// Check last element of linked list
			if (list.Tail == temp->pNext) {
				deleteTail(list);
				return;
			}

			Node* del = temp->pNext;
			temp->pNext = (temp->pNext)->pNext;
			delete del;

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

	// Check first element of linbked list
	if (pos == 1) {
		deleteHead(list);
		return;
	}

	for (int i = 2; i < pos; i++) {

		temp = temp->pNext;

		if (temp->pNext == NULL) {
			cout << "Can't delete element!\n";
			return;
		}
	}

	// Check last element of linked list
	if (list.Tail == temp->pNext) {
		deleteTail(list);
		return;
	}

	Node* del = temp->pNext;
	temp->pNext = (temp->pNext)->pNext;
	delete del;
}

void reverseList(LinkedList& list) {

	Node* cur = list.Head;
	Node* prev = NULL;
	Node* next = NULL;

	list.Tail = list.Head;

	while (cur != NULL) {
		next = cur->pNext;
		cur->pNext = prev;
		prev = cur;
		cur = next;
	}
	list.Head = prev;
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
