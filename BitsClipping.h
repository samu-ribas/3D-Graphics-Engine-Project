#ifndef BITSCLIPPING_H
#define BITSCLIPPING_H
#include<bitset>
#include<vector>

class BitsClipping{
public:
    std::vector<std::bitset<4>> vetorBits;

    BitsClipping(): vetorBits(5){
        vetorBits[0] = 0b0000;
        vetorBits[1] = 0b0001;
        vetorBits[2] = 0b0010;
        vetorBits[3] = 0b0100;
        vetorBits[4] = 0b1000;
    }
};

#endif // BITSCLIPPING_H
