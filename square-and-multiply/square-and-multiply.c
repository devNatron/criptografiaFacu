#include <stdio.h>

unsigned long long int maskBit[64];

void inicializacaoMaskBit(){
  maskBit[63] = 1;
  for(int i = 62; i >= 0; i--){
    maskBit[i] = maskBit[i+1] * 2;
  }
}

int main(){
    inicializacaoMaskBit();
    int x, h, n;
    int bitAtual;
    unsigned long long int resultado;
    scanf("%d %d %d", &x, &h, &n);

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

    printf("%d ^ %d mod %d = %llu", x, h, n, resultado);
    return 0;
}