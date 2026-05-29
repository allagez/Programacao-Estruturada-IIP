#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CARACTERES 200
#define MAXPRODUTOSVENDA 50
//Criacao das structs - Tema: Venda e controle de estoque


//OBS: EVITAR USAR ACENTOS PRA N DA AQUELES SIMBOLOS ESTRANHOS!


struct ControleE{ //controle de estoque
    int idprodutoEstoque; //id do produto
    char descricao[CARACTERES]; //descricao do produto
    double preco; //preco do produto
    int qtdc; //quantidade  de produtos no estoque
};

struct Venda{
    int idvenda; //id da venda em si
    int idprodutovenda[MAXPRODUTOSVENDA]; //id do prduto q foi vendido
    int qtdv[MAXPRODUTOSVENDA]; //quantidade do produto vendido
    int qtd_itens;
    double ValorT; //valor total
};
//funcao auxiliar
void lerStr(char str[], int max){
    fgets(str, max, stdin);
    int tam = strlen(str);
    if(tam > 0 && str[tam - 1] == '\n'){
        str[tam - 1] = '\0';
    }
}


//Funcao 1 - Cadastrar Novo Produto
void CadastrarNovoProduto(){
    struct ControleE novoProduto;
    FILE *arquivo;
    printf("\n==AREA CADASTRAR NOVO PRODUTO==\n");
    printf("\nDigite o ID do produto: ");
    scanf("%d", &novoProduto.idprodutoEstoque);
    getchar();
    printf("\nDigite a descricao do produto: ");
    lerStr(novoProduto.descricao, CARACTERES);
    printf("\nDigite o preco do produto: R$");
    scanf("%lf", &novoProduto.preco);
    printf("\nDigite a quantidade do produto no estoque: ");
    scanf("%d", &novoProduto.qtdc);
    arquivo = fopen("estoque.bin", "ab");
    if(arquivo == NULL){
        printf("\nErro ao tentar abrir arquivo!\n");
        return;
    }

    fwrite(&novoProduto, sizeof(struct ControleE), 1, arquivo);
    fclose(arquivo);
    printf("\nProduto Cadastrado com sucesso no Arquivo estoque.bin"); }

//Funcao 5 - Relatorio dos produtos
void relatorioProdutos(){
    struct ControleE p;
    FILE *arquivo = fopen("estoque.bin", "rb");
    if(arquivo == NULL){
        printf("\nErro ao tentar abrir arquivo!");
        return;
    }
    printf("\n==RELATORIO DE PRODUTOS NO ESTOQUE==\n");
    while(fread(&p, sizeof(struct ControleE), 1, arquivo) == 1){
        printf("ID: %d -  Descricao: %s - Preco: R$ %.2f - Qtd: %d\n", p.idprodutoEstoque, p.descricao, p.preco, p.qtdc);
    }

    fclose(arquivo);
    printf("----------------------------------------\n");
    }


//Funcao 2 - Venda com baixa automática no estoque
void RealizarVenda() {
    struct Venda novaVenda;
    struct ControleE p; 
    FILE *arquivo;
    FILE *arqEstoque;   
    int continuar = 1;
    int pos = 0;
    int achouProduto;

    printf("\n==AREA DE VENDA==\n");
    printf("Digite o ID da Venda: ");
    scanf("%d", &novaVenda.idvenda);

    novaVenda.ValorT = 0.0;

    do {
        if (pos >= MAXPRODUTOSVENDA) {
            printf("\nLimite maximo de produtos nesta venda atingido!\n");
            break;
        }
        printf("\nDigite o ID do produto vendido: ");
        scanf("%d", &novaVenda.idprodutovenda[pos]);
        printf("Digite a quantidade vendida: ");
        scanf("%d", &novaVenda.qtdv[pos]);

        arqEstoque = fopen("estoque.bin", "r+b"); // Abre para leitura e escrita
        achouProduto = 0;

        if (arqEstoque == NULL) {
            printf("\n[Erro] Nao foi possivel abrir o estoque para dar baixa no produto.\n");
        } else {
            
            while (fread(&p, sizeof(struct ControleE), 1, arqEstoque) == 1) {
                if (p.idprodutoEstoque == novaVenda.idprodutovenda[pos]) {
                    achouProduto = 1;

                    
                    if (p.qtdc >= novaVenda.qtdv[pos]) {
                        p.qtdc -= novaVenda.qtdv[pos];

                        
                        fseek(arqEstoque, -sizeof(struct ControleE), SEEK_CUR);
                        fwrite(&p, sizeof(struct ControleE), 1, arqEstoque);
                        printf("-> Baixa de %d unidades no estoque realizada com sucesso!\n", novaVenda.qtdv[pos]);
                    } else {
                        printf("-> [AVISO] Estoque insuficiente! Estoque atual: %d unidades.\n", p.qtdc);
                        
                    }
                    break;
                }
            }
            fclose(arqEstoque);

            if (achouProduto == 0) {
                printf("-> [AVISO] Produto ID %d nao foi encontrado no estoque!\n", novaVenda.idprodutovenda[pos]);
            }
        }

        pos++;

        printf("\nDeseja adicionar outro produto nesta venda? (1 - Sim 0 - Nao): ");
        scanf("%d", &continuar);

    } while(continuar != 0);

    novaVenda.qtd_itens = pos;

    arquivo = fopen("vendas.bin", "ab");
    if(arquivo == NULL){
        printf("\nErro ao tentar abrir arquivo de vendas!\n");
        return;
    }
    fwrite(&novaVenda, sizeof(struct Venda), 1, arquivo);
    fclose(arquivo);

    printf("\nVenda cadastrada com sucesso no arquivo vendas.bin:)\n");
}





//funcao 6
void relatorioVendas(){
    struct Venda v;
    struct ControleE p;
    FILE *arqVendas = fopen("vendas.bin", "rb");
    FILE *arqEstoque;
    int i, achou;

    if (arqVendas == NULL) {
        printf("\nNenhuma venda cadastrada ou erro ao abrir vendas.bin!\n");
        return;
    }

    printf("\n--- RELATORIO GERAL DE VENDAS ---\n");

    while (fread(&v, sizeof(struct Venda), 1, arqVendas) == 1) {
        printf("\n[Venda ID: %d] - Quantidade de produtos diferentes: %d\n", v.idvenda, v.qtd_itens);
        printf("Itens da compra:\n");


        for (i = 0; i < v.qtd_itens; i++) {
            achou = 0;
            arqEstoque = fopen("estoque.bin", "rb"); //Abre o estoque

            if (arqEstoque != NULL) {
                while (fread(&p, sizeof(struct ControleE), 1, arqEstoque) == 1) {
                    if (p.idprodutoEstoque == v.idprodutovenda[i]) {
                        printf("  -> Produto: %s - Qtd comprada: %d\n", p.descricao, v.qtdv[i]);
                        achou = 1;
                        break; 
                    }
                }
                fclose(arqEstoque);
            }

            
            if (achou == 0) {
                printf("  -> Produto [ID %d] (Nao encontrado no estoque) | Qtd comprada: %d\n", v.idprodutovenda[i], v.qtdv[i]);
            }
        }
    }
    fclose(arqVendas);
}

// Funcao 3 - Atualizar Produto
void AtualizarProduto() {
    struct ControleE p;
    FILE *arquivo;
    int idBusca, achou = 0;

    arquivo = fopen("estoque.bin", "r+b");

    if (arquivo == NULL) {
        printf("\nNenhum produto cadastrado ainda ou erro ao abrir o arquivo!\n");
        return;
    }

    printf("\n==ATUALIZAR PRODUTO==\n");
    printf("Digite o ID do produto que deseja atualizar: ");
    scanf("%d", &idBusca);

    while (fread(&p, sizeof(struct ControleE), 1, arquivo) == 1) {
        if (p.idprodutoEstoque == idBusca) {
            printf("\nProduto encontrado!\n");
            printf("Dados atuais -> Descricao: %s | Preco: R$ %.2f | Qtd: %d\n", p.descricao, p.preco, p.qtdc);
            getchar();
            printf("\nDigite a nova descricao: ");
            lerStr(p.descricao, CARACTERES);
            printf("Digite o novo preco: R$ ");
            scanf("%lf", &p.preco);
            printf("Digite a nova quantidade no estoque: ");
            scanf("%d", &p.qtdc);
            fseek(arquivo, -sizeof(struct ControleE), SEEK_CUR);
            fwrite(&p, sizeof(struct ControleE), 1, arquivo);

            achou = 1;
            printf("\nProduto atualizado com sucesso!\n");
            break;
        }
    }
    if (achou == 0) {
        printf("\nProduto com ID %d nao encontrado.\n", idBusca);
    }
    fclose(arquivo);
}


//funcao 4 - Remover Produto (Criando novo arquivo)
void RemoverProduto() {
    struct ControleE p;
    FILE *arqAntigo, *arqNovo;
    int idRemover, achou = 0;

    arqAntigo = fopen("estoque.bin", "rb");
    if (arqAntigo == NULL) {
        printf("\nNenhum produto cadastrado para remover ou erro ao abrir o arquivo!\n");
        return;
    }

    arqNovo = fopen("temp.bin", "wb"); 
    if (arqNovo == NULL) {
        printf("\nErro ao criar o arquivo temporario!\n");
        fclose(arqAntigo);
        return;
    }

    printf("\n== REMOVER PRODUTO ==\n");
    printf("Digite o ID do produto que deseja remover: ");
    scanf("%d", &idRemover);

    
    while (fread(&p, sizeof(struct ControleE), 1, arqAntigo) == 1) {
        if (p.idprodutoEstoque != idRemover) {
            //Se nao for o produto que queremos apagar, copiamos para o arquivo novo
            fwrite(&p, sizeof(struct ControleE), 1, arqNovo);
        } else {
            achou = 1;
        }
    }

    fclose(arqAntigo);
    fclose(arqNovo);

    if (achou == 1) {
        remove("estoque.bin");
        rename("temp.bin", "estoque.bin");
        printf("\nProduto removido com sucesso e arquivos atualizados!\n");
    } else { //se nao achar o id
        remove("temp.bin");
        printf("\nProduto com ID %d nao encontrado no estoque.\n", idRemover);
    }
}



int main() {
    //---------------------

    //*EM PRODUÇÃO - MENU*
    int entrada = 1;


    do{
        printf("\n______MENU______\n");
        printf("\n1 - Cadastrar Produto");
        printf("\n2 - Venda");
        printf("\n3 - Atualizar Produto");
        printf("\n4 - Remover Produto (e criacao de um novo arquivo)");
        printf("\n5 - Relatorio dos produtos");
        printf("\n6 - Relatorio de Vendas (cruzamento de dados)");
        printf("\n0 - Sair do Menu");
        printf("\nEscolha Uma Opcao do Menu: ");
        scanf("%d", &entrada);
        switch(entrada){
            case 1:
                CadastrarNovoProduto();
                break;
            case 2:
                RealizarVenda();
                break;
            case 3:
                AtualizarProduto();
                break;
            case 4:
                RemoverProduto();
                break;
            case 5:
                relatorioProdutos();
                break;
            case 6:
                relatorioVendas();
                break;
            case 0:
                printf("\nSaindo do programa!");
                break;
            default:
                printf("\nEssa opcao nao existe no programa!");
        }
    }while(entrada != 0);

    return 0;
}


