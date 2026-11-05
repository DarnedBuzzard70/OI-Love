//
// Created by 25845 on 2026/11/5.
//

#ifndef ZYCTEXTEDITOR_ZYCFASTREAD_H
#define ZYCTEXTEDITOR_ZYCFASTREAD_H

#include<bits/stdc++.h>

inline int read_int() {
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s = s * 10 + ch - '0';
        ch = getchar();
    }
    return s * w;
}

#endif //ZYCTEXTEDITOR_ZYCFASTREAD_H
