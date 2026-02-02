#ifndef FUNCOES_H
#define FUNCOES_H

#include "struct_func.h"
//funcoes gerais
void Menu_Inicial(int *n);
void Limpar_Buffer();
void Check(void *ptr);
void Edita_Nome(char *nome, int modo); //modo 0 para nome, modo 1 para email 

//funcoes do cliente
void Cadastrar_Cliente(Cliente **lista);
void Listar_Clientes(Cliente *lista);
void Menu_Editar_Cliente(Cliente *lista);
void Menu_Apagar_Cliente(Cliente **lista);
Cliente* Buscar_Cliente(Cliente *lista, char *cpf);


//funcoes de produto
void Cadastrar_Produto (Produto **lista);
void Listar_Produto (Produto *lista);
//quero usar o resultado como conf de parm para
//passar pra main(se o produto existe)
void Menu_Editar_Produto (Produto *lista);
void Menu_Apagar_Produto (Produto **lista);
Produto* Buscar_Produto (Produto *lista, int codigo);


//funcoes de produto/carrinhoo
void Menu_Compra(Cliente *lista_clientes, Produto *lista_produtos);
void Adicionar_ao_Carrinho(Cliente *cliente, Produto *lista_produtos); //localiza e adiciona o produto
void Listar_Carrinho(Cliente *cliente); //percorre a lista do carrinho e soma o total
void Remover_do_Carrinho(Cliente *cliente, int codigo); //remove 1 prdotuo


#endif