#include <iostream>

#pragma once
struct Coordinate {
public:
	int x;
	int y;

	Coordinate() {
		this->x = 0;
		this->y = 0;
	}

	Coordinate(int x, int y) {
		this->x = x;
		this->y = y;
	}

};

template <typename T>
struct DoubleLinkedNode {
public:
	T data;
	DoubleLinkedNode* next;
	DoubleLinkedNode* previous;

	DoubleLinkedNode(T data) {
		this->data = data;
		this->next = nullptr;
		this->previous = nullptr;
	}
};

template <class N>
class Node {
public:
	N data;
	Node* next;
	Node* previous;
	Node(N data) : data{ data } {}
};

template<class N>
class Queue {
public:
	Node<N>* front;
	Node<N>* back;
	int size;

	Queue() {
		front = nullptr;
		back = nullptr;
		size = 0;
	}
	Queue(Node<N>& node) {
		front = &node;
		back = &node;
		size = 1;
	}

	void enqueue(Node<N>& node) {
		if (isEmpty()) {
			front = &node;
			back = &node;
			size = 1;
			return;
		}
		back->next = &node;
		back = &node;
		size++;
	}

	Node<N>* dequeue() {
		Node<N>* temp = front;
		front = front->next;
		temp->next = nullptr;
		size--;
		return temp;
	}

	Node<N>* getFront() {
		return front;
	}

	Node<N>* getBack() {
		return back;
	}

	bool isEmpty() {
		return size == 0;
	}

	void popN(int n) {
		if (n > size) {
			n = size;
		}
		for (int i = 0; i < n; i++) {
			(dequeue())->~Node();
		}
	}

	int getSize() {
		return size;
	}

	void print() {
		if (isEmpty()) {
			std::cout << std::endl;
			return;
		}
		Node<N>* temp = front;
		do {
			std::cout << temp->data << ",";
			temp = temp->next;
		} while (temp != nullptr);
		std::cout << std::endl;
	}
};