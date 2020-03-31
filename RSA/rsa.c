//Autor: Jose Vitor Novaes Santos (RA:743556)
//Autor: Leonardo Seiji Nozaki (RA:743561)

#include <stdio.h>
#include <string.h>
#include <gmp.h>

void opcao1();
void gerarPrimo(mpz_t *p, mpz_t *q, int b);
void gcd(mpz_t *retorno, mpz_t r0, mpz_t r1);
int ExtendedEuclidean(mpz_t *retorno, mpz_t v0, mpz_t v1);
void opcao2();
void sam(mpz_t msg, mpz_t exp, mpz_t n);


int main(){
  int opcao;
  do{
    printf("----------Opcoes----------\n");
    printf("0 : Finalizar\n");
    printf("1 : Gerar chaves\n");
    printf("2 : Cifragem ou decifragem\n\n");
    printf("Digite a opcao desejada: ");
    scanf("%d", &opcao);
    if(opcao == 1){
      opcao1();
    }
    else if(opcao == 2){

      opcao2();
    }
    else if(opcao == 0){
      printf("Finalizando!\n");
    }
    else{
      printf("Opcao invalida\n");
    }
    printf("\n");
  } while(opcao != 0);

  return 0;
}

void opcao1(){
  mpz_t p, q, n, fiN, retorno, i, auxp, auxq, d, aux1, aux2;

  //Leitura do maximo numero de bits
  int bits = 0;
  printf("Digite o tamanho da chave desejada: ");
  scanf("%d", &bits);

  //Variaveis auxiliares
  mpz_init(p);
  mpz_init(q);
  mpz_init(n);
  mpz_init(fiN);
  mpz_init(retorno);
  mpz_init(i);
  mpz_init(auxp);
  mpz_init(auxq);
  mpz_init(d);
  mpz_init(aux1);
  mpz_init(aux2);

  //Gerar 2 primos com metade do tamanho desejado para n
  gerarPrimo(&p, &q, bits/2);

  //Calculando o valor de n
  mpz_mul(n, p, q);

  mpz_set(auxp, p);
  mpz_set(auxq, q);
  //Calculando o valor de fi(n)
  mpz_sub_ui(p, p, 1);
  mpz_sub_ui(q, q, 1);
  mpz_mul(fiN, p, q);

  mpz_set_ui(i, 2);
  while(mpz_cmp(i, fiN) < 0){
    mpz_set(aux1, i);
    mpz_set(aux2, fiN);
    gcd(&retorno, aux1, aux2);
    if(mpz_cmp_ui(retorno, 1) == 0){
      ExtendedEuclidean(&d, fiN, i);
      break;
    }
    mpz_add_ui(i, i, 1);
  }

  printf("Base: 10\n");
  gmp_printf("Modulo: %Zd\n", n);
  gmp_printf("Expoente publico: %Zd\n", i);
  gmp_printf("Expoente privado: %Zd\n", d);
  gmp_printf("Primo p: %Zd\n", auxp);
  gmp_printf("Primo q: %Zd\n", auxq);

  mpz_clear(p);
  mpz_clear(q);
  mpz_clear(n);
  mpz_clear(fiN);
  mpz_clear(retorno);
  mpz_clear(i);
  mpz_clear(auxp);
  mpz_clear(auxq);
  mpz_clear(d);
}

void opcao2(){
    char entrada[2049];
    mpz_t modulo;
    mpz_t exp;
    mpz_t mensagem;
    int base;

    //leitura da base
    scanf("%d%*c", &base);

    //leitura do n
    scanf("%[^\n]%*c", entrada);
    mpz_init(modulo);
    mpz_set_str(modulo, entrada, 10);

    //leitura da chave privada ou publica
    scanf("%[^\n]%*c", entrada);
    mpz_init(exp);
    mpz_set_str(exp, entrada, 10);

    //leitura da msg
    scanf("%[^\n]%*c", entrada);
    mpz_init(mensagem);
    mpz_set_str(mensagem, entrada, 10);

    printf("base: %d\n", base);
    sam(mensagem, exp, modulo);
}

void sam(mpz_t msg, mpz_t exp, mpz_t n){
    size_t index;
    mpz_t resultado;

    mpz_init(resultado);
    mpz_set(resultado, msg);

    index = (mpz_sizeinbase(exp, 2) - 1); //pega o numero de bits a partir do primeiro bit 1, -1 é para remover a contagem do \0
    index--;

    //anda de bit em bit realizando o quadrado e multiplicacao
    for(; index >= 0; index--){
        mpz_mul(resultado, resultado, resultado);
        mpz_mod(resultado, resultado, n);

        if(mpz_tstbit(exp, index)){ //teste o bit da posicao index e retorna se é 0 ou 1
            mpz_mul(resultado, resultado, msg);
            mpz_mod(resultado, resultado, n);
        }

        if(index == 0){
            break;
        }
    }

    gmp_printf("mensagem (de)criptografada: %Zd\n", resultado);
}

//Funcao para gerar dois primos com tamanho maximo de b bits
void gerarPrimo(mpz_t *p, mpz_t *q, int b){
  //Inicializando o estado
  gmp_randstate_t state;
  gmp_randinit_mt(state);

  //Gerar um numero aleatorio
  mpz_urandomb(*p, state, b);

  //Gerar um numero primo p maior que o numero aleatorio gerado
  mpz_nextprime(*p, *p);

  //Confirmar a primalidade do numero p
  while(mpz_probab_prime_p(*p, 50) == 0){
    mpz_nextprime(*p, *p);
  }

  //Gerar um numero primo q maior que o numero primo gerado para p
  mpz_nextprime(*q, *p);

  //Confirmar a primalidade do numero q
  while(mpz_probab_prime_p(*q, 50) == 0){
    mpz_nextprime(*q, *q);
  }

  //Desaloca o estado criado
  gmp_randclear(state);
}

//Funcao para calcular o gcd (greatest common divisor) de dois numeros
void gcd(mpz_t *retorno, mpz_t r0, mpz_t r1){
  while(1){
    //Verifica se os valores estao trocados,
    //o maior valor fica em r0 e o menor em r1
    if(mpz_cmp(r0, r1) < 0){
      mpz_set(*retorno, r1);
      mpz_set(r1, r0);
      mpz_set(r0, *retorno);
    }

    //Se r1 for 0, retorna o valor do gcd que esta em r0
    if(mpz_cmp_ui(r1, 0) == 0){
      mpz_set(*retorno, r0);
      return;
    }

    //Resto da divisao
    mpz_fdiv_r(r0, r0, r1);
  }
}

//Funcao para calcular o inverso modular de valor1 mod valor0
int ExtendedEuclidean(mpz_t *retorno, mpz_t v0, mpz_t v1){
  //Inicializando variaveis para trabalhar durante a execucao da funcao
  mpz_t valor0, valor1;
  mpz_init(valor0);
  mpz_init(valor1);
  mpz_set(valor0, v0);
  mpz_set(valor1, v1);

  //O maior valor deve ficar em valor0
  if(mpz_cmp(valor0, valor1) < 0){
    mpz_t ax;
    mpz_init(ax);
    mpz_set(ax, valor1);
    mpz_set(valor1, valor0);
    mpz_set(valor0, ax);
    mpz_clear(ax);
  }

  //Inicializando as variaveis necessarias
  mpz_t q, ri0, ri1, ri2, ti2, ti1, ti0, aux;
  mpz_init(q);
  mpz_init(ri0);
  mpz_init(ri1);
  mpz_init(ri2);
  mpz_init(ti2);
  mpz_init(ti1);
  mpz_init(ti0);
  mpz_init(aux);

  //Setando os valores das variaveis
  mpz_set_ui(ri0, 0);
  mpz_set_ui(ti0, 0);
  mpz_set_ui(ti2, 0);
  mpz_set_ui(ti1, 1);
  mpz_set(ri2, valor0);
  mpz_set(ri1, valor1);

  while(mpz_cmp_ui(ri0, 1) != 0){
    //Divisao inteira para encontrar o quociente
    mpz_fdiv_q(q, ri2, ri1);

    //Encontrar o resto da divisao
    mpz_fdiv_r(ri0, ri2, ri1);

    //Calcular o novo valor de T
    mpz_mul(aux, q, ti1);
    mpz_sub(ti0, ti2, aux);

    //Fazer a troca dos valores de T
    mpz_set(ti2, ti1);
    mpz_set(ti1, ti0);

    //Fazer a troca dos valores e R
    mpz_set(ri2, ri1);
    mpz_set(ri1, ri0);

  }

  //Verifica se o inverso deu negativo
  //Soma com o valor do modulo para retornar um valor positivo
  if(mpz_cmp_ui(ti0, 0) < 0){
    mpz_add(ti0, valor0, ti0);
  }

  mpz_set(*retorno, ti0);

  mpz_clear(valor0);
  mpz_clear(valor1);
  mpz_clear(q);
  mpz_clear(ri0);
  mpz_clear(ri1);
  mpz_clear(ri2);
  mpz_clear(ti2);
  mpz_clear(ti1);
  mpz_clear(ti0);
  mpz_clear(aux);
}
