//
// Created by antony on 10/26/19.
//

#ifndef CPPLAB_APP_H
#define CPPLAB_APP_H

#include "element.h"

namespace cpplab3v13{

    class Sheffer_stroke{
    private:
        conditions c1, c2;
        element elems[4];
        conditions answer;
    public:
        Sheffer_stroke(conditions c1 = X, conditions c2 = X);
        conditions output(conditions c1, conditions c2){ return answer; }
        conditions operator ()(conditions c1, conditions c2);
    };

}



#endif //CPPLAB_APP_H
