#ifndef MINHEAP_H
#define MINHEAP_H

#include <cstddef>

struct HuffNode; // 前向声明，定义见 huffman.h

class MinHeap {
public:
    explicit MinHeap(size_t initialCapacity = 16);
    ~MinHeap();

    MinHeap(const MinHeap&) = delete;
    MinHeap& operator=(const MinHeap&) = delete;

    void push(HuffNode* node);      // 插入节点，上浮调整
    HuffNode* pop();                // 弹出权值最小的节点，下沉调整
    HuffNode* top() const;          // 查看堆顶
    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }

private:
    HuffNode** data_;               // 动态数组存储堆元素（完全二叉树的顺序存储）
    size_t size_;
    size_t capacity_;

    static bool less(HuffNode* a, HuffNode* b); // 比较规则：权值小者优先，权值相同按符号字典序（保证结果确定）
    void siftUp(size_t idx);        // 上浮
    void siftDown(size_t idx);      // 下沉
    void grow();                    // 扩容
};

#endif // MINHEAP_H