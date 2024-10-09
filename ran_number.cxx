/*
Feito por: Vinicius == Jiboia
 Gerador de casos do rudinei
 depois de compilar chamar com os seguintes parametros
 arg1 é a quantidade de cidades 
 arg2 é a distancia maxima entre duas cidades para esse caso 
 arg3 é a probabilidade de uma cidade n ter conexão com uma outra (se for 0 vai ser completamente conectado, nao é mt bom deixar numeros proximos de 100)
 
 Se vc compilar com -Dncheck vc remove a parte de ele garantir que existe um caminho possivel, gera casos mais rapidamente.

 NAO É GARANTIA QUE VAI SEMPRE GERAR UM CASO VALIDO PQ EU N TESTEI MT 
*/


#include <random>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <utility>

#ifndef ncheck 

auto check_pos (int init, std::vector<int>& perm, const std::vector<std::vector<int>>& adj) -> int {
	if (!adj[init][perm[0]]) return 1;

	for (int i = 0; i < perm.size() - 1; ++i) {
		if (!adj[perm[i]][perm[i + 1]])
			return 1;
	}

	if (!adj[perm[perm.size() - 1]][init]) return 1;

	return 0;
}

auto ham (int init, int tam, const std::vector<std::vector<int>>& adj) -> std::pair<int, std::vector<int>> {
	std::vector<int> perm;
	std::pair<int, std::vector<int>> resp;

	for (int i = 0; i < tam; ++i) {
		if (i != init)
			perm.push_back(i);
	}

	std::vector<int> c(tam);

	int poss = check_pos(init, perm, adj);

	if (!poss) {
		resp.first = poss;
		resp.second = perm;
		return resp;
	}

	int i = 1;

	while (i < tam - 1) {
		if (c[i] < i) {
			if (!(i%2)) {
				std::swap(perm[0], perm[i]);
			}else {
				std::swap(perm[c[i]], perm[i]);
			}
			poss = check_pos(init, perm, adj);

			if (!poss) {
				resp.first = poss;
				resp.second = perm;
				return resp;
			}

			c[i] += 1;
			i = 1;
		} else {
			c[i] = 0;
			i += 1;
		}
	}

	resp.first = poss;
	resp.second = perm;

	return resp;
}	

#endif

int main (int argc, char** argv) {
	//Quantidade de cidades 
	int n;
	//É o limite da poll de distribuição de inteiros que o gerador usa para distancias
	int distancia_max;
	//Se vc colocar em 0 ele sempre vai gerar grafos completamente conexos
	//Eu nao acho q e mt bom colocar numero mt alto
	int por_n_conexao;
	n = std::atoi(argv[1]);
	distancia_max = std::atoi(argv[2]);
	por_n_conexao = std::atoi(argv[3]);

	int qtd_vertices = 0;

	std::random_device rnd;
	std::mt19937 rng(rnd());
	std::uniform_int_distribution<int> c_init(1, n);
	std::uniform_int_distribution<int> conj_amx(1, distancia_max);
	std::uniform_int_distribution<int> cem(1, 100);
	
	std::vector<std::vector<int>> m_adjc(n, std::vector<int>(n));
	
	int z = 0;
	for (int i = 0; i < n; ++i) {
		
		for (int j = z; j < n; ++j) {
			if (!m_adjc[i][j]) {
				if (por_n_conexao > cem(rng) || i == j)
					continue;

				int distancia = conj_amx(rng);
				m_adjc[i][j] = distancia;
				m_adjc[j][i] = distancia;
				++qtd_vertices;
			}
		}

		++z;
	}
	
	//Compile com -Dncheck para ele n garatir q tem um caminho possivel, acelera a criação de casos teste
#ifdef ncheck

	int cid = c_init(rng);
	std::cout << n << "\n" << cid << "\n" << qtd_vertices << "\n";
	
	int n_z = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = n_z; j < n; ++j) {
			if (m_adjc[i][j]) {
				std::cout << i + 1 << " " << j + 1 << " " << m_adjc[i][j] << "\n";
			}
		}

		++n_z;
	}

#else

	int cid = c_init(rng);	
	int n_z = 0;

	auto trt = ham(cid - 1, n, m_adjc);
	
	if (trt.first) {
		if (!m_adjc[cid - 1][trt.second[0]]) {
			int distancia = conj_amx(rng);
			m_adjc[cid - 1][trt.second[0]] = distancia;
			m_adjc[trt.second[0]][cid - 1] = distancia;
			++qtd_vertices;
		}

		for (int i = 0; i < trt.second.size() - 1; ++i) {
			if (!m_adjc[trt.second[i]][trt.second[i + 1]]) {
				int distancia = conj_amx(rng);
				m_adjc[trt.second[i]][trt.second[i + 1]] = distancia;
				m_adjc[trt.second[i + 1]][trt.second[i]] = distancia;
				++qtd_vertices;
			}
		}

		if (!m_adjc[trt.second[trt.second.size() - 1]][cid - 1]) {	
				int distancia = conj_amx(rng);
				m_adjc[trt.second[trt.second.size() - 1]][cid - 1] = distancia;
				m_adjc[trt.second[cid - 1]][trt.second[trt.second.size() - 1]] = distancia;
				++qtd_vertices;
		}
	}

	std::cout << n << "\n" << cid << "\n" << qtd_vertices << "\n";


	for (int i = 0; i < n; ++i) {
		for (int j = n_z; j < n; ++j) {
			if (m_adjc[i][j]) {
				std::cout << i + 1 << " " << j + 1 << " " << m_adjc[i][j] << "\n";
			}
		}

		++n_z;
	}
#endif 
}
