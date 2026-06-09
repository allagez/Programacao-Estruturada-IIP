#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAMStr 60
#define EST 26

struct Estado{
    char nome[TAMStr];
    int veiculos;
    int acidentes;
};

void lerStr(char str[], int tam){
    fgets(str, tam, stdin);
    int tamStr = strlen(str);
    if (tamStr > 0 && str[tamStr - 1] == '\n'){
        str[tamStr - 1] = '\0';
    }
}

void preencherEstados(struct Estado *E, int tam){
    char strTemp[TAMStr];
    for (int i = 0; i < tam; i += 1){
        printf("\n— ESTADO %d", i + 1);
        printf("\n— Estado: ");
        lerStr(E[i].nome, TAMStr);
        printf("— Quantidade de veículos: ");
        scanf("%d", &E[i].veiculos);
        printf("— Acidentes ocorridos: ");
        scanf("%d", &E[i].acidentes);
        lerStr(strTemp, TAMStr);
    }
}

void verificarAcidentes(struct Estado *E, int tam, int *maior, int *menor){
    for (int i = 1; i < tam; i += 1){
        if(E[i].acidentes > E[*maior].acidentes){
            *maior = i;
        }
        if(E[i].acidentes < E[*menor].acidentes){
            *menor = i;
        }
    }
}

double percentual(struct Estado *E, int i){
    return ((E[i].acidentes * 100)/ E[i].veiculos);
}

double mediaTotal(struct Estado *E, int tam){
    int somaTotal = 0;
    for (int i = 0; i < tam; i += 1){
        somaTotal += E[i].acidentes;
    }
    return somaTotal / tam;
}

void acimaMedia(struct Estado *E, int tam, double media){
    for (int i = 0; i < tam; i += 1){
        if(E[i].acidentes > media){
            printf("%s: %d acidentes\n", E[i].nome, E[i].acidentes);
        }
    }
}



int main(){
    struct Estado estados[EST];
    printf("Preencha os dados de cada estado brasileiro: ");
    preencherEstados(estados, EST);

    int maiorAcidentes =0 , menorAcidentes =0;
    verificarAcidentes(estados, EST, &maiorAcidentes, &menorAcidentes);
    printf("\n— Estado com o maior número de acidentes:\n%s (%d acidentes)\n", estados[maiorAcidentes].nome, estados[maiorAcidentes].acidentes);
    printf("— Estado com o menor número de acidentes:\n%s (%d acidentes)\n\n", estados[menorAcidentes].nome, estados[menorAcidentes].acidentes);

    for (int i = 0; i < EST; i += 1){
        printf("Estado: %s\nPercentual de acidentes por veículos: %.2lf%%\n\n", estados[i].nome, percentual(estados, i));
    }

    double mediaPais = mediaTotal(estados, EST);
    printf("A média de acidentes do país por estado é: %.2lf\n", mediaPais);

    printf("Estados que estão acima da média do país (%.2lf):\n", mediaPais);
    acimaMedia(estados, EST, mediaPais);

    return 0;
}

