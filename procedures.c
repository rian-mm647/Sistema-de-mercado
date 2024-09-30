#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibli.h"

FILE *abrirArquivo(const char *modo){
    FILE *file = fopen("estoque.txt", modo);
    if (file == NULL)
    {
        perror("Não foi possível abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    return file;
}

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);   
}

int codigoExiste(char *codigoProduto){
    FILE *file = abrirArquivo("r");
    char linha[100];
    char codigoExistente[10];
    while (fgets(linha, sizeof(linha), file)) {
        sscanf(linha, "%[^,]", codigoExistente);
        if (strcmp(codigoExistente, codigoProduto) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int nomeExiste(char *nomeProduto){
    FILE *file = abrirArquivo("r");
    char linha[100];
    char nomeExistente[50];
    while (fgets(linha, sizeof(linha), file)) {
        sscanf(linha, "%*[^,],%[^,]", nomeExistente);
        if (strcmp(nomeExistente, nomeProduto) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int quantidadeDisponivel(char *codigoProduto){
    FILE *file = abrirArquivo("r");
    char linha[100];
    char codigoExistente[10];
    int quantidadeEstoque = 0;
    while (fgets(linha, sizeof(linha), file))
    {
        sscanf(linha, "%[^,]", codigoExistente);
        if(strcmp(codigoExistente, codigoProduto) == 0){
            sscanf(linha, "%*[^,],%*[^,],%*[^,],%d", &quantidadeEstoque);
            fclose(file);
            return quantidadeEstoque;
        }
    }
    fclose(file);
    return -1;
    
}

void atualizarQuantidadeEstoque(char *codigoProduto, int quantidadeVendida){
    FILE *file = abrirArquivo("r");
    FILE *tempFile = fopen("estoque_temp.txt", "w");
    char linha[100], codigoExistente[10], nomeProduto[50];
    float precoProduto;
    int quantidadeEstoque;
    
    while (fgets(linha, sizeof(linha), file)) {
        sscanf(linha, "%[^,]", codigoExistente);
        if (strcmp(codigoExistente, codigoProduto) == 0) {
            sscanf(linha, "%*[^,],%[^,],%f,%d", nomeProduto, &precoProduto, &quantidadeEstoque);
            quantidadeEstoque -= quantidadeVendida;
            fprintf(tempFile, "%s,%s,%f,%d\n", codigoExistente, nomeProduto, precoProduto, quantidadeEstoque);
        } else {
            fputs(linha, tempFile);
        }
    }
    fclose(file);
    fclose(tempFile);
    remove("estoque.txt");
    rename("estoque_temp.txt", "estoque.txt");
}

int buscarProdutoPorCodigo(char *codigoProduto, char *linhaProduto){
    FILE *file = abrirArquivo("r");
    char linha[100];
    char codigoExistente[10];
    while (fgets(linha, sizeof(linha), file)) {
        sscanf(linha, "%[^,]", codigoExistente);
        if (strcmp(codigoExistente, codigoProduto) == 0) {
            fclose(file);
            strcpy(linhaProduto, linha);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int buscarProdutoNoCarrinho(char *codigoProduto, Carrinho *novoCarrinho){
    for (int i = 0; i < novoCarrinho->quantItens; i++)
    {
        if (strcmp(novoCarrinho->itens[i].codigo, codigoProduto) == 0)
        {
            return i;
        }
    }
    return -1;
}

void cadastrarProduto(Produto novoProduto){
    FILE *file = abrirArquivo("a");
    fprintf(file, "%s,%s,%.2f,%d\n", novoProduto.codigo, novoProduto.nome, novoProduto.preco, novoProduto.quantEstoque);
    fclose(file);
}

int lerLinhaArquivo(FILE *file, char *linha, int tamanho) {
    if (fgets(linha, tamanho, file) != NULL) {
        return 1;
    } else {
        return 0;
    }
}