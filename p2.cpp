#include <iostream>
#include "projeto.h"

using namespace std;

vector<vector<int>> matriz_densa;
vector<vector<float>> matriz_similaridade;

void criar_matriz_densa() {
    int n_clientes = (int)vetor_clientes.size();
    int n_produtos = (int)vetor_produtos.size();

    matriz_densa.assign(n_clientes, vector<int>(n_produtos, 0));

    for (int i = 0; i < n_clientes; i++) {
        for (int id_produto : compras_clientes[i]) {
            matriz_densa[i][id_produto] = 1;
        }
    }
    cout << "Matriz densa de compras criada!" << endl;
}

void computar_similaridade_jaccard() {
    int n = (int)vetor_clientes.size();
    int p = (int)vetor_produtos.size();
    
    matriz_similaridade.assign(n, vector<float>(n, 0.0f));

    for (int i = 0; i < n; i++) {
        int soma_i = (int)compras_clientes[i].size();
        for (int j = 0; j < n; j++) { 
            if (i == j) {
                matriz_similaridade[i][j] = 0.0f;
                continue;
            }

            int intersecao = 0;

            for (int k = 0; k < p; k++) {
                if (matriz_densa[i][k] == 1 && matriz_densa[j][k] == 1) intersecao++;
            }
            if (soma_i > 0) {
                matriz_similaridade[i][j] = 1.0f - ((float)intersecao / soma_i);
            } else {
                matriz_similaridade[i][j] = 1.0f;
            }
        }
    }
    cout << "Matriz de similaridade computada." << endl;
}