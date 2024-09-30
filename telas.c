#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include "bibli.h"

void mensagemInicial(){
    printf("\t-=-=-=-=-=-=-=BEM VINDO AO=-=-=-=-=-=-=-\n");
    printf(" __  __                             _              _          _____                   \n");
    printf("|  \\/  |                           | |            | |        |  __ \\                  \n");
    printf("| \\  / |  ___  _ __  ___  __ _   __| |  ___     __| |  ___   | |__) |___ __   __ ___  \n");
    printf("| |\\/| | / _ \\| '__|/ __|/ _` | / _` | / _ \\   / _` | / _ \\  |  ___// _ \\ \\ / // _ \\ \n");
    printf("| |  | ||  __/| |  | (__| (_| || (_| || (_) | | (_| || (_) | | |   | (_) |\\ V /| (_) |\n");
    printf("|_|  |_| \\___||_|   \\___|\\__,_| \\__,_| \\___/   \\__,_| \\___/  |_|    \\___/  \\_/  \\___/ \n");
    printf("                                                          AQUI VOCÊ É BEM ATENDIDO!!\n\n");
    system("pause");
    system("cls");
    menuPrincipal();
}

void menuPrincipal(){
    int opcao;
    while(opcao!=5){
        printf("1 - Cadastro de produto\n2 - Atualizar produto\n3 - Listar produtos em estoque\n4 - Comprar\n5 - Sair\n\nDigite o numero da opção desejada: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            system("cls");
            printf("Redirecionando ao menu de cadastro...");
            sleep(1);
            system("cls");
            menuCadastro();
            break;
        case 2:
            //menu atualizar produto
            break;
        case 3:
            system("cls");
            printf("Listando produtos...");
            sleep(1);
            system("cls");
            listarProdutos();   
            break;
        case 4:
            system("cls");
            printf("Redirecionando ao menu de compras...");
            sleep(1);
            system("cls");
            menuCompra();
            break;
        default:
            //mensagem de advertencia
            break;
        }
    }
    if (opcao == 5)
    {
        system("cls");
        printf("O MERCADO DO POVO AGRADACE A PREFERÊNCIA, VOLTE SEMPRE!");
        sleep(2);
        exit;
    }
    
}

int desejaContinuar(){
    char confirmacao;
    while(1){
    printf("\n\nDeseja continuar? (Digite \"S\" para confirmar, ou \"N\" para voltar): ");
    scanf("%c", &confirmacao);
    if (confirmacao == 'S' || confirmacao == 's') return 1;
    else if (confirmacao == 'N' || confirmacao == 'n') return 0;
    else printf("\nO caractere digitado é inválido!");
    }
    limparBuffer();
}

void menuCadastro(){
    Produto novoProduto;
    while(1){
        printf("\t -=-=-=-=CADASTRO DE NOVO PRODUTO=-=-=-=-\n\n");
        coletarCodigoProduto(&novoProduto);
        coletarNomeProduto(&novoProduto);
        coletarPrecoProduto(&novoProduto);
        coletarQuantidadeProduto(&novoProduto);
        printf("\nOs dados do produto são:\n\nID: %s\nNome: %s\nPreço: R$%.2f\nQuantidade em estoque: %d", novoProduto.codigo, novoProduto.nome, novoProduto.preco, novoProduto.quantEstoque);
        if (desejaContinuar() == 1) {
            cadastrarProduto(novoProduto);
            printf("\n\nProduto cadastrado com sucesso!\n");
            system("pause");
        } else {
            system("cls");
            printf("\n\nRedirecionando ao cadastro de produto...");
            sleep(2);
            system("cls");
            menuCadastro();
        }
    }
    system("cls");
}

void coletarCodigoProduto(Produto *novoProduto){
    char tempCodigo[10];
    while (1) {
        printf("\nDigite o código do produto que deseja cadastrar: ");
        scanf("%s", tempCodigo);
        limparBuffer();
        if (codigoExiste(tempCodigo)) {
            printf("\nCódigo já existe! Insira um código único.\n");
        } else {
            strcpy(novoProduto->codigo, tempCodigo);
            break;
        }
    }
}

void coletarNomeProduto(Produto *novoProduto){
    int valido = 0;
    char tempNome[50];
    while (!valido)
    {
        printf("\nDigite o nome do produto: ");
        fgets(tempNome, sizeof(tempNome), stdin);
        tempNome[strcspn(tempNome, "\n")] = 0;
        if (strlen(tempNome) < 2)
        {
            printf("\nErro: O nome do produto deve ter ao menos 2 caracteres!\n");
        } else if (nomeExiste(tempNome)){
            printf("\nO nome do produto já existe\n");
            if (desejaContinuar() == 1){
                strcpy(novoProduto->nome, tempNome);
                valido = 1;
            } else {
                limparBuffer();
                continue;
            }
        } else {
            strcpy(novoProduto->nome, tempNome);
            valido = 1;
        }
    }
}

void coletarPrecoProduto(Produto *novoProduto){
    int valido = 0;
    while (!valido)
    {
        printf("\nDigite o preço do produto (ex: 9.90): R$");
        if (scanf("%f", &novoProduto->preco) != 1 || novoProduto->preco <=0)
        {
            printf("Erro: O preço deve ser um número positivo!\n");
            limparBuffer();
        } else {
            valido = 1;
        }
    }
    limparBuffer();
}

void coletarQuantidadeProduto(Produto *novoProduto){
    int quantidade;
    while (1) {
        printf("\nDigite a quantidade disponível em estoque: ");
        if (scanf("%d", &quantidade) == 1 && quantidade >= 0) {
            novoProduto->quantEstoque = quantidade;
            limparBuffer();
            break;
        } else {
            printf("\nQuantidade inválida! Insira um número inteiro!\n");
            limparBuffer();
        }
    }
}

void listarProdutos(){
    FILE *file = abrirArquivo("r");
    char linha[200], codigo[10], nome[50];
    float preco;
    int quant;
    printf("\nLista de Produtos:\n");
    printf("---------------------------------------\n");
    printf("| %-5s | %-20s | %-9s | %-8s |\n", "Código", "Nome", "Preço", "Quantidade em estoque");
    printf("---------------------------------------\n");
    while (lerLinhaArquivo(file, linha, sizeof(linha))) {
        sscanf(linha, "%[^,],%[^,],%f,%d", codigo, nome, &preco, &quant);
        printf("| %-7s | %-20s | R$%-7.2f | %-21d |\n", codigo, nome, preco, quant);
    }
    printf("---------------------------------------\n\n\n");
    fclose(file);
}

void menuCompra(){
    Carrinho novoCarrinho;
    int opcao;
    while(opcao != 4){
        printf("\t\t-=-=-=-=-=-=-=MENU COMPRAS=-=-=-=-=-=-=-\n\n");
        printf("1 - Adicionar ao carrinho\n2 - Exibir/editar carrinho\n3 - Fechar compra\n4 - Voltar\nDigite o numero da opcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            system("cls");
            menuAdicionarAoCarrinho(&novoCarrinho);
            break;
        case 2:
            //função de exibir/editar o carrinho
            break;
        case 3:
            //função de fechar compra
            break;
        default:
            //mensagem de advertencia
            break;
        }
    }
    system("cls");
    menuPrincipal();
}

void menuAdicionarAoCarrinho(Carrinho *novoCarrinho){
    int opcao;
    while (opcao!=3)
    {
        printf("\t\t-=-=-=-=-=ADICIONAR AO CARRINHO=-=-=-=-=-\n\n");
        printf("1 - Buscar item por código\n2 - Listar itens\n3 - Voltar\nOpcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            system("cls");
            adicionarAoCarrinhoPorCodigo(novoCarrinho);
            break;
        case 2:
            listarProdutos();
            break;
        default:
            //mensagem de advertencia
            break;
        }
    }
    system("cls");
    menuCompra();
}

void adicionarAoCarrinhoPorCodigo(Carrinho *novoCarrinho){
    char codigo[10], linhaProduto[100];
    int quantidade, quantidadeEstoque, valido;
    while (valido != 1){
        printf("\t\t-=-=-=ADICIONAR POR CÓDIGO=-=-=-\n\n");
        printf("Digite o código do produto que deseja adicionar: ");
        scanf("%s", codigo);
        limparBuffer();
        if (codigoExiste(codigo)){
            mostrarPorCodigo(codigo, linhaProduto);
            if (desejaContinuar() == 1)
            {
                printf("\nQuanto desse produto você deseja adicionar? ");
                scanf("%d", &quantidade);
                quantidadeEstoque = quantidadeDisponivel(codigo);
                if (quantidade > quantidadeEstoque)
                {
                    printf("\nERRO: A quantidade desejada excede a disponível no estoque.\n");
                    break;
                }
            int indiceCarrinho = buscarProdutoNoCarrinho(codigo, novoCarrinho);
            if (indiceCarrinho == -1)
            {
                novoCarrinho->itens[indiceCarrinho].quantCarrinho += quantidade;
            } else {
                ItemCarrinho novoProduto;
                sscanf(linhaProduto, "%[^,],%[^,],%f,%*d", novoProduto.codigo, novoProduto.nome, &novoProduto.preco);
                novoProduto.quantCarrinho = quantidade;
                novoCarrinho->itens[novoCarrinho->quantItens++] = novoProduto;
            }
        atualizarQuantidadeEstoque(codigo, quantidade);
        printf("Item(ns) adicionado(s) com sucesso ao carrinho!\n");
        valido = 1;    
            }
        } else {
            printf("\nERRO: O códgio informado não existe no estoque!");
            system("pause");
            system("cls");
        }
    }
}

void mostrarPorCodigo(char codigo[10], char *linha){
    char codigoProduto[10], nomeProduto[50], linhaProduto[100];
    float precoProduto;
    int quantProduto;
        buscarProdutoPorCodigo(codigo, linhaProduto);
        printf("\n| %-5s | %-20s | %-9s | %-8s |\n", "Código", "Nome", "Preço", "Quantidade em estoque");
        printf("---------------------------------------\n");
        sscanf(linhaProduto, "%[^,],%[^,],%f,%d", codigoProduto, nomeProduto, &precoProduto, &quantProduto);
        printf("| %-7s | %-20s | R$%-7.2f | %-21d |\n", codigoProduto, nomeProduto, precoProduto, quantProduto);
        strcpy(linha, linhaProduto);
}