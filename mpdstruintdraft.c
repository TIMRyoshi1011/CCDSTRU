#include <stdio.h>
#include <string.h>

typedef char boolean[6];

int main() {

    /*Applicable Sets*/
    int A[4] = {1, 2, 3, 4};
    int i, j;
    int P[16];

    for (i = 0; i < 4; i++) 
        for (j = 0; j < 4; j++) 
            P[i] = A[i] * A[j];

    boolean B[2] = {"true", "false"};
     
    int C[4][4][2] = {{{1, 1}, {1, 2}, {1, 3}, {1, 4}},
                      {{1, 1}, {2, 2}, {3, 3}, {4, 4}},
                      {{1, 4}, {2, 3}, {3, 2}, {4, 1}},
                      {{4, 1}, {4, 2}, {4, 3}, {4, 4}}};

    //Set set T

    /*System variables*/

    int uno, dos, tres, F;
    boolean turn, go, over;

    /*System Facts*/

    /*System Initialization*/
    uno = 0;
    dos = 0;
    tres = 0;

    turn[1] = B[0];
    go[1] = B[1];

    return 0;
}