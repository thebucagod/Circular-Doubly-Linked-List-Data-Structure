#pragma once
template<class type>
class list {
public:
	list();
	~list();

	// Добавить узел
	bool push_front(type data);
	bool push_back(type data);
	bool push_node();

	// Удалить узел
	bool pop_front();
	bool pop_back();
	bool pop_node();

	// Геттер узла
	type front();
	type back();
	type get_node();

	bool empty();

private:
	struct Node {
		type n_data;
		Node* n_next;
		Node* n_prev;

		Node(type data)
			: n_data(data), n_next(nullptr), n_prev(nullptr) {};
	};

	Node* _head;
	Node* _tail;
	int _length;
};