#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

template<typename T>
class MyList
{
private:
    struct Node
    {
        T data;
        std::unique_ptr<Node> next;
        Node(const T& value, std::unique_ptr<Node> next_node = nullptr) : data(value), next(std::move(next_node)){}
    };

    
    std::unique_ptr<Node> head; 
    size_t m_size = 0;

    class MyListIterator
    {
        Node* current;
        
    public:
        explicit MyListIterator(Node* node) : current(node) {}

        T& operator*() const
        {
            if (current) 
            {
                return current->data;
            }
            else 
            {
                throw std::runtime_error("List node is empty");
            }
        }  

        T* operator->() const
        {
            if (!current) 
            {
                throw std::runtime_error("List node is empty");
            }
            return & (current->data);
        }

        MyListIterator& operator++()
        {
            if (current) {
                current = current->next.get();
            }
            return *this;
        }

        bool operator!=(const MyListIterator& other) const
        {
            return other.current != this->current;
        }

        bool operator==(const MyListIterator& other) const
        {
            return other.current == this->current;
        }

    };

public:
    explicit MyList(T value);
    MyList() : head(nullptr){};

    ~MyList();

    void push_front(const T& value);

    bool empty() const;

    size_t size() const;

    void pop_front();

    T& front();

    const T& front() const;

    void clear();
    
    MyListIterator begin() const 
    {
        return MyListIterator(head.get());
    }

    MyListIterator end() const
    {
        return MyListIterator(nullptr);
    }

};

template <typename T>
inline MyList<T>::MyList(T value)
{
    Node node = {value, nullptr};
    head = std::move(std::make_unique<Node>(node));
}

template <typename T>
inline MyList<T>::~MyList(){}

template <typename T>
inline void MyList<T>::push_front(const T &value)
{
    auto new_node = std::make_unique<Node>(value, std::move(head)); 
    head = std::move(new_node);
    m_size++;
}

template <typename T>
inline bool MyList<T>::empty() const
{
    return m_size == 0;
}

template<typename T>
inline size_t MyList<T>::size() const
{
    return m_size;
}

template<typename T>
inline void MyList<T>::pop_front()
{
    if (head) 
    {
        auto new_head = std::move(head->next);

    head = std::move(new_head);

    m_size--;
    }    
}

template<typename T>
inline T& MyList<T>::front()
{
    if (!head) 
    {
        throw std::runtime_error("Empty List");
    }
    return head->data;
}

template<typename T>
inline const T& MyList<T>::front() const
{
    if (!head) 
    {
        throw std::runtime_error("Empty List");
    }
    return head->data;
}

template<typename T>
inline void MyList<T>::clear()
{
    head.reset();
    m_size = 0;
}

