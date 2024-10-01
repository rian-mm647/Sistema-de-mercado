#Sistema de Mercado
Este é um sistema de gerenciamento de compras e estoque de um mercado, desenvolvido em C. Ele permite ao usuário visualizar e adicionar produtos ao estoque, adicionar itens ao carrinho, verificar o carrinho de compras e finalizar a compra com uma fatura detalhada.

#Funcionalidades
Manipulação do estoque:
O sistema permite adicionar produtos ao arquivo de estoque, contendo código, nome, preço e quantidade.

Visualização de Produtos:
O sistema exibe os produtos disponíveis, mostrando código, nome, preço e quantidade em estoque.

Adição ao Carrinho:
O usuário pode adicionar produtos ao carrinho utilizando o código do produto. A quantidade desejada é verificada com o estoque disponível antes da adição.

Visualização do Carrinho:
O usuário pode visualizar os produtos adicionados ao carrinho com seus códigos, nomes, preços e quantidades.

Finalização do Pedido:
O sistema calcula o valor total da compra, exibe uma fatura detalhada e limpa o carrinho ao final.

#Estrutura do Projeto
main.c: Função principal do sistema, gerencia o fluxo e interação com o usuário.
procedures.c: Funções auxiliares, como manipulação de arquivos, busca de produtos, atualização de estoque, etc.
telas.c: Funções relacionadas à interface e exibição das telas do sistema.

#Como Compilar
Para compilar o projeto, certifique-se de ter um compilador C (como GCC) instalado. Em seguida, abra o terminal da sua máquina e utilize o comando:

gcc main.c procedures.c telas.c -o mercado.exe

#Como Executar
Após compilar o projeto, execute o arquivo gerado:
./mercado.exe

#Requisitos do Sistema
Sistema operacional: Windows, Linux ou macOS.
Compilador C (ex: GCC).
Um terminal ou console para a execução.
