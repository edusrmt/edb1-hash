#ifndef HASHTBL_H
#define HASHTBL_H

#include <forward_list>
#include <ostream>

template<class KeyType, class DataType>
class HashEntry {
    public:
    /// Default constructor
    HashEntry(KeyType k_, DataType d_) : m_key(k_), m_data(d_) { }

    KeyType m_key;      //!< Stores the key for an entry.
    DataType m_data;    //!< Stores the data for an entry.
};

template <typename KeyType, typename DataType>
class HashTbl {
    public:
    using Entry = HashEntry<KeyType, DataType>;     //!< Alias
    HashTbl (size_t tbl_size_ = DEFAULT_SIZE);
    virtual ~HashTbl ();
    HashTbl (const HashTbl &);
    HashTbl (std::initializer_list<Entry> ilist);
    HashTbl &operator= (const HashTbl &);
    HashTbl &operator= (std::initializer_list<Entry> ilist);
    bool insert (const KeyType & k_, const DataType & d_) const;
    bool erase (const KeyType & k_);
    bool retrieve (const KeyType & k_, DataType & d_) const;
    void clear ();
    bool empty () const;
    size_t size () const;
    DataType& at (const KeyType&);
    DataType& operator[] (const KeyType& k_);
    size_t count (const KeyType& k_) const;
    friend std::ostream& operator<< (std::ostream &, const HashTbl&);

    private:
    void rehash();                              //!< Change Hash table size if load factor λ > 1.0
    unsigned int m_size;                        //!< Hash table size.
    unsigned int m_count;                       //!< Number of elements currently stored in the table.
    std::forward_list<Entry> *m_data_table;     //!< The table: array of pointers to collision list.
    static const short DEFAULT_SIZE = 11;       //!< Hash table’s default sizE: 11 table entries.     
};

#endif