#ifndef PROJETO
#define PROJETO

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std;

struct Recomendador {
    vector<string> vetor_clientes;
    vector<string> vetor_produtos;
    map<string, int> mapa_clientes;
    map<string, int> mapa_produtos;
    vector<list<int>> compras_clientes;
    vector<vector<int>> matriz_densa;
    vector<vector<float>> matriz_similaridade;
};

void carregar_base(Recomendador &rec, const char* nome_arquivo);
void criar_matriz_densa(Recomendador &rec);
void computar_similaridade_jaccard(Recomendador &rec);
void exibir_compras_cliente(Recomendador &rec, string cod_cliente);

#endif