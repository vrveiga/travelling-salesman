#include <stdio.h>
#include <time.h>
#include "lista.h"

#define INF 99999999

/**
 * Função para gerar todas as permutações de caminhos
 * 
 * @param n -> Número de cidades
 * @param ini -> Cidade inicial 
 * @param m -> Quantidade de caminhos 
 * @param lista -> Lista de dados que guarda a permutação atual
 * @param caminho -> Lista que guarda a rota mais eficiente até o momento
 * @param dist -> Lista de Listas que guarda as distâncias entre as cidades
 * @param usado -> Lista que guarda o valor que verifica se uma cidade já está na permutação atual
 * @param ret -> Distância mais eficiente a ser percorrida
 * 
 * @return -> void
 */
void forca_bruta(LISTA* lista, LISTA* caminho, LISTA* dist[20], LISTA* usado, int n, int* ret, int ini) {  
    // Verifica se a permutação atual possúi o tamanho necessário (n-1)  
    if (lista_tamanho(lista) == n-1) {
        // Soma na variável "atual" as distâncias da rota da permutação atual
        int atual = lista_buscar(dist[ini-1], lista_buscar(lista, 0)-1);

        for (int i = 1; i < n-1; i++) {
            int u = lista_buscar(lista, i-1);
            int v = lista_buscar(lista, i);
            atual += lista_buscar(dist[u-1], v-1);
        }
        atual += lista_buscar(dist[lista_buscar(lista, n-2)-1], ini-1);

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
        // Construção da perumutação. Loop passa pelas cidades 1 até n, colocando elas na
        // estrutura "lista" caso ela não esteja, de forma recursiva
        for (int i = 1; i <= n; i++) {
            if (i == ini || lista_buscar(usado, i-1)) continue;
            lista_trocar(usado, i-1, 1);
            lista_adicionar_fim(lista, i);
            forca_bruta(lista, caminho, dist, usado, n, ret, ini);
            lista_remover_fim(lista);
            lista_trocar(usado, i-1, 0);
        }
    }
}

int main() {
    // Número de cidades, caminhos e cidade inicial
    int n, m, ini;
    // Vetor de listas das distâncias entre as cidades
    LISTA* dist[20];

    // Leitura dos dados e inicializar distâncias
    scanf("%d %d %d", &n, &ini, &m);
    if (n <= 1 || ini < 1 || ini > n) {
        printf("ERRO: Número de cidades inválido!!!\n");
        return 0;
    }

    //Inicializando as listas com as distâncias
    for (int i = 0; i < n; i++) {
        dist[i] = lista_criar();
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            lista_adicionar_fim(dist[i], 0);
        }
    }

    for (int i = 0; i < m; i++) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        x--;
        y--;
        lista_trocar(dist[x], y, w);
        lista_trocar(dist[y], x, w);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (lista_buscar(dist[i], j) == 0) {
                lista_trocar(dist[i], j, INF);
                lista_trocar(dist[j], i, INF);
            }
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         printf("%d ", lista_buscar(dist[i], j));
    //     } printf("\n");
    // }

    // Criação das Estruturas de Dados
    LISTA* lista = lista_criar();
    LISTA* usado = lista_criar();
    LISTA* caminho = lista_criar();
    int resp = INF;

    // Inicializa a lista usado
    for (int i = 0; i < n; i++) {
        lista_adicionar_fim(usado, 0);
    }

    clock_t start, end;

    start = clock();
    forca_bruta(lista, caminho, dist, usado, n, &resp, ini);
    end = clock();

    double tempo = (double)(end - start) / CLOCKS_PER_SEC;

    // printf("Tempo de Execução: %lf segundos\n", tempo);

    // Printando a resposta
    printf("Cidade Origem: %d\n", ini);
    printf("Rota: %d", ini);
    for (int i = 1; i <= n; i++) {
        printf(" - %d", lista_buscar(caminho, i));
    }
    printf("\nMenor Distância: %d\n", resp);

    // Apagando as estruturas
    lista_apagar(&lista);
    lista_apagar(&caminho);
    lista_apagar(&usado);
    for (int i = 0; i < n; i++) {
        lista_apagar(&(dist[i]));
    }

    return 0;
}
