#include <stdio.h>
#include "lista.h"
#include <time.h>
#include <stdbool.h>

#define INF 99999999

// problema do caixeiro viajante em O(N^2*2^N) usando dp em bitmask

int main() {
    //Declarando variáveis
    int n, ini, m, resp = INF;
    LISTA* dist[16];
    LISTA* dp[1<<15];
    LISTA* pai[1<<15];

    //Lendo o input
    scanf("%d %d %d", &n, &ini, &m);

    //Inicializando o vetor de listas de adjacência
    for (int i = 0; i < n; i++) {
        dist[i] = lista_criar();
        for (int j = 0; j < n; j++) {
            lista_adicionar_fim(dist[i], 0);
        }
    }

    //Lendo as distâncias entre as cidades
    for (int i = 0; i < m; i++) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        x--, y--; // prefixar as cidades no 0 (1 -> 0, 2 ->1, ...)
        lista_trocar(dist[x], y, w);
        lista_trocar(dist[y], x, w);
    }

    //Lidando com as estradas que não existem
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (lista_buscar(dist[i], j) == 0) {
                lista_trocar(dist[i], j, INF);
                lista_trocar(dist[j], i, INF);
            }
        }
    }
    
    for (int mask = 0; mask < (1<<(n-1)); mask++) {
        dp[mask] = lista_criar();
        pai[mask] = lista_criar();
        for (int i = 0; i < n; i++) {
            lista_adicionar_fim(dp[mask], INF); // inicia todas as distâncias mínimas como INF
            lista_adicionar_fim(pai[mask], -1);
        }
    }

    lista_trocar(dp[0], 0, 0); // caso base

    clock_t start, end;

    start = clock();
    for (int mask = 0; mask < (1<<(n-1)); mask++) { // percorre todas as combinações de cidades visitadas
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (mask & (1<<(j-1))) continue; // se o j já tiver sido visitado
                int now = lista_buscar(dp[mask], i) + lista_buscar(dist[i], j); // distancia mínima até i + distancia de i pro próx
                if (now < lista_buscar(dp[mask+(1<<(j-1))], j)) {
                    lista_trocar(dp[mask+(1<<(j-1))], j, now); // se for menor, troca 
                    lista_trocar(pai[mask+(1<<(j-1))], j, i); // guarda de onde veio para montar o caminho
                }
            }
        }
    }
    end = clock();

    int ultima_cidade = -1;
    int mask = (1<<(n-1))-1; // mudei isso

    for (int i = 1; i < n; i++) {
        if (lista_buscar(dp[mask], i) + lista_buscar(dist[i], 0) < resp) {
            resp = lista_buscar(dp[mask], i) + lista_buscar(dist[i], 0);
            ultima_cidade = i;
            // obtem a resposta minima para visitar todas as cidades + distancia de voltar pra 1
        }
    }

    double tempo = (double)(end - start) / CLOCKS_PER_SEC;

    // printf("Tempo de Execução: %lf segundos\n", tempo);

    LISTA* caminho = lista_criar();
    int cidade_atual = ultima_cidade;
    int id = 0;
    int id_ini = -1;

    while (cidade_atual != 0) {
        lista_adicionar_fim(caminho, cidade_atual + 1);
        if (cidade_atual+1 == ini) 
            id_ini = id;
        id++;
        int prox_cidade = lista_buscar(pai[mask], cidade_atual);
        mask ^= (1<<(cidade_atual-1));
        cidade_atual = prox_cidade;
    }
    lista_adicionar_fim(caminho, 1);
    if (id_ini == -1)
        id_ini = id;

    // printf("%d\n", id_ini);
    // for (int i = 0; i <= id; i++) printf("%d ", lista_buscar(caminho, i));
    // printf("\n");

    printf("Cidade Origem: %d\n", ini);    
    printf("Rota: %d", ini);

    bool go_left = true;
    if (id_ini == 0) {
        if (lista_buscar(caminho, id) > lista_buscar(caminho, 1))
            go_left = false;
    } else if (id_ini == id) {
        if (lista_buscar(caminho, id-1) > lista_buscar(caminho, 0))
            go_left = false;
    } else {
        if (lista_buscar(caminho, id_ini-1) > lista_buscar(caminho, id_ini+1))
            go_left = false;
    }

    if (go_left) {
        for (int i = id_ini-1; i >= 0; i--) 
            printf(" - %d", lista_buscar(caminho, i));
        for (int i = id; i >= id_ini; i--)
            printf(" - %d", lista_buscar(caminho, i));
    } else {
        for (int i = id_ini+1; i <= id; i++)
            printf(" - %d", lista_buscar(caminho, i));
        for (int i = 0; i <= id_ini; i++) 
            printf(" - %d", lista_buscar(caminho, i));
    }

    printf("\nMenor Distância: %d\n", resp);

    // Desalocar listas
    lista_apagar(&caminho);
    
    for (int i = 0; i < n; i++) 
        lista_apagar(&(dist[i]));

    for (int i = 0; i < (1<<(n-1)); i++) {
        lista_apagar(&(dp[i]));
        lista_apagar(&(pai[i]));
    }
}