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
void Editar_Cliente(Cliente *lista);
void Apagar_Cliente(Cliente **lista);
Cliente* Buscar_Cliente(Cliente *lista, char *cpf);


//funcoes de produto
void Cadastrar_Produto (Produto **lista);
void Listar_Produto (Produto *lista);
void Editar_Produto (Produto *lista);
void Apagar_Produto (Produto **lista);
Produto* Buscar_Produto (Produto *lista, int codigo);


//funcoes de produto/carrinhoo
void Menu_Compra(Cliente *lista_clientes, Produto *lista_p);
void Adicionar_ao_Carrinho(Cliente *cliente, Produto *lista_p); //localiza e adiciona o produto
void Listar_Carrinho(Cliente *cliente); //percorre a lista do carrinho e soma o total
void Remover_do_Carrinho(Cliente *lista_c,Produto *lista_p ); //remove 1 prdotuo

#endif