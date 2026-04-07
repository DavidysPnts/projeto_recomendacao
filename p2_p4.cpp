#include "projeto.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Obrigatorio para conversao de std::vector e listas do Python

namespace py = pybind11;

using namespace std;

void criar_matriz_densa(Recomendador &rec) {
    int n_clientes = (int)rec.vetor_clientes.size();
    int n_produtos = (int)rec.vetor_produtos.size();

    rec.matriz_densa.assign(n_clientes, vector<int>(n_produtos, 0));

    for (int i = 0; i < n_clientes; i++) {
        for (int id_produto : rec.compras_clientes[i]) {
            rec.matriz_densa[i][id_produto] = 1;
        }
    }
    cout << "Matriz densa de compras criada!" << endl;
}

void computar_similaridade_jaccard(Recomendador &rec, bool modo_otimizado) {
    int n = (int)rec.vetor_clientes.size();
    int p = (int)rec.vetor_produtos.size();

    rec.matriz_intersecao.assign(n, vector<int>(n, 0));

    if (modo_otimizado) {
        // Modo Otimizado
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int soma = 0;
                for (int k = 0; k < p; k++) {
                    soma += rec.matriz_densa[i][k] * rec.matriz_densa[j][k];
                }
                rec.matriz_intersecao[i][j] = soma;
                rec.matriz_intersecao[j][i] = soma;
            }
        }
    } else {
        // Modo Padrão
        vector<vector<int>> transposta(p, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < p; j++) {
                transposta[j][i] = rec.matriz_densa[i][j];
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) { 
                double soma = 0;
                for (int k = 0; k < p; k++) {
                    soma += rec.matriz_densa[i][k] * transposta[k][j];
                }
                rec.matriz_intersecao[i][j] = (int)soma;
            }
        }
    }

    rec.matriz_similaridade.assign(n, vector<float>(n, 0.0f));

    for (int i = 0; i < n; i++) {
        int soma_i = (int)rec.compras_clientes[i].size();
        for (int j = 0; j < n; j++) { 
            if (i == j) {
                rec.matriz_similaridade[i][j] = 0.0f;
                continue;
            }

            int intersecao = rec.matriz_intersecao[i][j];

            if (soma_i > 0) {
                rec.matriz_similaridade[i][j] = 1.0f - ((float)intersecao / soma_i);
            } else {
                rec.matriz_similaridade[i][j] = 1.0f;
            }
        }
    }
    if (modo_otimizado) {
        cout << "Matriz de similaridade computada (modo otimizado)." << endl;
    } else {
        cout << "Matriz de similaridade computada (modo padrao)." << endl;
    }
}