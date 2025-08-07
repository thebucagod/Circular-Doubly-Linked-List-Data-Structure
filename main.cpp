#include <iostream>

#include "list.h"

int main() {
	list<int> ml;

	ml.push_front(321);
	ml.push_front(41234);
	ml.push_front(1234);
	ml.push_front(123);
	ml.push_front(0);
	ml.push_front(1);

	ml.pop_front();
	ml.pop_back();

	std::cout << ml;

	return 0;
}