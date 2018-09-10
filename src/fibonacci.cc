//
// Created by aknight on 7/18/18.
//

#include "fibonacci.h"

namespace edu { namespace sbcc { namespace cs140 {

    uint64_t fibonacci(uint64_t i) {
        uint64_t number = 0;
        for (uint64_t index = 0, hold, previous = 0; index <= i; index++) {
            if (index == 0) continue;
            if (index == 1) {
                number = 1;
                continue;
            }
            hold = number;
            number += previous;
            previous = hold;
        }
        return number;
    }

}}}