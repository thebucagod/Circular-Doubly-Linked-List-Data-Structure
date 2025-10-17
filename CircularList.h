#pragma once

#include <iostream>
#include <string>

// ��������������� ���������� ���������� ������
template<class type>
class CircularList;

// ��������������� ���������� ���������� ���������
template<class type>
std::ostream& operator<<(std::ostream& os, const CircularList<type>& obj);

template<class type>
class CircularList {
public:
	CircularList();
	CircularList(const CircularList<type>& other);
	CircularList(CircularList<type>&& other) noexcept;
	~CircularList();

	friend std::ostream& operator<< <type>(std::ostream& os, const CircularList<type>& obj);

	// �������� ����
	void push_front(const type& data);
	void push_front(type&& data) noexcept;
	void push_back(const type& data);
	void push_back(type&& data) noexcept;
	void push_node(const type& data, int index);
	void push_node(type&& data, int index);

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


/*
	������������ � �����������
*/

// �����������
template<class type>
CircularList<type>::CircularList()
	: _length(0), _head(nullptr), _tail(nullptr) {}

// ����������� �����������
template<class type>
inline CircularList<type>::CircularList(const CircularList<type> &other)
	: _length(0), _head(nullptr), _tail(nullptr) {
	
	if (this == &other) return;
	if (other.empty()) return;

	try {
		Node* current_other = other._head;
		do {
			push_back(current_other->n_data);
			current_other = current_other->n_next;
		} while (current_other != other._head);
	} catch (...) {
		while (!empty()) {
			pop_front();
		}
		throw;
	}
}

// ���������� �����������
template<class type>
inline CircularList<type>::CircularList(CircularList<type>&& other) noexcept
	: _length(other._length), _head(other._head), _tail(other._tail) {	
	other._length = 0;
	other._head = nullptr;
	other._tail = nullptr;
}

// ����������
template<class type>
CircularList<type>::~CircularList() {
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


/*
	������� ����� � ������
	������� �� ��������� � � ���������� �����������
	���������� void
	������ ������ � ����� �� �������
*/

// ����� ����� ���� � ������
template<class type>
void CircularList<type>::push_front(const type& data) {

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
}

// ����� ����� ���� � ������ � ���������� �����������
template<class type>
void CircularList<type>::push_front(type&& data) noexcept {
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
}

// ����� ����� ���� � �����
template<class type>
void CircularList<type>::push_back(const type& data) {
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
}

// ����� ����� ���� � ����� � ���������� �����������
template<class type>
void CircularList<type>::push_back(type&& data) noexcept {
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
}

// ����� ����� ���� � �������� ������
template<class type>
void CircularList<type>::push_node(const type& data, int index) {
	if (index > _length || index < 0) {
		throw std::out_of_range("Index" + std::to_string(index) + 
								" is out of range [0, " + 
								std::to_string(_length) + "]");
	}

	// ������� ������
	if (index == 0) return push_front(data);
	if (index == _length) return push_back(data);

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
}

// ����� ����� ���� � �������� ������ � ���������� �����������
template<class type>
void CircularList<type>::push_node(type&& data, int index) {
	if (index > _length || index < 0) {
		throw std::out_of_range("Index" + std::to_string(index) +
			" is out of range [0, " +
			std::to_string(_length) + "]");
	}

	// ������� ������
	if (index == 0) return push_front(std::move(data));
	if (index == _length) return push_back(std::move(data));

	// �������� ������ ����
	Node* new_node = new Node(std::move(data));
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
}


/*
	�������� ����� � ������
	�������� �� ��������� � � ���������� �����������
	���������� bool
	�� ������ ������, ����� ������� 0
*/

// ������� ���� � ������
template<class type>
bool CircularList<type>::pop_front() {
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
bool CircularList<type>::pop_back() {
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


/*
	������ ��������� �����
*/

//....


/*
	��������������� ������
*/

// �������� �� ������ ������
template<class type>
inline bool CircularList<type>::empty() const {
	return _head == nullptr;
}

// ����� ��������� �������
template<class type>
inline int CircularList<type>::size() const {
	return _length;
}


/* 
	���������� ����������
*/

// ���������� ��������� ������ ������
template<class type>
std::ostream& operator<<(std::ostream& os, const CircularList<type>& obj) {
	if (obj.empty()) {
		os << "[]";
		return os;
	}

	typename CircularList<type>::Node* current = obj._head;
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