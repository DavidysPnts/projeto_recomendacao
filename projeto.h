#ifndef PROJETO
#define PROJETO

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

// No p3 tem uns vetores que não adicionei na struct por uso temporário!
struct Recomendador {
    vector<string> vetor_clientes;
    vector<string> vetor_produtos;
    map<string, int> mapa_clientes;
    map<string, int> mapa_produtos;
    vector<list<int>> compras_clientes; // Tirar da struct?
    vector<vector<int>> matriz_densa;
    vector<vector<int>> matriz_intersecao; // Tirar da struct?
    vector<vector<float>> matriz_similaridade;
};

struct ProdutoRanqueado {
    int id_produto;
    double score_ranqueamento;
};

void carregar_base(Recomendador &rec, const char* nome_arquivo);
void criar_matriz_densa(Recomendador &rec);
void computar_similaridade_jaccard(Recomendador &rec);
void exibir_compras_cliente(Recomendador &rec, string cod_cliente);
bool compararPorScore(const ProdutoRanqueado &a, const ProdutoRanqueado &b);
vector<ProdutoRanqueado> gerar_recomendacoes(Recomendador &rec, string cod_cliente_c, int k);

#endif