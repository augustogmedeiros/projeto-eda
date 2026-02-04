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
    {     printf("\n[ERRO] Falha na alocacao de memória [ERRO]\n"); exit(1);    }
}


void Menu_Inicial(int *n) {
    printf("\n\n"); 
    printf("=============== MENU INICIAL ===============\n"); //alterar nome futuramente
    printf("  [1] Gerenciamento de Clientes\n");
    printf("  [2] Gerenciamento de Produtos\n");
    printf("  [3] Carrinho\n");
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
    while (aux != NULL) 
    {
        if (aux->codigo == codigo) 
        {
            return aux; //retorna endereço se enconrar
        }
        aux = aux->prox; //seguimento
    }

    return NULL;
}


// função auxiliar para o cliente, retorna o endereço de memoria ou NULL
Cliente* Buscar_Cliente(Cliente *lista, char *cpf) 
{
    Cliente *aux = lista; // ponteiro para o inicio da lista

    // percorre a lista ate NULL (fim)
    while (aux != NULL) 
    {
        // se o cpf for igual, retorna 0
        if (strcmp(aux->cpf, cpf) == 0) 
        {
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
    printf("===== CADASTRO DE PRODUTO ===== \n");
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
    printf("\n===== LISTA DE PRODUTOS =====\n");
    while (aux != NULL) 
    {
        printf("Codigo: %d | Nome: %s | Preco: %.2f | Estoque: %d\n", //formato
        aux->codigo, aux->nome, aux->preco, aux->estoque);
        aux = aux->prox;
    }
}


void Apagar_Produto(Produto **lista)
{
    printf("===== REMOCAO DE PRODUTO ===== \n");
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
    {     printf("\n[ERRO] Produto com o código: %d não encontrado [ERRO]\n", codigo_remocao); return;    }

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
    printf("===== ATUALIZACAO DE PRODUTO ===== \n");
    int codigo;
    printf("Digite o código do Produto a ser editado: ");
    scanf("%d", &codigo);
    Limpar_Buffer();
    Produto *aux = Buscar_Produto(lista, codigo);

    if (aux == NULL) //nao encontrado
    {    printf("[ERRO] Produto com código %d nao encontrado [ERRO]\n", codigo); return;    }
        
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
/*--------------------------------------CLIENTE/PRODUTOS-----------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////////


void Cadastrar_Cliente(Cliente **lista) 
{
    printf("===== CADASTRO DE CLIENTE ===== \n");

    char cpf_temp[15]; // verifica se o cpf ja foi cadastrado
    int valido;
    unsigned int i; // contador

    do {
        valido = 1;
        printf("Digite o CPF: ");
        scanf(" %[^\n]", cpf_temp);
        Limpar_Buffer();

        if (strlen(cpf_temp) != 11) { //cpf tem que ter tamanho 11
            valido = 0;
            printf("[ERRO] CPF invalido \n");
        }
    } while(valido == 0);

    if (Buscar_Cliente(*lista, cpf_temp) != NULL) {
        printf("[ERRO] Este CPF ja esta cadastrado [ERRO] \n");
        return;
    }
    Cliente *novo = (Cliente*) malloc(sizeof(Cliente));
    Check(novo); // verifica o malloc

    // copia o cpf para a struct
    strcpy(novo->cpf, cpf_temp);

    // leitura dos dados
   do {
        valido = 1;
        printf("Nome Completo: ");
        scanf(" %[^\n]", novo->nome);
        Limpar_Buffer();

        for(i = 0; i < strlen(novo->nome); i++) {
            // 
            if(!isalpha(novo->nome[i]) && !isspace(novo->nome[i])) { //nome tem que ter apenas letras ou espaço
                valido = 0;
                break;
            }
        }
        
        if(!valido) printf("[ERRO] Nome invalido [ERRO] \n");
    } while(valido == 0);

    Edita_Nome(novo->nome, 0); // formata o nome

    printf("Email: ");
    scanf(" %[^\n]", novo->email);
    Limpar_Buffer(); 
    Edita_Nome(novo->email, 1); // formata o email

    do {
        valido = 1;
        printf("Telefone: ");
        scanf(" %[^\n]", novo->telefone);
        Limpar_Buffer();

        if(strlen(novo->telefone) < 8) { // telefone 8 digitos ou mais
            valido = 0;
            printf("[ERRO] Telefone invalido [ERRO]\n");
        }
    } while(valido == 0);

    printf("Data de Nascimento (DD/MM/AAAA): ");
    scanf(" %[^\n]", novo->data_nascimento);
    Limpar_Buffer(); 

    novo->Carrinho = NULL; // carrinho do cliente começa vazio
    novo->prox = *lista; // O novo aponta para o antigo primeiro
    *lista = novo;       // O ponteiro principal agora aponta para o novo
    printf("Cliente cadastrado\n");
}

void Listar_Clientes(Cliente *lista) 
{
    if (lista == NULL) {
        printf("\n[ERRO] Nenhum cliente cadastrado [ERRO]\n"); return;   }
        
    

    printf("\n===== LISTA DE CLIENTES ===== \n");
    Cliente *aux = lista;
    
    while (aux != NULL) {
        printf("CPF: %-14s | Nome: %-20s | Email: %s\n", 
               aux->cpf, aux->nome, aux->email);
        printf("   Tel: %-14s | Nasc: %s\n", 
               aux->telefone, aux->data_nascimento);
        printf("==========================================\n");
        
        aux = aux->prox;
    }
}


void Editar_Cliente(Cliente *lista) 
{
    char cpf[15];
    int valido; // variavel de controle
    unsigned int i; // contador

    printf("\n===== EDITAR CLIENTE ===== \n");
    printf("Digite o CPF do cliente que deseja editar: ");
    scanf(" %[^\n]", cpf);
    Limpar_Buffer(); 

    Cliente *encontrado = Buscar_Cliente(lista, cpf);
    if (encontrado == NULL) {   printf("[ERRO] Cliente nao encontrado [ERRO]\n"); return;   }
        
    // se encontrar, edita os dados diretamente no ponteiro
    printf("Cliente Encontrado: %s\n", encontrado->nome);
    printf("Digite os novos dados \n");

    do {
        valido = 1;
        printf("Novo Nome: ");
        scanf(" %[^\n]", encontrado->nome);
        Limpar_Buffer();

        for(i = 0; i < strlen(encontrado->nome); i++) {
            if(!isalpha(encontrado->nome[i]) && !isspace(encontrado->nome[i])) {
                valido = 0;
                break;
            }
        }
        
        if(!valido) printf("[ERRO] Nome invalido [ERRO]\n");
    } while(valido == 0);

    Edita_Nome(encontrado->nome, 0);

    printf("Novo Email: ");
    scanf(" %[^\n]", encontrado->email);
    Limpar_Buffer(); 
    Edita_Nome(encontrado->email, 1);

    do {
        valido = 1;
        printf("Novo Telefone: ");
        scanf(" %[^\n]", encontrado->telefone);
        Limpar_Buffer();

        if(strlen(encontrado->telefone) < 8) { // telefone tem que possuir 8 digitos ou mais
            valido = 0;
            printf("[ERRO] Telefone invalido [ERRO]\n"); 
        }
    } while(valido == 0);

    printf("Dados atualizados!\n");
}

void Apagar_Cliente(Cliente **lista) 
{
    char cpf[15];
    printf("\n===== APAGAR CLIENTE =====\n");
    printf("Digite o CPF do cliente a ser excluido: ");
    scanf(" %[^\n]", cpf);

    if (*lista == NULL) {   printf("[ERRO] Lista vazia [ERRO]\n"); return;    }

    Cliente *anterior = NULL;
    Cliente *atual = *lista;

    // loop para encontrar o nó e manter o ponteiro para o anterior
    while (atual != NULL && strcmp(atual->cpf, cpf) != 0) 
    {
        anterior = atual;
        atual = atual->prox;
    }

    // se o loop percorrer tudo e não encontrar (NULL)
    if (atual == NULL) {    printf("[ERRO] Cliente nao encontrado [ERRO]\n"); return;   }

    Produto *p_temp = atual->Carrinho;//apagando carrinho antes de apagar cliente p evitar lixo d emmoria
    Produto *p_prox;
    while(p_temp != NULL) {
        p_prox = p_temp->prox;
        free(p_temp);
        p_temp = p_prox;
    }

    // se o cliente apagado for o primeiro da lista
    if (anterior == NULL) {     *lista = atual->prox;   }
    // passa o inicio da lista para o segundo elemento se o cliente apagado nao for o primeiro da lista

    else {   anterior->prox = atual->prox;   } 
    // o anterior pula o apagado e aponta para o proximo da lista    
    

    free(atual);
    printf("Cliente removido permanentemente.\n");
}


///////////////////////////////////////////////////////////////////////////////////////////////////
/*------------------------------------------MODO COMPRA------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////////


void Adicionar_ao_Carrinho(Cliente *lista_c, Produto *lista_p )
{
    char cpf[15];
    int codigo, qtd;
    printf("\n===== ADICIONAR AO CARRINHO =====\n");
    printf("Digite o CPF do cliente: ");
    scanf(" %14[^\n]", cpf);
    Cliente *c = Buscar_Cliente(lista_c, cpf);  //checa se cliente existe 
    if (c == NULL)  {   printf("[ERRO] Cliente não encontrado [ERRO]\n"); return; }

    printf("Digite o código do produto :");
    scanf("%d", &codigo);

    Produto *p = Buscar_Produto(lista_p, codigo);  //checa se produto existe 
    if (p == NULL)   {   printf("[ERRO] Produto não encontrado [ERRO]\n"); return;   }
    
        
    printf("Digite a quantidade desejada :");
    scanf("%d", &qtd);

    if(qtd > p->estoque)
    {
        printf("[ERRO] Estoque insuficiente [ERRO]\n"); 
        printf("Quantidade Disponível: %d\n", p->estoque); 
        return;
    }
    if(qtd <= 0) {    printf("[ERRO] Quantidade invalida [ERRO]\n"); return;    }

    Produto *novo_item = (Produto*) malloc(sizeof(Produto));//aloca
    Check(novo_item);//checa alocacao

    novo_item->codigo = p->codigo;
    strcpy(novo_item->nome, p->nome); 
    novo_item->preco = p->preco;
    novo_item->estoque = qtd;
    // Copia do estoque para o carrinho designado

    novo_item->prox = c->Carrinho;//coloca no crrinho
    c->Carrinho = novo_item;

    p->estoque -= qtd;//atualiza estoque

    printf("%s adicionado ao carrinho!\n", p->nome);
}



void Listar_Carrinho(Cliente *lista_c)//checa se cliente existe/carrinho esta vazio
{   
    Cliente *c;
    char cpf[15];
    float valor_total = 0;
    int total_itens = 0;
    Produto *aux;
    
    
    printf("\n===== CARRINHO: =====\n");
    printf("Digite o CPF do cliente: ");
    scanf(" %14[^\n]", cpf);
    Limpar_Buffer();

    c = Buscar_Cliente(lista_c, cpf);
    if (c == NULL)
    {   printf("[ERRO] Cliente não encontrado [ERRO]\n");    }
    
    else
    {
        aux = c->Carrinho;//atribuindo ao carrinho certo
        if (c->Carrinho == NULL) 
        {   printf("Seu carrinho está vazio!\n");     }
        else 
        {
            printf("\n===== CARRINHO DE COMPRAS: =====");  
        }

        while (aux != NULL) 
        {
            float subtotal = aux->preco * aux->estoque;

            printf("Cód: %-4d | Produto: %-15s | Qtd: %-3d | Preço Un: %.2f | Subtotal: %.2f\n",
                   aux->codigo, aux->nome, aux->estoque, aux->preco, subtotal);

            valor_total += subtotal;
            total_itens += aux->estoque;
            aux = aux->prox; 
        }

        printf("==========================================\n");
        printf("===== TOTAL DE ITENS: %d \n", total_itens);
        printf("===== VALOR TOTAL DA COMPRA: R$ %.2f \n", valor_total);
        printf("==========================================\n");
    }
}


void Remover_do_Carrinho(Cliente *lista_c, Produto *lista_p) //passar oq esta no carrinho ao inves de codigo
{
    char cpf[15];
    int codigo_busca;
    Cliente *c;

    printf("===== REMOVER ITEM DO CARRINHO =====\n");
    printf("Digite o CPF do cliente: ");
    scanf(" %14[^\n]", cpf);

    c = Buscar_Cliente(lista_c, cpf);
    if (c == NULL)  {   printf("[ERRO] Cliente não encontrado [ERRO]\n"); return;   }
    

    if (c->Carrinho == NULL)     { printf("Seu carrinho está vazio!\n"); return; }

    printf("Digite o código do produto que deseja remover: ");
    scanf("%d", &codigo_busca);
    Limpar_Buffer();

    Produto *anterior = NULL;
    Produto *atual = c->Carrinho; 
    while (atual != NULL && atual->codigo != codigo_busca) //procura o produto pela lista
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) //nao encontrado
    {   printf("[ERRO] O Produto com código %d não está no carrinho [ERRO]\n", codigo_busca); return;  }
          
    Produto *p_estoque = Buscar_Produto(lista_p, codigo_busca);
    if (p_estoque != NULL) //se encontrado, checa se o produto ainda existe
    {
        p_estoque->estoque += atual->estoque; // Devolve a quantidade escolhida
    }

    if (anterior == NULL) 
    {
        c->Carrinho = atual->prox;//primeiro da lista
    } 
    else 
    {
        anterior->prox = atual->prox;//meio ou fim
    }

    free(atual);

    printf("Item %d removido do carrinho!\n", codigo_busca);
}   