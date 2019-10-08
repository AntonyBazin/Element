//
// Created by antony on 10/7/19.
//

#include <gtest/gtest.h>
#include "element.h"


TEST(element_construtor, default_constructor){
    const cpplab3v13::element elem;
    ASSERT_NO_THROW(elem.get_conn(0));
    ASSERT_NO_THROW(elem.get_conn(1));
    cpplab3v13::connection c1 = elem.get_conn(0), c2  = elem.get_conn(1);
    ASSERT_EQ(c1.condition, cpplab3v13::X);
    ASSERT_EQ(c2.condition, cpplab3v13::X);
    ASSERT_EQ(c1.type, cpplab3v13::IN);
    ASSERT_EQ(c2.type, cpplab3v13::OUT);

    for(int i = 0; i < 3; ++i){
        ASSERT_EQ(c1.sockets[i], -1);
        ASSERT_EQ(c2.sockets[i], -1);
    }
}

TEST(element_construtor, init_constructor1){
    cpplab3v13::element elem(2);
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

TEST(element_construtor, init_constructor2){
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

TEST(element_construtor, init_constructor3){
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







int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}