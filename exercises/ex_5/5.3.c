#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 25
#define CARACTERES 100

struct Conta {
    int numero;
    char nome[CARACTERES];
    char cpf[CARACTERES];
    char telefone[CARACTERES];
    double saldo;
};

void lerStr(char str[], int tamMax){
    fgets(str, tamMax, stdin);
    int tamStr = strlen(str);
    if (tamStr > 0 && str[tamStr - 1] == '\n' ) {
        str[tamStr - 1] = '\0';
    }
}

void preencherConta(struct Conta *C, int num){
    
    char strTemp[CARACTERES]; 
    printf("————— CONTA %d —————\n", i + 1);
    printf("Insira os campos necessários:\nNúmero da conta: ");
    scanf("%d", &C[i].numero);
    lerStr(strTemp, CARACTERES);
    printf("Nome do cliente: ");
    lerStr(C[i].nome, CARACTERES);
    printf("CPF: ");
    lerStr(C[i].cpf, CARACTERES);
    printf("Telefone: ");
    lerStr(C[i].telefone, CARACTERES);
    printf("Saldo da conta: ");
    scanf("%lf", &C[i].saldo);
    printf("\n");
    lerStr(strTemp, CARACTERES);

}

int buscaConta( struct Conta *C, int num, int tam){
    if (tam == 0){
        return -1;
    }
    for (int i =0; i < tam; i += 1){
        if (C[i].numero == num);
        return i;
    }
    return -2;
}

int main(){
    struct Conta contaCorrente[TAM];
    struct Conta contaPoupanca[TAM];
    printf("          MENU          \n");
    printf("Selecione uma opção válida:\n[1] — ");


    return 0;
}