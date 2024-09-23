#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "lista.h"

#define INF 999999999

/**
 * Função para gerar todas as permutações de caminhos
 * 
 * @param lista -> Estrutura de dados que guarda a permutação atual
 * @param caminho -> Estrutura de dados que guarda a rota mais eficiente até o momento
 * @param dist -> Matriz que guarda as distâncias entre as cidades
 * @param usado -> Vetor que guarda o valor que verifica se uma cidade já está na permutação atual
 * @param n -> Número de cidades
 * @param ret -> Distância mais eficiente a ser percorrida
 * 
 * @return -> void
 */
void forca_bruta(LISTA* lista, LISTA* caminho, int dist[20][20], bool* usado, int n, int* ret, int ini) {  
    // Verifica de a permutação atual possúi o tamanho necessário (n-1)  
    if (lista_tamanho(lista) == n-1) {
        // Soma na variável "atual" as distâncias da rota da permutação atual
        int atual = dist[ini][lista_buscar(lista, 0)];
        for (int i = 1; i < n-1; i++) {
            int u = lista_buscar(lista, i-1);
            int v = lista_buscar(lista, i);
            atual += dist[u][v];
        }
        atual += dist[lista_buscar(lista, n-2)][ini];

        // Verifica se a soma ("atual") é menor que a menor distância até o momento
        if (atual < *ret) {
            // Atualiza a menor distância ("ret") e a melhor rota ("caminho")
            *ret = atual;
            lista_limpar(caminho);
            lista_adicionar_fim(caminho, ini);
            for (int i = 0; i < n-1; i++) {
                int at = lista_buscar(lista, i);
                lista_adicionar_fim(caminho, at);
            }
            lista_adicionar_fim(caminho, ini);
        }
    } else {
        // Construção da perumutação. Loop passa pelas cidades 2 até n, colocando elas na
        // estrutura "lista" caso ela não esteja de forma recursiva
        for (int i = 1; i <= n; i++) {
            if (i == ini || usado[i]) continue;
            usado[i] = true;
            lista_adicionar_fim(lista, i);
            forca_bruta(lista, caminho, dist, usado, n, ret, ini);
            lista_remover_fim(lista);
            usado[i] = false;
        }
    }
}

int main() {
    // Número de cidades, caminhos e cidade inicial
    int n, m, ini;
    // Matriz das distâncias entre as cidades
    int dist[20][20] = {};
    // Vetor que guarda o valor que verifica se uma cidade já está na permutação atual
    bool usado[20] = {};

    // Leitura dos dados
    scanf("%d %d %d", &n, &ini, &m);
    if (n <= 1 || ini < 1 || ini > n) {
        printf("ERRO: Número de cidades inválido!!!\n");
        return 0;
    }

    for (int i = 0; i < m; i++) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        dist[x][y] = w;
        dist[y][x] = w;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            if (dist[i][j] == 0) {
                dist[i][j] = INF;
                dist[j][i] = INF;
            }
        }
    }

    // Criação das Estruturas de Dados
    LISTA* lista = lista_criar();
    LISTA* caminho = lista_criar();
    int resp = INF;

    clock_t start, end;

    start = clock();
    forca_bruta(lista, caminho, dist, usado, n, &resp, ini);
    end = clock();

    double tempo = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Tempo de Execução: %lf segundos\n", tempo);

    // Printando a resposta
    printf("Cidade Origem: %d\n", ini);
    printf("Rota: %d", ini);
    for (int i = 1; i <= n; i++) {
        printf(" - %d", lista_buscar(caminho, i));
    }
    printf("\nMenor Distância: %d\n", resp);

    lista_apagar(&lista);
    lista_apagar(&caminho);
}