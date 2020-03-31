/*
Nome: José Vitor Novaes Santos RA: 743556
*/

#include <stdio.h>
#include <string.h>

unsigned long long int maskBit[64];

void inicializacaoMaskBit(){
  maskBit[63] = 1;
  for(int i = 62; i >= 0; i--){
    maskBit[i] = maskBit[i+1] * 2;
  }
}

int euclidean(int q, int resto);
int extendedEuclidean(int r0, int r1);
int eulersPhi(int m);
unsigned long long int sam(int x, int h, int n);

int main(){
    inicializacaoMaskBit();
    int n,e,c;
    int phi = 0;
    int d = 0;
    unsigned long long int mensagem = 0;

    scanf("%d %d %d", &n, &e, &c);

    phi = eulersPhi(n);
    d = extendedEuclidean(phi, e);
    
    //caso a chave seja negativa
    if(d < 0){
        d = phi + d;
    }
    
    mensagem = sam(c, d, n);
    
    //printf("phi(n): %d\npKey: %d\ndecrypt: %llu\n", phi, d, mensagem);
    printf("%llu\n", mensagem);
    return 0;
}

int extendedEuclidean(int r0, int r1){
    int q, t0, t1, aux;
    q = t0 = t1 = 0;

    t0 = 0;
    t1 = 1;
    
    int i = 2;
    while(r1 > 1){        
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
    return t1;
}

int euclidean(int q, int resto){
    int aux;
    
    int i = 2;
    while(resto > 0){        
        aux = resto;
        resto = q % resto; //ri
        q = aux;

        i++;
    }
    return q;
}

int eulersPhi(int m){
    int gcd = 0; 
    int phi = 0;
    for(int i=0; i<m; i++){
        gcd = euclidean(m, i);

        if(gcd == 1){
            phi++;
        }
    }
    return phi;
}



unsigned long long int sam(int x, int h, int n){
    int bitAtual;
    unsigned long long int resultado;

    resultado = x;
    int i=32;
    for(;i < 64; i++){
        bitAtual = h & maskBit[i];
        if(bitAtual){
            break;
        }
    }

    i++; // i = t-1, onde t é o primeiro bit 1 mais significativo;
    for(; i < 64; i++){
        bitAtual = h & maskBit[i];
        resultado = ( (resultado * resultado) % n);

        if(bitAtual == maskBit[i]){
            resultado = ( (resultado * x) % n);
        }
    } 

    //printf("%d ^ %d mod %d = %llu\n", x, h, n, resultado);
    return resultado;
}