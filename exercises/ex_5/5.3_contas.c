#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 5
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


int buscaConta( struct Conta *C, int num, int tam){
    if (tam == 0){
        return -1;
    }
    for (int i =0; i < tam; i += 1){
        if (C[i].numero == num) {
            return i;
        }
    }
    return -2;
}


void preencherConta(struct Conta *C, int num, int *i){
    int numContido = buscaConta(C, num, *i);
    if (numContido >= 0){
        printf("\nNúmero da conta já existe! Tente novamente\n");
        return;
    }
    char strTemp[CARACTERES]; 
    printf("————— CONTA %d —————\n", (*i) + 1);
    C[*i].numero = num;
    printf("Insira os campos necessários:\n");
    printf("Nome do cliente: ");
    lerStr(C[*i].nome, CARACTERES);
    printf("CPF: ");
    lerStr(C[*i].cpf, CARACTERES);
    printf("Telefone: ");
    lerStr(C[*i].telefone, CARACTERES);
    printf("Saldo da conta: ");
    scanf("%lf", &C[*i].saldo);
    printf("\n");
    lerStr(strTemp, CARACTERES);
    *i += 1;
}

void consultarSaldo(struct Conta *C, int num, int tam){
    int i = buscaConta(C, num, tam);
    if (i >= 0){
        printf("O saldo da conta bancária é de R$%.2lf\n", C[i].saldo);
    } else {
        printf("A conta informada não está cadastrada!\n");
    }
}

void deposito(struct Conta *C, int num, int tam){
    int i = buscaConta(C, num, tam);
    if (i >= 0){
        double valor;
        printf("Informe o valor a ser depositado na conta: R$");
        scanf("%lf", &valor);
        C[i].saldo += valor;
    } else {
        printf("A conta informada não está cadastrada!\n");
    }
}

void saque(struct Conta *C, int num, int tam){
    int i = buscaConta(C, num, tam);
    if (i >= 0){
        double valor;
        printf("Informe o valor do saque em conta: R$");
        scanf("%lf", &valor);
        if (valor > C[i].saldo){
            printf("SALDO INSUFICIENTE!\n");
        } else {
            C[i].saldo -= valor;
        }
    } else {
        printf("A conta informada não está cadastrada!\n");
    }
}

void exibirContas(struct Conta *C, int tam){
    printf("\n");
    for(int i = 0; i < tam; i++){
        printf("NUMERO DA CONTA: %d", C[i].numero);
        printf("\nNOME DO TITULAR: %s", C[i].nome);
        printf("\nTELEFONE: %s", C[i].telefone);
        printf("\n=============\n");
     }
}


int main(){
    struct Conta contaCorrente[TAM];
    struct Conta contaPoupanca[TAM];
    int qtdCorrente = 0;
    int qtdPoupanca = 0;
    char strTemp[CARACTERES];
    int entrada;
    int novoNum;
    int selecaoConta;
    do {
        printf("\n          MENU          \n");
        printf("Selecione uma opção válida:\n[1] — Cadastro de conta\n[2] — Consultar saldo\n[3] — Depositar em conta\n[4] — Saque em conta\n[5] — Exibir dados de contas bancárias\n[0] — Encerrar programa\n— ");
        scanf("%d", &entrada);
        switch(entrada){
            case 1:
                printf("Selecione a conta que você deseja cadastrar\n(1 — Conta Corrente; 2 — Conta Poupança): ");
                scanf("%d", &selecaoConta);
                switch(selecaoConta){
                    case 1:
                        if (qtdCorrente >= TAM){
                            printf("LIMITE DE CADASTROS DE CONTA ATINGIDO!");
                        } else {
                            printf("Insira o número da Conta Corrente: ");
                            scanf("%d", &novoNum);
                            lerStr(strTemp, CARACTERES);
                            preencherConta(contaCorrente, novoNum, &qtdCorrente);
                        }
                        break;
                    case 2:
                        if (qtdPoupanca >= TAM){
                            printf("LIMITE DE CADASTROS DE CONTA ATINGIDO!");
                        } else {
                            printf("Insira o número da Conta Poupanca: ");
                            scanf("%d", &novoNum);
                            lerStr(strTemp, CARACTERES);
                            preencherConta(contaPoupanca, novoNum, &qtdPoupanca);
                        }
                        break;
                    default:
                        printf("Entrada inválida! Tente novamente\n");
                    }
                break;
            case 2:
                printf("Selecione a conta que você deseja verificar o saldo\n(1 — Conta Corrente; 2 — Conta Poupança): ");
                scanf("%d", &selecaoConta);
                switch(selecaoConta){
                    case 1:
                        printf("Insira o número da Conta Corrente: ");
                        scanf("%d", &novoNum);
                        consultarSaldo(contaCorrente, novoNum, TAM);
                        break;
                    case 2:
                        printf("Insira o número da Conta Poupanca: ");
                        scanf("%d", &novoNum);
                        consultarSaldo(contaPoupanca, novoNum, TAM);
                        break;
                    default:
                        printf("Entrada inválida! Tente novamente\n");
                    }
                break;
            case 3:
                printf("Selecione a conta que você deseja efetuar o depósito\n(1 — Conta Corrente; 2 — Conta Poupança): ");
                scanf("%d", &selecaoConta);
                switch(selecaoConta){
                    case 1:
                        printf("Insira o número da Conta Corrente: ");
                        scanf("%d", &novoNum);
                        deposito(contaCorrente, novoNum, TAM);
                        break;
                    case 2:
                        printf("Insira o número da Conta Poupanca: ");
                        scanf("%d", &novoNum);
                        deposito(contaPoupanca, novoNum, TAM);
                        break;
                    default:
                        printf("Entrada inválida! Tente novamente\n");
                    }
                break;
            case 4:
                printf("Selecione a conta que você deseja efetuar o saque\n(1 — Conta Corrente; 2 — Conta Poupança): ");
                scanf("%d", &selecaoConta);
                switch(selecaoConta){
                    case 1:
                        printf("Insira o número da Conta Corrente: ");
                        scanf("%d", &novoNum);
                        saque(contaCorrente, novoNum, TAM);
                        break;
                    case 2:
                        printf("Insira o número da Conta Poupanca: ");
                        scanf("%d", &novoNum);
                        saque(contaPoupanca, novoNum, TAM);
                        break;
                    default:
                        printf("Entrada inválida! Tente novamente\n");
                    }
                break;
            case 5:
                printf("Selecione quais contas que você deseja exibir\n(1 — Conta Corrente; 2 — Conta Poupança): ");
                scanf("%d", &selecaoConta);
                switch(selecaoConta){
                    case 1:
                        exibirContas(contaCorrente, TAM);
                        break;
                    case 2:
                        exibirContas(contaPoupanca, TAM);
                        break;
                    default:
                        printf("Entrada inválida! Tente novamente\n");
                    }
                break; 
            case 0:
                    break;
            default:
                printf("Opção inválida! Tente novamente\n");        
        }
    } while (entrada != 0);

    return 0;
}