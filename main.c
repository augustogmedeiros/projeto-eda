#include <stdio.h>
#include <stdlib.h>
#include "struct_func.h" 
#include "funcoes.h"     

int main() 
{
    Produto *lista_produtos = NULL;
    Cliente *lista_clientes = NULL;
    int opcao_menu1 = 0;
    int opcao_menu2 = 0;

    do 
    {
        Menu_Inicial(&opcao_menu1); 

        switch (opcao_menu1) 
        {
            case 1:
                do {
                    printf("\n ===== GESTAO DE CLIENTES =====\n");
                    printf(" 1. Cadastrar Novo Cliente\n");
                    printf(" 2. Listar Clientes\n");
                    printf(" 3. Editar Cliente\n");
                    printf(" 4. Apagar Cliente\n");
                    printf(" 5. Voltar ao Menu Principal\n"); 
                    printf("\n");
                    printf(" Escolha uma opcao: ");
                    scanf("%d", &opcao_menu2);
                    printf("\n");
                    Limpar_Buffer(); 

                    switch (opcao_menu2) 
                    {
                        case 1: Cadastrar_Cliente(&lista_clientes); break;
                        case 2: Listar_Clientes(lista_clientes); break;
                        case 3: Editar_Cliente(lista_clientes); break;
                        case 4: Apagar_Cliente(&lista_clientes); break;
                        case 5: printf(" Voltando ao Menu Principal\n"); break;
                        default: printf(" Opcao invalida\n");
                    }
                } while (opcao_menu2 != 5); 
                break;


            case 2:
                do {
                    printf("\n===== GESTAO DE PRODUTOS =====\n");
                    printf(" 1. Cadastrar Novo Produto\n");
                    printf(" 2. Listar Produtos (Estoque)\n");
                    printf(" 3. Editar Produto\n");
                    printf(" 4. Apagar Produto\n");
                    printf(" 5. Voltar ao Menu Principal\n");
                    printf("\n");
                    printf(" Escolha uma opcao: ");
                    scanf("%d", &opcao_menu2);
                    printf("\n");
                    Limpar_Buffer();

                    switch (opcao_menu2) 
                    {
                        case 1: Cadastrar_Produto(&lista_produtos); break;
                        case 2: Listar_Produto(lista_produtos); break;
                        case 3: Editar_Produto(lista_produtos); break;
                        case 4: Apagar_Produto(&lista_produtos); break;
                        case 5: printf(" Voltando ao Menu Principal\n"); break;
                        default: printf(" Opcao invalida\n");
                    }
                } while (opcao_menu2 != 5);
                break;


            case 3:
                do {
                    printf("\n===== CARRINHO DE COMPRAS =====\n");
                    printf(" 1. Adicionar Item ao Carrinho\n");
                    printf(" 2. Ver Carrinho de um Cliente\n");
                    printf(" 3. Remover Item do Carrinho\n");
                    printf(" 4. Voltar ao Menu Principal\n"); 
                    printf("\n");
                    printf(" Escolha uma opcao: ");
                    scanf("%d", &opcao_menu2);
                    printf("\n");
                    Limpar_Buffer();

                    switch (opcao_menu2) 
                    {
                        case 1: Adicionar_ao_Carrinho(lista_clientes, lista_produtos); break;
                        case 2: Listar_Carrinho(lista_clientes); break;
                        case 3: Remover_do_Carrinho(lista_clientes, lista_produtos); break;
                        case 4: printf(" Voltando ao Menu Principal\n"); break;
                        default: printf(" Opcao invalida\n");
                    }
                } while (opcao_menu2 != 4);
                break;


            case 0:
                printf("\n Encerrando o sistema e limpando memoria\n");
                break;

            default:
                printf("\n Opcao invalida no Menu Principal\n");
        }

    } while (opcao_menu1 != 0);
    return 0;
}