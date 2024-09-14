#ifndef LISTA_H
    #define LISTA_H

    typedef struct lista LISTA;

    #define TAM_MAX 20

    LISTA* lista_criar();
    void lista_adicionar_fim(LISTA* lista, int x);
    void lista_remover_fim(LISTA* lista);
    int lista_buscar(LISTA* lista, int indice);
    int lista_tamanho(LISTA* lista);
    void lista_limpar(LISTA* lista);
    void lista_apagar(LISTA** lista);

#endif