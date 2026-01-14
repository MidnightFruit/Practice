#include <clocale>
#include <iostream>
#include <ostream>
#include "src/MyList.hpp"

int main(int, char**){

    std::setlocale(LC_ALL, "");

    MyList<int> List;
    List.push_front(1);
    List.push_front(2);
    List.push_front(3);
    
    std::cout << "Here's full list: \n";
    
    for (const auto& value : List) {
        std::cout << value << "->";
    }
    std::cout << std::endl;
    std::cout << "List size: " << List.size() << std::endl;
    std::cout << "First in list: " << List.front() << std::endl << "Pop first element in list\n";
    List.pop_front();
    std::cout << "New list size: " << List.size() << std::endl;
    std::cout << "New first in list: " << List.front() << std::endl;
    std::cout << "Incrementing first element\n";
    int& a = List.front();
    a++;
    std::cout << "New first element: " << List.front() << std::endl;


}
