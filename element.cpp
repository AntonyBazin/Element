//
// Created by antony on 9/29/19.
//

#include "element.h"


namespace cpplab3v13{

    element::element() {
        this->conns = 2;
        connection in, out;
        in.type = IN;
        out.type = OUT;

        add_conn(in);
        add_conn(out);

    }

    element &element::add_conn(connection newcomer) {
        if(this->conns == connections_max)
            throw std::runtime_error("Too many connections to add more!");
        for(int i = 0; i < connections_max; ++i){
            if(cs[i].type == IM){
                cs[i] = newcomer;
                break;
            }
        }
        return *this;
    }

}
