#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

// ... [suas variaveis globais aqui] ...

struct ProdutoRanqueado {
    int id_produto;
    double score_ranqueamento;
};

// Passo 4 (Preparação): Ordenação Não Decrescente (Crescente)
// Retorna true se 'a' é menor que 'b' (os menores scores vêm primeiro)
bool compararPorScoreNaoDecrescente(const ProdutoRanqueado &a, const ProdutoRanqueado &b) {
    return a.score_ranqueamento < b.score_ranqueamento; 
}

// O Módulo de Recomendação Exato
// Nota: Adicionei a matriz_similaridade como parâmetro, pois o Passo 1 e 3 exigem.
vector<ProdutoRanqueado> gerar_recomendacoes_oficial(
    string cod_cliente_c, 
    int k, 
    const vector<int>& matriz_interacao, 
    const vector<double>& matriz_similaridade) 
{
    vector<ProdutoRanqueado> recomendacoes_finais;

    if (mapa_clientes.find(cod_cliente_c) == mapa_clientes.end()) {
        return recomendacoes_finais;
    }

    int c = mapa_clientes[cod_cliente_c];
    int total_produtos = vetor_produtos.size();
    int total_clientes = vetor_clientes.size();

    // =================================================================
    // PASSO 2: Inicialização do Vetor de Ranqueamento (Valor inicial = 1)
    // =================================================================
    vector<ProdutoRanqueado> R(total_produtos);
    for (int p = 0; p < total_produtos; p++) {
        R[p].id_produto = p;
        R[p].score_ranqueamento = 1.0; 
    }

    // =================================================================
    // PASSO 1: Identificação de Vizinhos (L)
    // =================================================================
    vector<int> L;
    for (int s = 0; s < total_clientes; s++) {
        if (s == c) continue; // Não seja o próprio cliente c

        // Busca a similaridade entre c e s na matriz de similaridade
        double sim_c_s = matriz_similaridade[(c * total_clientes) + s];
        
        if (sim_c_s < 1.0) { // Similaridade menor que 1
            L.push_back(s);
        }
    }

    // =================================================================
    // PASSO 3: Cálculo do Ranqueamento
    // =================================================================
    for (int s : L) { // Para cada cliente s pertencente a L
        double sim_c_s = matriz_similaridade[(c * total_clientes) + s];

        for (int p = 0; p < total_produtos; p++) { // Para cada produto p
            
            // Verifica na matriz de interacao se 's' comprou e se 'c' NAO comprou
            bool s_comprou = (matriz_interacao[(s * total_produtos) + p] > 0);
            bool c_nao_comprou = (matriz_interacao[(c * total_produtos) + p] == 0);

            if (s_comprou && c_nao_comprou) {
                // Atualiza o ranqueamento: Rp <- Rp * s(c, s)
                R[p].score_ranqueamento = R[p].score_ranqueamento * sim_c_s;
            }
        }
    }

    // =================================================================
    // PASSO 4: Ordenação e Seleção
    // =================================================================
    // Ordena de forma NÃO DECRESCENTE (Crescente)
    sort(R.begin(), R.end(), compararPorScoreNaoDecrescente);

    // Retorna os k primeiros produtos da lista R
    for (int i = 0; i < k && i < R.size(); i++) {
        recomendacoes_finais.push_back(R[i]);
    }

    return recomendacoes_finais;
}
