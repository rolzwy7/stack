// DoublyLinkedList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct DoublyLinkedList {
	DoublyLinkedList *next;
	DoublyLinkedList *prev;
	int val;
};

void addElement(DoublyLinkedList* &head, DoublyLinkedList* &tail, int val) {
	head = new DoublyLinkedList{head, nullptr, val};
	// Set tail at the end
	if (tail == nullptr)
		tail = head;
	// Set prev for last added element
	if (head->next != nullptr)
		head->next->prev = head;
}

void printElementsHead(DoublyLinkedList* head) {
	while (head) {
		printf("%d, ", head->val);
		head = head->next;
	}
}

void printElementsTail(DoublyLinkedList* tail) {
	while (tail) {
		printf("%d, ", tail->val);
		tail = tail->prev;
	}
}

void deleteDoublyLinkedList(DoublyLinkedList* &head, DoublyLinkedList* &tail) {
	DoublyLinkedList* tmp;
	while (head) {
		tmp = head;
		head = head->next;
		delete tmp;
	}
	head = tail = nullptr;
}

int main(int argc, char* argv[]) {
    return 0;
}



