//
// Created by antony on 9/29/19.
//

#ifndef CPPLAB3_ELEMENT_H
#define CPPLAB3_ELEMENT_H

#include <iostream>

namespace cpplab3v13{

    enum conditions{LOW, HIGH, X};

    struct connection{
        bool type;
        int sockets[3];
        conditions condition;
    };

    struct connections{
        connection c;
        connections *next;
    };

    class element{
    private:
        static const int connections_amount = 10;
        int conns;
        connection cs[connections_amount];
    public:
        explicit element(int c) :conns(c){};
        element(int in, int out);
        element(connection* arr, int sum);

        element& reorg();
        element& set_conn(int number);
        element& connect_conn(int which, int amount);
        element& disconnect_conn(int which, int amount);
        element& add_conn(connection newcomer);

        connections* get_conns() const;
        connection get_conn(int number) const;

    };
}

#endif //CPPLAB3_ELEMENT_H
