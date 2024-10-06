#include <stdio.h>
#include <time.h>

#define INF 99999999

// problema do caixeiro viajante em O(N^2*2^N) usando dp em bitmask

int main() {
    //Declarando variáveis
    int n, ini, m, resp = INF;
    int dist[16][16] = {}; 
    int dp[1<<15][16];
    int pai[1<<15][16];

    //Lendo o input
    scanf("%d %d %d", &n, &ini, &m);
    if (n <= 1 || ini < 1 || ini > n) {
        printf("ERRO: Número de cidades inválido!!!\n");
        return 0;
    }

    //Inicializando a matriz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = 0;
        }
    }

    //Lendo as distâncias entre as cidades
    for (int i = 0; i < m; i++) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        x--, y--; // prefixar as cidades no 0 (1 -> 0, 2 ->1, ...)
        dist[x][y] = w;
        dist[y][x] = w;
    }

    //Lidando com as estradas que não existem
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (dist[i][j] == 0) {
                dist[i][j] = INF;
                dist[j][i] = INF;
            }
        }
    }
    
    for (int mask = 0; mask < (1<<(n-1)); mask++) {
        for (int i = 0; i < n; i++) {
            dp[mask][i] = INF; // inicia as distancias mínimas de 'ini' a n como INF
        }
    }
    
    dp[0][0] = 0; // caso base

    clock_t start, end;

    start = clock();
    for (int mask = 0; mask < (1<<(n-1)); mask++) { // percorre todas as combinações de cidades visitadas
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (mask & (1<<(j-1))) continue; // se o j já tiver sido visitado
                int now = dp[mask][i] + dist[i][j]; // distancia mínima até i + distancia de i pro próx
                if (now < dp[mask+(1<<(j-1))][j]) {
                    dp[mask+(1<<(j-1))][j] = now; // se for menor, troca 
                    pai[mask+(1<<(j-1))][j] = i; // guarda de onde veio para montar o caminho
                }
            }
        }
    }
    end = clock();

    int ultima_cidade = -1;

    for (int i = 1; i < n; i++) {
        if (dp[(1<<(n-1))-1][i] + dist[i][0] < resp) {
            resp = dp[(1<<(n-1))-1][i] + dist[i][0];
            ultima_cidade = i;
            // obtem a resposta minima para visitar todas as cidades + distancia de voltar pra 1
        }
    }

    double tempo = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Tempo de Execução: %lf segundos\n", tempo);

    int caminho[16];
    int mask = (1<<(n-1))-1;
    int cidade_atual = ultima_cidade;
    int id = 0;

    while (cidade_atual != 0) {
        caminho[id++] = cidade_atual + 1;
        int prox_cidade = pai[mask][cidade_atual];
        mask ^= (1<<(cidade_atual-1));
        cidade_atual = prox_cidade;
    }
    caminho[id++] = 1;

    printf("Cidade Origem: 1\n");
    
    printf("Rota: 1");
    for (int i = 0; i <= id-1; i++) {
        printf(" - %d", caminho[i]);
    }

    printf("\nMenor Distância: %d\n", resp);
}