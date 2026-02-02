#ifndef FUNCOES_H
#define FUNCOES_H

#include "struct_func.h"


//funcoes de produto
void Cadastrar_Produto (Produto **lista);
void Listar_Produto (Produto *lista);
Produto* Buscar_Produto (Produto *lista, int codigo); //quero usar o resultado como conf de parm para
//passar pra main(se o produto existe)
void Editar_Produto (Produto *lista, int codigo);
void Apagar_Produto (Produto **lista, int codigo);


//funcoes de produto/carrinho
void Adicionar_ao_Carrinho(Cliente *cliente, Produto *lista_produtos); //localiza e adiciona o produto
void Listar_Carrinho(Cliente *cliente); //percorre a lista do carrinho e soma o total
void Remover_do_Carrinho(Cliente *cliente, int codigo); //remove 1 prdotuo


#endif