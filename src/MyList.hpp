#include <iostream>
#include <memory>
#include <utility>
//#include <memory>

template<typename T>
class MyList
{
private:
    struct Node
    {
        T data;
        std::unique_ptr<Node> next;
    };
    std::unique_ptr<Node> head; 
public:
    size_t size = 0;
    MyList(T value);
    ~MyList();
    void push_front(const T& value);
};

template <typename T>
inline MyList<T>::MyList(T value)
{
    Node node = {value, nullptr};
    head = std::make_unique<Node>(node);
}

template <typename T>
inline MyList<T>::~MyList()
{
}

template <typename T>
inline void MyList<T>::push_front(const T &value)
{
    auto new_node = std::make_unique<Node>({value, std::move(head)}); 
    head = (new_node);
    size++;
}
