#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

void maxHeapForParent(vector<int> *heap_ptr, int idx) {
	int
		heap_size		= heap_ptr->size() - 1,
		parent_idx		= idx,
		parent_val		= heap_ptr->at(parent_idx),
		left_child_idx	= 2 * parent_idx + 1,
		left_child_val	= (!(left_child_idx > heap_size)) ? heap_ptr->at(left_child_idx) : 0,
		right_child_idx = 2 * parent_idx + 2,
		right_child_val = !(right_child_idx > heap_size) ? heap_ptr->at(right_child_idx) : 0;	
	// Left child
	if (!(left_child_idx > heap_size) && (parent_val < left_child_val)) {
		swap(heap_ptr->at(parent_idx), heap_ptr->at(left_child_idx));
		swap(parent_val, left_child_val);
		maxHeapForParent(heap_ptr, left_child_idx);
	}
	// Right child
	if (!(right_child_idx > heap_size) && (parent_val < right_child_val)) {
		swap(heap_ptr->at(parent_idx), heap_ptr->at(right_child_idx));
		swap(parent_val, right_child_val);
		maxHeapForParent(heap_ptr, right_child_idx);
	}
}

void createMaxHeap(vector<int> *heap_ptr) {
	for (int i = ((heap_ptr->size() - 1) - 1) / 2; i >= 0; i--)
		maxHeapForParent(heap_ptr, i);
}

bool isMaxHeap(vector<int> *heap_ptr) {
	int
		left_child_idx,
		right_child_idx,
		heap_size = heap_ptr->size() - 1;
	bool
		left_child_exists,
		right_child_exists;
	for (int i = 0; i < heap_size+1; i++) {
		left_child_idx = 2 * i + 1;
		right_child_idx = 2 * i + 2;
		left_child_exists  =  (!(left_child_idx > heap_size)) ? true : false;
		right_child_exists = (!(right_child_idx > heap_size)) ? true : false;

		if (left_child_exists) {
			if(heap_ptr->at(i) < heap_ptr->at(left_child_idx))return false;}
		if (right_child_exists) {
			if(heap_ptr->at(i) < heap_ptr->at(right_child_idx))return false;}
	}
	return true;
}

void heapify(vector<int> *heap_ptr, int* tab, int tab_size) {
	for (int i = 0; i < tab_size; i++)
		heap_ptr->push_back(tab[i]);
	createMaxHeap(heap_ptr);
}

int main(int argc, char* argv[]) {
	vector<int> heap;
	vector<int> *heap_ptr = &heap;
	int
		tab[] = { 4, 10, 9, 5, 7, 4, 14},
		*tab_ptr = tab,
		tab_size = sizeof(tab)/sizeof(*tab);

	for (int e : *heap_ptr)
		cout << e << ", ";
	cout << endl;

	heapify(heap_ptr, tab_ptr, tab_size);

	for (int e : *heap_ptr)
		cout << e << ", ";
	cout << endl;

	if (isMaxHeap(heap_ptr))
		cout << "[+] Is max heap\n";
	else
		cout << "[-] Isn't max heap\n";

    return 0;
}

