#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

struct Categoria{
    int codigo;
    char nome[50];
};

struct Produto{
    int codigo;
    char titulo[100];
    char descricao[256];
    int categoria;
    int preco;
};

int buscaCategoria(struct Categoria *C, int codigo, int tam) {
    if (tam == 0) {
        return -1;
    }
    for (int i = 0; i < tam; i += 1) {
        if (C[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

void lerStr(char *str, int tam) {
    fgets(str, tam, stdin);
    int tamStr = strlen(str);
    if (tamStr > 0 && str[tamStr - 1] == '\n') {
        str[tamStr - 1] = '\0';
    }
}
void cadastrarCategoria(struct Categoria *C, int *qtd) {
    if (*qtd >= TAM) {
        return;
    }
    
    int numNovo;
    scanf("%d", &numNovo);
    
    if (buscaCategoria(C, numNovo, TAM) >= 0) {
        printf("Já existe categoria com esse codigo");
        return;
    }
    
    C[*qtd].codigo = numNovo;
    char strTemp[50];
    lerStr(strTemp, 50);
    lerStr(C[*qtd].nome, 50);
    *qtd += 1;
}



void imprimirCategorias(struct Categoria *c, int qtd) {
    for (int i = 0; i < qtd; i += 1) {
        printf("%d\n", c[i].codigo);
        printf("%s\n", c[i].nome);
    }
}

void imprimirProdutos(struct Produto *P, int qtdP, struct Categoria *C, int qtdC) {
    int j;
    for (int i = 0; i < qtdP; i += 1) {
        printf("%d", P[i].codigo);
        printf("%s", P[i].titulo);
        printf("%s", P[i].descricao);
        
        j = buscaCategoria(C, P[i].categoria, qtdC);
        printf("%s", C[j].nome);
        printf("%.2f", P[i].preco / 100.00);
    }
}
void selectionSortDesc(struct Produto *P, int qtd) {
    int i, j, menor;
    struct Produto aux;
    
    for (i = 0; i < qtd - 1; i += 1) {
        menor = i;
        for (j = i + 1; j <= qtd - 1; j += 1) {
            if (strcmp(P[j].descricao, P[menor].descricao) > 0) {
                menor = j;
            }
        }
        aux = P[i];
        P[i] = P[menor];
        P[menor] = aux;
    }
}

void buscaBinariaDesc(struct Produto *P, int qtd, char *x) {
    int inicio = 0;
    int meio;
    int fim = qtd - 1;
    do {
        int meio = (inicio + fim) / 2;
        if (strcmp(P[meio].descricao, x) > 0) {
            fim = meio - 1;
        } else if (strcmp(P[meio].descricao, x) < 0){
            inicio = meio + 1;
        } else {
            break;
        }
    } while (inicio <= fim);
    
    if (inicio <= fim && strcmp(P[meio].descricao, x) == 0) {
        printf("A descrição está registrada!");
    } else {
        printf("A descrição não foi encontrada!");
    }
}

int main() {
    struct Categoria categorias[TAM];
    struct Produto produtos[TAM];
    int qtdC = 0, qtdP = 0;

    cadastrarCategoria(categorias, &qtdC);

    produtos[0].codigo = 1;
    strcpy(produtos[0].titulo, "Produto Exemplo");
    strcpy(produtos[0].descricao, "Descricao unica");
    produtos[0].categoria = categorias[0].codigo;
    produtos[0].preco = 4999;  
    qtdP = 1;

    imprimirCategorias(categorias, qtdC);

    imprimirProdutos(produtos, qtdP, categorias, qtdC);

    buscaBinariaDesc(produtos, qtdP, "Descricao unica");

    buscaBinariaDesc(produtos, qtdP, "Descricao falsa");

    return 0;
}