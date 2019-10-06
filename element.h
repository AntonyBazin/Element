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
        if(std::cin.eof()) return 0;    // конец файла
        if (!std::cin.good()) return -1; // ошибка ввода
        return 1;
    }

    class element{
    private:
        static const int connections_max = 10;
        int conns;
        connection cs[connections_max];
    public:
        //element();
        explicit element(int in = 1, int out = 1);
        element(connection* arr, int sum);

        void get_conns() const;    //selectors
        int get_conn_state(int number) const;

        element& total_reorg();    // modificators
        element& set_conn_state(int number, int new_state);
        element& connect_conn(int which, int amount);
        element& disconnect_conn(int which, int amount);
        element& add_conn(connection newcomer);

    };
}

#endif //CPPLAB3_ELEMENT_H
