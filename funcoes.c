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

void Menu_Inicial(int *n) {
    printf("\n\n"); 
    printf("==========================================\n");
    printf("---------------MENU INICIAL---------------\n"); //alterar nome futuramente
    printf("==========================================\n");
    printf("  [1] Gerenciamento de Clientes\n");
    printf("  [2] Gerenciamento de Produtos\n");
    printf("  [3] Modo Compra (Carrinho)\n");
    printf("  [0] Sair do Programa\n");
    scanf("%d", n);
    Limpar_Buffer();
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

// função auxiliar para o cliente, retorna o endereço de memoria ou NULL
Cliente* Buscar_Cliente(Cliente *lista, char *cpf) {
    Cliente *aux = lista; // ponteiro para o inicio da lista

    // percorre a lista ate NULL (fim)
    while (aux != NULL) {
        // se o cpf for igual, retorna 0
        if (strcmp(aux->cpf, cpf) == 0) {
            return aux; // retorna o ponteiro para o cliente
        }
        aux = aux->prox;
    }
    return NULL; // nao encontrou cliente com o cpf cadastrado
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
    scanf("%f", &novo->preco);
    Limpar_Buffer();
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
        printf("Codigo: %d | Nome: %s | Preco: %.2f | Estoque: %d\n", //formato
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

    printf("\nProduto encontrado: %s Preco atual: %.2f\n", aux->nome, aux->preco); //nao alterar codigo
    printf("Digite o Novo Nome: ");
    scanf(" %49[^\n]", aux->nome); 
    Limpar_Buffer();
    Edita_Nome(aux->nome, 0); //padroniza novamente  
    printf("Digite o Novo Preco: ");
    scanf("%f", &aux->preco);
    printf("Digite o Novo Estoque: ");
    scanf("%d", &aux->estoque);
    Limpar_Buffer();

    printf("Produto atualizado com sucesso!\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------CLIENTE--------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////////
void Cadastrar_Cliente(Cliente **lista) {
    printf("--- CADASTRO DE CLIENTE --- \n");

    char cpf_temp[15]; // verifica se o cpf ja foi cadastrado
    printf("Digite o CPF: ");
    scanf(" %[^\n]", cpf_temp);

    if (Buscar_Cliente(*lista, cpf_temp) != NULL) {
        printf("[ERRO] Este CPF ja esta cadastrado [ERRO] \n");
        return;
    }
    Cliente *novo = (Cliente*) malloc(sizeof(Cliente));
    Check(novo); // verifica o malloc

    // copia o cpf para a struct
    strcpy(novo->cpf, cpf_temp);

    // leitura dos dados
    printf("Nome Completo: ");
    scanf(" %[^\n]", novo->nome);
    Edita_Nome(novo->nome, 0); // formata o nome
    Limpar_Buffer();

    printf("Email: ");
    scanf(" %[^\n]", novo->email);
    Edita_Nome(novo->email, 1); // formata o email
    Limpar_Buffer();

    printf("Telefone: ");
    scanf(" %[^\n]", novo->telefone);
    Limpar_Buffer();

    printf("Data de Nascimento (DD/MM/AAAA): \n");
    scanf(" %[^\n]", novo->data_nascimento);
    Limpar_Buffer();

    novo->Carrinho = NULL; // carrinho do cliente começa vazio
    novo->prox = *lista; // O novo aponta para o antigo primeiro
    *lista = novo;       // O ponteiro principal agora aponta para o novo
    printf("Cliente cadastrado!\n");
}


void Listar_Clientes(Cliente *lista) {
    if (lista == NULL) {
        printf("\n[ERRO] Nenhum cliente cadastrado [ERRO]\n");
        return;
    }

    printf("\n--- LISTA DE CLIENTES --- \n");
    Cliente *aux = lista;
    
    while (aux != NULL) {
        printf("CPF: %-14s | Nome: %-20s | Email: %s\n", 
               aux->cpf, aux->nome, aux->email);
        printf("   Tel: %-14s | Nasc: %s\n", 
               aux->telefone, aux->data_nascimento);
        printf("----------------------------------------------------\n");
        
        aux = aux->prox;
    }
}

void Editar_Cliente(Cliente *lista) {
    char cpf[15];
    printf("\n--- EDITAR CLIENTE --- \n");
    printf("Digite o CPF do cliente que deseja editar: ");
    scanf(" %[^\n]", cpf);

    Cliente *encontrado = Buscar_Cliente(lista, cpf);

    if (encontrado == NULL) {
        printf("[ERRO] Cliente nao encontrado [ERRO]\n");
        return;
    }

    // se encontrar, edita os dados diretamente no ponteiro
    printf("Cliente Encontrado: %s\n", encontrado->nome);
    printf("Digite os novos dados \n");

    printf("Novo Nome: ");
    scanf(" %[^\n]", encontrado->nome);
    Edita_Nome(encontrado->nome, 0);

    printf("Novo Email: ");
    scanf(" %[^\n]", encontrado->email);
    Edita_Nome(encontrado->email, 1);

    printf("Novo Telefone: ");
    scanf(" %[^\n]", encontrado->telefone);

    printf("Dados atualizados!\n");
}

void Apagar_Cliente(Cliente **lista) {
    char cpf[15];
    printf("\n--- APAGAR CLIENTE ---\n");
    printf("Digite o CPF do cliente a ser excluido: ");
    scanf(" %[^\n]", cpf);

    if (*lista == NULL) {
        printf("[ERRO] Lista vazia [ERRO]\n");
        return;
    }
    Cliente *anterior = NULL;
    Cliente *atual = *lista;

    // loop para encontrar o nó e manter o ponteiro para o anterior
    while (atual != NULL && strcmp(atual->cpf, cpf) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    // se o loop percorrer tudo e não encontrar (NULL)
    if (atual == NULL) {
        printf("[ERRO] Cliente nao encontrado [ERRO]\n");
        return;
    }

    // se o cliente apagado for o primeiro da lista
    if (anterior == NULL) {
        *lista = atual->prox; // passa o inicio da lista para o segundo elemento
    } 
    // se o cliente apagado nao for o primeiro da lista
    else {
        anterior->prox = atual->prox; // o anterior pula o apagado e aponta para o proximo da lista
    }

    free(atual);
    printf("Cliente removido permanentemente.\n");
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