#include <cstddef>
#include <memory>


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
    std::unique_ptr<T> head;
public:
    
    size_t size() const;

    bool empty() const;

    void pop();

    void push(const T& value);

    T& top() const;

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
}

template <typename T>
inline void MyStack<T>::push(const T& value)
{
}

template <typename T>
inline T &MyStack<T>::top() const
{

}

template <typename T>
MyStack<T>::MyStack()
{
}

template <typename T>
MyStack<T>::~MyStack()
{
}
