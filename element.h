//
// Created by antony on 9/29/19.
//

#ifndef CPPLAB3_ELEMENT_H
#define CPPLAB3_ELEMENT_H
#pragma once

#include <iostream>
#include <csignal>

namespace cpplab3v13{

    int dialog();
    void signal_handler(int);

    enum conditions{LOW, HIGH, X};
    enum types{IN, OUT, IM};

    struct connection{
        types type;
        int sockets[3];
        conditions condition;
        connection(){
            type = IM;
            condition = X;
            for(int & socket : sockets){
                socket = -1;
            }
        }
    };

    template <class T>
    int input_number(T &a, std::istream& stream){
        auto previous_handler = std::signal(SIGINT, signal_handler);
        if (previous_handler == SIG_ERR) {
            std::cerr << "Установка сигнала неудачна\n";
            return EXIT_FAILURE;
        }
        stream >> a;
        if(stream.eof()) return 0;    // eof
        if (!stream.good()){
            stream.clear();
            stream.ignore(100, '\n');
            return -1; // input error
        }
        return 1;
    }

    class element{
    private:
        static const int connections_max = 10;
        int conns;
        connection cs[connections_max];
    public:
        explicit element(int in = 1, int out = 1);
        element(connection* arr, int sum);

        void print_conns() const;   //TODO add stream&
        int get_conn_state(int number) const;   //selectors
        connection get_conn(int number) const;

        element& total_reorg(); //for overloading   //modificators
        element& set_conn_state(int number, int new_state);
        element& connect_conn(int which, int whereto);
        element& disconnect_conn(int which);
        element& add_conn(connection newcomer);
        element& delete_conn(int which);
    };

    int d_add_conn(element&),
        d_del_conn(element&),
        d_show_all(element&),
        d_disconnect_conn(element&),
        d_connect_conn(element&),
        d_change_all_states(element&),
        d_print_conn_state(element&),
        d_set_conn_state(element&);
}

#endif //CPPLAB3_ELEMENT_H
