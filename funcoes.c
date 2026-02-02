#include "struct_func.h"
#include "funcoes.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
/*printf("--- xxxxxxxxxxxxxxxxxxxxxxxxxxxxx --- \n");*/
/*printf("[ERRO] xxxxxxxxxxxxxxxxxxxxxxxxx [ERRO]\n", codigo);*/

///////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------AUXILIARES------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////////

void Limpar_Buffer() //limpa o buffer do teclado
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void Check(void *ptr) //checa se a alocação deu certo
{
    if (ptr == NULL) 
    {
        printf("\n[ERRO] Falha na alocacao de memória [ERRO]\n");
        exit(1); 
    }
}

void Edita_Nome(char *nome, int modo) 
{
    //remove o \n do final do fgets
    size_t tam = strlen(nome);
    // strlen retorna unsigned, por isso utilizamos unsigned int no for ( evitar o warning)
    for(unsigned int i = 0; i < tam; i++) 
    {
        if(modo == 0) 
        { 
           //altera para maiuscula a primeira letra ou apos o espaço
            if(i == 0 || nome[i-1] == ' ') 
            {    
                nome[i] = toupper(nome[i]);
            } else {
                nome[i] = tolower(nome[i]);
            }
        }
        else if(modo == 1) 
        { 
            // tudo minusculo se for modo 1: email
            nome[i] = tolower(nome[i]);
        }
    }
}

Produto* Buscar_Produto(Produto *lista, int codigo)
{
    Produto *aux = lista;
    while (aux != NULL) {
        if (aux->codigo == codigo) 
        {
            return aux; //retorna endereço se enconrar
        }
        aux = aux->prox; //seguimento
    }

    return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------LOGICAS--------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////////



void Cadastrar_Produto(Produto **lista)
{
    printf("--- CADASTRO DE PRODUTO --- \n");
    Produto *novo = (Produto*) malloc(sizeof(Produto)); 
    Check(novo);//checa se a memoria foi alocada

    printf("Digite o Código do Produto: ");
    scanf("%d", &novo->codigo);
    Limpar_Buffer();
    printf("Digite o Nome do Produto: ");
    scanf("%49[^\n]", novo->nome); //funçao p ler com espaços sem usar fgets(nao logico p ignorar espaço)
    Limpar_Buffer();
    Edita_Nome(novo->nome, 0); // padroniza nome
    printf("Digite o Preço do Produto: ");
    scanf("%d", &novo->preco);
    printf("Digite o Estoque Disponível do Produto: "); /*(add futuramente funcao pra subtrair automaticamente do estoque
    quando um produto entra no carrinho de um cliente?)*/
    scanf("%d", &novo->estoque);
    Limpar_Buffer();
    novo->prox = *lista; 
    *lista = novo;
    printf("Produto cadastrado com sucesso!\n");//possivelmente adicionar verif de produto unico

}


void Listar_Produto(Produto *lista) 
{
    if (lista == NULL) 
    {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    Produto *aux = lista;
    printf("\n--- LISTA DE PRODUTOS ---\n");
    while (aux != NULL) 
    {
        printf("Codigo: %d | Nome: %s | Preco: %d | Estoque: %d\n", //formato
        aux->codigo, aux->nome, aux->preco, aux->estoque);
        aux = aux->prox;
    }
}


void Apagar_Produto(Produto **lista)
{
    printf("--- REMOCAO DE PRODUTO --- \n");
    int codigo_remocao;
    printf("Digite o código do Produto a ser removido: ");
    scanf("%d", &codigo_remocao);
    Limpar_Buffer();

    Produto *anterior = NULL;
    Produto *atual = *lista;

    while (atual != NULL && atual->codigo != codigo_remocao) //andando plea lista
    {
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL)
    {
        printf("Produto com o código: %d não encontrado. \n", codigo_remocao);
        return;
    }

    if (anterior == NULL) //anterios==null == while nao rodou == começo da lista
    {
        *lista = atual->prox;//ponteiro inicial agr aponta para 2* elemtno
    } 
    else //meio ou fim da lista
    {
        anterior->prox = atual->prox;
    }
    free(atual);//solta a memoria
    
    printf("Produto removido com sucesso! \n");
}


void Editar_Produto(Produto *lista)
{
    printf("--- ATUALIZACAO DE PRODUTO --- \n");
    int codigo;
    printf("Digite o código do Produto a ser editado: ");
    scanf("%d", &codigo);
    Limpar_Buffer();
    Produto *aux = Buscar_Produto(lista, codigo);

    if (aux == NULL) //nao encontrado
    {
        printf("[ERRO] Produto com código %d nao encontrado. [ERRO]\n", codigo);
        return;
    }

    printf("\nProduto encontrado: %s Preco atual: %d\n", aux->nome, aux->preco); //nao alterar codigo
    printf("Digite o Novo Nome: ");
    scanf("%49[^\n]", aux->nome); 
    Limpar_Buffer();
    Edita_Nome(aux->nome, 0); //padroniza novamente  
    printf("Digite o Novo Preco: ");
    scanf("%d", &aux->preco);
    printf("Digite o Novo Estoque: ");
    scanf("%d", &aux->estoque);
    Limpar_Buffer();

    printf("Produto atualizado com sucesso!\n");
}


















































/*void Libera_Lista(Produto **lista)      //NAO PRECISA??//
{
    Produto *atual = *lista;
    Produto *proximo_no;

    while(atual != NULL)
    {
        proximo_no = atual->prox; // end -> prox
        free(atual);             // apaga atual
        atual = proximo_no;       // anda pela lista
    }
    *lista==NULL;
    
    printf("Lista apagada e memória liberada com sucesso! \n");
}*/






