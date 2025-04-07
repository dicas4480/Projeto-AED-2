#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define ENCOMENDAS_H

#define MAX_string 500

typedef struct {
    char nome[30];
    /*podemos adicionar
    mais detalhes para 
    a estrutura pessoa*/
}Pessoa;

typedef struct{
    int dia;
    int mes;
    int ano;
}Dia;

typedef struct {
    int id;
    Pessoa cliente;
    char descricao[MAX_string];
    Dia data;
}Encomenda;

typedef struct NoEncomenda{
    Encomenda encomenda;      // criarmos um tipo encomenda para aceder as infos das encoemndas
    struct NoEncomenda *proximo;
}NoEncomenda;

void lerDataValida(Dia *data) {
    int dia, mes, ano;
    int data_valida = 0;

    // isto quer dizer que o ciclo so vai terminar quando
    // a variavel data_valida for verdadeira/tomar o valor de 1
    while (!data_valida) {
        printf("Introduza a data (dia/mes/ano):\n");
        scanf("%d/%d/%d", &dia, &mes, &ano);

        if (ano < 1900) {
            printf("Ano inválido! O ano deve ser maior ou igual a 1900.\n");
            continue;
        }

        if (mes < 1 || mes > 12) {
            printf("Mês inválido! Deve estar entre 1 e 12.\n");
            continue;
        }

        int dias_no_mes;
        switch (mes) {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                dias_no_mes = 31; 
                break;

            case 4: case 6: case 9: case 11:
                dias_no_mes = 30;
                 break;

            case 2:
                dias_no_mes = 28;
                 break;
        }

        if (dia < 1 || dia > dias_no_mes) {
            printf("Dia inválido! Esse mês tem apenas %d dias.\n", dias_no_mes);
            continue;
        }

        data_valida = 1;
    }

    data->dia = dia;
    data->mes = mes;
    data->ano = ano;
}

void inserirEncomenda(NoEncomenda **lista_encomendas, Encomenda nova_encomenda){

    NoEncomenda *nova = (NoEncomenda*)malloc(sizeof(NoEncomenda));
    nova->encomenda = nova_encomenda;
    nova->proximo = NULL;

    if(*lista_encomendas == NULL){
        *lista_encomendas = nova;
    }else{
        NoEncomenda *temp = *lista_encomendas;
        while(temp!=NULL){

            temp = temp->proximo;
        }

        temp->proximo = nova;
    }

}

void criarEncomenda(Encomenda *nova_encomenda){

    printf("Introduza o id da encomenda :\n");
    scanf("%d",&nova_encomenda->id);
    getchar();         // usada para limpar o buffer de entrada, para depois fazer um fgtes sem problemas
    
    printf("Introduza o nome do cliente:\n");
    fgets(nova_encomenda->cliente.nome,30,stdin);
    nova_encomenda->cliente.nome[strcspn(nova_encomenda->cliente.nome, "\n")] = '\0';  // usamos isto para tirar o \n do enter que o fgets mete 

    printf("Escreva uma breve descricao do produto :\n");
    fgets(nova_encomenda->descricao,500,stdin);
    nova_encomenda->descricao[strcspn(nova_encomenda->descricao, "\n")] = '\0';  

    printf("Introduza a data:(dia/mes/ano)\n");
    scanf("%d/%d/%d",&nova_encomenda->data.dia,&nova_encomenda->data.mes,&nova_encomenda->data.ano);

    // Data da Encomenda
    // Chama uma função que garante que a data introduzida é válida
    // (dia dentro do mês, mês entre 1 e 12, ano ≥ 1900, fevereiro sempre com 28 dias) 
    lerDataValida(&nova_encomenda->data);


    // e tambem convem mais tarde criar uma funçao que guarde esta informaçao num ficheiro


}


void listarEncomendas(NoEncomenda *lista_encomendas){

    if(lista_encomendas==NULL){
        printf("\nLista Vazia\n");
        return;
    }

    while(lista_encomendas!=NULL){

        printf("Id: %d || Cliente : %s || Data: %02d/%02d/%04d\n",lista_encomendas->encomenda.id,lista_encomendas->encomenda.cliente.nome,lista_encomendas->encomenda.data.dia,lista_encomendas->encomenda.data.mes,lista_encomendas->encomenda.data.ano);

        printf("Descricao : %s\n",lista_encomendas->encomenda.descricao);

        lista_encomendas = lista_encomendas -> proximo ;
    }
}

// Funcao para libertar a memoria alocada para a lista de encomendas
// Esta funcao percorre a lista e liberta cada nodo, garantindo que não há vazamentos de memória.
// A função é chamada quando a lista de encomendas não é mais necessária,
// garantindo que toda a memória alocada é libertada corretamente e
// permitindo que a lista seja atualizada para NULL após a libertação da memória.
void libertar_encomendas(NoEncomenda **lista_encomendas){
    NoEncomenda *temp;
    while(*lista_encomendas != NULL){
        temp = *lista_encomendas;
        *lista_encomendas = (*lista_encomendas)->proximo;
        free(temp);
    }
}

// A função é útil para gerenciar a lista de encomendas, permitindo que o utilizador remova encomendas específicas quando necessário.
// A função percorre a lista de encomendas, procurando o nodo com o ID especificado.
// Se encontrado, o nodo é removido da lista e a memória alocada para ele é libertada.
void atualizar_estado_encomenda(NoEncomenda *lista_encomendas, int id){
    NoEncomenda *temp = lista_encomendas;
    while(temp != NULL){
        if(temp->encomenda.id == id){
            printf("Estado da encomenda %d atualizado com sucesso!\n", id);
            return;
        }
        temp = temp->proximo;
    }
    printf("Encomenda com ID %d não encontrada.\n", id);
}


// Funcao para remover uma encomenda da lista
// Esta funcao percorre a lista de encomendas, procurando o nodo com o ID especificado.
// Se encontrado, o nodo é removido da lista e a memória alocada para ele é libertada.
// A função também atualiza a lista de encomendas para refletir a remoção e imprime uma mensagem de sucesso ou erro.
void remover_encomenda(NoEncomenda **lista_encomendas, int id){
    NoEncomenda *temp = *lista_encomendas;
    NoEncomenda *anterior = NULL;

    while(temp != NULL && temp->encomenda.id != id){
        anterior = temp;
        temp = temp->proximo;
    }

    if(temp == NULL){
        printf("Encomenda com ID %d não encontrada.\n", id);
        return;
    }

    if(anterior == NULL){
        *lista_encomendas = temp->proximo;
    }else{
        anterior->proximo = temp->proximo;
    }

    free(temp);
    printf("Encomenda com ID %d removida com sucesso!\n", id);
}

