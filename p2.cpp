#include "projeto.h"

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

void computar_similaridade_jaccard(Recomendador &rec) {
    int n = (int)rec.vetor_clientes.size();
    int p = (int)rec.vetor_produtos.size();

    rec.matriz_intersecao.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < p; k++) {
                rec.matriz_intersecao[i][j] += rec.matriz_densa[i][k] * rec.matriz_densa[j][k];
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
    cout << "Matriz de similaridade computada." << endl;
}