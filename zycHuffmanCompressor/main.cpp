//
// Created by 25845 on 2026/11/19.
//

#include <bits/stdc++.h>
#include "compressor.h"

#ifdef _WIN32
#include <windows.h>
#endif

static const char *schemeName(Scheme s) {
    return s == Scheme::BYTE ? "字节频率" : "字符频率(ANSI/GBK)";
}

static void printStats(const Stats &st, bool isCompress) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  使用方案: " << schemeName(st.scheme) << "\n";
    std::cout << "  不同符号数: " << st.symbolCount << "\n";
    std::cout << "  编码后字节数: " << st.bitLength << "\n";
    if (isCompress) {
        //妈的，制表符对不齐不对了
        std::cout << "  原始文件大小: " << st.originalSize << " 字节\n";
        std::cout << "  压缩文件大小: " << st.packedSize << " 字节（含编码表头部）\n";
        if (st.packedSize > 0) {
            std::cout << "  压缩比: " << (double) st.originalSize / st.packedSize << "\n";
            std::cout << "  空间节省: " << (1.0 - (double) st.packedSize / st.originalSize) * 100.0 << " %\n";
        }
    } else {
        std::cout << "  压缩文件大小: " << st.packedSize << " 字节\n";
        std::cout << "  还原文件大小: " << st.originalSize << " 字节\n";
    }
    std::cout << "  耗时: " << st.elapsedMs << " ms\n";
}

static void doCompress(const std::string &in, const std::string &out, Scheme scheme) {
    Stats st = compressFile(in, out, scheme);
    std::cout << "压缩完成: " << in << " -> " << out << "\n";
    printStats(st, true);
}

static void doDecompress(const std::string &in, const std::string &out) {
    Stats st = decompressFile(in, out);
    std::cout << "解压缩完成: " << in << " -> " << out << "\n";
    printStats(st, false);
}

static void printUsage() {
    std::cout << "用法:\n"
            << "  zycHuffmanCompressor.exe \t\t\t进入交互式菜单\n" <<
            "  zycHuffmanCompressor.exe c b <输入> <输出> \t按字节频率压缩（适用于所有文件）\n" <<
            "  zycHuffmanCompressor.exe c c <输入> <输出> \t按字符频率压缩（适用于ANSI/GBK文本）\n" <<
            "  zycHuffmanCompressor.exe d <输入> <输出> \t解压缩（自动识别方案）\n";
}

int main(int argc, char **argv) {
#ifdef _WIN32
    // Windows 下设置控制台为 UTF-8，防止乱码
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    try {
        // 用命令直接运行
        if (argc >= 2) {
            std::string cmd = argv[1];
            if (cmd == "c" && argc == 5) {
                std::string mode = argv[2];
                if (mode != "b" && mode != "c") {
                    printUsage();
                    return 114514;
                }
                doCompress(argv[3], argv[4], mode == "b" ? Scheme::BYTE : Scheme::CHAR);
                return 0;
            }
            if (cmd == "d" && argc == 4) {
                doDecompress(argv[2], argv[3]);
                return 0;
            }
            printUsage();
            return 114514;
        }

        // 不用命令可以进去的正常菜单
        while (true) {
            std::cout << "\n========= zycHuffmanCompressor =========\n"
                    << "  1. 字节频率压缩文件\n"
                    << "  2. 字符频率压缩文件（适用于ANSI/GBK文本）\n"
                    << "  3. 解压缩文件\n"
                    << "  0. 退出\n"
                    << "请选择操作: ";
            std::string choice;
            if (!std::getline(std::cin, choice)) break;

            if (choice == "0") {
                std::cout << "再见！\n";
                break;
            }
            if (choice != "1" && choice != "2" && choice != "3") {
                std::cout << "无效选择，请重新输入：\n";
                continue;
            }

            std::string inFile, outFile;
            std::cout << "请输入输入文件路径: ";
            if (!std::getline(std::cin, inFile)) {
                break;
            }
            std::cout << "请输入输出文件路径: ";
            if (!std::getline(std::cin, outFile)) {
                break;
            }

            try {
                if (choice == "1") {
                    doCompress(inFile, outFile, Scheme::BYTE);
                } else if (choice == "2") {
                    doCompress(inFile, outFile, Scheme::CHAR);
                } else {
                    doDecompress(inFile, outFile);
                }
            } catch (const std::exception &e) {
                std::cout << "操作失败: " << e.what() << "\n";
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "错误: " << e.what() << "\n";
        return 114514;
    }
    return 0;
}
