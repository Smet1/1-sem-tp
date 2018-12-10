// Задача 1-1

#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

const int BASIC_CAPACITY = 8;
// TODO(): на константы (Done)
// TODO(): в рехэше вызывать функцию горнера (Done)

/////////////////
struct Hash_val {
    std::string val;
    bool deleted = false;
    bool empty = true;

    Hash_val(std::string &val) : val(val), deleted(false), empty(false) {}
    Hash_val() : val(), deleted(false), empty(true) {}
};


void delete_hash_val(Hash_val& in_val) {
    in_val.val.clear();
    in_val.deleted = true;
    in_val.empty = true;
}

size_t hash_key(std::string &str, size_t hash_size) {
    size_t key = 0;
    int a = 97;
    for (char i : str) {
        key = (key * a + i) % hash_size;
    }

    //    key = (key + j * j) % hash_size;

    //    j++;
    return key;
}

/////////////////

class Dynamic_mas {
 public:
    Dynamic_mas() : capacity(0), size(0) {
        array = nullptr;
    }

    explicit Dynamic_mas(size_t cap) : capacity(cap), size(0) {
        array = new Hash_val[cap];
    }

    ~Dynamic_mas() {
        delete[] array;
        capacity = 0;
        size = 0;
    }

    Hash_val& operator[](size_t index);

    void push_back(Hash_val val);  // запихуевание в конец
    Hash_val pop_back();

    void swap(size_t a, size_t b);

    Hash_val back();
    void insert(Hash_val val, size_t position);
    void del(size_t position);

    size_t get_capacity() const;
    size_t get_size() const;

    void print();

 private:
    Hash_val *array;
    size_t capacity;
    size_t size;

    void inc_capacity();  // увеличение капасити
};

void Dynamic_mas::push_back(Hash_val val) {
    if (size == capacity) {
        inc_capacity();
    }

    array[size++] = val;
}

void Dynamic_mas::inc_capacity() {
    size_t new_cap = capacity * 2;

    auto new_arr = new Hash_val[new_cap];
    for (size_t i = 0; i < capacity; i++) {
        if (array[i].val.empty()) {
            continue;
        }
        int i_prob = 0;
        size_t key = 0;

//        int a = 97;
//        for (char j : array[i].val) {
//            key = (key * a + j) % new_cap;
//        }
        key = hash_key(array[i].val, new_cap);

        while (new_cap > i_prob) {
            if (new_arr[key].empty) {
                new_arr[key] = array[i];

                break;
            } else {
                key = (key + i_prob + 1) % new_cap;
//                key = (temp + i_prob * (i_prob + 1) / 2) % new_cap;

//                std::cout << i_prob << " <-- i_prob, key = " << key << std::endl;
                ++i_prob;

            }
        }

    }

    delete[] array;

    array = new_arr;
    capacity = new_cap;
}

void Dynamic_mas::print() {
    if (size == 0) {
        std::cout << "nothing to print, size = 0\n";
        return;
    } else {
        for (size_t i = 0; i < size; i++) {
            std::cout << array[i].val << " ";
        }
        std::cout << std::endl;
    }
}

void Dynamic_mas::swap(size_t a, size_t b) {
    std::swap(array[a], array[b]);
}

Hash_val Dynamic_mas::pop_back() {
    Hash_val tmp = array[size--];
    return tmp;
}
Hash_val& Dynamic_mas::operator[](size_t index) {
    assert(index <= capacity);
    return array[index];
}

size_t Dynamic_mas::get_capacity() const {
    return capacity;
}

size_t Dynamic_mas::get_size() const { return size; }

Hash_val Dynamic_mas::back() {
    assert(size > 0);
    return array[size - 1];
}

void Dynamic_mas::insert(Hash_val val, size_t position) {
//    assert(position <= capacity);

    array[position] = val;
    ++size;

    if (size >= 0.75 * capacity) {
        inc_capacity();
    }

}

void Dynamic_mas::del(size_t position) {
    delete_hash_val(array[position]);
    size--;
}

/////////////////////////////////////////////

class HashTable {
 public:
    HashTable();
    bool add(std::string val);
    bool find(std::string val);
    bool remove(std::string val);
    void print();
    size_t size() { return str_mas.get_size(); }

 private:
    Dynamic_mas str_mas;
};

HashTable::HashTable() : str_mas(BASIC_CAPACITY) { }

bool HashTable::add(std::string val) {
    int i_prob = 0;
    size_t mas_cap = str_mas.get_capacity();
    size_t key = hash_key(val, str_mas.get_capacity());
    size_t temp = key;
//    std::cout << "key[0] = " << key << std::endl;

    if (find(val))
        return false;

    while (mas_cap > i_prob) {
        if (!str_mas[key].deleted && !str_mas[key].empty && str_mas[key].val == val) {
            return false;
        }
        if (str_mas[key].empty) {
            str_mas.insert(
                Hash_val(val),
                key
            );

            return true;
        } else {
//            key = (temp + i_prob * (i_prob + 1) / 2) % str_mas.get_capacity();
            key = (key + i_prob + 1) % str_mas.get_capacity();
//            std::cout << i_prob << " <-- i_prob, val = " << (temp + (i_prob * i_prob)) << ", key = " << key << std::endl;
            i_prob += 1;
        }
    }

    return false;
}

bool HashTable::find(std::string val) {
    int i_prob = 0;
    size_t mas_cap = str_mas.get_capacity();
    size_t key = hash_key(val, str_mas.get_capacity());
    size_t temp = key;
//    std::cout << "key[0] = " << key << std::endl;

    while (mas_cap > i_prob) {
        if (!str_mas[key].deleted && !str_mas[key].empty && str_mas[key].val == val) {
            return true;
        }
        if (str_mas[key].empty && !str_mas[key].deleted) {

            return false;
        } else {
//            key = (temp + i_prob * (i_prob + 1) / 2) % str_mas.get_capacity();
            key = (key + i_prob + 1) % str_mas.get_capacity();
//            std::cout << i_prob << " <-- i_prob, val = " << (temp + (i_prob * i_prob)) << ", key = " << key << std::endl;
            i_prob += 1;
        }
    }

    return false;
}

bool HashTable::remove(std::string val) {
    int i_prob = 0;
    size_t mas_cap = str_mas.get_capacity();
    size_t key = hash_key(val, str_mas.get_capacity());
    size_t temp = key;
//    std::cout << "key[0] = " << key << std::endl;
    if (!find(val))
        return false;

    while (mas_cap > i_prob) {
        if (!str_mas[key].deleted && !str_mas[key].empty && str_mas[key].val == val) {
//            delete_hash_val(str_mas[key]);
            str_mas.del(key);
            return true;
        }
        if (str_mas[key].empty && !str_mas[key].deleted) {

            return false;
        } else {
//            key = (temp + i_prob * (i_prob + 1) / 2) % str_mas.get_capacity();
            key = (key + i_prob + 1) % str_mas.get_capacity();
//            std::cout << i_prob << " <-- i_prob, val = " << (temp + (i_prob * i_prob)) << ", key = " << key << std::endl;
            i_prob += 1;
        }
    }

    return false;
}

void HashTable::print() {
    for (size_t i = 0; i < str_mas.get_capacity(); i++) {
        std::cout << "[" << i << "] |" << str_mas[i].val << "|"
        << ", deleted = " << str_mas[i].deleted << ", empty = " << str_mas[i].empty << std::endl;
    }
}

void hash_interface(HashTable& ht, std::string& val, char& op) {
    switch (op) {
        case '+':
            if (ht.add(val)) {
                std::cout << "OK\n";
            } else {
                std::cout << "FAIL\n";
            }
            return;
        case '?':
            if (ht.find(val)) {
                std::cout << "OK\n";
            } else {
                std::cout << "FAIL\n";
            }
            return;
        case '-':
            if (ht.remove(val)) {
                std::cout << "OK\n";
            } else {
                std::cout << "FAIL\n";
            }
            return;
        default:
            std::cout << "UNKNOWN OPERATION\n";
            return;
    }
}

int main() {
    char operation;
    std::string value;

    HashTable ht;

    while (std::cin >> operation >> value) {
        hash_interface(ht, value, operation);
//        ht.print();
    }

    return 0;
}
