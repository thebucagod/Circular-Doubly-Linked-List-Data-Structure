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

	while (_head) {
		Node* temp = _head->n_next;
		delete _head;
		_head = temp;
	}

	_tail = nullptr;
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
