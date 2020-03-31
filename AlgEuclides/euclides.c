/*
Nome: José Vitor Novaes Santos RA: 743556
*/

#include <stdio.h>
#include <string.h>

int main(){
    int q, r0, r1, t0, t1, aux;
    q = r0 = r1 = t0 = t1 = 0;
    
    scanf("%d %d", &r0, &r1);
    t0 = 0;
    t1 = 1;
    
    int i = 2;
    while(r1 > 0){        
        aux = r1;
        q = r0 / r1; //qi
        r1 = r0 % r1; //ri
        r0 = aux;

        //ti
        aux = t1;
        t1 = t0 - ( t1 * q ); //ti
        t0 = aux;

        i++;
    }
    printf("r1: %d - t1: %d\n", r1, t1);
}