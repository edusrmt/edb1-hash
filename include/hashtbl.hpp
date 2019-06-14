/**
 * @file
 * @author Eduardo Sarmento <cealvesarmento@gmail.com> & Victor Vieira <victor@agenciaatwork.com>
 * @version 1.0
 * 
 * @section DESCRIPTION
 * 
 * Implementation of a hash table in C++.
 */
#ifndef HASHTBL_H
#define HASHTBL_H

#include <forward_list>
#include <ostream>
#include <functional>
#include <exception>

namespace ac {

    /**
     * @brief HashTable entry structure
     * @author Eduardo Sarmento & Victor Vieira
     * 
     * A simple class that implements a hash table entry structure, with a key k_ and a information d_.
     */
    template<class KeyType, class DataType>
    class HashEntry {
        public:
        /// Default constructor
        HashEntry(KeyType k_, DataType d_) : m_key(k_), m_data(d_) { }

        /// Compares two entries and returns true if are equals and false otherwise.
        bool operator==(const HashEntry &rhs) const {
            return m_data == rhs.m_data;
        }

        KeyType m_key;      //!< Stores the key for an entry.
        DataType m_data;    //!< Stores the data for an entry.
    };

    /**
     * @brief HashTable data structure
     * @author Eduardo Sarmento & Victor Vieira
     * 
     * A simple class that implements a hash table.
     */
    template <typename KeyType, typename DataType, typename KeyHash = std::hash<KeyType>, typename KeyEqual = std::equal_to<KeyType>>
    class HashTbl {
        public:
        using Entry = HashEntry<KeyType, DataType>;     //!< Alias

        /// Default constructor. Creates a empty table.
        HashTbl (size_t tbl_size_ = DEFAULT_SIZE) : m_size{tbl_size_} {
            while (!isPrime(m_size)) m_size++;

            m_data_table = new std::forward_list<Entry>[m_size];
            m_count = 0;
        }

        /// Destructs a table
        ~HashTbl () {            
            for (size_t i = 0; i < m_size; i++) {
                m_data_table[i].clear();                
            }

            delete [] m_data_table;
        }

        /// Constructs a table from another table.
        HashTbl (const HashTbl &other) : m_size {other.m_size} {
            m_data_table = new std::forward_list<Entry>[m_size];
            m_count = 0;
            
            for (size_t addr = 0; addr < m_size; addr++) {
                for (auto it = other.m_data_table[addr].begin(); it != other.m_data_table[addr].end(); it++) {
                    insert(it->m_key, it->m_data);
                }
            }     
        }

        /// Constructs a table from a initializer list
        HashTbl (std::initializer_list<Entry> ilist) {            
            m_size = 0;           
            m_count = 0; 
            while (!isPrime(m_size)) m_size++;

            m_data_table = new std::forward_list<Entry>[m_size];            

            for (size_t i = 0; i < ilist.size(); i++) {                
                insert((ilist.begin() + i)->m_key, (ilist.begin() + i)->m_data);
            }
        }
         
        /// Copy values from another table and replaces in the table.
        HashTbl &operator= (const HashTbl &other) {
            clear();
            m_size = other.m_size;       
            m_data_table = new std::forward_list<Entry>[m_size];
            
            for (size_t addr = 0; addr < m_size; addr++) {
                for (auto it = other.m_data_table[addr].begin(); it != other.m_data_table[addr].end(); it++) {
                    insert(it->m_key, it->m_data);
                }
            }   

            return *this;
        }

        /// Copy values from a std::initializer_list and replaces in the table.
        HashTbl &operator= (std::initializer_list<Entry> ilist) {
            clear();
            m_size = ilist.size();           

            while (!isPrime(m_size)) m_size++;
            
            m_data_table = new std::forward_list<Entry>[m_size];                        

            for (size_t i = 0; i < ilist.size(); i++) {                
                insert((ilist.begin() + i)->m_key, (ilist.begin() + i)->m_data);
            }

            return *this;
        }

        /// Insert in the table the d_ information and associated with the key k_. If the key already exists, the methods overwrite the data with d_ data and returns false. Otherwise, if all goes well, the methods returns true.
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
            
            
            rehash();

            return true;
        }
        
        /// Removes an table item identified by your key k_. If the key is found, the methods returns true, otherwise, returns false.
        bool erase (const KeyType & k_) {
            KeyHash hashFunc;
            KeyEqual equalFunc;
            auto addr(hashFunc(k_) % m_size);

            for (auto it = m_data_table[addr].begin(); it != m_data_table[addr].end(); it++) {
                if (equalFunc( (*it).m_key, k_)) {
                    m_data_table[addr].remove(*it);
                    m_count--;
                    return true;
                }
            }

            return false;
        }

        /// Recover the necessary information in d_ associated with the key k_. If the key is found, the methods returns true, otherwise, returns false.
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

        /// Clears (delete) all related memory to the table's colision lists, removing all of elements.
        void clear () {
            m_count = 0;

            for (size_t addr = 0; addr < m_size; addr++) {
                for (auto it = m_data_table[addr].begin(); it != m_data_table[addr].end(); it++) {
                    m_data_table[addr].remove(*it);
                }
            }   
        }

        /// Returns true if the dispersion table is empty, and false otherwise.
        bool empty () const {
            return m_count == 0;
        }

        /// Returns the size of the table 
        size_t size () const {
            return m_count;
        }
        
        /// Returns a reference to the associated with the key k_. If the key is not in the table, the methods throws a std::out_of_range exception.
        DataType& at (const KeyType& k_) {
            KeyHash hashFunc;
            KeyEqual equalFunc;
            auto addr(hashFunc(k_) % m_size);

            for (auto it = m_data_table[addr].begin(); it != m_data_table[addr].end(); it++) {
                if (equalFunc( it->m_key, k_))
                    return it->m_data;
            }

            throw std::out_of_range("key");
        }

        /// Returns a reference to the data associated with the key k_. If the key is not in the table, the method performs the insert and returns the reference to the newly inserted data.
        DataType& operator[] (const KeyType& k_) {            
            KeyHash hashFunc;
            KeyEqual equalFunc;
            auto addr(hashFunc(k_) % m_size);

            for (auto it = m_data_table[addr].begin(); it != m_data_table[addr].end(); it++) {
                if (equalFunc( it->m_key, k_))
                    return it->m_data;
            }     

            DataType *d_ = new DataType;
            insert (k_, *d_);
            delete d_;

            for (auto it = m_data_table[addr].begin(); it != m_data_table[addr].end(); it++) {
                if (equalFunc( it->m_key, k_))
                    return it->m_data;
            }

            return *d_;
        }

        size_t count (const KeyType& k_) const {
            KeyHash hashFunc;
            auto addr(hashFunc(k_) % m_size);

            size_t counter = 0;
            for (auto it = m_data_table[addr].begin(); it != m_data_table[addr].end(); it++) {
                counter++;
            }
            
            return counter;
        }
        
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

        /// Change Hash table size if load factor λ > 1.0
        void rehash() {
            if (m_count > m_size) {
                size_t old_size = m_size;
                m_size *= 2;
                m_count = 0;
                while (!isPrime(m_size)) m_size++;
                std::forward_list<Entry> *old_data_table = m_data_table;
                m_data_table = new std::forward_list<Entry>[m_size];
                
                for (size_t addr = 0; addr < old_size; addr++) {
                    for (auto it = old_data_table[addr].begin(); it != old_data_table[addr].end(); it++) {
                        insert(it->m_key, it->m_data);
                    }
                }
            }            
        }   

        size_t m_size;                              //!< Hash table size.
        size_t m_count;                             //!< Number of elements currently stored in the table.
        std::forward_list<Entry> *m_data_table;     //!< The table: array of pointers to collision list.
        static const short DEFAULT_SIZE = 11;       //!< Hash table’s default sizE: 11 table entries.     
    };
}

#endif