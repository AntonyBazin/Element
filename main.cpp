#include "element.h"


int main() {
     std::cout << "Hello, World!" << std::endl;
     cpplab3v13::element elem;
     cpplab3v13::element elem2(3, 4);
     auto *ptr = new cpplab3v13::connection[5];
     cpplab3v13::element elem3(ptr, 5);
     delete [] ptr;
     elem3.total_reorg();
     elem3.get_conns();
     return 0;
}