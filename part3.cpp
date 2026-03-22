#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm> // Necessário para o std::sort

using namespace std;

// --- Variáveis globais simuladas do seu projeto ---
extern vector<string> vetor_clientes;
extern map<string, int> mapa_clientes;
extern vector<string> vetor_produtos;
extern map<string, int> mapa_produtos;
// --------------------------------------------------

// 1. A estrutura exigida pelo projeto
struct ProdutoRanqueado {
    int id_produto;
    double score_ranqueamento;
};

// 2. Função de comparação para o std::sort
// Retorna true se 'a' deve vir antes de 'b'.
// Como queremos os MELHORES produtos primeiro, a ordem é DECRESCENTE (>).
bool compararPorScore(const ProdutoRanqueado &a, const ProdutoRanqueado &b) {
    return a.score_ranqueamento > b.score_ranqueamento; 
}

// 3. O Módulo de Recomendação
vector<ProdutoRanqueado> gerar_recomendacoes(string cod_cliente_original, int k, const vector<int>& matriz_plana) {
    vector<ProdutoRanqueado> vetor_ranqueamento;

    // Verifica se o cliente existe na nossa base
    if (mapa_clientes.find(cod_cliente_original) == mapa_clientes.end()) {
        cout << "Erro: Cliente " << cod_cliente_original << " nao encontrado." << endl;
        return vetor_ranqueamento; // Retorna vazio
    }

    int id_cliente = mapa_clientes[cod_cliente_original];
    int total_produtos = vetor_produtos.size();

    // Calcula o score para TODOS os produtos para este cliente
    for (int j = 0; j < total_produtos; j++) {
        ProdutoRanqueado prod;
        prod.id_produto = j;
        
        // Pega o valor base de interação da nossa Matriz Plana
        int indice_flat = (id_cliente * total_produtos) + j;
        int interacoes = matriz_plana[indice_flat];

        // ===================================================================
        // LÓGICA DA SEÇÃO 2.3: Substitua a linha abaixo pelo seu algoritmo!
        // Aqui estou apenas simulando um cálculo fictício para o exemplo.
        // ===================================================================
        prod.score_ranqueamento = (interacoes * 2.5) + (j * 0.1); 
        
        vetor_ranqueamento.push_back(prod);
    }

    // ORDENAÇÃO: Aplica o algoritmo de ordenação com base no score
    sort(vetor_ranqueamento.begin(), vetor_ranqueamento.end(), compararPorScore);

    // Seleciona apenas os k primeiros produtos (ou menos, se k for maior que o total)
    vector<ProdutoRanqueado> top_k;
    for (int i = 0; i < k && i < vetor_ranqueamento.size(); i++) {
        top_k.push_back(vetor_ranqueamento[i]);
    }

    return top_k;
}
