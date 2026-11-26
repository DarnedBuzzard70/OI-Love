#include "hashtable.h"

HashTable::HashTable(size_t initialBuckets)
    : bucketCount_(initialBuckets ? initialBuckets : 1024), count_(0) {
    buckets_ = new Entry *[bucketCount_];
    for (size_t i = 0; i < bucketCount_; ++i) buckets_[i] = nullptr;
}

HashTable::~HashTable() {
    for (size_t i = 0; i < bucketCount_; ++i) {
        Entry *e = buckets_[i];
        while (e != nullptr) {
            Entry *next = e->next;
            delete e;
            e = next;
        }
    }
    delete[] buckets_;
}

// BKDR 哈希：对字节（含 0x80 以上的高位字节）也能均匀散列
size_t HashTable::hashKey(const std::string &key, size_t bucketCount) {
    unsigned long long seed = 131; // 31 131 1313 13131 ...
    unsigned long long hash = 0;
    for (unsigned char c: key) {
        hash = hash * seed + c;
    }
    return static_cast<size_t>(hash % bucketCount);
}

void HashTable::rehash() {
    size_t newCount = bucketCount_ * 2;
    Entry **newBuckets = new Entry *[newCount];
    for (size_t i = 0; i < newCount; ++i) newBuckets[i] = nullptr;
    for (size_t i = 0; i < bucketCount_; ++i) {
        Entry *e = buckets_[i];
        while (e != nullptr) {
            Entry *next = e->next;
            size_t idx = hashKey(e->key, newCount);
            e->next = newBuckets[idx];
            newBuckets[idx] = e;
            e = next;
        }
    }
    delete[] buckets_;
    buckets_ = newBuckets;
    bucketCount_ = newCount;
}

unsigned long long *HashTable::find(const std::string &key) {
    size_t idx = hashKey(key, bucketCount_);
    for (Entry *e = buckets_[idx]; e != nullptr; e = e->next) {
        if (e->key == key) return &e->value;
    }
    return nullptr;
}

void HashTable::increment(const std::string &key, unsigned long long delta) {
    size_t idx = hashKey(key, bucketCount_);
    for (Entry *e = buckets_[idx]; e != nullptr; e = e->next) {
        if (e->key == key) {
            e->value += delta;
            return;
        }
    }
    buckets_[idx] = new Entry(key, delta, buckets_[idx]);
    ++count_;
    if (count_ * 4 > bucketCount_ * 3) rehash(); // 负载因子 > 0.75 扩容
}

void HashTable::set(const std::string &key, unsigned long long value) {
    size_t idx = hashKey(key, bucketCount_);
    for (Entry *e = buckets_[idx]; e != nullptr; e = e->next) {
        if (e->key == key) {
            e->value = value;
            return;
        }
    }
    buckets_[idx] = new Entry(key, value, buckets_[idx]);
    ++count_;
    if (count_ * 4 > bucketCount_ * 3) rehash();
}
