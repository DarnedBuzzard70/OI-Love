#include "minheap.h"
#include "huffman.h"
#include <stdexcept>
#include <utility>

MinHeap::MinHeap(size_t initialCapacity)
    : size_(0), capacity_(initialCapacity ? initialCapacity : 16) {
    data_ = new HuffNode*[capacity_];
}

MinHeap::~MinHeap() {
    delete[] data_; // 只释放堆数组本身，节点内存由hfm树负责释放
}

// 权值小者优先；权值相同时按符号字典序，保证同一输入构建出的树是确定的
bool MinHeap::less(HuffNode* a, HuffNode* b) {
    if (a->weight != b->weight) return a->weight < b->weight;
    return a->symbol < b->symbol;
}

//tmd，老子怎么知道要多少个节点
void MinHeap::grow() {
    size_t newCap = capacity_ * 2;
    HuffNode** newData = new HuffNode*[newCap];
    for (size_t i = 0; i < size_; ++i) newData[i] = data_[i];
    delete[] data_;
    data_ = newData;
    capacity_ = newCap;
}

void MinHeap::siftUp(size_t idx) {
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        if (less(data_[idx], data_[parent])) {
            std::swap(data_[idx], data_[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

void MinHeap::siftDown(size_t idx) {
    while (true) {
        size_t left = idx * 2 + 1, right = idx * 2 + 2, smallest = idx;
        if (left < size_ && less(data_[left], data_[smallest])) smallest = left;
        if (right < size_ && less(data_[right], data_[smallest])) smallest = right;
        if (smallest == idx) break;
        std::swap(data_[idx], data_[smallest]);
        idx = smallest;
    }
}

void MinHeap::push(HuffNode* node) {
    if (size_ == capacity_) grow();
    data_[size_] = node;
    siftUp(size_);
    ++size_;
}

//我tm求求我自己了，别老丢元素。
HuffNode* MinHeap::pop() {
    if (size_ == 0) throw std::runtime_error("最小堆为空，无法弹出");
    HuffNode* result = data_[0];
    --size_;
    if (size_ > 0) {
        data_[0] = data_[size_];
        siftDown(0);
    }
    return result;
}

HuffNode* MinHeap::top() const {
    if (size_ == 0) throw std::runtime_error("最小堆为空，无法取堆顶");
    return data_[0];
}