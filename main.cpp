#include "projeto.h"

using namespace std;

int main() {
    Recomendador rec;
    cout << "Sistema de Recomendacao:\n" << endl;

    carregar_base(rec, "dados_venda_cluster_0.csv");
    criar_matriz_densa(rec);
    computar_similaridade_jaccard(rec);

    cout << "\nVerificacao de Dados:" << endl;
    exibir_compras_cliente(rec, "99IE1A01");
    exibir_compras_cliente(rec, "9OFA7P01");
    exibir_compras_cliente(rec, "99DL9N01");
    
    cout << "\nDistancia Jaccard entre Cliente 0 e Cliente 1: " 
         << rec.matriz_similaridade[0][1] << endl;
    
    return 0;
}