//
// Created by antony on 9/29/19.
//

#ifndef CPPLAB3_ELEMENT_H
#define CPPLAB3_ELEMENT_H

#include <iostream>
#include <csignal>

namespace cpplab3v13{

    const char *messages[] = {"0. Quit                ",
                              "1. Add connection",
                              "2. Delete connection",
                              "3. Print info",
                              "4. Disconnect something",
                              "5. Connect something",
                              "6. total state change"};

    const int NMsgs = sizeof(messages)/sizeof(messages[0]);

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
        if (!std::cin.good()){
            std::cin.clear();
            std::cin.ignore(100, '\n');
            return -1; // ошибка ввода
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

        void get_conns() const;    //selectors
        int get_conn_state(int number) const;

        element& total_reorg();    // modificators
        element& set_conn_state(int number, int new_state);
        element& connect_conn(int which, int whereto);
        element& disconnect_conn(int which, int disconn_id);
        element& add_conn(connection newcomer);
        element& delete_conn(int which);

    };
}

#endif //CPPLAB3_ELEMENT_H
