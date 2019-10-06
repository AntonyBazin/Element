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

    element &element::total_reorg() {
        int c, rc;
        for(int i = 0; i < this->conns; ++i){
            std::cout << "please, enter the condition(1 for high signal level, "
            << "0 for low signal level -1 for X) of connection #" << (i + 1)
            << " of type " << (cs[i].type == IN ? "INPUT" : "OUTPUT") << std::endl;
            do{
                std::cin >> c;
                rc = std::cin.good();
                if(rc == 1) break;
                if(!rc) return *this;
                std::cout << "incorrect input, please, try again:";
            }while(rc < 0);

            switch(c){
                case 1:
                    cs[i].condition = HIGH;
                    break;
                case 0:
                    cs[i].condition = LOW;
                    break;
                default:
                   cs[i].condition = X;
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
                case 1:
                    std::cout << "HIGH; ";
                    break;
                case 0:
                    std::cout << "LOW; ";
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

        }
    }


}
