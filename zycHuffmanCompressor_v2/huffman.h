#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include <vector>
#include <utility>

// 哈夫曼树节点：叶子节点存放符号（一个字节或一个 GBK 字符），内部节点符号为空
struct HuffNode {
    std::string symbol; // 叶子节点：符号；内部节点：""
    unsigned long long weight; // 权值（频率）
    HuffNode *left; // 左子树，编码 0
    HuffNode *right; // 右子树，编码 1

    HuffNode(const std::string &s, unsigned long long w,
             HuffNode *l = nullptr, HuffNode *r = nullptr)
        : symbol(s), weight(w), left(l), right(r) {
    }

    bool isLeaf() const { return left == nullptr && right == nullptr; }
};

// 编码表条目：符号 + 01 编码（用结构体一维数组存放编码表）
struct CodeEntry {
    std::string symbol;
    std::string code;
};

// 频率对：符号 + 频率
typedef std::pair<std::string, unsigned long long> FreqPair;

// 根据频率表构建哈夫曼树（内部使用手写最小堆选取两个最小权值节点）
// 频率表为空返回 nullptr；只有一个符号时根即叶子，编码规定为 "0"
HuffNode *buildHuffmanTree(const std::vector<FreqPair> &freqs);

// 由哈夫曼树生成编码表：左子树编 0，右子树编 1
void generateCodes(HuffNode *root, std::vector<CodeEntry> &table);

// 解压缩时根据编码表重建一棵等价的哈夫曼树
HuffNode *rebuildTree(const std::vector<CodeEntry> &table);

// 释放整棵树的节点内存（后序遍历）
void freeTree(HuffNode *root);

#endif // HUFFMAN_H
