#include "MyList.hpp"
#include <cstddef>
#include <memory>
#include <concepts>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <cmath>


template<typename T>
concept HashibleKey = requires(T t){ t.length(); t[0]; } || std::is_integral_v<T> || std::is_same_v<T, const char*>;

template<HashibleKey K, typename V>
class MyHashTable
{
    
    struct KeyValue
    {
        K key;
        V value;
        KeyValue(const K& k, const V& v) : key(k), value(v) {}
    };
    
    std::unique_ptr<MyList<KeyValue>[]> buckets;

    size_t m_size = 0;
    size_t m_capacity = 17;
    const double max_load_factor = 0.66;

    size_t hash(const K& key) const
    {
        size_t hash = 0;
        if constexpr (std::is_integral_v<K>)
        {
            hash = static_cast<size_t>(key) * 2654435761U % m_capacity;
        }
        else if constexpr (std::is_same_v<K, const char*>)
        {
            size_t str_size = std::strlen(key);
            for (size_t i = 0; i < str_size; i++)
            {
                hash = hash * 31 + key[i];
            }
            hash %= m_capacity;
        }
        else
        {
            for (size_t i = 0; i < key.length(); i++)
            {
                hash = hash * 31 + key[i];
            }
            hash %= m_capacity;
        }
        return hash;
    }

    bool is_prime(size_t n);
    
    size_t next_prime(size_t n);

public:

    MyHashTable(size_t init_capaciti = 17);
    
    void put(const K& key, const V& value);
    
    V& get(const K& key);
    
    size_t size() const {return m_size;}
    
    bool empty() const {return m_size == 0;}
    
    double get_load_factor();

    void resize(size_t n);

    bool remove(const K& key);
};


template<HashibleKey K, typename V>
inline double MyHashTable<K, V>::get_load_factor()
{
    return double(m_size) / m_capacity;
}

template <HashibleKey K, typename V>
inline void MyHashTable<K, V>::resize(size_t n)
{
    size_t old_capacity = m_capacity;

    m_capacity = next_prime(n);
    
    m_size = 0;

    auto old_buckets = std::move(buckets);

    buckets = std::make_unique<MyList<KeyValue>[]>(m_capacity);

    for (size_t i = 0; i < old_capacity; i++)
    {
        for (auto& item : old_buckets[i])
        {
            put(item.key, item.value);
        }
    }
    
}

template <HashibleKey K, typename V>
inline bool MyHashTable<K, V>::remove(const K &key)
{
    try
    {
        size_t hash_key = hash(key);

        KeyValue to_remove(key, get(key));
        
        if (buckets[hash_key].remove(to_remove))
        {
            m_size--;
            return true;
        }
    }
    catch(const std::out_of_range)
    {
        return false;
    }

    return false;
}

template <HashibleKey K, typename V>
inline bool MyHashTable<K, V>::is_prime(size_t n)
{
    if (n <= 1 or n % 2 == 0)
    {
        return false;
    }
    if (n==2)
    {
        return true;
    }
    for (size_t i = 3; i <= sqrt(n); i+=2)
    {
        if (n % i == 0)
        {
            return false;
        }
        
    }
    
    return true;
}

template <HashibleKey K, typename V>
inline size_t MyHashTable<K, V>::next_prime(size_t n)
{
    if (n <= 2)
    {
        return 2;
    }
    if (n % 2 == 0)
    {
        n++;
    }
    
    while (!is_prime(n))
    {
        n+=2;
    }
    
    return n;
}

template <HashibleKey K, typename V>
inline MyHashTable<K, V>::MyHashTable(size_t init_capaciti)
{
    m_capacity = init_capaciti;
    buckets = std::make_unique<MyList<KeyValue>[]>(m_capacity);
}

template <HashibleKey K, typename V>
inline void MyHashTable<K, V>::put(const K &key, const V &value)
{
    size_t hash_index = hash(key);

    if(buckets[hash_index].empty())
    {
        KeyValue new_value(key, value);

        buckets[hash_index].push_front(new_value);

        m_size++;
    }
    else
    {

        for (auto& item : buckets[hash_index]) {
            if (item.key == key)
            {
                item.value = value;

                return;
            }
        }
        
        KeyValue new_value(key, value);

        buckets[hash_index].push_front(new_value);

        m_size++;

    }
    if (get_load_factor() > max_load_factor)
    {
        resize(m_capacity * 2);
    }
    
}

template <HashibleKey K, typename V>
inline V &MyHashTable<K, V>::get(const K &key)
{
    size_t hash_key = hash(key);
    for (auto& item : buckets[hash_key])
    {
        if (item.key == key)
        {
            return item.value;
        }
    }
    
    throw std::out_of_range("Key not found");
}
