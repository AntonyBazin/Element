//
// Created by antony on 9/29/19.
//

#ifndef CPPLAB3_ELEMENT_H
#define CPPLAB3_ELEMENT_H

#include <iostream>

namespace cpplab3v13{

    enum conditions{LOW, HIGH, X};
    enum types{IN, OUT, IM};

    struct connection{
        types type;
        int sockets[3];
        conditions condition;
        connection(){
            type = IM;
            condition = X;
            for(int & socket : sockets){  //TODO: ask
                socket = -1;
            }
        }
    };

    template <class T>
    int get_number(T &a){
        std::cin >> a;
        if (!std::cin.good()) // ошибка ввода/конец файла
            if(std::cin.eof()) return 0;
            return -1;
        return 1;
    }

    class element{
    private:
        static const int connections_max = 10;
        int conns;
        connection cs[connections_max];
    public:
        explicit element();
        element(int in, int out);
        element(connection* arr, int sum);

        void get_conns() const;    //selectors

        element& total_reorg();    // modificators
        element& set_conn(int number);
        element& connect_conn(int which, int amount);
        element& disconnect_conn(int which, int amount);
        element& add_conn(connection newcomer);

    };
}

#endif //CPPLAB3_ELEMENT_H
