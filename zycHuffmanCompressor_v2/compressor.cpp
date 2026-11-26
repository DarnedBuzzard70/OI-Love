//
// Created by 25845 on 2026/11/26.
//

#include "compressor.h"
#include "huffman.h"
#include "hashtable.h"
#include <fstream>
#include <stdexcept>
#include <bitset>
#include <chrono>
#include <algorithm>
#include <vector>

// 二进制文件读写

std::string readFileBinary(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("无法打开文件: " + filename);
    file.seekg(0, std::ios::end);
    std::streamoff fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::string buffer(static_cast<size_t>(fileSize), '\0');
    if (fileSize > 0) file.read(&buffer[0], fileSize);
    file.close();
    return buffer;
}

void writeFileBinary(const std::string &filename, const std::string &data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("无法打开输出文件: " + filename);
    file.write(data.data(), static_cast<std::streamsize>(data.size()));
    file.close();
}

// 编码表转义 / 还原
// ':' 分隔符号与编码，'\n' 分隔每对编码，因此符号中出现的这些字符必须转义

static std::string escape(const std::string &str) {
    std::string result;
    for (char c: str) {
        switch (c) {
            case '\\': result += "\\\\";
                break;
            case '\n': result += "\\n";
                break;
            case '\r': result += "\\r";
                break;
            case '\t': result += "\\t";
                break;
            case ':': result += "\\:";
                break;
            default: result += c;
                break;
        }
    }
    return result;
}

static std::string unescape(const std::string &str) {
    std::string result;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '\\' && i + 1 < str.size()) {
            switch (str[i + 1]) {
                case '\\': result += '\\';
                    ++i;
                    break;
                case 'n': result += '\n';
                    ++i;
                    break;
                case 'r': result += '\r';
                    ++i;
                    break;
                case 't': result += '\t';
                    ++i;
                    break;
                case ':': result += ':';
                    ++i;
                    break;
                default: // 不认识的转义保留原样
                    result += '\\';
                    result += str[++i];
                    break;
            }
        } else {
            result += str[i];
        }
    }
    return result;
}

// 频率统计与符号切分
// GBK（简体中文 Windows 的 ANSI）字符长度：首字节 0x81~0xFE 为双字节中文，否则单字节
// static int charLength(const char *s) {
//     unsigned char c = static_cast<unsigned char>(*s);
//     if (c >= 0x81 && c <= 0xFE) {
//         return 2;
//     }
//     return 1;
// }

static int charLength(const char *s) {
    // *out_encoding = 0;
    unsigned char c = static_cast<unsigned char>(*s);

    // 第一步：尝试按 UTF-8 解析并校验续字节
    int u8_len = -1;
    if (c < 0x80) {
        u8_len = 1;
    } else if ((c & 0xE0) == 0xC0) {
        u8_len = 2;
    } else if ((c & 0xF0) == 0xE0) {
        u8_len = 3;
    } else if ((c & 0xF8) == 0xF0) {
        u8_len = 4;
    }

    bool utf8_valid = false;
    if (u8_len > 0) {
        utf8_valid = true;
        for (int i = 1; i < u8_len; i++) {
            unsigned char sub = static_cast<unsigned char>(s[i]);
            if ((sub & 0xC0) != 0x80) {
                utf8_valid = false;
                break;
            }
        }
    }

    if (utf8_valid) {
        // *out_encoding = (u8_len == 1) ? 0 : 1;
        return u8_len;
    }

    // UTF-8 校验失败，回退 GBK 逻辑
    if (c >= 0x81 && c <= 0xFE) {
        // *out_encoding = 2;
        return 2;
    } else {
        // *out_encoding = 0;
        return 1;
    }
}


// 把文件内容按方案切分成符号序列
static std::vector<std::string> splitSymbols(const std::string &buffer, Scheme scheme) {
    std::vector<std::string> symbols;
    if (scheme == Scheme::BYTE) {
        symbols.reserve(buffer.size());
        for (unsigned char byte: buffer) {
            symbols.push_back(std::string(1, static_cast<char>(byte)));
        }
    } else {
        size_t i = 0;
        while (i < buffer.size()) {
            int len = charLength(buffer.c_str() + i);
            if (i + static_cast<size_t>(len) > buffer.size()) {
                len = 1;
                // 末尾残缺字节，很他妈烦。
            }
            symbols.push_back(buffer.substr(i, static_cast<size_t>(len)));
            i += static_cast<size_t>(len);
        }
    }
    return symbols;
}

// 统计频率：字节方案用定长数组[256]（查找 O(1)），字符方案用自定义哈希表
static std::vector<FreqPair> countFrequencies(const std::vector<std::string> &symbols,
                                              Scheme scheme) {
    std::vector<FreqPair> freqs;
    if (scheme == Scheme::BYTE) {
        unsigned long long freq[256] = {0};
        for (const std::string &s: symbols) {
            ++freq[static_cast<unsigned char>(s[0])];
        }
        for (int b = 0; b < 256; ++b) {
            if (freq[b] > 0) {
                freqs.push_back({std::string(1, static_cast<char>(b)), freq[b]});
            }
        }
    } else {
        HashTable freqTable;
        for (const std::string &s: symbols) freqTable.increment(s);
        freqTable.forEach([&freqs](const std::string &key, unsigned long long value) {
            freqs.push_back({key, value});
        });
        // 哈希表遍历顺序不定，按符号排序保证构建结果确定
        std::sort(freqs.begin(), freqs.end(),
                  [](const FreqPair &a, const FreqPair &b) { return a.first < b.first; });
    }
    return freqs;
}

// ---------- 01 字符串 <-> 比特流 ----------

// 01 字符串打包为字节流：8 bit 一组，末尾不足补 0
static std::string packBits(const std::string &encodeTxt) {
    std::string byteStream;
    byteStream.reserve(encodeTxt.size() / 8 + 1);
    unsigned char buffer = 0;
    int bitsInBuffer = 0;
    for (char bit: encodeTxt) {
        buffer = static_cast<unsigned char>((buffer << 1) | (bit == '1' ? 1 : 0));
        ++bitsInBuffer;
        if (bitsInBuffer == 8) {
            byteStream += static_cast<char>(buffer);
            buffer = 0;
            bitsInBuffer = 0;
        }
    }
    if (bitsInBuffer > 0) {
        // 补零凑整最后一个字节
        buffer = static_cast<unsigned char>(buffer << (8 - bitsInBuffer));
        byteStream += static_cast<char>(buffer);
    }
    return byteStream;
}

// 字节流还原为 01 字符串，并按真实 bit 长度截掉末尾填充的 0
static std::string unpackBits(const std::string &byteStream, uint64_t bitLength) {
    std::string result;
    result.reserve(byteStream.size() * 8);
    for (unsigned char c: byteStream) {
        result += std::bitset<8>(c).to_string();
    }
    if (bitLength > result.size()) throw std::runtime_error("比特流长度不足，文件已损坏");
    result.resize(static_cast<size_t>(bitLength));
    return result;
}

// ---------- 压缩 ----------

Stats compressFile(const std::string &inputFile, const std::string &outputFile, Scheme scheme) {
    auto startTime = std::chrono::steady_clock::now();
    Stats stats;
    stats.scheme = scheme;

    // 1. 二进制读入原始文件，切分符号并统计频率
    std::string buffer = readFileBinary(inputFile);
    stats.originalSize = buffer.size();
    std::vector<std::string> symbols = splitSymbols(buffer, scheme);
    std::vector<FreqPair> freqs = countFrequencies(symbols, scheme);
    stats.symbolCount = freqs.size();

    // 2. 构建哈夫曼树并生成编码表
    HuffNode *root = buildHuffmanTree(freqs);
    std::vector<CodeEntry> table;
    generateCodes(root, table);

    // 3. 编码表同时放入自定义哈希表（符号 -> 下标），编码时 O(1) 查找
    HashTable codeIndex;
    for (size_t i = 0; i < table.size(); ++i) {
        codeIndex.set(table[i].symbol, i);
    }

    // 4. 将原始内容逐符号转换为 01 字符串
    std::string encodeTxt;
    for (const std::string &s: symbols) {
        unsigned long long *idx = codeIndex.find(s);
        if (idx == nullptr) throw std::runtime_error("编码表中缺少符号，内部错误");
        encodeTxt += table[*idx].code;
    }
    stats.bitLength = encodeTxt.size();
    freeTree(root);

    // 5. 按格式写压缩文件：标识 + 编码表 + 01串长度 + 比特流
    std::string out;
    out += (scheme == Scheme::BYTE) ? "HUF2B\n" : "HUF2C\n";
    for (const CodeEntry &entry: table) {
        out += escape(entry.symbol);
        out += ':';
        out += entry.code;
        out += '\n';
    }
    out += "END_HEADER\n";
    out += std::to_string(stats.bitLength);
    out += '\n';
    out += packBits(encodeTxt);

    writeFileBinary(outputFile, out);
    stats.packedSize = out.size();

    auto endTime = std::chrono::steady_clock::now();
    stats.elapsedMs = std::chrono::duration<double, std::milli>(endTime - startTime).count();
    return stats;
}

// ---------- 解压缩 ----------

// 在一行编码表记录中找到未被转义的 ':' 分隔符位置
static size_t findSeparator(const std::string &line) {
    for (size_t i = 0; i < line.size(); i += 1) {
        if (line[i] == '\\') {
            i += 1;
            continue;
        }
        if (line[i] == ':') return i;
    }
    throw std::runtime_error("编码表行缺少分隔符，文件已损坏");
}

Stats decompressFile(const std::string &inputFile, const std::string &outputFile) {
    auto startTime = std::chrono::steady_clock::now();
    Stats stats;

    std::string buffer = readFileBinary(inputFile);
    stats.packedSize = buffer.size();

    // 1. 校验标识并识别方案
    if (buffer.size() < 6 || buffer.compare(0, 4, "HUF2") != 0 || buffer[5] != '\n') {
        throw std::runtime_error("不是本程序生成的压缩文件（缺少 HUF2 标识）");
    }
    stats.scheme = (buffer[4] == 'B') ? Scheme::BYTE : Scheme::CHAR;
    size_t pos = 6;

    // 2. 定位编码表结束标记（符号最长 2 字节且已转义，不会与标记混淆）
    const std::string marker = "END_HEADER\n";
    size_t markerPos = buffer.find(marker, pos);
    if (markerPos == std::string::npos) throw std::runtime_error("缺少 END_HEADER，文件已损坏");

    // 3. 逐行解析编码表
    std::vector<CodeEntry> table;
    while (pos < markerPos) {
        size_t lineEnd = buffer.find('\n', pos);
        if (lineEnd == std::string::npos || lineEnd > markerPos) {
            throw std::runtime_error("编码表格式错误，文件已损坏");
        }
        std::string line = buffer.substr(pos, lineEnd - pos);
        pos = lineEnd + 1;
        if (line.empty()) continue;
        size_t sep = findSeparator(line);
        CodeEntry entry;
        entry.symbol = unescape(line.substr(0, sep));
        entry.code = line.substr(sep + 1);
        table.push_back(entry);
    }
    pos = markerPos + marker.size();
    stats.symbolCount = table.size();

    // 4. 读取 01 串真实长度
    size_t lenEnd = buffer.find('\n', pos);
    if (lenEnd == std::string::npos) throw std::runtime_error("缺少长度字段，文件已损坏");
    std::string lenStr = buffer.substr(pos, lenEnd - pos);
    uint64_t bitLength = 0;
    for (char c: lenStr) {
        if (c < '0' || c > '9') throw std::runtime_error("长度字段非法，文件已损坏");
        bitLength = bitLength * 10 + static_cast<uint64_t>(c - '0');
    }
    stats.bitLength = bitLength;
    pos = lenEnd + 1;

    // 5. 比特流还原为 01 字符串，可以同时截掉打包时补的 0
    std::string byteStream = buffer.substr(pos);
    std::string bits = unpackBits(byteStream, bitLength);

    // 6. 根据编码表重建哈夫曼树，从根出发逐 bit 译码
    HuffNode *root = rebuildTree(table);
    std::string output;
    if (root != nullptr) {
        HuffNode *cur = root;
        for (char bit: bits) {
            cur = (bit == '0') ? cur->left : cur->right;
            if (cur == nullptr) throw std::runtime_error("译码路径不存在，文件已损坏");
            if (cur->isLeaf()) {
                output += cur->symbol;
                cur = root;
            }
        }
        if (cur != root) throw std::runtime_error("比特流未结束于叶子节点，文件已损坏");
    }
    freeTree(root); //不释放手搓的指针你一定会不会内存泄漏

    writeFileBinary(outputFile, output);
    stats.originalSize = output.size();

    auto endTime = std::chrono::steady_clock::now();
    stats.elapsedMs = std::chrono::duration<double, std::milli>(endTime - startTime).count();
    return stats;
}
