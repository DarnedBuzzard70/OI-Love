#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <string>
#include <cstdint>

// 两种压缩方案
enum class Scheme {
    BYTE, CHAR // 字节频率，字符频率
};

// 压缩 / 解压结果统计
struct Stats {
    uint64_t originalSize = 0; // 原始文件字节数
    uint64_t packedSize = 0; // 压缩文件总字节数（含头部）
    uint64_t bitLength = 0; // 编码后 01 字符串长度（bit 数）
    size_t symbolCount = 0; // 不同符号（字节 / 字符）个数
    double elapsedMs = 0.0; // 耗时（毫秒）
    Scheme scheme = Scheme::BYTE;
};

// 二进制方式一次性读入整个文件
std::string readFileBinary(const std::string &filename);

// 二进制方式写出整个文件
void writeFileBinary(const std::string &filename, const std::string &data);

// 压缩：inputFile -> outputFile，scheme 指定统计方案
Stats compressFile(const std::string &inputFile, const std::string &outputFile, Scheme scheme);

// 解压缩：自动从压缩文件头部识别方案并还原
Stats decompressFile(const std::string &inputFile, const std::string &outputFile);

#endif // COMPRESSOR_H
