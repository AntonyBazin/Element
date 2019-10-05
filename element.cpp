//
// Created by antony on 9/29/19.
//

#include "element.h"


namespace cpplab3v13{

    element::element() {
        this->conns = 0;
        connection in, out;
        in.type = IN;
        out.type = OUT;

        add_conn(in);
        add_conn(out);

    }

    element::element(int in, int out) {
        this->conns = 0;
        for(int i = 0; i < (in + out); ++i){
            connection con;
            con.type = i < in ? IN : OUT;
            add_conn(con);
        }
    }

    element::element(connection *arr, int sum) {
        this->conns = 0;
        for(int i = 0; i < sum; ++i)
            add_conn(arr[i]);
    }


    element &element::add_conn(connection newcomer) {
        if(this->conns >= connections_max)
            throw std::runtime_error("Too many connections to add more!");
        for(int i = 0; i < connections_max; ++i){
            if(cs[i].type == IM){
                cs[i] = newcomer;
                this->conns++;
                break;
            }
        }
        return *this;
    }
}
