#pragma once
#include <iostream>
using namespace std;

namespace itertools{
    template <typename container, typename lambda>
    class filterfalse{
        container cont;
        lambda condition;
    public:
        filterfalse(lambda co, container c): cont(c), condition(co){}

        class iterator{
            typename container::iterator it_begin;
            typename container::iterator it_end;
            lambda condition;
        public:
            iterator(typename container::iterator begin,typename container::iterator end,lambda co)
            : it_begin(begin), it_end(end), condition(co){}

            bool operator==(const iterator &it) const 
            {
                return it_begin == it.it_begin;
            }

            bool operator!=(const iterator &it) const 
            {
                return it_begin != it.it_begin;
            }

            iterator &operator++(){
            ++it_begin;
            while (it_begin != it_end && condition(*it_begin))
            {
            it_begin++;
            }
            return *this;
            }

            const iterator operator++(int){
            iterator temp = *this;
            ++(*this);
            return temp;
            }

            decltype(*(cont.begin())) operator*(){
            if(condition(*it_begin)) ++(*this);
            return *it_begin;
            }
        };

        iterator begin(){
        return iterator(cont.begin(),cont.end(),this->condition);
        }

        iterator end(){
        return iterator(cont.end(),cont.end(),this->condition);
        }
    };

}