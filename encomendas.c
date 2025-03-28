#include <stdio.h>

#include "encomendas.h"




int main(){

    Encomenda nova_encomenda;
    NoEncomenda *lista_encomendas = NULL; // inicializar a lista vazia 

    criarEncomenda(&nova_encomenda);  // Chama a função que preenche os dados

    // Mostra os dados lidos para verificar se correu bem
    printf("\n--- ENCOMENDA CRIADA ---\n");
    printf("ID: %d\n", nova_encomenda.id);
    printf("Cliente: %s\n", nova_encomenda.cliente.nome);
    printf("Descrição: %s\n", nova_encomenda.descricao);
    printf("Data: %02d/%02d/%04d\n", nova_encomenda.data.dia, nova_encomenda.data.mes, nova_encomenda.data.ano); // metemos os (%02d) para o input so ser de dois digitos e o mesmo meetodo para o resto 


    inserirEncomenda(&lista_encomendas,nova_encomenda);

    // testar se inseriu a encomenda 
    printf("\nEncomendas na lista\n");
    listarEncomendas(lista_encomendas);

    return 0;
}