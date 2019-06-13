#ifndef HASHTBL_H
#define HASHTBL_H

#include <forward_list>
#include <ostream>
#include <functional>

namespace ac {

    template<class KeyType, class DataType>
    class HashEntry {
        public:
        /// Default constructor
        HashEntry(KeyType k_, DataType d_) : m_key(k_), m_data(d_) { }

        KeyType m_key;      //!< Stores the key for an entry.
        DataType m_data;    //!< Stores the data for an entry.
    };

    template <typename KeyType, typename DataType, typename KeyHash = std::hash<KeyType>, typename KeyEqual = std::equal_to<KeyType>>
    class HashTbl {
        public:
        using Entry = HashEntry<KeyType, DataType>;     //!< Alias

        HashTbl (size_t tbl_size_ = DEFAULT_SIZE) : m_size{tbl_size_} {
            while (!isPrime(m_size)) m_size++;

            m_data_table = new std::forward_list<Entry>[m_size];
            m_count = 0;
        }

        ~HashTbl () {

        }

        HashTbl (const HashTbl &);
        HashTbl (std::initializer_list<Entry> ilist);
        HashTbl &operator= (const HashTbl &);
        HashTbl &operator= (std::initializer_list<Entry> ilist);

        bool insert (const KeyType & k_, const DataType & d_) {
            KeyHash hashFunc;
            KeyEqual equalFunc;
            Entry newEntry(k_, d_);            

            auto addr(hashFunc(k_) % m_size);  
            for (auto it = m_data_table[addr].begin(); it != m_data_table[addr].end(); it++) {
                if (equalFunc( (*it).m_key, newEntry.m_key)) {
                    *it = newEntry;
                    return false;
                }
            }
            
            m_count++;
            m_data_table[addr].push_front(newEntry);
            return true;
        }

        bool erase (const KeyType & k_);

        bool retrieve (const KeyType & k_, DataType & d_) const {
            KeyHash hashFunc;
            KeyEqual equalFunc;
            auto addr(hashFunc(k_) % m_size);

            for (auto it = m_data_table[addr].begin(); it != m_data_table[addr].end(); it++) {
                if (equalFunc( (*it).m_key, k_)) {
                    d_ = (*it).m_data;
                    return true;
                }
            }

            return false;
        }

        void clear ();

        bool empty () const {
            return m_count == 0;
        }

        size_t size () const {
            return m_count;
        }

        DataType& at (const KeyType&);

        DataType& operator[] (const KeyType& k_) {
            KeyHash hashFunc;
            KeyEqual equalFunc;
            auto addr(hashFunc(k_) % m_size);

            for (auto it = m_data_table[addr].begin(); it != m_data_table[addr].end(); it++) {
                if (equalFunc( it->m_key, k_))
                    return it->m_data;
            }     

            DataType *d_ = new DataType;                  

            insert(k_, *d_);            
            return *d_;
        }

        size_t count (const KeyType& k_) const;
        //friend std::ostream& operator<< (std::ostream &, const HashTbl&);

        private:
        bool isPrime (size_t n) {
            if (n <= 1) 
                return false; 

            for (size_t i = 2; i < n; i++) 
                if (n % i == 0) 
                    return false; 
        
            return true; 
        }

        void rehash();                              //!< Change Hash table size if load factor λ > 1.0
        size_t m_size;                        //!< Hash table size.
        size_t m_count;                       //!< Number of elements currently stored in the table.
        std::forward_list<Entry> *m_data_table;     //!< The table: array of pointers to collision list.
        static const short DEFAULT_SIZE = 11;       //!< Hash table’s default sizE: 11 table entries.     
    };
}

#endif