#include <stdio.h>
#include "lista.h"

int brute() {
    
}

int main() {
    int n;
    int dist[16][16] = {};

    scanf("%d", &n);
    for (int i = 0; i < (n*(n-1))/2; i++) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        dist[x][y] = w;
        dist[y][x] = w;
    }

    LISTA* lista = lista_criar();
    lista_remover_fim(lista);
    lista_adicionar_fim(lista, 10);
    printf("%d\n", lista_buscar(lista, 0));
    lista_remover_fim(lista);

    for (int i = 0; i < 25; i++) {
        lista_adicionar_fim(lista, i+1);
    }
    for (int i = 0; i < 25; i++) {
        printf("%d\n", lista_buscar(lista, i));
    }
}