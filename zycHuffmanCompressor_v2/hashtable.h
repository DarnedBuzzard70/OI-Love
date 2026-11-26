#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cstddef>
#include <string>

class HashTable {
public:
    explicit HashTable(size_t initialBuckets = 1024);

    ~HashTable();

    HashTable(const HashTable &) = delete;

    HashTable &operator=(const HashTable &) = delete;

    // 查找键，返回指向值的指针；不存在返回 nullptr
    unsigned long long *find(const std::string &key);

    // 键不存在则插入并置 0，然后加上 delta（频率统计用）
    void increment(const std::string &key, unsigned long long delta = 1);

    // 设置键值（编码表中存“符号 -> 编码表下标”）
    void set(const std::string &key, unsigned long long value);

    size_t size() const { return count_; }

    // 遍历所有键值对，f(key, value)
    template<typename Func>
    void forEach(Func f) const {
        for (size_t i = 0; i < bucketCount_; ++i) {
            for (Entry *e = buckets_[i]; e != nullptr; e = e->next) {
                f(e->key, e->value);
            }
        }
    }

private:
    struct Entry {
        std::string key;
        unsigned long long value;
        Entry *next;

        Entry(const std::string &k, unsigned long long v, Entry *n)
            : key(k), value(v), next(n) {
        }
    };

    Entry **buckets_;
    size_t bucketCount_;
    size_t count_;

    static size_t hashKey(const std::string &key, size_t bucketCount); // BKDR 哈希
    void rehash(); // 负载因子超过 0.75 时扩容再散列
};

#endif // HASHTABLE_H
