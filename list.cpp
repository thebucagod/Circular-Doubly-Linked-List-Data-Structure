#include "list.h"

// Конструктор
template<class type>
list<type>::list()
	: _length(0), _head(nullptr), _tail(nullptr) {}

// Деструктор
template<class type>
list<type>::~list() {
	if (empty()) return;

	_tail->n_next = nullptr;
	_head->n_prev = nullptr;

	while (_head) {
		Node* temp = _head->n_next;
		delete _head;
		_head = temp;
	}

	_tail = nullptr;
}

// Пушим новый узел в начало
template<class type>
bool list<type>::push_front(type data) {
	Node* new_node = new Node(data);

	if (empty()) {
		_head = _tail = new_node;
		new_node->n_next = new_node;  
		new_node->n_prev = new_node; 
	} else {
		new_node->n_next = _head;
		new_node->n_prev = _tail;
		_head->n_prev = new_node;
		_tail->n_next = new_node;
		_head = new_node;
	}
		
	_length++;
    return true;
}

// Проверка на пустой список
template<class type>
bool list<type>::empty() const {
	return _head == nullptr;
}

// Метод получения размера
template<class type>
int list<type>::size() const {
	return _length;
}
