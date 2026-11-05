/*
   https://github.com/DarnedBuzzard70/OI-Love
 */

#include <bits/stdc++.h>
#include "zycFastRead.h"
#include "zycTextEditorFunctions.h"

using namespace std;

int zycMENU() {
    puts("ZYC TEXT EDITOR MENU");
    puts("1. Insert Line");
    puts("2. Delete Line");
    puts("3. Modify Line");
    puts("4. Undo");
    puts("5. Redo");
    puts("6. Print All Lines");
    puts("7. Load File");
    puts("8. Save File");
    puts("9. Find Text");
    puts("10. Replace Text");
    puts("11. Copy Line");
    puts("12. Paste Line");
    puts("13. Exit");
    puts("Please enter your choice (1-13):");
    return 0;
}


int zycExit() {
    puts("See you later!");
    exit(0);
    return 2;
}

int zycChoiceAsk() {
    zycOP = read_int();
    switch (zycOP) {
        case 1: zycInsertLine();
            break;
        case 2: zycDeleteLine();
            break;
        case 3: zycModifyLine();
            break;
        case 4: zycUndo();
            break;
        case 5: zycRedo();
            break;
        case 6: zycPrintAllLines();
            break;
        case 7: zycLoadFile();
            break;
        case 8: zycSaveFile();
            break;
        case 9: zycFindText();
            break;
        case 10: zycReplaceText();
            break;
        case 11: zycCopyLine();
            break;
        case 12: zycPasteLine();
            break;
        case 13: zycExit();
            break;
        default:
            puts("Invalid choice. Please enter a number between 1 and 13.");
            break;
    }
    return 0;
}

int main() {
    while (true) {
        zycMENU();
        zycChoiceAsk();
    }
    return 0;
}
