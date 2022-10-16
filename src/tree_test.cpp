// maiamabl
#include <gtest/gtest.h>
#include "tree.h"

using namespace s21;

void print_set(std::set<int> set) {
    for (auto &items : set) {
    std::cout << items << " ";
    }
    std::cout << std::endl;
}

int main() {
    Tree<int, false> abc;
    std::set<int> sabc;

    std::cout << "Func Empty() begin" << std::endl;
    std::cout << "___MY___ = " << abc.empty() << std::endl;
    std::cout << "ORIGINAL = " << sabc.empty() << std::endl;
    std::cout << std::endl;

    // for (int i = 0; i < 15; i++) {
    //     abc.insert(rand() % 50, s21::F_DU);
    // }

    // abc.insert(55);
    // abc.insert(3);
    // abc.insert(76);
    // abc.insert(22);
    // abc.insert(39);
    // abc.insert(60);
    // abc.insert(45);
    // abc.insert(12);
    // abc.insert(66);
    // abc.insert(97);
    
    abc = {55,3,76,22,39,60,45,12,66,97};
    sabc = {55,3,76,22,39,60,45,12,66,97};
    // sabc = {55};


    std::cout << "Func Print Sorted:" << std::endl;
    abc.printSorted(abc.getRoot());
    std::cout << std::endl;
    print_set(sabc);
    std::cout << std::endl;

    std::cout << "Func Empty() end" << std::endl;
    std::cout << "___MY___ = " << abc.empty() << std::endl;
    std::cout << "ORIGINAL = " << sabc.empty() << std::endl;
    std::cout << std::endl;

    std::cout << "Func Search(39) true" << std::endl;
    // std::cout << abc.find(39) << std::endl;
    // std::cout << sabc.find(39) << std::endl;
    std::cout << std::endl;

    std::cout << "Func Search(111) false" << std::endl;
    // std::cout << abc.find(111) << std::endl;
    // std::cout << sabc.find(111). << std::endl;
    std::cout << std::endl;

    std::cout << "Func Erase(55) root" << std::endl;
    std::cout << abc.erase(55) << std::endl;
    std::cout << sabc.erase(55) << std::endl;
    abc.printSorted(abc.getRoot());
    std::cout << std::endl;
    print_set(sabc);
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Func Erase(97) max" << std::endl;
    std::cout << abc.erase(97) << std::endl;
    std::cout << sabc.erase(97) << std::endl;
    abc.printSorted(abc.getRoot());
    std::cout << std::endl;
    print_set(sabc);
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Func Erase(3) min" << std::endl;
    std::cout << abc.erase(3) << std::endl;
    std::cout << sabc.erase(3) << std::endl;
    abc.printSorted(abc.getRoot());
    std::cout << std::endl;
    print_set(sabc);
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Func Erase(111) false" << std::endl;
    std::cout << abc.erase(111) << std::endl;
    std::cout << sabc.erase(111) << std::endl;
    abc.printSorted(abc.getRoot());
    std::cout << std::endl;
    print_set(sabc);
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Func Size()" << std::endl;
    std::cout << "___MY___ = " << abc.size() << std::endl;
    std::cout << "ORIGINAL = " << sabc.size() << std::endl;
    std::cout << std::endl;

    std::cout << "Func MaxSize()" << std::endl;
    std::cout << "___MY___ = " << abc.max_size() << std::endl;
    std::cout << "ORIGINAL = " << sabc.max_size() << std::endl;
    std::cout << std::endl;

    std::cout << "Func Minimum(12)" << std::endl;
    std::cout << "___MY___ = " << abc.minimum(abc.getRoot())->data_ << std::endl;
    std::cout << std::endl;

    std::cout << "Func Maximum(76)" << std::endl;
    std::cout << "___MY___ = " << abc.maximum(abc.getRoot())->data_ << std::endl;
    std::cout << std::endl;

    std::cout << "Func Begin() and End()" << std::endl;
    std::cout << "___MY__B = " << abc.begin().operator*() << std::endl;
    std::cout << "___MY__E = " << abc.end().operator*() << std::endl;
    std::cout << std::endl;

    std::cout << "Func Operator++() and Operator--()" << std::endl;
    std::cout << "___MY__B = " << abc.begin().operator++().operator*() << std::endl;
    std::cout << "___MY__E = " << abc.end().operator--().operator*() << std::endl;

    std::cout << std::endl;

    std::cout << "Func Clear()" << std::endl;
    abc.clear();
    sabc.clear();
    abc.printSorted(abc.getRoot());
    std::cout << std::endl;
    print_set(sabc);
}