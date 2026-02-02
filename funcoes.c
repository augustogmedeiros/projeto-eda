#include "struct_func.h"
#include <stdio.h>

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
    novo->prox = *lista; 
    *lista = novo;
    printf("Produto cadastrado com sucesso!\n");//possivelmente adicionar verif de produto unico

}

// 2. LISTAR TODOS OS PRODUTOS
void Listar_Produto(Produto *lista) 
{
    if (lista == NULL) 
    {
        printf("\nNenhum produto cadastrado.\n");
        return;
    }

    Produto *aux = lista;
    printf("\n--- LISTA DE PRODUTOS ---\n");
    while (aux != NULL) {
        printf("Codigo: %d | Nome: %s | Preco: %d | Estoque: %d\n", 
               aux->codigo, aux->nome, aux->preco, aux->estoque);
        aux = aux->prox;
    }
}
