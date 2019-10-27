//
// Created by antony on 10/26/19.
//

#include <iostream>
#include <sstream>
#include "app.h"

namespace cpplab3v13{
    Sheffer_stroke::Sheffer_stroke(conditions c1, conditions c2) {
        connection addition;
        std::istringstream set1("0\n 1\n 0\n");
        std::istringstream set2("0\n 1\n 1\n");
        std::istringstream set3("1\n 1\n 0\n");
        std::istringstream set4("1\n 0\n 1\n");
        addition.type = IN;
        for(int i = 0; i < 4; ++i){
            elems[i].add_conn(addition);
            elems[i](0, 1);
            elems[i](2, 1);
        }
        set1 >> elems[0];
        set2 >> elems[1];
        set3 >> elems[2];
        set4 >> elems[3];
        this->c1 = c1, this->c2 = c2;
        answer = X;
    }


    conditions Sheffer_stroke::operator()(conditions c1, conditions c2) {
        answer = X;
        for(int i = 0; i < 4; ++i){
            if(elems[i][0].condition == c1 && elems[i][2].condition == c2)
                answer = elems[i][1].condition;
        }
        return answer;
    }

}



