//
// Created by 25845 on 2026/11/5.
//

#include "zycTextEditorFunctions.h"
#include "zycFastRead.h"

int zycOP;
list<zycFrame> zycData;
stack<zyc_OP_Log> zycUndoStack, zycRedoStack;
zycFrame zycClipboard;

list<zycFrame>::iterator zycFindbyIdx(int id) {
    for (auto it = zycData.begin(); it != zycData.end(); ++it) {
        if (it->idx == id) {
            return it;
        }
    }
    return zycData.end();
    /*
    找不到拉到，返回 zycData.end()
    */
}

void zycRefreshIdx() {
    int cur = 1;
    for (auto &it: zycData) {
        it.idx = cur++;
    }
}

int zycInsertLine() {
    int pos;
    string s;
    cout << "Insert after which line? \n";
    cout << " (It you want to insert at head, enter 0): \n";
    cin >> pos;
    cin.ignore();
    /*
       一定要丢弃上一个'\n'。
    */
    cout << "Input line content: ";
    getline(cin, s);
    zycFrame newf;
    newf.USLine = s;
    auto it = zycFindbyIdx(pos);
    zyc_OP_Log log;
    log.OP_type = 1;
    log.line = pos + 1;
    log.new_content = newf;
    if (pos == 0) {
        zycData.push_front(newf);
    } else if (it != zycData.end()) {
        ++it;
        zycData.insert(it, newf);
    } else {
        cout << "Line not found, append to end. \n";
        zycData.push_back(newf);
    }
    zycRefreshIdx();
    zycUndoStack.push(log);
    while (!zycRedoStack.empty()) zycRedoStack.pop();
    cout << "Insert success. \n";
    return 0;
}

int zycDeleteLine() {
    int del_id;
    cout << "Input line number to delete: ";
    cin >> del_id;
    auto it = zycFindbyIdx(del_id);
    if (it == zycData.end()) {
        cout << "Line not exist! \n";
        return -1;
    }
    zyc_OP_Log log;
    log.OP_type = 2;
    log.line = del_id;
    log.old_content = *it;
    zycData.erase(it);
    zycRefreshIdx();
    zycUndoStack.push(log);
    while (!zycRedoStack.empty()) zycRedoStack.pop();
    cout << "Delete success. \n";
    return 0;
}

int zycModifyLine() {
    int mid;
    string ns;
    cout << "Input line number to modify: ";
    cin >> mid;
    cin.ignore();
    /*
       一定要丢弃上一个'\n'。
       血的教训之梅开二度！
    */
    auto it = zycFindbyIdx(mid);
    if (it == zycData.end()) {
        cout << "Line not exist! \n";
        return -1;
    }
    zyc_OP_Log log;
    log.OP_type = 3;
    log.line = mid;
    log.old_content = *it;
    cout << "New content: ";
    getline(cin, ns);
    it->USLine = ns;
    log.new_content = *it;
    zycUndoStack.push(log);
    while (!zycRedoStack.empty()) zycRedoStack.pop();
    cout << "Modify success. \n";
    return 0;
}

int zycUndo() {
    if (zycUndoStack.empty()) {
        cout << "Nothing to undo!\n";
        return -1;
    }
    auto log = zycUndoStack.top();
    zycUndoStack.pop();
    zycRedoStack.push(log);

    if (log.OP_type == 1) {
        auto it = zycFindbyIdx(log.line);
        if (it != zycData.end()) zycData.erase(it);
    } else if (log.OP_type == 2) {
        auto it = zycFindbyIdx(log.line - 1);
        if (it != zycData.end()) {
            ++it;
            zycData.insert(it, log.old_content);
        } else {
            zycData.push_back(log.old_content);
        }
    } else if (log.OP_type == 3) {
        auto it = zycFindbyIdx(log.line);
        if (it != zycData.end()) it->USLine = log.old_content.USLine;
    }
    zycRefreshIdx();
    cout << "Undo done\n";
    return 0;
}

int zycRedo() {
    if (zycRedoStack.empty()) {
        cout << "Nothing to redo!\n";
        return -1;
    }
    auto log = zycRedoStack.top();
    zycRedoStack.pop();
    zycUndoStack.push(log);
    if (log.OP_type == 1) {
        auto it = zycFindbyIdx(log.line - 1);
        if (it != zycData.end()) {
            ++it;
            zycData.insert(it, log.new_content);
        } else {
            zycData.push_back(log.new_content);
        }
    } else if (log.OP_type == 2) {
        auto it = zycFindbyIdx(log.line);
        if (it != zycData.end()) {
            zycData.erase(it);
        }
    } else if (log.OP_type == 3) {
        auto it = zycFindbyIdx(log.line);
        if (it != zycData.end()) {
            it->USLine = log.new_content.USLine;
        }
    }
    zycRefreshIdx();
    cout << "Redo done\n";
    return 0;
}

int zycPrintAllLines() {
    cout << "All Lines: \n";
    for (auto &zycIt: zycData) {
        cout << zycIt.idx << ": " << zycIt.USLine << endl;
    }
    cout << "\n";
    return 0;
}

int zycLoadFile() {
    string fname;
    cout << "Input filename: ";
    cin >> fname;
    ifstream fin(fname);
    if (!fin.is_open()) {
        cout << "Open file failed!\n";
        return -1;
    }
    zycData.clear();
    string line;
    while (getline(fin, line)) {
        zycFrame f;
        f.USLine = line;
        zycData.push_back(f);
    }
    zycRefreshIdx();
    fin.close();
    cout << "Load file success\n";
    return 0;
}

int zycSaveFile() {
    string fname;
    cout << "Input filename: ";
    cin >> fname;
    ofstream fout(fname);
    if (!fout.is_open()) {
        cout << "Create file failed!\n";
        return -1;
    }
    for (auto &it: zycData) {
        fout << it.USLine << '\n';
    }
    fout.close();
    cout << "Save file success\n";
    return 0;
}

int zycFindText() {
    string key;
    cin.ignore();
    cout << "Text to find: ";
    getline(cin, key);
    bool found = false;
    for (auto &it: zycData) {
        if (it.USLine.find(key) != string::npos) {
            cout << "Line " << it.idx << ": " << it.USLine << '\n';
            found = true;
        }
    }
    if (!found) cout << "Not found\n";
    return 0;
}

int zycReplaceText() {
    string oldstr, newstr;
    cin.ignore();
    cout << "Old text: ";
    getline(cin, oldstr);
    cout << "New text: ";
    getline(cin, newstr);
    int cnt = 0;
    for (auto &it: zycData) {
        size_t pos = 0;
        while ((pos = it.USLine.find(oldstr, pos)) != string::npos) {
            it.USLine.replace(pos, oldstr.size(), newstr);
            pos += newstr.size();
            cnt++;
        }
    }
    cout << "Replaced " << cnt << " times\n";
    return 0;
}

int zycCopyLine() {
    int cid;
    cout << "Copy which line: ";
    cin >> cid;
    auto it = zycFindbyIdx(cid);
    if (it == zycData.end()) {
        cout << "Line not exist!\n";
        return -1;
    }
    zycClipboard = *it;
    cout << "Copy line " << cid << " success\n";
    return 0;
}

int zycPasteLine() {
    int pos;
    cout << "Paste after which line? (0=head): ";
    cin >> pos;
    auto it = zycFindbyIdx(pos);
    if (pos == 0) {
        zycData.push_front(zycClipboard);
    } else if (it != zycData.end()) {
        ++it;
        zycData.insert(it, zycClipboard);
    } else {
        zycData.push_back(zycClipboard);
    }
    zycRefreshIdx();
    zyc_OP_Log log;
    log.OP_type = 1;
    log.line = pos + 1;
    log.new_content = zycClipboard;
    zycUndoStack.push(log);
    while (!zycRedoStack.empty()) zycRedoStack.pop();
    cout << "Paste done\n";
    return 0;
}