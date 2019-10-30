#include "element.h"
#include "app.h"

using namespace cpplab3v13;

int main() {
    int rc, c1, c2;
    Sheffer_stroke stroke;
    std::cout << "default stroke output:" << std::endl
    << stroke.output() << std::endl;

    while(true){
        std::cout << "Input 2 conditions for the Sheffer stroke function:"
        << std::endl;
        do{
            rc = input_number(c1, std::cin);
            if(rc == 1) break;
            if(!rc) {
                std::cout << "That's all. Bye!" << std::endl;
                return 0;
            }
            std::cout << "incorrect input, please, try again:";
        }while(rc < 0);

        do{
            rc = input_number(c2, std::cin);
            if(rc == 1) break;
            if(!rc) {
                std::cout << "That's all. Bye!" << std::endl;
                return 0;
            }
            std::cout << "incorrect input, please, try again:";
        }while(rc < 0);

        switch(stroke(static_cast<conditions>(c1), static_cast<conditions>(c2))){
            case 0:
                std::cout << "LOW; ";
                break;
            case 1:
                std::cout << "HIGH; ";
                break;
            default:
                std::cout << "NOT DEFINED; ";
                break;
        }
    }
    return 0;
}