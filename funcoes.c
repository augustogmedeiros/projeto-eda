#include "struct_func.h"
#include <stdio.h>

/*struct Produto{
    int codigo;
    char nome[50];
    int preco;
    int estoque;

    struct Produto *prox;
};*/

void Cadastrar_Produto(Produto **lista)
{
    Produto *novo = (Produto*) malloc(sizeof(Produto)); 
    if (novo == NULL) return;

    printf("Digite o Código do Produto: ");
    scanf("%d", &novo->codigo);
    limpar_buffer();
    printf("Digite o Nome do Produto: ");
    scanf("%49[^\n]", novo->nome); //funçao p ler com espaços sem usar fgets(nao logico p ignorar espaço)
    limpar_buffer();
    printf("Digite o Preço do Produto: ");
    scanf("%d", &novo->preco);
    printf("Digite o Estoque Disponível do Produto: "); /*(add futuramente funcao pra subtrair automaticamente do estoque
    quando um produto entra no carrinho de um cliente?)*/
    scanf("%d", &novo->estoque);
    limpar_buffer();

    
    


    



}