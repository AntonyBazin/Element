//
// Created by antony on 10/7/19.
//

#ifndef CPPLAB3_RUN_H
#define CPPLAB3_RUN_H

#include "element.h"

namespace cpplab3v13{

    void signal_handler(int signal){
        if (signal == SIGINT) {
            std::cerr << "SIGINT принят\n";
        } else {
            std::cerr << "Unexpected signal: " << signal << "\n";
        }
        std::_Exit(EXIT_SUCCESS);
    }

    int run(connection *ptr);

    int run(connection *ptr) {
        element elem(ptr, 5);

        while(true){
            int a, b, rc;
            connection con;
            auto previous_handler = signal(SIGINT, signal_handler);
            if (previous_handler == SIG_ERR) {
                std::cerr << "Signal set failed!\n";
                return EXIT_FAILURE;
            }

            for(int i = 0; i < NMsgs; ++i) {
                std::cout << (messages[i]);
            }

            std::cout << "Please, input action index:";

            do{
                rc = get_number(a);
                if(rc == 1) break;
                if(!rc) return 0;
                std::cout << "incorrect input, please, try again:";
            }while(rc < 0);

            switch(a) {
                case 0:
                    return 0;
                case 1:
                    std::cout << "Input connection\'s type(0 for in, else for out):"
                              << std::endl;

                    do{
                        rc = get_number(b);
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
                    break;
                case 2:
                    std::cout << "Input connection index to delete:" << std::endl;

                    do{
                        rc = get_number(b);
                        if(rc == 1) break;
                        if(!rc) return 0;
                        std::cout << "Incorrect input, please, try again:";
                    }while(rc < 0);

                    try{
                        elem.delete_conn(b);
                    } catch(std::runtime_error &rt){
                        std::cout << rt.what() << std::endl;
                    }

                    break;
                case 3:
                    elem.get_conns();
                    break;
                case 4:
                    std::cout << "Input connection index to disconnect:" << std::endl;
                    do{
                        rc = get_number(a);
                        if(rc == 1) break;
                        if(!rc) return 0;
                        std::cout << "Incorrect input, please, try again:";
                    }while(rc < 0);

                    std::cout << "Input target connection index:" << std::endl;
                    do{
                        rc = get_number(b);
                        if(rc == 1) break;
                        if(!rc) return 0;
                        std::cout << "Incorrect input, please, try again:";
                    }while(rc < 0);

                    try{
                        elem.disconnect_conn(a, b);
                    } catch(std::runtime_error &rt){
                        std::cout << rt.what() << std::endl;
                    }
                    break;
                case 5:
                    std::cout << "Input connection index to connect:" << std::endl;
                    do{
                        rc = get_number(a);
                        if(rc == 1) break;
                        if(!rc) return 0;
                        std::cout << "Incorrect input, please, try again:";
                    }while(rc < 0);

                    std::cout << "Input target connection index:" << std::endl;
                    do{
                        rc = get_number(b);
                        if(rc == 1) break;
                        if(!rc) return 0;
                        std::cout << "Incorrect input, please, try again:";
                    }while(rc < 0);

                    try{
                        elem.connect_conn(a, b);
                    } catch(std::runtime_error &rt){
                        std::cout << rt.what() << std::endl;
                    }
                    break;
                case 6:
                    elem.total_reorg();
                    break;
                case 7:
                    std::cout << "Input connection index to get info about:" << std::endl;
                    do{
                        rc = get_number(b);
                        if(rc == 1) break;
                        if(!rc) return 0;
                        std::cout << "Incorrect input, please, try again:";
                    }while(rc < 0);
                    elem.get_conn_state(b);
                    break;
                default:
                    std::cout << "unexpected command index!" << std::endl;
                    break;
            }

        }
    }
}
#endif //CPPLAB3_RUN_H
