// maiamabl
#include <gtest/gtest.h>
#include "s21_set.h"

using namespace s21;

void print_set(std::set<int> set) {
    for (auto &items : set) {
    std::cout << items << " ";
    }
    std::cout << std::endl;
}

int main() {
    set<int> abc;
    std::set<int> sabc;

    std::cout << "Func Empty() begin" << std::endl;
    std::cout << "___MY___ = " << abc.empty() << std::endl;
    std::cout << "ORIGINAL = " << sabc.empty() << std::endl;
    std::cout << std::endl;

    // abc.insert(556);
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

    std::cout << "Func Find(39) true" << std::endl;
    std::cout << abc.find(39).operator*() << std::endl;
    std::cout << sabc.find(39).operator*() << std::endl;
    std::cout << std::endl;

    std::cout << "Func Find(111) false" << std::endl;
    // std::cout << abc.find(111).operator*() << std::endl;
    std::cout << sabc.find(111).operator*() << std::endl;
    std::cout << std::endl;

    // std::cout << "Func Erase(55) root" << std::endl;
    // std::cout << abc.erase(55) << std::endl;
    // std::cout << sabc.erase(55) << std::endl;
    // abc.printSorted(abc.getRoot());
    // std::cout << std::endl;
    // print_set(sabc);
    // std::cout << std::endl;
    // std::cout << std::endl;

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

    std::cout << "Func Begin() and End()" << std::endl;
    std::cout << "___MY__B = " << abc.begin().operator*() << std::endl;
    std::cout << "ORIGINAL = " << sabc.begin().operator*() << std::endl;
    // std::cout << "___MY__E = " << abc.end() << std::endl;
    // std::cout << "___MY__E = " << sabc.end() << std::endl;
    std::cout << std::endl;

    std::cout << "Func Operator++() and Operator--()" << std::endl;
    std::cout << "___MY__B = " << abc.begin().operator++().operator*() << std::endl;
    std::cout << "ORIGINAL = " << sabc.begin().operator++().operator*() << std::endl;
    std::cout << "ORIGINAL = " << sabc.end().operator--().operator*() << std::endl;

    std::cout << std::endl;

    std::cout << "Func Clear()" << std::endl;
    abc.clear();
    sabc.clear();
    abc.printSorted(abc.getRoot());
    std::cout << std::endl;
    print_set(sabc);
}