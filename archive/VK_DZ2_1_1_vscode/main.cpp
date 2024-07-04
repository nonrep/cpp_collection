#include <iostream>
#include <string>
#include <vector>

template<class T, class H>
class HashTable {
public:
    HashTable(int initialSize, const H& _hasher);
    bool Add(const T& key);
    bool Has(const T& key);
    bool Delete(const T& key);

private:
    H hasher;
    unsigned int keysCount;
    unsigned int deletedCount;
    enum CellState {Empty, Key, Deleted};
    struct HashTableCell {
        T Key;
        CellState State;
        HashTableCell() : State(Empty) {}
    };
    std::vector<HashTableCell> table;

    // для нахождения индекса элемента в Has и Delete
    int find(const T& key, unsigned int hash);
    // хеширует таблицу заново, когда удаленных элементов больше половины
    void recreateTable();
    void growTable();
};

template<class T, class H>
HashTable<T, H>::HashTable(int initialSize, const H& _hasher) :
    hasher(_hasher),
    table(initialSize),
    keysCount(0),
    deletedCount(0)
{
}

template<class T, class H>
bool HashTable<T, H>::Add(const T& key) {
    if (4 * keysCount > 3 * table.size())
        growTable();
    
    unsigned int hash = hasher(key) % table.size();
    int firstDeleted = -1;
    unsigned int i = 0;
    while (table[hash].State != Empty) {
        if (table[hash].Key == key && table[hash].State == Key)
            return false;

        if (table[hash].State == Deleted) {
            if (table[hash].Key == key) {
                table[hash].State = Key;
                --deletedCount;
                ++keysCount;
                return true;
            }
            if (firstDeleted == -1)
                firstDeleted = hash;
        }
        hash = (hash + (++i)) % table.size();
    }
    if (firstDeleted != -1)
        hash = firstDeleted;

    table[hash].Key = key;
    table[hash].State = Key;
    ++keysCount;
    return true;
}

template<class T, class H>
bool HashTable<T, H>::Has(const T& key) {
    unsigned int hash = hasher(key) % table.size();
    hash = find(key, hash);
    if (hash == -1)
        return false;

    if (table[hash].Key == key && table[hash].State == Key)
        return true;
    
    return false;
}

template<class T, class H>
bool HashTable<T, H>::Delete(const T& key) {
    unsigned int hash = hasher(key) % table.size();
    hash = find(key, hash);
    if (hash == -1)
        return false;

    if (table[hash].Key == key && table[hash].State == Key) {
        table[hash].State = Deleted;
        ++deletedCount;
        --keysCount;
        if (2 * deletedCount > table.size())
            recreateTable();

        return true;
    }

    return false;
}

template<class T, class H>
int HashTable<T, H>::find(const T& key, unsigned int hash) {
    unsigned int i = 0;
    while (table[hash].State != Empty) {
        if (table[hash].Key == key)
            return hash;

        hash = (hash + (++i)) % table.size();
    }   
    return -1;
}

template<class T, class H>
void HashTable<T, H>::recreateTable() {
    deletedCount = 0;
    keysCount = 0;
    std::vector<HashTableCell> oldTable = table;
    table.clear();
    table.resize(oldTable.size());
    for (int i = 0; i < oldTable.size(); i++) {
        if (oldTable[i].State == Key)
            Add(oldTable[i].Key);
    }
}

template<class T, class H>
void HashTable<T, H>::growTable() { 
    deletedCount = 0;
    keysCount = 0;
    std::vector<HashTableCell> oldTable = table;
    table.clear();
    table.resize(2 * oldTable.size());
    for (int i = 0; i < oldTable.size(); i++) {
        if (oldTable[i].State == Key)
            Add(oldTable[i].Key);
    }
}

struct StringHasher {
	unsigned int operator()( const std::string& key ) const {
		unsigned int hash = 0;
		for( unsigned int i = 0; i < key.size(); ++i ) {
			hash = hash * 137 + key[i];
		}
		return hash;
	}
};

int main() {
    StringHasher hasher;
	HashTable<std::string, StringHasher> table(1000, hasher);
	char operation = 0;
	std::string word;
	while(std::cin >> operation >> word) {
		switch(operation) {
			case '+':
				std::cout << (table.Add(word) ? "OK" : "FAIL") << std::endl;
				break;
			case '-':
				std::cout << (table.Delete(word) ? "OK" : "FAIL") << std::endl;
				break;
			case '?':
				std::cout << (table.Has(word) ? "OK" : "FAIL") << std::endl;
				break;
		}
	}
}