//
// Created by 25845 on 2026/11/5.
//

#ifndef ZYCTEXTEDITOR_ZYCTEXTEDITORFUNCTIONS_H
#define ZYCTEXTEDITOR_ZYCTEXTEDITORFUNCTIONS_H

#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <fstream>
using namespace std;

// 结构体定义，放头文件
struct zycFrame {
    int idx;
    string USLine;
};

struct zyc_OP_Log {
    int OP_type;
    int line;
    zycFrame old_content, new_content;
    /*
       OP_type: 1插入, 2=删除, 3=修改。
     */
};


extern int zycOP;
extern list<zycFrame> zycData;
extern stack<zyc_OP_Log> zycUndoStack, zycRedoStack;
extern zycFrame zycClipboard;


list<zycFrame>::iterator zycFindbyIdx(int id);
void zycRefreshIdx();
int zycInsertLine();
int zycDeleteLine();
int zycModifyLine();
int zycUndo();
int zycRedo();
int zycPrintAllLines();
int zycLoadFile();
int zycSaveFile();
int zycFindText();
int zycReplaceText();
int zycCopyLine();
int zycPasteLine();

#endif //ZYCTEXTEDITOR_ZYCTEXTEDITORFUNCTIONS_H