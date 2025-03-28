#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define ENCOMENDAS_H

#define MAX_string 500

typedef struct {
    char nome[30];
    /*podemos adicionar
    mas detalhes para 
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