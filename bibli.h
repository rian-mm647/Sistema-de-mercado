#ifndef BIBLI_H
#define BIBLI_H

typedef struct{
    char codigo[10];
    char nome[50];
    float preco;
    int quantEstoque;
}Produto;

typedef struct{
    char codigo[10];
    char nome[50];
    float preco;
    int quantCarrinho;
}ItemCarrinho;

typedef struct{
    ItemCarrinho itens[100];
    int quantItens;
    float valorTotal;
}Carrinho;

void mensagemInicial();
void menuPrincipal();
int desejaContinuar();
void menuCadastro();
void coletarCodigoProduto();
void coletarNomeProduto();
void coletarPrecoProduto();
void coletarQuantidadeProduto();
void listarProdutos();
void menuCompra();
void menuAdicionarAoCarrinho(Carrinho *novoCarrinho);
void adicionarAoCarrinhoPorCodigo(Carrinho *novoCarrinho);
void mostrarPorCodigo(char codigo[10], char *linha);
void exibirCarrinho(Carrinho *novoCarrinho);
void fecharPedido(Carrinho *novoCarrinho);
FILE *abrirArquivo(const char *modo);
void limparBuffer();
int codigoExiste(char *codigoProduto);
int nomeExiste(char *nomeProduto);
int quantidadeDisponivel(char *codigoProduto);
void atualizarQuantidadeEstoque(char *codigoProduto, int quantidadeVendida);
int buscarProdutoPorCodigo(char *codigoProduto, char *linhaProduto);
int buscarProdutoNoCarrinho(char *codigoProduto, Carrinho *novoCarrinho);
void cadastrarProduto(Produto novoProduto);
int lerLinhaArquivo(FILE *file, char *linha, int tamanho);


#endif