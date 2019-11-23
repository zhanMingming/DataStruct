/*
* @Author: zhanmingming
* @Date:   2019-11-23 20:51:24
* @Last Modified by:   zhanmingming
* @Last Modified time: 2019-11-23 22:55:14
*/
#include "Knearest.h"
#include <iostream>


void PrintVector(const std::vector<int> & a) {
    for(auto iter = a.begin(); iter != a.end(); ++iter) {
        std::cout << *iter << " : ";
    }
    std::cout << std::endl;
}


std::vector<int>  Knearest(const std::vector<int> &a, int value, int k) {
    if (k > a.size()) {
        return  std::vector<int>();
    }

    int pos = Position(a,  value);

    std::vector<int> ret;
    if (pos == 0) {

        ret.assign(a.begin(), a.begin() + k);
        return ret;
    }
    if (pos == a.size() - 1) {
        ret.assign(a.end() - k, a.end());
        return ret;
    }

    int posMid = abs(a[pos] - value) <= abs(a[pos+1] - value) ? pos  : pos + 1;

    int posBegin = posMid;
    int posEnd = posMid;

    int posPreBegin = posBegin - 1;
    int posNextEnd =  posEnd + 1;

    while (posEnd - posBegin <  k - 1) {
        if (abs(a[posPreBegin] - value) <= abs(a[posNextEnd] - value)) {
            posBegin = posPreBegin;
            if (posPreBegin > 0) {
                --posPreBegin;
            } else  {
                posEnd = posNextEnd;
                ++posNextEnd;
            }
        } else {
            posEnd = posNextEnd;
            if (posNextEnd < a.size() - 1) {
                ++posNextEnd;
            } else {
                posBegin =  posPreBegin;
                --posPreBegin;
            }
        }
    }

    ret.assign(a.begin()+posBegin, a.begin()+posEnd+1);
    return ret;
}


void TestPosition() {
    std::vector<int> a = {1,3, 5, 14, 19, 20, 21, 26, 37, 88, 89};

    std::cout << Position(a, 5) << std::endl;
    std::cout << Position(a, 10) << std::endl;
    std::cout << Position(a, 20) << std::endl;
    std::cout << Position(a, 80) << std::endl;

    std::cout << "-----------" << std::endl;
    std::cout << Position2(a, 5) << std::endl;
    std::cout << Position2(a, 10) << std::endl;
    std::cout << Position2(a, 20) << std::endl;
    std::cout << Position2(a, 80) << std::endl;
}

int main(void) {
    std::vector<int> a = {1,3, 5, 14, 19, 20, 21, 26, 37, 88, 89};

    PrintVector(Knearest(a, 5, 5));
    PrintVector(Knearest(a, 5, 4));
    PrintVector(Knearest(a, 5, 3));
    PrintVector(Knearest(a, 5, 2));
    PrintVector(Knearest(a, 5, 1));


    PrintVector(Knearest(a, 25, 5));
    PrintVector(Knearest(a, 25, 4));
    PrintVector(Knearest(a, 25, 3));
    PrintVector(Knearest(a, 25, 2));
    PrintVector(Knearest(a, 25, 1));


    std::vector<int> b = {1, 3, 5};
    PrintVector(Knearest(b, 4, 3));

    PrintVector(Knearest(b, 4, 2));
    PrintVector(Knearest(b, 4, 1));


}




