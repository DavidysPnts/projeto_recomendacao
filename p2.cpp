#include <iostream>
#include <vector> //precisa desses includes se já tem no .h?
#include <list>
#include <map>
#include <string>
#include "projeto.h" // A ponte que conecta com a Atividade 1

using namespace std;

// Declaração das matrizes globais da Atividade 2
// Linhas (Clientes) x Colunas (Produtos)
vector<vector<int>> matriz_densa;

// Linhas (Clientes) x Colunas (Clientes)
vector<vector<float>> matriz_similaridade;

// --- PASSO 1: Criar a Matriz Densa ---
void criar_matriz_densa() {
    int n_clientes = (int)vetor_clientes.size();
    int n_produtos = (int)vetor_produtos.size();

    // Inicializa a matriz com zeros
    matriz_densa.assign(n_clientes, vector<int>(n_produtos, 0));

    // Para cada cliente, marcamos 1 nos produtos que estão na sua lista de compras
    for (int i = 0; i < n_clientes; i++) {
        for (int id_produto : compras_clientes[i]) {
            matriz_densa[i][id_produto] = 1;
        }
    }
    cout << "[INFO] Matriz densa de compras criada." << endl;
}

// --- PASSO 2: Calcular Similaridade (Lógica da Transposta e PDF) ---
void computar_similaridade_jaccard() {
    int n = (int)vetor_clientes.size();
    int p = (int)vetor_produtos.size();
    
    matriz_similaridade.assign(n, vector<float>(n, 0.0f));

    // Comparamos cada cliente (i) com TODOS os outros (j)
    for (int i = 0; i < n; i++) {
        // j começa de 0, pois a matriz é assimétrica
        for (int j = 0; j < n; j++) { 
            if (i == j) {
                matriz_similaridade[i][j] = 1.0f;
                continue;
            }

            int intersecao = 0;
            int soma_i = 0;

            // Percorremos os produtos (colunas da matriz densa)
            for (int k = 0; k < p; k++) {
                if (matriz_densa[i][k] == 1 && matriz_densa[j][k] == 1) intersecao++;
                if (matriz_densa[i][k] == 1) soma_i++; // Tamanho de Pi
            }

            // Fórmula exata da Seção 2.2 do PDF
            float resultado = 1.0f;
            if (soma_i > 0) {
                resultado = 1.0f - ((float)intersecao / soma_i);
            }
            
            matriz_similaridade[i][j] = resultado;
        }
    }
    cout << "[INFO] Matriz de similaridade computada." << endl;
}