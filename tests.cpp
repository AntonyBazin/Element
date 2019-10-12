//
// Created by antony on 10/7/19.
//

#include <gtest/gtest.h>
#include "element.h"


TEST(element_construtor, element_construtor_default_constructor__Test){
    cpplab3v13::element elem;
    ASSERT_NO_THROW(elem.get_conn(0));
    ASSERT_NO_THROW(elem.get_conn(1));
    cpplab3v13::connection c1 = elem.get_conn(0), c2  = elem.get_conn(1);
    ASSERT_EQ(c1.condition, cpplab3v13::X);
    ASSERT_EQ(c2.condition, cpplab3v13::X);
    ASSERT_EQ(c1.type, cpplab3v13::IN);
    ASSERT_EQ(c2.type, cpplab3v13::OUT);

    ASSERT_THROW(elem.set_conn_state(0, 1),
            std::runtime_error);
    ASSERT_THROW(elem.set_conn_state(1, 1),
                 std::runtime_error);

    for(int i = 0; i < 3; ++i){
        ASSERT_EQ(c1.sockets[i], -1);
        ASSERT_EQ(c2.sockets[i], -1);
    }
}

TEST(element_construtor, element_construtor_init_constructor1__Test){
    const cpplab3v13::element elem(2);
    ASSERT_NO_THROW(elem.get_conn(0));
    ASSERT_NO_THROW(elem.get_conn(1));
    ASSERT_NO_THROW(elem.get_conn(2));

    cpplab3v13::connection c1 = elem.get_conn(0),
            c2 = elem.get_conn(1),
            c3 = elem.get_conn(2);
    ASSERT_EQ(c1.condition, cpplab3v13::X);
    ASSERT_EQ(c2.condition, cpplab3v13::X);
    ASSERT_EQ(c3.condition, cpplab3v13::X);
    ASSERT_EQ(c1.type, cpplab3v13::IN);
    ASSERT_EQ(c2.type, cpplab3v13::IN);
    ASSERT_EQ(c3.type, cpplab3v13::OUT);

    for(int i = 0; i < 3; ++i){
        ASSERT_EQ(c1.sockets[i], -1);
        ASSERT_EQ(c2.sockets[i], -1);
        ASSERT_EQ(c3.sockets[i], -1);
    }
}

TEST(element_construtor, element_construtor_init_constructor2__Test){
    cpplab3v13::element elem(2, 2);
    ASSERT_NO_THROW(elem.get_conn(0));
    ASSERT_NO_THROW(elem.get_conn(1));
    ASSERT_NO_THROW(elem.get_conn(2));
    ASSERT_NO_THROW(elem.get_conn(3));

    cpplab3v13::connection c1 = elem.get_conn(0),
            c2 = elem.get_conn(1),
            c3 = elem.get_conn(2),
            c4 = elem.get_conn(3);
    ASSERT_EQ(c1.condition, cpplab3v13::X);
    ASSERT_EQ(c2.condition, cpplab3v13::X);
    ASSERT_EQ(c3.condition, cpplab3v13::X);
    ASSERT_EQ(c4.condition, cpplab3v13::X);
    ASSERT_EQ(c1.type, cpplab3v13::IN);
    ASSERT_EQ(c2.type, cpplab3v13::IN);
    ASSERT_EQ(c3.type, cpplab3v13::OUT);
    ASSERT_EQ(c4.type, cpplab3v13::OUT);

    for(int i = 0; i < 3; ++i){
        ASSERT_EQ(c1.sockets[i], -1);
        ASSERT_EQ(c2.sockets[i], -1);
        ASSERT_EQ(c3.sockets[i], -1);
        ASSERT_EQ(c4.sockets[i], -1);
    }
}

TEST(element_construtor, element_construtor_init_constructor3__Test){
    auto *ptr = new cpplab3v13::connection[7];
    for(int i = 0; i < 5; ++i){
        ptr[i].type = i < 2 ? cpplab3v13::IN : cpplab3v13::OUT;
    }
    cpplab3v13::element elem(ptr, 5);
    delete [] ptr;
    for(int i = 0; i < 5; ++i){
        ASSERT_NO_THROW(elem.get_conn(i));
        cpplab3v13::connection c1 = elem.get_conn(i);
        ASSERT_EQ(c1.condition, cpplab3v13::X);
        for(int j = 0; j < 3; ++j){
            ASSERT_EQ(c1.sockets[j], -1);
        }
    }
}

TEST(setters, setters_connect_conn_Test){
    cpplab3v13::element elem;
    elem.connect_conn(0, 1);
    ASSERT_NO_THROW(elem.set_conn_state(0, 1));
    ASSERT_NO_THROW(elem.set_conn_state(1, 1));
    ASSERT_THROW(elem.set_conn_state(100, 1),
                 std::runtime_error);
    ASSERT_THROW(elem.set_conn_state(-5, 1),
                 std::runtime_error);

}

TEST(setters, setters_set_conn_state__Test){
    cpplab3v13::element elem;
    elem.connect_conn(0, 1);
    elem.set_conn_state(0, 1);
    elem.set_conn_state(1, 0);
    ASSERT_EQ(elem.get_conn_state(0), cpplab3v13::HIGH);
    ASSERT_EQ(elem.get_conn_state(1), cpplab3v13::LOW);
}

TEST(setters, setters_disconnect_conn_Test){
    cpplab3v13::element elem;
    elem.connect_conn(0, 1);
    ASSERT_THROW( elem.disconnect_conn(-1, 1),
                 std::runtime_error);
    ASSERT_THROW( elem.disconnect_conn(0, -1),
                  std::runtime_error);
    ASSERT_THROW( elem.disconnect_conn(100, 1),
                  std::runtime_error);
    ASSERT_THROW( elem.disconnect_conn(0, 100),
                  std::runtime_error);
    elem.disconnect_conn(0, 1);
    ASSERT_THROW(elem.set_conn_state(0, 1),
            std::runtime_error);
    ASSERT_THROW(elem.set_conn_state(1, 1),
            std::runtime_error);
    ASSERT_EQ(elem.get_conn_state(0), cpplab3v13::X);
    ASSERT_EQ(elem.get_conn_state(1), cpplab3v13::X);
    for(int i = 0; i < 3; ++i){
        ASSERT_EQ(elem.get_conn(0).sockets[i], -1);
        ASSERT_EQ(elem.get_conn(1).sockets[i], -1);
    }
}

TEST(setters, setters_add_conn_Test){
    cpplab3v13::element elem;
    elem.connect_conn(0, 1);
    cpplab3v13::connection con1;
    con1.type = cpplab3v13::IN;
    elem.add_conn(con1);
    ASSERT_THROW(elem.set_conn_state(2, 1),
                 std::runtime_error);
    ASSERT_THROW(elem.connect_conn(0, 2),
            std::runtime_error);
    cpplab3v13::connection con2;
    con2.type = cpplab3v13::OUT;
    elem.add_conn(con2);
    ASSERT_THROW(elem.connect_conn(0, 3),
                 std::runtime_error);
    ASSERT_THROW(elem.connect_conn(1, 3),
                 std::runtime_error);
}

TEST(setters, setters_delete_conn_Test){
    cpplab3v13::element elem;
    elem.connect_conn(0, 1);
    cpplab3v13::connection con1, con2;
    con1.type = cpplab3v13::IN;
    con2.type = cpplab3v13::OUT;
    elem.add_conn(con1);
    elem.add_conn(con2);
    ASSERT_THROW(elem.disconnect_conn(-1, 3),
                 std::runtime_error);
    ASSERT_THROW(elem.connect_conn(100, 3),
                 std::runtime_error);
    elem.delete_conn(3);
    ASSERT_THROW(elem.connect_conn(0, 3),
                 std::runtime_error);

}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}