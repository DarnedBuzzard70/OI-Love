//手搓的优先队列，但是又有点要改的地方，就重新写了最小堆模块

#ifndef ZYCPQ_H
#define ZYCPQ_H

#include <bits/stdc++.h>

template<class T, class Container = std::vector<T>, class Compare = std::less<T> >
class zyc_priority_queue {
private:
    Container _c;
    Compare _comp;

    void shangfu(int erzi) {
        int baba = (erzi - 1) / 2;
        while (erzi > 0) {
            if (_comp(_c[baba], _c[erzi])) {
                std::swap(_c[baba], _c[erzi]);
                erzi = baba;
                baba = (erzi - 1) / 2;
            } else {
                break;
            }
        }
    }

    void xiachen(int baba) {
        int n = static_cast<int>(_c.size());
        int erzi = baba * 2 + 1;
        while (erzi < n) {
            if (erzi + 1 < n && _comp(_c[erzi], _c[erzi + 1])) {
                erzi++;
            }
            if (_comp(_c[baba], _c[erzi])) {
                std::swap(_c[baba], _c[erzi]);
                baba = erzi;
                erzi = baba * 2 + 1;
            } else {
                break;
            }
        }
    }

public:
    zyc_priority_queue() = default;

    template<class InputIterator>
    zyc_priority_queue(InputIterator first, InputIterator last) {
        _c.assign(first, last);
        int n = static_cast<int>(_c.size());
        for (int i = (n - 2) / 2; i >= 0; --i) {
            xiachen(i);
        }
    }

    void push(const T &val) {
        _c.push_back(val);
        shangfu(static_cast<int>(_c.size() - 1));
    }

    void pop() {
        std::swap(_c[0], _c.back());
        _c.pop_back();
        xiachen(0);
    }

    const T &top() const {
        return _c[0];
    }

    bool empty() const {
        return _c.empty();
    }

    size_t size() const {
        return _c.size();
    }

    const T &operator[](size_t index) const {
        return _c[index];
    }

    //按下标随机访问内存，正常的优先队列不使用。
};

#endif //ZYCPQ_H
