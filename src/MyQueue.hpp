#include <cstddef>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <utility>


template<typename T>
class MyQueue
{
    private:
    struct Node
    {
        T data;
        std::unique_ptr<Node> next;


        Node(const T &value, std::unique_ptr<Node> next_node)
            : data(value), next(std::move(next_node)){}
    };

    std::unique_ptr<Node> front_ptr;
    Node* back_ptr = nullptr;

    size_t m_size = 0;

    public:

    void push_back(const T & value)
    {
        auto new_node = std::make_unique<Node>(value, nullptr);

        if (!front_ptr) {
            front_ptr = std::move(new_node);
            back_ptr = front_ptr.get();
        }
        else {
            back_ptr->next = std::move(new_node);
            back_ptr = back_ptr->next.get();
        }
        m_size++;
    }

    T& get()
    {
        if (!front_ptr) {
            throw std::runtime_error("Empty queue");
        }
        return front_ptr->data;
    }

    void pop()
    {
        if (!front_ptr) {
            throw std::runtime_error("Empty queue");
        }

        front_ptr = std::move(front_ptr->next);

        if (!front_ptr) {
            back_ptr = nullptr;
        }
        
        m_size--;
    }

    size_t size()
    {
        return m_size;
    }
    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const MyQueue<U> &queue);
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const MyQueue<T> &queue) 
{
    auto curr = queue.front_ptr.get();
    while (curr) {
        os << curr->data;
        curr = curr->next.get();
        if (curr) {
            os << " -> ";
        }
    }
    return os;
}
