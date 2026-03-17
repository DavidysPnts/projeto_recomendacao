#include <iostream>
#include "projeto.h"

using namespace std;

int main() {
    cout << "Sistema de Recomendacao:\n" << endl;

    // 1. Carregar dados (Módulo p1)
    carregar_base("dados_venda_cluster_0.csv");

    // 2. Criar estrutura matemática (Módulo p2)
    criar_matriz_densa();

    // 3. Processar similaridade (Módulo p2)
    computar_similaridade_jaccard();

    // 4. Teste final
    cout << "\nVerificacao de Dados:" << endl;
    exibir_compras_cliente("99IE1A01");
    exibir_compras_cliente("9OFA7P01");
    exibir_compras_cliente("99DL9N01");
    
    if (vetor_clientes.size() > 1) {
        cout << "Distancia (Jaccard) entre Cliente 0 e Cliente 1: " 
             << matriz_similaridade[0][1] << endl;
    }

    return 0;
}