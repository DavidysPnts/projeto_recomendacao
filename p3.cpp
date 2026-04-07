#include "projeto.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Obrigatorio para conversao de std::vector e listas do Python

namespace py = pybind11;

using namespace std;

bool compararPorScore(const ProdutoRanqueado &a, const ProdutoRanqueado &b) {
    return a.score_ranqueamento < b.score_ranqueamento; 
}

vector<ProdutoRanqueado> gerar_recomendacoes(Recomendador &rec, string cod_cliente_c, int k) {
    vector<ProdutoRanqueado> recomendacoes_finais;

    if (rec.mapa_clientes.find(cod_cliente_c) == rec.mapa_clientes.end()) {
        cout << "Cliente nao encontrado." << endl;
        return recomendacoes_finais;
    }

    int c = rec.mapa_clientes[cod_cliente_c];
    int total_produtos = (int)rec.vetor_produtos.size();
    int total_clientes = (int)rec.vetor_clientes.size();

    vector<ProdutoRanqueado> R(total_produtos);
    for (int p = 0; p < total_produtos; p++) {
        R[p].id_produto = p;
        R[p].score_ranqueamento = 1.0; 
    }

    vector<int> L;
    for (int s = 0; s < total_clientes; s++) {
        if (s == c) continue;

        double similaridade_c_s = rec.matriz_similaridade[c][s];
        
        if (similaridade_c_s < 1.0) {
            L.push_back(s);
        }
    }

    for (int s : L) {
        double similaridade_c_s = rec.matriz_similaridade[c][s];

        for (int p = 0; p < total_produtos; p++) {
            bool s_comprou = (rec.matriz_densa[s][p] == 1);
            bool c_nao_comprou = (rec.matriz_densa[c][p] == 0);

            if (s_comprou && c_nao_comprou) {
                R[p].score_ranqueamento *= similaridade_c_s;
            }
        }
    }

    sort(R.begin(), R.end(), compararPorScore);

    for (int i = 0; i < k && i < (int)R.size(); i++) {
        if (R[i].score_ranqueamento < 1.0) {
            recomendacoes_finais.push_back(R[i]);
        }
    }

    return recomendacoes_finais;
}