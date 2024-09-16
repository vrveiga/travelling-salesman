#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

struct lista {
    int dados[TAM_MAX];
    int tam;
};

LISTA* lista_criar() {
    LISTA* buffer = malloc(sizeof(LISTA));
    if (buffer == NULL) {
        printf("ERRO: Não foi possível alocar a lista!!!\n");
        exit(-1);
    }

    buffer->tam = 0;
    return buffer;
}

void lista_adicionar_fim(LISTA* lista, int x) {
    if (lista == NULL) {
        printf("ERRO: Lista não existe!!!\n");
        return;
    }
    if (lista->tam >= TAM_MAX) {
        printf("ERRO: Lista cheia!!!\n");
        return;
    }

    lista->dados[lista->tam] = x;
    lista->tam++;
}

void lista_remover_fim(LISTA* lista) {
    if (lista == NULL) {
        printf("ERRO: Lista não existe!!!\n");
        return;
    }
    if (lista->tam == 0) {
        printf("ERRO: Lista vazia!!!\n");
        return;
    }

    lista->tam--;
}

int lista_buscar(LISTA* lista, int indice) {
    if (lista == NULL) {
        printf("ERRO: Lista não existe!!!\n");
        return -1;
    }

    if (indice < 0 || indice >= lista->tam) {
        printf("ERRO: Indice inválido!!!\n");
        exit(-1);
    }
    return lista->dados[indice];
}

int lista_tamanho(LISTA* lista) {
    if (lista == NULL) {
        printf("ERRO: Lista não existe!!!\n");
        return -1;
    }

    return lista->tam;
}

void lista_limpar(LISTA* lista) {
    if (lista == NULL) {
        printf("ERRO: Lista não existe!!!\n");
        return;
    }

    lista->tam = 0;
}

void lista_apagar(LISTA** lista) {
    if (*lista == NULL) {
        printf("ERRO: Lista não existe!!!\n");
        return;
    }

    free(*lista);
    *lista = NULL;
}