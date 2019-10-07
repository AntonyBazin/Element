#include "run.h"


int main() {

    auto *ptr = new cpplab3v13::connection[7];
    run(ptr);

    delete [] ptr;
    return 0;
}
