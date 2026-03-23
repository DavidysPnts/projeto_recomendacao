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

    cout << "\nRecomendacoes:" << endl;

    string clientes_teste[] = {"99IE1A01", "9OFA7P01", "99DL9N01"};
    int k = 5;

    for (int i = 0; i < 3; i++) {
        string cod = clientes_teste[i];
        cout << "\nRecomendacoes para o cliente: " << cod << endl;

        vector<ProdutoRanqueado> recomendacoes = gerar_recomendacoes(rec, cod, k);

        if (recomendacoes.size() == 0) {
            cout << "Nenhuma recomendacao encontrada para este cliente." << endl;
        } else {
            for (int j = 0; j < (int)recomendacoes.size(); j++) {
                int id = recomendacoes[j].id_produto;
                string nome = rec.vetor_produtos[id];
                double score = recomendacoes[j].score_ranqueamento;

                cout << "  " << j + 1 << ". " << nome << " (Score: " << score << ")" << endl;
            }
        }
    }

    return 0;
}