#ifndef STRUCT_FUNC_H
#define STRUCT_FUNC_H

typedef struct  Cliente Cliente;
typedef struct  ItemCarrinho ItemCarrinho;
typedef struct   Produto Produto;

struct Produto
{
    int     codigo;
    char    nome[50];
    float   preco;
    int     estoque;

    Produto *prox;
};

struct ItemCarrinho
{
    Produto         *Produto;
    int             quantidade_compra;
    ItemCarrinho    *prox; 
};

struct Cliente 
{
    char    cpf[15];
    char    nome[100];
    char    email[100];
    char    telefone[20];
    char    data_nascimento[12];

    ItemCarrinho *Carrinho; // usei o ponteiro errado aq
    Cliente *prox;
};
#endif