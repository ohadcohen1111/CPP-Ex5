
#include "doctest.h"
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"

using namespace itertools;
using namespace std;

template <typename T>
bool equals(T a, T b){ return a == b;}
struct lessThan3 {
    bool operator()(int i) const { return i < 3; }
};
vector<int> vecInt = {1,2,3,4,5,6,7,8,9,10};
vector<string> vecString = {"Hello", "Bye", "Adam"};

TEST_CASE("range"){
    int j = 0;
    for(int i : range(0,20)){
        CHECK(i == j++);
    }
}

TEST_CASE("accumulate"){
    for (int i: accumulate(range(5,20)))
    {
	CHECK(i >= 5);
    CHECK (i != 0);
    CHECK(i <= 180);
    }
    accumulate vec =accumulate(vecString);
    accumulate<vector<string>>::iterator it1 = vec.begin();
    CHECK(equals(*it1,string("Hello")));
    CHECK(equals(*(++it1),string("HelloBye")));
    CHECK(equals(*(++it1),string("HelloByeAdam")));
    for (auto i: accumulate(vecString))
    CHECK(i != "");
    for (int i: accumulate(range(5,9), [](int x, int y){return x*y;}))
    {
    CHECK(i >= 5);
    CHECK(i != 0);
    CHECK(i <= 1680);
    }

    for (int i: accumulate(range(1,10)))
    CHECK(i>0);
    auto lam =[](int x, int y){return x*y;}; 
    accumulate a =accumulate(range(1,10),lam);
    accumulate<range,decltype(lam)>::iterator it = a.begin();
    CHECK((*it) == 1);
    CHECK(*(++it) == 2);
    CHECK(*(++it)== 6);
    CHECK(*(++it)== 24);
    CHECK(*(++it)== 120);
    CHECK(*(++it)== 720);
    CHECK(*(++it)== 5040);
    CHECK(*(++it)== 40320);
    CHECK(*(++it)== 362880);
}

TEST_CASE("filterfalse"){
    for (auto i: filterfalse(lessThan3{}, vecInt))
    {
        CHECK(i >= 3);
        CHECK(i <= 10);
    }
    for (auto i: filterfalse([](int i){return i%2==0;}, range(5,20)) )
    {
        CHECK(i%2 != 0);
        CHECK(i > 0);
    }
}


TEST_CASE("accumulate of string vector"){
    vector<string> v = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
    accumulate a =accumulate(v);
    accumulate<vector<string>>::iterator it1 = a.begin();
    CHECK((*it1)== string("a"));
    CHECK(*(++it1)== string("ab"));
    CHECK(*(++it1)== string("abc"));
    CHECK(*(++it1)== string("abcd"));
    CHECK(*(++it1)== string("abcde"));
    CHECK(*(++it1)== string("abcdef"));
    CHECK(*(++it1)== string("abcdefg"));
    CHECK(*(++it1)== string("abcdefgh"));
    CHECK(*(++it1)== string("abcdefghi"));
}