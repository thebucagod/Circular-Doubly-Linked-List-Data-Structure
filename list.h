#pragma once

#include <iostream>
#include <string>

// ��������������� ���������� ���������� ������
template<class type>
class list;

// ��������������� ���������� ���������� ���������
template<class type>
std::ostream& operator<<(std::ostream& os, const list<type>& obj);

template<class type>
class list {
public:
	list();
	list(const list<type>& other);
	list(list<type>&& other) noexcept;
	~list();

	friend std::ostream& operator<< <type>(std::ostream& os, const list<type>& obj);

	// �������� ����
	bool push_front(const type& data);
	bool push_front(type&& data) noexcept;
	bool push_back(const type& data);
	bool push_back(type&& data) noexcept;
	bool push_node(const type& data, int index);

	// ������� ����
	bool pop_front();
	bool pop_back();
	bool pop_node(int index);

	// ������ ����
	type front();
	type back();
	type get_node(int index);

	// ��������������� ������
	bool empty() const;
	int size() const;

private:
	struct Node {
		type n_data;
		Node* n_next;
		Node* n_prev;

		template<class U>
		Node(U&& data) noexcept
			: n_data(std::forward<U>(data)),
			  n_next(nullptr),
			  n_prev(nullptr) {};
	};

	Node* _head;
	Node* _tail;
	int _length;
};

// �����������
template<class type>
list<type>::list()
	: _length(0), _head(nullptr), _tail(nullptr) {}

// ����������� �����������
template<class type>
inline list<type>::list(const list<type> &other)
	: _length(0), _head(nullptr), _tail(nullptr) {
	
	if (other.empty()) return;

	Node* current_other = other._head;

	_head = new Node(other._head->n_data);
	_tail = _head;
	_length = 1;

	current_other = current_other->n_next;

	while (current_other != other._head) {
		Node* new_node = new Node(current_other->n_data);
		new_node->n_prev = _tail;
		_tail->n_next = new_node;

		_tail = new_node;

		current_other = current_other->n_next;
		++_length;
	}

	_head->n_prev = _tail;
	_tail->n_next = _head;
}

// ���������� �����������
template<class type>
inline list<type>::list(list<type>&& other) noexcept
	: _length(other._length), _head(other._head), _tail(other._tail) {	
	other._length = 0;
	other._head = nullptr;
	other._tail = nullptr;
}

// ����������
template<class type>
list<type>::~list() {
	if (empty()) return;

	// ��������� ����
	_tail->n_next = nullptr;
	_head->n_prev = nullptr;

	while (_head) {
		Node* temp = _head->n_next;
		delete _head;
		_head = temp;
	}

	_tail = nullptr;
}

// ����� ����� ���� � ������
template<class type>
bool list<type>::push_front(const type& data) {
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

// ����� ����� ���� � ������ � ���������� �����������
template<class type>
inline bool list<type>::push_front(type&& data) noexcept {
	Node* new_node = new Node(std::move(data));

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

// ����� ����� ���� � �����
template<class type>
bool list<type>::push_back(const type& data) {
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
		_tail = new_node;
	}

	_length++;
	return true;
}

// ����� ����� ���� � ����� � ���������� �����������
template<class type>
inline bool list<type>::push_back(type&& data) noexcept {
	Node* new_node = new Node(std::move(data));

	if (empty()) {
		_head = _tail = new_node;
		new_node->n_next = new_node;
		new_node->n_prev = new_node;
	} else {
		new_node->n_next = _head;
		new_node->n_prev = _tail;
		_head->n_prev = new_node;
		_tail->n_next = new_node;
		_tail = new_node;
	}

	_length++;
	return true;
}

template<class type>
inline bool list<type>::push_node(const type& data, int index) {
	if (index > _length || index < 0) {
		throw std::out_of_range("Index" + std::to_string(index) + 
								" is out of range [0, " + 
								std::to_string(_length) + "]";
	}

	// ������� ������
	if (index == 0) return push_front(data);
	if (index == _length)	return push_back(data);

	// �������� ������ ����
	Node* new_node = new Node(data);
	Node* temp = _head;

	// ������� ���� � �������� (index-1)
	for (int i = 0; i < index - 1; i++) {
		temp = temp->n_next;
	}
	// ������� ����
	new_node->n_next = temp->n_next;
	new_node->n_prev = temp;
	temp->n_next->n_prev = new_node;
	temp->n_next = new_node;

	++_length;
	return true;
}

// ������� ���� � ������
template<class type>
bool list<type>::pop_front() {
	if (empty()) return false;

	if (_length == 1) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
		_length = 0;

		return true;
	}

	Node* temp = _head;
	_head = _head->n_next;
	_tail->n_next = _head;
	_head->n_prev = _tail;
	--_length;

	delete temp;
	temp = nullptr;

	return true;
}

// ������� ���� � �����
template<class type>
bool list<type>::pop_back() {
	if (empty()) return false;

	if (_length == 1) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
		_length = 0;

		return true;
	}

	Node* temp = _tail;
	_tail = _tail->n_prev;
	_tail->n_next = _head;
	_head->n_prev = _tail;
	--_length;

	delete temp;
	temp = nullptr;

	return true;
}

// �������� �� ������ ������
template<class type>
bool list<type>::empty() const {
	return _head == nullptr;
}

// ����� ��������� �������
template<class type>
int list<type>::size() const {
	return _length;
}

// ���������� ��������� ������ ������
template<class type>
std::ostream& operator<<(std::ostream& os, const list<type>& obj) {
	if (obj.empty()) {
		os << "[]";
		return os;
	}

	typename list<type>::Node* current = obj._head;
	os << "[";
	for (int i = 0; i < obj._length; i++) {
		os << current->n_data;
		if (i < obj._length - 1) {
			os << ", ";
		}
		current = current->n_next;
	}
	os << "]";
	return os;
}