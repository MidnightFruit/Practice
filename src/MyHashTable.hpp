#include "MyList.hpp"
#include <cstddef>
#include <memory>
#include <concepts>
#include <stdexcept>
#include <type_traits>
#include <utility>


template<typename T>
concept HashibleKey = requires(T t){ t.length(); t[0]; } || std::is_arithmetic_v<T>;

template<HashibleKey K, typename V>
class MyHashTable
{
    struct KeyValue
    {
        K key;
        V value;
        KeyValue(const K& k, const V& v) : key(k), value(v) {}
    };
    
    std::unique_ptr<MyList<KeyValue>[]> bucket;

    size_t m_size = 0;
    size_t m_capacity = 16;
    const double max_load_factor = 0.66;
    double load_factor = 0;

    size_t hash(const K& key) const
    {

    }

public:

    MyHashTable(size_t init_capaciti = 16);
    void put(const K&, const V& value);
    V& get(const K& key);
    size_t size() const {return m_size;}
    bool empty() const {return m_size == 0;}
    double get_load_factor();
};

template<typename K, typename V>
inline double MyHashTable<K, V>::get_load_factor()
{
    return double(m_size) / m_capacity;
}

template<typename K, typename V>
inline MyHashTable<K, V>::MyHashTable(size_t init_capaciti)
{
    m_capacity = init_capaciti;
    bucket = std::make_unique<MyList<KeyValue>[]>(m_capacity);
}

