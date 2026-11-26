//
// Created by 25845 on 2026/11/26.
//

#include "huffman.h"
#include "minheap.h"
#include <stdexcept>

HuffNode *buildHuffmanTree(const std::vector<FreqPair> &freqs) {
    if (freqs.empty()) return nullptr;

    // 1. 每个符号生成一个叶子节点，全部放入手写最小堆
    MinHeap heap(freqs.size() * 2 + 1);
    for (const FreqPair &fp: freqs) {
        heap.push(new HuffNode(fp.first, fp.second));
    }

    // 2. 反复合并两个权值最小的节点，直到只剩根节点
    while (heap.size() > 1) {
        HuffNode *a = heap.pop(); // 最小 -> 左子树（编 0）
        HuffNode *b = heap.pop(); // 次小 -> 右子树（编 1）
        HuffNode *parent = new HuffNode("", a->weight + b->weight, a, b);
        heap.push(parent);
    }
    return heap.pop();
}

// 递归遍历生成编码：向左追加 '0'，向右追加 '1'
static void generateCodesImpl(HuffNode *node, const std::string &prefix,
                              std::vector<CodeEntry> &table) {
    if (node == nullptr) return;
    if (node->isLeaf()) {
        // 特例：整份文件只有一种符号时，根即叶子，规定编码为 "0"
        table.push_back({node->symbol, prefix.empty() ? "0" : prefix});
        return;
    }
    generateCodesImpl(node->left, prefix + "0", table);
    generateCodesImpl(node->right, prefix + "1", table);
}

void generateCodes(HuffNode *root, std::vector<CodeEntry> &table) {
    table.clear();
    generateCodesImpl(root, "", table);
}

HuffNode *rebuildTree(const std::vector<CodeEntry> &table) {
    if (table.empty()) return nullptr;
    HuffNode *root = new HuffNode("", 0);
    for (const CodeEntry &entry: table) {
        if (entry.code.empty()) throw std::runtime_error("编码表中存在空编码，文件已损坏");
        HuffNode *cur = root;
        // 每个编码唯一决定了该符号在树中的路径：0 走左，1 走右
        for (char bit: entry.code) {
            if (bit == '0') {
                if (cur->left == nullptr) cur->left = new HuffNode("", 0);
                cur = cur->left;
            } else if (bit == '1') {
                if (cur->right == nullptr) cur->right = new HuffNode("", 0);
                cur = cur->right;
            } else {
                throw std::runtime_error("编码表中出现非 0/1 字符，文件已损坏");
            }
        }
        if (!cur->isLeaf() || !cur->symbol.empty()) {
            throw std::runtime_error("编码表存在前缀冲突，文件已损坏");
        }
        cur->symbol = entry.symbol;
    }
    return root;
}

void freeTree(HuffNode *root) {
    if (root == nullptr) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
