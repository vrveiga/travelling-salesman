#include <stdio.h>
#include <stdbool.h>
#include "lista.h"

#define INF 99999999

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
void forca_bruta(LISTA* lista, LISTA* caminho, int dist[20][20], bool* usado, int n, int* ret) {  
    // Verifica de a permutação atual possúi o tamanho necessário (n-1)  
    if (lista_tamanho(lista) == n-1) {
        // Soma na variável "atual" as distâncias da rota da permutação atual
        int atual = dist[1][lista_buscar(lista, 0)];
        for (int i = 1; i < n-1; i++) {
            int u = lista_buscar(lista, i-1);
            int v = lista_buscar(lista, i);
            atual += dist[u][v];
        }
        atual += dist[lista_buscar(lista, n-2)][1];

        // Verifica se a soma ("atual") é menor que a menor distância até o momento
        if (atual < *ret) {
            // Atualiza a menor distância ("ret") e a melhor rota ("caminho")
            *ret = atual;
            lista_limpar(caminho);
            lista_adicionar_fim(caminho, 1);
            for (int i = 0; i < n-1; i++) {
                int at = lista_buscar(lista, i);
                lista_adicionar_fim(caminho, at);
            }
            lista_adicionar_fim(caminho, 1);
        }
    } else {
        // Construção da perumutação. Loop passa pelas cidades 2 até n, colocando elas na
        // estrutura "lista" caso ela não esteja de forma recursiva
        for (int i = 2; i <= n; i++) {
            if (usado[i]) continue;
            usado[i] = true;
            lista_adicionar_fim(lista, i);
            forca_bruta(lista, caminho, dist, usado, n, ret);
            lista_remover_fim(lista);
            usado[i] = false;
        }
    }    
}

int main() {
    // Número de cidades
    int n;
    // Matriz das distâncias entre as cidades
    int dist[20][20] = {};
    // Vetor que guarda o valor que verifica se uma cidade já está na permutação atual
    bool usado[20] = {};

    // Leitura dos dados
    scanf("%d", &n);
    for (int i = 0; i < (n*(n-1))/2; i++) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        dist[x][y] = w;
        dist[y][x] = w;
    }

    // Criação das Estruturas de Dados
    LISTA* lista = lista_criar();
    LISTA* caminho = lista_criar();

    // Variável para guardar a menor distância
    int resp = INF;

    // Chamada da função para calcular a melhor rota e menor distância
    forca_bruta(lista, caminho, dist, usado, n, &resp);

    // Printando a resposta
    printf("Cidade Origem: 1\n");
    printf("Rota: 1");
    for (int i = 1; i < n+1; i++) {
        printf(" - %d", lista_buscar(caminho, i));
    }
    printf("\nMenor Distância: %d\n", resp);

    lista_apagar(&lista);
    lista_apagar(&caminho);
}