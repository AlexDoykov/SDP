<template typename T>
struct Node
{
	T value;
	Node<T>* prev;
	Node<T>* next;
	Node(T value){
		this.value = value;
		prev = nullptr;
		next = nullptr;
	}
};

<template typename T>
class DoubleLinkedList
{
private:
	Node<T>* first;
	Node<T>* last;

public:

	DoubleLinkedList(){
		first = nullptr;
		last = nullptr;
	}

	DoubleLinkedList(const DoubleLinkedList& other){
		this.first = new Node<T>(other.first->data);
		this.last = new Node<T>(other.last->data);
		Node<T>* crr = first;
		while(crr != this.last){
			this.sta
		}
	}

	void push_back(const T& value){
		
	}

	~DoubleLinkedList();

	/* data */
};