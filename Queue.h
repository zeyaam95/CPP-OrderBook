#pragma once

template <typename anyType>
class Queue
{
private:
	struct Node{
		anyType* value = nullptr;
		Node* back = nullptr;
		Node(anyType& val) {
			this->value = val;
		}
	};
	Node* front = nullptr;
public:
	Queue() {

	}
	Queue(anyType val)
	{
		front = Node(val);
	}
	~Queue() {
		if (!front) return;
		Node *temp = front, *prevNode = nullptr;
		while (temp) {
			prevNode = temp;
			temp = temp->back;
			delete prevNode;
		}
	}
	void enQueue(anyType&);
	void deQueue(anyType&);
};