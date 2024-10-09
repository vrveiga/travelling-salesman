#include <stdio.h>
#include "lista.h"
#include <time.h>
#include <stdbool.h>

#define INF 99999999


// Problema do caixeiro viajante em O(N^2*2^N) usando dp em bitmask


int main() {
    int n, ini, m, resp = INF;
    LISTA* dist[16];
    LISTA* dp[1<<15]; // Armazena o caminho mínimo para uma cidade considerando a bitmask
    LISTA* pai[1<<15]; // Armazena a cidades anterior a última de cada mask da dp 

    //Lendo o input
    scanf("%d %d %d", &n, &ini, &m);

    //Inicializando o vetor de listas de adjacência "dist"
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
    
    //Inicializando a "dp" e a "pai"
    for (int mask = 0; mask < (1<<(n-1)); mask++) {
        dp[mask] = lista_criar();
        pai[mask] = lista_criar();
        for (int i = 0; i < n; i++) {
            lista_adicionar_fim(dp[mask], INF); // Inicia todas as distâncias mínimas como INF
            lista_adicionar_fim(pai[mask], -1); // Inicia com -1, não passou por nenhuma cidade
        }
    }

    lista_trocar(dp[0], 0, 0); // Caso base

    clock_t start, end;

    start = clock();
    for (int mask = 0; mask < (1<<(n-1)); mask++) { // Percorre todas as combinações de cidades visitadas
        for (int i = 0; i < n; i++) { 
            for (int j = 1; j < n; j++) {
                if (mask & (1<<(j-1))) continue; // Se o j já tiver sido visitado
                int now = lista_buscar(dp[mask], i) + lista_buscar(dist[i], j); // Distância mínima até i + distancia de i pro próx
                if (now < lista_buscar(dp[mask+(1<<(j-1))], j)) {
                    lista_trocar(dp[mask+(1<<(j-1))], j, now); // Se for menor, troca 
                    lista_trocar(pai[mask+(1<<(j-1))], j, i); // Guarda de onde veio para montar o caminho
                }
            }
        }
    }
    end = clock();

    int ultima_cidade = -1;
    int mask = (1<<(n-1))-1;

    // Obtém a resposta mínima para visitar todas as cidades + distância de voltar para 1
    for (int i = 1; i < n; i++) {
        if (lista_buscar(dp[mask], i) + lista_buscar(dist[i], 0) < resp) {
            resp = lista_buscar(dp[mask], i) + lista_buscar(dist[i], 0);
            ultima_cidade = i;
        }
    }

    double tempo = (double)(end - start) / CLOCKS_PER_SEC;

    // printf("Tempo de Execução: %lf segundos\n", tempo);

    LISTA* caminho = lista_criar(); // Armazena a rota saindo da cidade 1 
    int cidade_atual = ultima_cidade;
    int id = 0;
    int id_ini = -1; //id da cidade ini na lista caminho

    // Armazena o caminho com início e fim na cidade 1 
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

    // Se ini é a cidade 1 
    if (id_ini == -1)
        id_ini = id;

    // Printando a resposta 
    printf("Cidade Origem: %d\n", ini);    
    printf("Rota: %d", ini);

    // A direção do caminho é para esquerda se a distância da cidade nesse sentido for a menor 
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

    // Printa a rota considerando a direção (go_left) e realizando 
    // um "shift" para a rota com início em ini
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

    // Apagando as estrturas    
    lista_apagar(&caminho);
    
    for (int i = 0; i < n; i++) 
        lista_apagar(&(dist[i]));

    for (int i = 0; i < (1<<(n-1)); i++) {
        lista_apagar(&(dp[i]));
        lista_apagar(&(pai[i]));
    }
}