#include "element.h"


int main() {
     cpplab3v13::element elem;
     cpplab3v13::element elem2(3, 4);
     auto *ptr = new cpplab3v13::connection[7];
     cpplab3v13::element elem3(ptr, 5);
     elem.get_conns();
     //elem2.total_reorg();
     //elem2.get_conns();
     delete [] ptr;
     return 0;
}