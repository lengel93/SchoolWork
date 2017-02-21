/*************************************************************************//**
* @file
*
* @mainpage Program 2 - Hash Class
*
* @section course_section Course Information
*
* @author Matt Achen, Lyndon Engel
*
* @date 3-30-2016
*
* @par Professor:
*         Hinker
*
* @par Course:
*         CSC 300
*
* @par Location:
*         McLaury - Room 306
*
* @section program_section Program Information
*
* @details Using this hash.h file, one should be able to use our implementation
*       of the hash class in their own program.
*
* @section compile_section Compiling and Usage
*
* @par Compiling Instructions:
*      No special instructions
*
* @par Usage:
@verbatim

@endverbatim
*
* @section todo_bugs_modification_section Todo, Bugs, and Modifications
*
* @bug When running our visualization on linux, screen goes to black instantly after last redisplay
*
* @todo none
*
* @par Modifications and Development Timeline:
@verbatim
Date           Modification
-------------  -------------------------------------------------------------
March 24        Began project, built class
March 25        Began visual implementation, continued building funcions
March 27        Began "final" round of debugging, found lots of bugs
March 28        Project date extended, spent on other classes
March 29        Continued debugging, fixed lots of bugs, found more
March 30        Debugged to its hopefull conclusion
@endverbatim
*
*****************************************************************************/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cmath>
#include <typeinfo>
#include <sstream>
using namespace std;


#ifndef __HASH_H_
#define __HASH_H_
typedef unsigned int uint32_t;
enum status { Filled, Empty, Deleted };/*!< Holds bucket info */

struct xy {
    int x;
    int y;
};

/*!
* @brief Holds functions for HashTable
*/
template<typename K, typename V>
class Hash
{
public:
    int maxFreq;
    K maxKey;
    Hash();                   /*!< Default constructor */
    Hash(int init_size);     /*!< Default constructor with size */
    ~Hash();		/*!< Deconstructor */

    int fillvalue = 0; /*!< How full the Hashtable is */

    uint32_t MurmurHash2(const void * key, int len);/*!< Hash Function */
    V& operator[](const K& key);               /*!< overloaded operator */
    V& insert(const K& key, V& value);         /*!< insert function */
    V find(const K& key);                      /*!< find function */
    int hf(const K& key);                      /*!< helps hash function */
    int size();                                /*!< returns table size */
    double loadFactor();                       /*!< percentage filled */
    int hashCodeGenerated(int hashCode);       /*!< frequency of hashcode */
    int* bucketProbed();                       /*!< Buckets Probed */
    void remove(const K& key);                 /*!< removes bucket form HT */
    void rehash();                             /*!< Rehash */

private:
    /*!
    * @brief Holds bucket values
    */
    struct HashNode {
        V value; /*!< value */
        K key;  /*!< key */
        int probed;/*!< number of times probed */
        int tgen; /*!< number of times generated */
        enum status info;/*!< status of bucket */
    };
    /*!
    * @brief Holds hashtable info
    */
    struct HashTable {
        int size; /*!< size of table */
        HashNode *table; /*!< pointer to nodes */
    };

    bool isprime(int n);
    int nextprime(int n);

    HashTable *htable;
};
/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Returns true if the number is prime, false if the number is not prime
*
* @param[in]      n     - number
* @returns        true  - if prime
* @returns        false - if not prime
*****************************************************************************/
template<typename K, typename V>
bool Hash<K, V>::isprime(int n)
{
    int i;
    double max;
    max = sqrt(n) + 1;

    for (i = 2; i < max; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Finds the next prime from the inserted integer.
*
* @param[in]      n       - number
* @returns        n       - returns next prime
*****************************************************************************/
template<typename K, typename V>
int Hash<K, V>::nextprime(int n)
{
    if (n <= 0) {
        n = 3;
    }

    if (n % 2 == 0) {
        n++;
    }

    while (!isprime(n)) {
        n += 2;
    }

    return n;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Overloads the [] operators to return the value at a given position in the
* hash table.
*
* @param[in]      key     - takes in the key
* @returns        index   - returns the index
*****************************************************************************/
template<typename K, typename V>
V& Hash<K,V>::operator[](const K& key)
{
    uint32_t index = 0;
    int i = 0;
    //same as find
    for (i = 0; i < size(); i++) {
        index = hf(key);

        index = (index + i * i) % size();

        if (htable->table[index].info == Filled && htable->table[index].key == key) {
            return htable->table[index].value;
        }
    }

    return htable->table[index].value;
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Class constructor, creates the first hash table.
*
*****************************************************************************/
template<typename K, typename V>
Hash<K, V>::Hash()
{
    htable = new HashTable; //creates new hash table

    htable->size = 11; //sets table size

    htable->table = new HashNode[htable->size]; //creates the buckets in the hashtable

    for (int i = 0; i < htable->size; i++) { //sets initial values in the table
        htable->table[i].key = K();
        htable->table[i].value = V();
        htable->table[i].info = Empty;
        htable->table[i].probed = 0;
        htable->table[i].tgen = 0;
    }
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Contructs a new hashtable with a given size.
*
* @param[in]      init_size     - size user wants hashtable
*****************************************************************************/
template<typename K, typename V>
Hash<K, V>::Hash(int init_size)
{
    htable = new HashTable; //creates new hash table

    htable->size = init_size; //sets table size

    htable->table = new HashNode[init_size]; //creates the buckets in the hashtable

    for (int i = 0; i < init_size; i++) { //sets initial values in the table
        htable->table[i].key = K();
        htable->table[i].value = V();
        htable->table[i].info = Empty;
        htable->table[i].probed = 0;
        htable->table[i].tgen = 0;
    }
}

/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Deconstructor
*
*****************************************************************************/
template<typename K, typename V>
Hash<K, V>::~Hash()
{
    delete[] htable;
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function generates a hashcode based on a key. If the key is an int
* it gets turned into a string and then is run through are hash function.
*
* @param[in]      key     - takes in the key
* @returns        index   - returns the index
*****************************************************************************/
template<typename K, typename V>
int Hash<K, V>::hf(const K& key)
{
    stringstream ss;
    string key2;

    if(typeid(K).name() == typeid(int).name()) {
        ss << key;
        key2 = ss.str();
        return MurmurHash2(key2.c_str(), key2.size());
    }

    key2 = key;

    return MurmurHash2(key2.c_str(), key2.size());
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function takes in the key and the value. It then checks the load factor
* to make sure the table isn't too full. If the table is too full then it runs
* the rehash function. After that it generates the index and then inputs the key
* into the table using quadratic hashing. Once the value is inserted the function
* returns the value.
*
* @param[in]      key               - reads in the key
* @param[in]      value	            - value
* @returns        value             - value
*****************************************************************************/
template<typename K, typename V>
V& Hash<K, V>::insert(const K& key, V& value)
{
    uint32_t index = 0;
    int i = 0;


    if (loadFactor() >= .75) { //checks load factor
        cout<<"loadFactor "<<loadFactor() * 100<<"% rehashing..."<<endl;
        rehash();
        cout<<"New size is: "<<size()<<endl<<endl;
    }

    for (i = 0;; i++) {
        index = hf(key);
        index = (index + i * i) % size();

        if(htable->table[index].value == value) {
            htable->table[index].probed += 1;
            htable->table[index].tgen += 1;
            return value;
        }

        else if (htable->table[index].info != Filled) {
            htable->table[index].value = value;
            htable->table[index].key = key;
            htable->table[index].probed += 1;
            htable->table[index].tgen += 1;
            htable->table[index].info = Filled;
            fillvalue += 1;

            return value;
        }

        htable->table[index].probed += 1;
        htable->table[index].tgen += 1;
    }

    return value;
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Returns the size of the hash table.
*
* @returns        size  - size of table
*****************************************************************************/
template<typename K, typename V>
int Hash<K, V>::size()
{
    int size;

    size = htable->size;

    return size;
}


/**************************************************************************//**
* @author Austin Appleby
*
* @par Description:
* Uses black magic to create an index.
*
* @param[in]      key               - reads in the key
* @param[in]      len	            - length of string
* @returns        index             - index
*****************************************************************************/
template <typename K, typename V>
uint32_t Hash<K, V>::MurmurHash2(const void * key, int len)
{
    // 'm' and 'r' are mixing constants generated offline.
    // They're not really 'magic', they just happen to work well.

    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    // Initialize the hash to a 'random' value

    uint32_t h = 11^ len;

    // Mix 4 bytes at a time into the hash

    const unsigned char * data = (const unsigned char *)key;

    while (len >= 4) {
        uint32_t k = *(uint32_t*)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    // Handle the last few bytes of the input array

    switch (len) {
    case 3:
        h ^= data[2] << 16;
    case 2:
        h ^= data[1] << 8;
    case 1:
        h ^= data[0];
        h *= m;
    };

    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This function rehashes the table making it bigger. It first creates a new
* temp node and then copies your current nodes into it. After which it resizes
* your main table and then fills it with default data. It then goes through the
* temp table creating new indexes for the keys and inserting them into the new
* table. After its done it frees the temp table.
*
*****************************************************************************/
template<typename K, typename V>
void Hash<K, V>::rehash()
{
    int i = 0;
    int size = 0, newsize = 0; //old table size, new table size
    fillvalue = 0; //sets fill value back to 0

    size = htable->size; //gets old table size
    newsize = nextprime(size * 2); //calculates new table size

    HashNode *temp = htable->table; //creates temp table

    htable->table = new HashNode[newsize]; //allocates new table size
    htable->size = newsize;

    for (int i = 0; i < newsize; i++) { //fills new table with default info
        htable->table[i].key = K();
        htable->table[i].value = V();
        htable->table[i].info = Empty;
        htable->table[i].probed = 0;
        htable->table[i].tgen = 0;
    }

    //runs through the temp table inserting everything into new table
    for (i = 0; i < size; i++) {
        if (temp[i].info == Filled) {
            insert(temp[i].key, temp[i].value);
        }
    }
    delete[] temp; //deletes temp table
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* This calculates how full the hash table is and returns it as a percentage.
*
* @returns        fillpercent  - what percent of the table is filled
*****************************************************************************/
template<typename K, typename V>
double Hash<K, V>::loadFactor()
{
    int size;
    double fillpercent = 0;

    size = htable->size;

    //takes total number of items in the table and divides it by table size
    fillpercent = (double)fillvalue / (double)size;

    return fillpercent;
}


/**************************************************************************//**
* @author Ian Beamer
*
* @par Description:
* Checks a given place in the hashtable to see how many times that hashcode was
* created.
*
* @param[in]      hashCode          - reads in the hashCode
* @returns        count             - number of times hash code was generated
*****************************************************************************/
template<typename K, typename V>
int Hash<K, V>::hashCodeGenerated(int hashCode)
{
    int count = 0;


    count = htable->table[hashCode].tgen;

    return count;
}


/**************************************************************************//**
* @author Lyndon Engel,Matt Achen
*
* @par Description:
* Creates a pointer to an array and fills it with how many times each bucket
* in the hashtable was probed. After its done filling the array it returns a
* pointer to it.
*
* @returns        probe             - number of times hash code was generated
*****************************************************************************/
template<typename K, typename V>
int* Hash<K, V>::bucketProbed()
{
    int *probe = new(nothrow) int[size()];
    maxFreq = 0;
    for(int i = 0; i < size(); i++) {
        probe[i] = htable->table[i].probed;
        if (probe[i] > maxFreq) {
            maxFreq = htable->table[i].probed;
            maxKey = htable->table[i].key;
        }

    }

    return probe;
}

/**************************************************************************//**
* @author Lyndon Engel, Ian Breamer
*
* @par Description:
* Quadratically traverses through the hashtable looking for the given key.
* Once the key is found the function returns the value.
*
* @param[in]      key               - reads in the key
* @returns        value             - value
*****************************************************************************/
template<typename K, typename V>
V Hash<K, V>::find(const K& key)
{
    uint32_t index = 0;
    int i = 0;

    // Quadratically probes through the hashtable
    for (i = 0; i < size(); i++) {
        index = hf(key);

        index = (index + i * i) % size();
        //checks if the bucket is filled and the keys equal
        if (htable->table[index].info == Filled && htable->table[index].key == key) {
            return htable->table[index].value;
        }
    }

    return htable->table[index].value;
}


/**************************************************************************//**
* @author Lyndon Engel
*
* @par Description:
* Quadratically traverses through the hashtable looking for the given key.
* Once the key is found the function marks the bucket as deleted.
*
* @param[in]      key               - reads in the key
*****************************************************************************/
template<typename K, typename V>
void Hash<K, V>::remove(const K& key)
{
    uint32_t index = 0;
    int i = 0;
    //same as find except deletes the bucket once found
    for (i = 0; i < size(); i++) {
        index = hf(key);

        index = (index + i * i) % size();

        if (htable->table[index].info == Filled && htable->table[index].key == key) {
            htable->table[index].info = Deleted;
            fillvalue -= 1;
            return;
        }
    }
    return;
}
#endif