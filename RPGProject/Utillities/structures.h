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