#include "CircularList.h"
#include <iostream>
#include <string>

void demonstrate_basic_operations() {
    std::cout << "=== BASIC OPERATIONS DEMO ===" << std::endl;

    CircularList<int> list;

    // Добавление элементов в начало и конец
    std::cout << "Initial empty list: " << list << std::endl;

    list.push_front(1);
    list.push_front(2);
    list.push_back(3);
    list.push_back(4);

    std::cout << "After push_front(1,2) and push_back(3,4): " << list << std::endl;
    std::cout << "Size: " << list.size() << ", Empty: " << std::boolalpha << list.empty() << std::endl;
}

void demonstrate_insertion_operations() {
    std::cout << "\n=== INSERTION OPERATIONS DEMO ===" << std::endl;

    CircularList<std::string> list;

    // Добавляем несколько элементов
    list.push_back("Hello");
    list.push_back("World");
    list.push_front("Start");

    std::cout << "Initial list: " << list << std::endl;

    // Вставка по индексу
    list.push_node("Middle", 2);
    std::cout << "After push_node(\"Middle\", 2): " << list << std::endl;

    // Вставка в начало и конец через push_node
    list.push_node("VeryStart", 0);
    list.push_node("VeryEnd", list.size());
    std::cout << "After push_node to start and end: " << list << std::endl;
}

void demonstrate_deletion_operations() {
    std::cout << "\n=== DELETION OPERATIONS DEMO ===" << std::endl;

    CircularList<int> list;

    // Заполняем список
    for (int i = 1; i <= 5; i++) {
        list.push_back(i);
    }

    std::cout << "Initial list: " << list << std::endl;

    // Удаление из начала
    list.pop_front();
    std::cout << "After pop_front(): " << list << std::endl;

    // Удаление из конца
    list.pop_back();
    std::cout << "After pop_back(): " << list << std::endl;

    // Покажем размер
    std::cout << "Current size: " << list.size() << std::endl;
}

void demonstrate_move_semantics() {
    std::cout << "\n=== MOVE SEMANTICS DEMO ===" << std::endl;

    CircularList<std::string> list1;
    list1.push_back("Move");
    list1.push_back("Semantics");
    list1.push_back("Demo");

    std::cout << "Original list: " << list1 << std::endl;

    // Конструктор перемещения
    CircularList<std::string> list2(std::move(list1));
    std::cout << "After move construction:" << std::endl;
    std::cout << "Source list (should be empty): " << list1 << std::endl;
    std::cout << "Destination list: " << list2 << std::endl;

    // Перемещающие версии push-методов
    std::string temp_str = "TemporaryString";
    list2.push_front(std::move(temp_str));
    std::cout << "After push_front with move, list: " << list2 << std::endl;
    std::cout << "Original string after move: \"" << temp_str << "\"" << std::endl;
}

void demonstrate_copy_semantics() {
    std::cout << "\n=== COPY SEMANTICS DEMO ===" << std::endl;

    CircularList<int> original;
    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    std::cout << "Original list: " << original << std::endl;

    // Конструктор копирования
    CircularList<int> copy(original);
    std::cout << "Copied list: " << copy << std::endl;

    // Изменяем копию и проверяем, что оригинал не изменился
    copy.pop_front();
    std::cout << "After modifying copy:" << std::endl;
    std::cout << "Original: " << original << std::endl;
    std::cout << "Copy: " << copy << std::endl;
}

void demonstrate_error_handling() {
    std::cout << "\n=== ERROR HANDLING DEMO ===" << std::endl;

    CircularList<int> list;
    list.push_back(1);
    list.push_back(2);

    std::cout << "Current list: " << list << std::endl;

    try {
        // Попытка вставить по невалидному индексу
        std::cout << "Attempting to push_node at index 5..." << std::endl;
        list.push_node(99, 5);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    try {
        // Попытка вставить по отрицательному индексу
        std::cout << "Attempting to push_node at index -1..." << std::endl;
        list.push_node(99, -1);
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // Удаление из пустого списка
    CircularList<int> empty_list;
    std::cout << "Attempting to pop from empty list..." << std::endl;
    bool result = empty_list.pop_front();
    std::cout << "pop_front on empty list returned: " << std::boolalpha << result << std::endl;
}

void demonstrate_complex_operations() {
    std::cout << "\n=== COMPLEX OPERATIONS DEMO ===" << std::endl;

    CircularList<CircularList<int>> list_of_lists;

    CircularList<int> inner1;
    inner1.push_back(1);
    inner1.push_back(2);

    CircularList<int> inner2;
    inner2.push_back(3);
    inner2.push_back(4);
    inner2.push_back(5);

    list_of_lists.push_back(inner1);
    list_of_lists.push_back(inner2);

    std::cout << "List of lists: " << list_of_lists << std::endl;
}

int main() {
    std::cout << "CIRCULAR LINKED LIST DEMONSTRATION\n" << std::endl;

    try {
        demonstrate_basic_operations();
        demonstrate_insertion_operations();
        demonstrate_deletion_operations();
        demonstrate_move_semantics();
        demonstrate_copy_semantics();
        demonstrate_error_handling();
        demonstrate_complex_operations();

        std::cout << "\n=== ALL DEMONSTRATIONS COMPLETED SUCCESSFULLY ===" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}