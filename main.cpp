#include "element.h"

int main() {

    auto *ptr = new cpplab3v13::connection[7];
    for(int i = 0; i < 5; ++i){
        ptr[i].type = i < 2 ? cpplab3v13::IN : cpplab3v13::OUT;
    }
    cpplab3v13::run(ptr, 5);
    delete [] ptr;
    return 0;
}
