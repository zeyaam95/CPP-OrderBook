#pragma once
#include <iostream>

template <typename anyType>
class Queue {
private:
	template<class anyType>
	struct Node {
		anyType *value;
		Node<anyType> *back = nullptr;
		Node(anyType *val) {
			value = val;
		}
	};
	int size = 0;
	Node<anyType> *front = nullptr;
public:
	Queue() {

	}

	Queue(anyType *val)
	{
		front = Node(val);
	}

	~Queue() {
		if (!front) return;
		Node<anyType> *temp = front, *prevNode = nullptr;
		while (temp) {
			prevNode = temp;
			temp = temp->back;
			delete prevNode;
		}
	}
	void enQueue(anyType *item) {
		if (!front) {
			front = new Node<anyType>(item);
			size++;
			return;
		}
		else if (*item >= *(front->value)) {
			cout << "Added at the front! "<< *item <<endl;
			Node<anyType> *prevNode = new Node<anyType>(item);
			prevNode->back = front;
			front = prevNode;
			size++;
			return;
		}
		else {
			Node<anyType> *temp = front;
			Node<anyType> *prevNode = nullptr;
			while (temp->back != nullptr) {
				prevNode = temp;
				if (*item <= *(temp->value) && *item >= *(temp->back->value)) {
					prevNode = new Node<anyType>(item);
					prevNode->back = temp->back;
					temp->back = prevNode;
					cout << "Node Added! *item <= *(temp->value) && *item >= *(temp->back->value))" << endl;
					size++;
					return;
				}
				cout << "Node Tranversed!"<< endl;
				temp = temp->back;
			}
			if (prevNode == nullptr) {
				temp->back = new Node<anyType>(item);
				cout << "Node Added! prevNode == nullptr" << endl;
				size++;
				return;
			}/**
			prevNode->back = new Node<anyType>(item);
			prevNode = prevNode->back;
			prevNode->back = temp;
			cout << "Node Added!" << endl;*/
			return;
		}
	}

	void deQueue() {
		if (!front) return;
		Node<anyType>* temp = this->front;
		front = front->back;
		free(temp);
	}

	anyType& operator[](const int NUM) {
		Node<anyType> *temp = front;
		while (temp != NULL && NUM != 0) {
			temp = temp->back;
		}
		return *(temp->value);
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Queue<anyType>& q) {
		Node<anyType> *temp = q.front;
		cout << *(temp->back->value);
		while (temp) {
			out << *(temp->value) << endl;
			temp = temp->back;
		}
		return out;
	}

	int length() {
		return this->size;
	}
};
