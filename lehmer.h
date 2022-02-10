//
// Created by Bruger on 08-02-2022.
//

#ifndef STP_LEHMER_H
#define STP_LEHMER_H


class lehmer {
private:
    unsigned int state;
public:
    unsigned int operator()();
    static unsigned int min();
    static unsigned int max();
};


#endif //STP_LEHMER_H
