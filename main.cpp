#include "element.h"

using namespace cpplab3v13;

int main() {
    for(int i = 0; i < 8; ++i){
        auto x = static_cast<conditions>(i > 3 ? 1 : 0),
            y = static_cast<conditions>(i / 2 % 2),
            z = static_cast<conditions>(i % 2);
        std::cout << "#" << i << " {" << x << "; " << y << "; " << z << "}:"
        << std::endl << cpplab3v13::f(x, y, z) << std::endl;
    }
    return 0;
}