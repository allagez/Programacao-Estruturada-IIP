#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define  CARACTERES 50
#define TAM 26

struct Estado{
    char nome[CARACTERES];
    int veiculos;
    int acidentes;
};

void lerStr(char str[], int max){
    fgets(str, max, stdin);
    int tam = strlen(str);
    if (tam !=0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}

void preencherEstados(struct Estado *E, int tam){
    char tempStr[CARACTERES];
    for (int i = 0; i < tam; i += 1){
        printf("———————— Estado %d ————————\n", i + 1);
        printf("Nome do estado: ");
        lerStr(E[i].nome, CARACTERES);
        printf("Veículos que circulam no estado: ");
        scanf("%d", &E[i].veiculos);
        printf("Acidentes no estado: ");
        scanf("%d", &E[i].acidentes);
        lerStr(tempStr, CARACTERES);
        printf("\n");
    }
}

void buscaMaioreMenor(struct Estado *E, int tam, int *maior, int *menor){
    for (int i = 0; i < tam; i += 1){
        if (E[i].acidentes > E[*maior].acidentes){
            *maior = i;
        }
        if (E[i].acidentes < E[*menor].acidentes){
            *menor = i;
        }
    }
}

double percentual(struct Estado *E, int i){
    return (E[i].acidentes * 100.0)/E[i].veiculos;
}

int main(){
    struct Estado estados[TAM];
    preencherEstados(estados, TAM);

    int maior = 0, menor = 0;
    buscaMaioreMenor(estados, TAM, &maior, &menor);
    printf("O estado com maior número de acidentes:\n%s — %d\n", estados[maior].nome, estados[maior].acidentes);
    printf("O estado com menor número de acidentes:\n%s — %d\n", estados[menor].nome, estados[menor].acidentes);
    
    printf("Percentual de veículos envolvidos em acidente por estado:\n");
    for (int i = 0; i < TAM; i += 1){
        printf("%s — %.2f%%\n", estados[i].nome, percentual(estados, i));
    }
    return 0;
}