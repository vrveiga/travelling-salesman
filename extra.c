#include <stdio.h>

#define INF 999999999

// problema do caixeiro viajante em O(N^2*2^N) usando dp em bitmask

int main() {
    int n, ans = INF;
    int dist[16][16] = {};
    int dp[1<<15][16];

    scanf("%d", &n);
    for (int i = 0; i < (n*(n-1))/2; i++) {
        int x, y, w;
        scanf("%d %d %d", &x, &y, &w);
        x--, y--; // prefixar as cidades no 0 (1 -> 0, 2 ->1, ...)
        dist[x][y] = w;
        dist[y][x] = w;
    }

    for (int mask = 0; mask < (1<<(n-1)); mask++) {
        for (int i = 0; i < n; i++) {
            dp[mask][i] = INF; // inicia as distancias mínimas de 1 a n como INF
        }
    }
    
    dp[0][0] = 0; // caso base

    for (int mask = 0; mask < (1<<(n-1)); mask++) { // percorre todas as combinações de cidades visitadas
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (mask & (1<<(j-1))) continue; // se o j já tiver sido visitado
                int now = dp[mask][i] + dist[i][j]; // distancia mínima até i + distancia de i pro próx
                if (now < dp[mask+(1<<(j-1))][j]) {
                    dp[mask+(1<<(j-1))][j] = now; // se for menor, troca 
                }
            }
        }
    }

    for (int i = 1; i < n; i++) {
        if (dp[(1<<(n-1))-1][i] + dist[i][0] < ans) {
            ans = dp[(1<<(n-1))-1][i] + dist[i][0]; 
            // obtem a resposta minima para visitar todas as cidades + distancia de voltar pra 1
        }
    }
    printf("Menor Caminho: %d\n", ans);
}