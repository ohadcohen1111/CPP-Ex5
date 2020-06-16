#pragma once
namespace itertools {
    class range {
        int start;
        int finish;
    public:
        range(int s, int f) : start(s), finish(f) {}

        class iterator {
            int current;
        public:
            iterator(int c = 0) : current(c) {}

            iterator &operator++() {
                current = current + 1;
                return *this;
            }

            const iterator operator++(int) {
                iterator temp = *this;
                ++current;
                return temp;
            }

            bool operator==(const iterator &it) const {
                return current == it.current;
            }

            bool operator!=(const iterator &it) const {
                return current != it.current;
            }

            int operator*(){
                return current;
            }

        };

        iterator begin() {
            return iterator(start);
        }

        iterator end() {
            return iterator(finish);
        }

    };
}