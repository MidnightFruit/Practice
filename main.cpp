#include <iostream>
#include <string>
#include "src/MyList.hpp"


template<typename T>
concept HashibleKey = requires(T t){ t.length(); t[0]; } || std::is_arithmetic_v<T>;


int main(int, char**){

    //std::setlocale(LC_ALL, "");
//
    //MyList<int> List;
    //List.push_front(1);
    //List.push_front(2);
    //List.push_front(3);
    //
    //std::cout << "Here's full list: \n";
    //
    //for (const auto& value : List) {
    //    std::cout << value << "->";
    //}
    //std::cout << std::endl;
    //std::cout << "List size: " << List.size() << std::endl;
    //std::cout << "First in list: " << List.front() << std::endl << "Pop first element in list\n";
    //List.pop_front();
    //std::cout << "New list size: " << List.size() << std::endl;
    //std::cout << "New first in list: " << List.front() << std::endl;
    //std::cout << "Incrementing first element\n";
    //int& a = List.front();
    //a++;
    //std::cout << "New first element: " << List.front() << std::endl;

    //MyQueue<int> a;
//
    //a.push_back(1);
    //a.push_back(2);
    //a.push_back(3);
    //
    //std::cout << a << "\n";
//
    //a.push_back(4);
//
    //std::cout << a << "\n";
//
    //std::cout << a.get() << "\n";
//
    //a.pop();
//
    //std::cout << a << "\n"; 
    std::cout << "main";

    return 0;
}
