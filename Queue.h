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
	void enQueueBid(anyType *item) {
		if (!front) {
			front = new Node<anyType>(item);
			size++;
			return;
		}
		else if (*item >= *(front->value)) {
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
					size++;
					return;
				}
				temp = temp->back;
			}
			temp->back = new Node<anyType>(item);
			size++;
			return;
		}
	}

	void enQueueAsk(anyType *item) {
		if (!front) {
			front = new Node<anyType>(item);
			size++;
			return;
		}
		else if (*item <= *(front->value)) {
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
				if (*item >= *(temp->value) && *item <= *(temp->back->value)) {
					prevNode = new Node<anyType>(item);
					prevNode->back = temp->back;
					temp->back = prevNode;
					size++;
					return;
				}
				temp = temp->back;
			}
			temp->back = new Node<anyType>(item);
			size++;
			return;
		}
	}

	void deQueue() {
		if (!this->front) return;
		Node<anyType>* queue = this->front;
		front = front->back;
		free(queue);
		size--;
	}

	anyType& operator[](const int NUM) {
		Node<anyType> *temp = front;
		while (temp != NULL && NUM != 0 && NUM < this->size) {
			temp = temp->back;
		}
		return *(temp->value);
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Queue<anyType>& q) {
		if (!q.front) return out;
		Node<anyType> *temp = q.front;
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
