#ifndef KNEAREST_H
#define KNEAREST_H

#include <vector>
/*
思路：首先找出给定值在给定数组中的插入位置（不是真的将给定值插入给定数组），
然后以此位置为基准，向左或向右依次找出最接近的k个整数。

难点：个人在处理过程中的难点在于向左或向右移动过程中的确切位置的确定。
 */

// 返回小于等于 value 的下标
int  Position(std::vector<int> a, int value)  {
    int begin = 0;
    int end = a.size() - 1;

    while (begin <= end) {
        int pos = (end + begin)/ 2;
        if (a[pos] == value) {
            return pos;
        } else if (a[pos] > value) {
            end = pos - 1;
        } else {
            begin = pos + 1;
        }
         
    }
    return end;
}


// 返回大于等于 value 的下标
int  Position2(std::vector<int> a, int value)  {
    int begin = 0;
    int end = a.size() - 1;

    while (begin <= end) {
        int pos = (end + begin)/ 2;
        if (a[pos] == value) {
            return pos;
        } else if (a[pos] > value) {
            end = pos - 1;
        } else {
            begin = pos + 1;
        }
         
    }
    return begin;
}


#endif
