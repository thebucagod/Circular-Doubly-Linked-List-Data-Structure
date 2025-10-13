#include <iostream>

#include "CircularList.h"

int main() {
	CircularList<int> ml;

	ml.push_front(321);
	ml.push_front(41234);
	ml.push_front(1234);
	ml.push_front(123);
	ml.push_front(0); 
	ml.push_front(1);

	CircularList<int> mk(std::move(ml));

	ml.pop_front();
	ml.pop_back();



	std::cout << ml << std::endl;
	std::cout << mk << std::endl;

	return 0;
}