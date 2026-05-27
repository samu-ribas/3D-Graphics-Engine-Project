#ifndef BITSCLIPPING_H
#define BITSCLIPPING_H
#include<bitset>
#include<vector>

class BitsClipping{
public:
    std::vector<std::bitset<4>> vetorBits;

    BitsClipping(): vetorBits(9){
        vetorBits[0]= 0b1001 ; vetorBits[3]= 0b1000 ; vetorBits[6] = 0b1010 ;
        vetorBits[1]= 0b0001 ; vetorBits[4]= 0b0000 ; vetorBits[7] = 0b0010 ;
        vetorBits[2]= 0b0101 ; vetorBits[5]= 0b0100 ; vetorBits[8] = 0b0110 ;
    }
};

#endif // BITSCLIPPING_H
