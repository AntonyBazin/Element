//
// Created by antony on 9/29/19.
//

#include "element.h"

namespace cpplab3v13{

    const char *messages[] = {"0. Quit                ",
                              "1. Add connection",
                              "2. Delete connection",
                              "3. Print info",
                              "4. Disconnect something",
                              "5. Connect something",
                              "6. Total state change",
                              "7. Get connection info",
                              "8. Set connection state"};

    const int NMsgs = sizeof(messages)/sizeof(messages[0]);

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
        for(int i = 0; i < sum; ++i){
            if(arr[i].type == IM) arr[i].type = IN;
            for(int j = 0; j < 3; ++j){
                arr[i].sockets[j] = -1;
            }
            add_conn(arr[i]);
        }
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

            bool lonely = true;
            for(int j = 0; j < 3; ++j){
                if(cs[i].sockets[j] != -1){
                    lonely = false;
                    break;
                }
            }
            if(lonely) continue;

            std::cout << "please, enter the condition(1 for high signal level, "
            << "0 for low signal level, anything else for X)"
            << std::endl << "Of connection #" << (i + 1)
            << " of type " << (cs[i].type == IN ? "INPUT:" : "OUTPUT:")
            << std::endl;

            do{
                rc = input_number(c, std::cin);
                if(rc == 1) break;
                if(!rc) return *this;  // eof
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

    void element::print_conns() const {
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
                default:
                    std::cout << "IMAGINARY; ";
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
        if(which < 0 || which >= connections_max)
            throw std::runtime_error("invalid connection index");
        if(cs[which].type == IM)
            throw std::runtime_error("there is no such connection");
        if(whereto < 0 || whereto >= connections_max)
            throw std::runtime_error("invalid connection index");
        if(cs[whereto].type == IM)
            throw std::runtime_error("there is no such connection");
        if(cs[whereto].type == cs[which].type)
            throw std::runtime_error("you can\'t connect same types");

        if(cs[which].type == OUT){
            int h = which;
            which = whereto;
            whereto = h;
        }

        for(int i = 0; i < 3; ++i){
            if(cs[whereto].sockets[i] == -1){
                break;
            }
            if(i == 2)
                throw std::runtime_error("no place to plug in in target");
        }

        if(cs[which].sockets[0] != -1)
            throw std::runtime_error("this connection is busy! disconnect it first!");
        else
            cs[which].sockets[0] = whereto;

        for(int i = 0; i < 3; ++i){
            if(cs[whereto].sockets[i] == -1){
                cs[whereto].sockets[i] = which;
                break;
            }
        }

        return *this;
    }

    element &element::disconnect_conn(int which) {
        if(which < 0 || which >= connections_max)
            throw std::runtime_error("invalid connection index");
        if(cs[which].type == IM)
            throw std::runtime_error("there is no such connection");

        if(cs[which].type == IN){
            if(cs[which].sockets[0] != -1){
                for(int i = 0; i < 3; ++i){
                    if(cs[cs[which].sockets[0]].sockets[i] == which)
                        cs[cs[which].sockets[0]].sockets[i] = -1;
                }
            }
        } else{
            for(int i = 0; i < 3; ++i){ //OUT-type has 3 available sockets
                if(cs[which].sockets[i] != -1){   // find a connected socket
                    for(int j = 0; j < connections_max; ++j){ //find where to
                            cs[cs[which].sockets[i]].sockets[0] = -1; //OUT can only be connected to IN
                    } //and IN has only one available socket
                }
            }
        }

        return *this;
    }

    element &element::delete_conn(int which) {
        if(which < 0 || which >= connections_max)
            throw std::runtime_error("invalid connection index");
        if(cs[which].type == IM)
            throw std::runtime_error("there is no such connection");
        for(int i = 0; i < conns; ++i){
            for(int j = 0; j < 3; ++j){
                if(cs[i].sockets[j] == which)
                    cs[i].sockets[j] = -1;
            }
        }
        cs[which] = cs[--conns];
        cs[conns].type = IM;
        cs[conns].condition = X;
        for(int i = 0; i < 3; ++i){
            if(cs[which].sockets[i] != -1){
                for(int j = 0; j < 3; ++j){
                    if(cs[cs[which].sockets[i]].sockets[j] == conns){
                        cs[cs[which].sockets[i]].sockets[j] = which;
                    }
                }

            }
        }
        return *this;
    }

    connection element::get_conn(int number) const {
        if(number < 0 || number >= connections_max)
            throw std::runtime_error("invalid connection index");
        return cs[number];
    }

    conditions& element::operator[](int index) {
        if(index < 0 || index >= connections_max)
            throw std::runtime_error("invalid connection index");
        if(cs[index].type == IM)
            throw std::runtime_error("there is no such connection");
        return cs[index].condition;
    }

    conditions element::operator[](int index) const { //const connection
        if(index < 0 || index >= connections_max)
            throw std::runtime_error("invalid connection index");
        if(cs[index].type == IM)
            throw std::runtime_error("there is no such connection");
        return cs[index].condition;
    }

    element &element::operator()(int which, int whereto) {
        if(which < 0 || which >= connections_max)
            throw std::runtime_error("invalid connection index");
        if(cs[which].type == IM)
            throw std::runtime_error("there is no such connection");
        if(whereto < 0 || whereto >= connections_max)
            throw std::runtime_error("invalid connection index");
        if(cs[whereto].type == IM)
            throw std::runtime_error("there is no such connection");
        if(cs[whereto].type == cs[which].type)
            throw std::runtime_error("you can\'t connect same types");

        if(cs[which].type == OUT){
            int h = which;
            which = whereto;
            whereto = h;
        }

        for(int i = 0; i < 3; ++i){
            if(cs[whereto].sockets[i] == -1){
                break;
            }
            if(i == 2)
                throw std::runtime_error("no place to plug in in target");
        }

        if(cs[which].sockets[0] != -1)
            throw std::runtime_error("this connection is busy! disconnect it first!");
        else
            cs[which].sockets[0] = whereto;

        for(int i = 0; i < 3; ++i){
            if(cs[whereto].sockets[i] == -1){
                cs[whereto].sockets[i] = which;
                break;
            }
        }

        return *this;
    }


    void signal_handler(int signal){
        if (signal == SIGINT) {
            std::cerr << "SIGINT received\n";
        } else {
            std::cerr << "Unexpected signal: " << signal << "\n";
        }
        std::_Exit(EXIT_SUCCESS);
    }


    int dialog(){
        char *report = (char*)"";
        int rc, i, n;
        do{
            std::cout << report << std::endl;
            report = (char*)"You are wrong. Please, try again.";
            for(i = 0; i < NMsgs; ++i) {  //print list of alternatives
                std::cout << messages[i] << std::endl;
            }
            printf("Make your choice: ~ ");
            n = input_number(rc, std::cin);  //enter number of alternative
            if(!n) rc = 0;  //EOF == end of the program
        } while(rc < 0 || rc >= NMsgs);
        return rc;
    }

    int d_add_conn(element& elem){
        int rc, b;
        connection con;

        std::cout << "Input connection\'s type(1 for in, else for out):"
                  << std::endl;

        do{
            rc = input_number(b, std::cin);
            if(rc == 1) break;
            if(!rc) return 0;
            std::cout << "Incorrect input, please, try again:";
        }while(rc < 0);

        con.type = (b == 1 ? IN : OUT);
        try {
            elem.add_conn(con);
        } catch (std::runtime_error &rt) {
            std::cout << rt.what() << std::endl;
        }
        return 1;
    }

    int d_del_conn(element& elem){
        int rc, b;

        std::cout << "Input connection id to delete:" << std::endl;

        do{
            rc = input_number(b, std::cin);
            if(rc == 1) break;
            if(!rc) return 0;
            std::cout << "Incorrect input, please, try again:";
        }while(rc < 0);

        try{
            elem.delete_conn(b - 1);
        } catch(std::runtime_error &rt){
            std::cout << rt.what() << std::endl;
        }
        return 1;
    }

    int d_show_all(element& elem){
        elem.print_conns();
        return 1;
    }

    int d_disconnect_conn(element& elem){
        int rc, a;

        std::cout << "Input connection id to disconnect:" << std::endl;
        do{
            rc = input_number(a, std::cin);
            if(rc == 1) break;
            if(!rc) return 0;
            std::cout << "Incorrect input, please, try again:";
        }while(rc < 0);

        try{
            elem.disconnect_conn(a - 1);
        } catch(std::runtime_error &rt){
            std::cout << rt.what() << std::endl;
        }
        return 1;
    }

    int d_connect_conn(element& elem){
        int rc, a, b;

        std::cout << "Input connection id to connect:" << std::endl;
        do{
            rc = input_number(a, std::cin);
            if(rc == 1) break;
            if(!rc) return 0;
            std::cout << "Incorrect input, please, try again:";
        }while(rc < 0);

        std::cout << "Input target connection id:" << std::endl;
        do{
            rc = input_number(b, std::cin);
            if(rc == 1) break;
            if(!rc) return 0;
            std::cout << "Incorrect input, please, try again:";
        }while(rc < 0);

        try{
            elem(a - 1, b - 1);
        } catch(std::runtime_error &rt){
            std::cout << rt.what() << std::endl;
        }
        return 1;
    }

    int d_change_all_states(element& elem){
        elem.total_reorg();
        return 1;
    }

    int d_print_conn_state(element& elem){
        int rc, b;

        std::cout << "Input connection id to get info about:" << std::endl;
        do{
            rc = input_number(b, std::cin);
            if(rc == 1) break;
            if(!rc) return 0;
            std::cout << "Incorrect input, please, try again:";
        }while(rc < 0);

        try{
            elem.get_conn_state(b - 1);
        } catch(std::runtime_error &rt){
            std::cout << rt.what() << std::endl;
        }
        return 1;
    }

    int d_set_conn_state(element& elem){
        int rc, b, a;

        std::cout << "Input connection id to set state:" << std::endl;
        do{
            rc = input_number(b, std::cin);
            if(rc == 1) break;
            if(!rc) return 0;
            std::cout << "Incorrect input, please, try again:";
        }while(rc < 0);
        std::cout << "Input new state(0 - low, 1 - high, else - X)" << std::endl;
        do{
            rc = input_number(a, std::cin);
            if(rc == 1) break;
            if(!rc) return 0;
            std::cout << "Incorrect input, please, try again:";
        }while(rc < 0);

        try{
            elem.set_conn_state(b - 1, a - 1);
        } catch(std::runtime_error &rt){
            std::cout << rt.what() << std::endl;
        }
        return 1;
    }

}
