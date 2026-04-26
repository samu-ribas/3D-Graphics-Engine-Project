#ifndef MATRIZ_H
#define MATRIZ_H

class matriz
{
private:
    //double valor[3][3];

public:

    matriz() {
        for ( int j = 0; j < 3; j++ )
        {
            for ( int i = 0; i < 3; i++ )
            {
                m[i][j] = 0;
            }
        }
    }

    static double *multiplicar( double m1[3][3], double m2[3][3] )
    {
        double resul[3][3];
        for ( int j = 0; j < 3; j++ )
        {
            for ( int i = 0; i < 3; i++ )
            {
                resul =
            }
        }
        return resul;
    }
};

#endif // MATRIZ_H
