//#include "bstset.h"
//#include <iostream>
//using namespace std;
//
//
//int main() {
//    cout << "hello" << endl;
//    BSTSet<int> mySet;
//    mySet.insert(5);
//    mySet.insert(2);
//    mySet.insert(8);
//    mySet.insert(7);
//    mySet.insert(5); // Duplicate insert (replaces old 5 with new 5)
//     // Now let's find the first element not smaller than 4
//    //BSTSet<int>::SetIterator it (nullptr, nullptr);
//    BSTSet<int>::SetIterator it = mySet.find_first_not_smaller(4);
//    const int* p;
//    while ((p = it.get_and_advance()) != nullptr)
//         std::cout << *p << ' ';
//    std::cout << std::endl;
//}
//
//
