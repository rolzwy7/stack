#include "stdafx.h"

struct LinkedList {
	LinkedList* next;
	int val;
};

void addElement(LinkedList* &head, int val) {
	head = new LinkedList{head, val};
}

void printElements(LinkedList* head) {
	while (head) {
		printf("%d, ", head->val);
		head = head->next;
	}
}

unsigned int getSize(LinkedList* head) {
	unsigned int ret = 0;
	while (head) {
		++ret;
		head = head->next;
	}
	return ret;
}

void deleteLinkedList(LinkedList* &head) {
	LinkedList* tmp;
	while (head) {
		tmp = head;
		head = head->next;
		delete tmp;
	}
}

bool deleteSingleElement(LinkedList* &head, int val) {
	LinkedList* tmp, *restore = head;

	// Delete if first element == val
	if (head->val == val) {
		tmp = head;
		head = head->next;
		delete tmp;
		head = restore;
		return true;
	}
	
	while (head) {
		tmp = head;
		head = head->next;
		if (head->val == val) {
			head = head->next;
			delete tmp->next;
			tmp->next = head;
			head = restore;
			return true;
		}
	}
	head = restore;
	return false;
}

LinkedList* getElement(LinkedList* head, int search) {
	while (head) {
		if (head->val == search)
			return head;
		head = head->next;
	}
	return nullptr;
}

int main(int argc, char* argv[]) {
    return 0;
}

