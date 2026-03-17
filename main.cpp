#include <iostream>
#include "projeto.h"

using namespace std;

int main() {
    cout << "Sistema de Recomendacao:\n" << endl;

    carregar_base("dados_venda_cluster_0.csv");
    criar_matriz_densa();
    computar_similaridade_jaccard();

    cout << "\nVerificacao de Dados:" << endl;
    exibir_compras_cliente("99IE1A01");
    exibir_compras_cliente("9OFA7P01");
    exibir_compras_cliente("99DL9N01");
    
    cout << "\nDistancia Jaccard entre Cliente 0 e Cliente 1: " 
         << matriz_similaridade[0][1] << endl;
    
    return 0;
}