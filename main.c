#include <stdio.h>
#include <stdbool.h>
#include "lista.h"

#define INF 99999999

void forca_bruta(LISTA* lista, int dist[20][20], bool* usado, int n, int* ret) {    
    if (lista_tamanho(lista) == n-1) {
        int atual = dist[1][lista_buscar(lista, 0)];
        for (int i = 1; i < n-1; i++) {
            int u = lista_buscar(lista, i-1);
            int v = lista_buscar(lista, i);
            atual += dist[u][v];
        }
        atual += dist[lista_buscar(lista, n-2)][1];

        if (atual < *ret) {
            *ret = atual;
        }
    } else {
        for (int i = 2; i <= n; i++) {
            if (usado[i]) continue;
            usado[i] = true;
            lista_adicionar_fim(lista, i);
            forca_bruta(lista, dist, usado, n, ret);
            lista_remover_fim(lista);
            usado[i] = false;
        }
    }    
}

int main() {
    int n;
    int dist[20][20] = {};
    bool usado[20] = {};

    scanf("%d", &n);
    for (int i = 0; i < (n*(n-1))/2; i++) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        dist[x][y] = w;
        dist[y][x] = w;
    }

    LISTA* lista = lista_criar();
    int resp = INF;

    forca_bruta(lista, dist, usado, n, &resp);

    printf("O melhor caminho tem peso: %d\n", resp);

    lista_apagar(&lista);
}