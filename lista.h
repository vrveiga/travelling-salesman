#ifndef LISTA_H
    #define LISTA_H

    typedef struct lista LISTA;

    // Tamanho máximo da lista
    #define TAM_MAX 20

    // Criar a lista, retornando o ponteiro para ela
    LISTA* lista_criar();
    // Adiciona um elemento (x) ao fim da lista
    void lista_adicionar_fim(LISTA* lista, int x);
    // Remove o último item da lista
    void lista_remover_fim(LISTA* lista);
    // Retorna o elemento a partir de seu "indice" na lista
    int lista_buscar(LISTA* lista, int indice);
    // Troca um dos elementos da lista por outro a partir do indice
    void lista_trocar(LISTA* lista, int indice, int novo);
    // Retorna o tamanho da lista
    int lista_tamanho(LISTA* lista);
    //Limpa a lista de seus elementos
    void lista_limpar(LISTA* lista);
    //Apaga a lista
    void lista_apagar(LISTA** lista);

#endif