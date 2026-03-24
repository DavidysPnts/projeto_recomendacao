#include "projeto.h"

using namespace std;

int main() {
    Recomendador rec;
    cout << "Sistema de Recomendacao:\n" << endl;

    carregar_base(rec, "dados_venda_cluster_2.csv");
    criar_matriz_densa(rec);

    // Teste do padrão:
    clock_t t1 = clock();
    computar_similaridade_jaccard(rec, false);
    clock_t t2 = clock();
    double tempo_padrao = (double)(t2 - t1) / CLOCKS_PER_SEC;

    // Teste do otimizado:
    clock_t t3 = clock();
    computar_similaridade_jaccard(rec, true); 
    clock_t t4 = clock();
    double tempo_otimizado = (double)(t4 - t3) / CLOCKS_PER_SEC;

    // Exibicao simples dos tempos
    cout << "\n--- Comparativo de Performance ---" << endl;
    cout << "Tempo Padrao: " << tempo_padrao << " segundos" << endl;
    cout << "Tempo Otimizado: " << tempo_otimizado << " segundos" << endl;

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