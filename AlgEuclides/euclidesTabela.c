#include <stdio.h>
#include <string.h>

int main(){
    int euclidesTable[10][4];
    int q, r0, r1, s, t, aux;
    q = r0 = r1 = s = t = 0;
    
    memset(euclidesTable, -1, sizeof(euclidesTable));
    scanf("%d %d", &euclidesTable[0][1], &euclidesTable[1][1]);
    euclidesTable[0][2] = 1; euclidesTable[0][3] = 0;
    euclidesTable[1][2] = 0; euclidesTable[1][3] = 1;
    
    int i = 2;
    while(euclidesTable[i-1][1] != 1 && euclidesTable[i-1][1] != 0){
        //qi
        euclidesTable[i][0] = euclidesTable[i-2][1] / euclidesTable[i-1][1];
        //ri
        euclidesTable[i][1] = euclidesTable[i-2][1] % euclidesTable[i-1][1];
        
        //si
        euclidesTable[i][2] = euclidesTable[i-2][2] - (euclidesTable[i-1][2] * euclidesTable[i][0]);
        //ti
        euclidesTable[i][3] = euclidesTable[i-2][3] - (euclidesTable[i-1][3] * euclidesTable[i][0]);
        
        i++;
    }

    for(int i=0; i<10; i++){
        for(int j=0; j<4; j++){
            printf("%d ", euclidesTable[i][j]);
        }
        printf("\n");
    }

}