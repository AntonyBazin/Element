//
// Created by antony on 9/29/19.
//

#include "element.h"


namespace cpplab3v13{

    element::element(int in, int out) {
        this->conns = 0;
        for(int i = 0; i < (in + out) && i < connections_max; ++i){
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

    element &element::total_reorg() {
        int c, rc;
        for(int i = 0; i < this->conns; ++i){
            std::cout << "please, enter the condition(1 for high signal level, "
            << "0 for low signal level, anything else for X)"
            << std::endl << "Of connection #" << (i + 1)
            << " of type " << (cs[i].type == IN ? "INPUT:" : "OUTPUT:") << std::endl;
            do{
                rc = get_number(c);
                if(rc == 1) break;
                if(!rc) return *this;  // eof TODO any eof measures?
                std::cout << "incorrect input, please, try again:";
            }while(rc < 0);

            switch(c){
                case 0:
                    set_conn_state(i, 0);
                    break;
                case 1:
                    set_conn_state(i, 1);
                    break;
                default:
                    set_conn_state(i, 2);
                   break;
            }
        }
        return *this;
    }

    void element::get_conns() const { //TODO: large method, split - ?
        std::cout << "info about all existing connections:" << std::endl;

        for(int i = 0; i < this->conns; ++i){
            std::cout << "connection #" << (i+1) << ":" << std::endl
            << "Condition: ";
            switch(cs[i].condition){
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

            std::cout << "type: ";
            switch(cs[i].type){
                case 0:
                    std::cout << "INPUT; ";
                    break;
                case 1:
                    std::cout << "OUTPUT; ";
                    break;
                default:        //TODO: NB! delete this after debugging, useless
                    std::cout << "NOT DEFINED; ";
                    break;
            }

            std::cout << "connected to elements:";
            for(int j = 0; j < 3; ++j){
                if(cs[i].sockets[j] != -1){
                    std::cout << " " << (cs[i].sockets[j] + 1);
                }
            }
            std::cout << std::endl << std::endl;
        }
    }

    element &element::set_conn_state(int number, int new_state) {
        if(number < 0 || number >= connections_max)
            throw std::runtime_error("invalid connection index");
        if(cs[number].type == IM)
            throw std::runtime_error("there is no such connection");
        bool lonely = true;
        for(int i = 0; i < 3; ++i){
            if(cs[number].sockets[i] != -1){
                lonely = false;
                break;
            }
        }
        if(lonely)
            throw std::runtime_error("only X state permitted for lonely connections");

        switch(new_state){
            case 0:
                cs[number].condition = LOW;
                break;
            case 1:
                cs[number].condition = HIGH;
                break;
            default:
                cs[number].condition = X;
                break;
        }
        return *this;
    }

    int element::get_conn_state(int number) const {
        if(number < 0 || number >= connections_max)
            throw std::runtime_error("invalid connection index");
        if(cs[number].type == IM)
            throw std::runtime_error("there is no such connection");
        return cs[number].condition;
    }

    element &element::connect_conn(int which, int whereto) {
        if(which < 0 || which >= connections_max)  //TODO: refactor this
            throw std::runtime_error("invalid connection index");
        if(cs[which].type == IM)
            throw std::runtime_error("there is no such connection");
        if(whereto < 0 || whereto >= connections_max)
            throw std::runtime_error("invalid connection index");
        if(cs[whereto].type == IM)
            throw std::runtime_error("there is no such connection");

        if(cs[which].type == IN){
            if(cs[which].sockets[0] != -1)
                throw std::runtime_error("this connection is busy! disconnect it first!");
            else
                cs[which].sockets[0] = whereto;
        } else{
            for(int i = 0; i < 3; ++i){
                if(cs[which].sockets[i] == -1){
                    cs[which].sockets[i] = whereto;
                    break;
                }
                if(i == 2)
                    throw std::runtime_error("this connection is busy! disconnect it first!");
            }
        }
        return *this;
    }


}
