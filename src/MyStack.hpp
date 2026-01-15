#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>


template<typename T>
class MyStack
{
private:
        struct Node
    {
        T data;
        std::unique_ptr<Node> next;
        Node(const T& value, std::unique_ptr<Node> next_node = nullptr) : data(value), next(std::move(next_node)){}
    };
    size_t m_size = 0;
    std::unique_ptr<Node> head;
public:
    
    size_t size() const;

    bool empty() const;

    void pop();

    void push(const T& value);

    const T& top() const;

    T& top();

    MyStack();
    ~MyStack();
};

template <typename T>
inline size_t MyStack<T>::size() const
{
    return m_size;
}

template <typename T>
inline bool MyStack<T>::empty() const
{
    return m_size==0;
}

template <typename T>
inline void MyStack<T>::pop()
{
    if (!head) {
        throw std::runtime_error("Stack is empty!");
    }
    head = std::move(head->next);
    m_size--;
}

template <typename T>
inline void MyStack<T>::push(const T& value)
{
    head = std::make_unique<Node>(value, std::move(head));
    m_size++;
}

template <typename T>
inline T &MyStack<T>::top() 
{
    if (!head) {
        throw std::runtime_error("Stack is empty!");
    }
    return head->data;
}

template <typename T>
inline const T &MyStack<T>::top() const 
{
    if (!head) {
        throw std::runtime_error("Stack is empty!");
    }
    return head->data;
}


template <typename T>
MyStack<T>::MyStack()
{

}

template <typename T>
MyStack<T>::~MyStack()
{
}
