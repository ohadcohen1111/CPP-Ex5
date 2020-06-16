#pragma once
#include <iostream>
using namespace std;

namespace itertools{
    template <typename container1, typename container2>
    class compress{
        container1 cont1;
        container2 cont2;
    public:
        compress(container1 co1, container2 co2): cont1(co1), cont2(co2){}

        class iterator{
            typename container1::iterator a;
            typename container2::iterator b;
            typename container1::iterator it_end;
        public:
            iterator(typename container1::iterator _a,typename container2::iterator _b, typename container1::iterator end)
            : a(_a), b(_b), it_end(end){}

            bool operator==(const iterator &it) const 
            {
                return a == it.a;
            }

            bool operator!=(const iterator &it) const 
            {
                return a != it.a;
            }

            iterator &operator++(){
            a++;
            b++;
            while (a != it_end && !(*b))
            {
            a++;
            b++;
            }
            return *this;
            }

            const iterator operator++(int){
            iterator temp = *this;
            ++(*this);
            return temp;
            }

            decltype(*(cont1.begin())) operator*(){
            if(!(*b)) ++(*this);
            return *a;
            }
        };

        iterator begin(){
        return iterator(cont1.begin(),cont2.begin(),cont1.end());
        }

        iterator end(){
        return iterator(cont1.end(),cont2.begin(),cont1.end());
        }
    };
}