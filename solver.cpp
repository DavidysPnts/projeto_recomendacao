#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// Inclui o seu cabeçalho principal onde as funções estão declaradas
#include "projeto.h" 

namespace py = pybind11;

PYBIND11_MODULE(Recomendador, r) {
    r.doc() = "Algoritmo de recomendação";

    // ----------------------------------------------------------------------
    // OBSERVAÇÃO IMPORTANTE PARA COMPILAR:
    // Como suas funções usam a struct "Recomendador" e "ProdutoRanqueado", 
    // o pybind11 precisa conhecê-las para não dar erro. 
    // Por isso, essas duas linhas abaixo são obrigatórias antes dos r.def:
    py::class_<Recomendador>(r, "Recomendador")
        .def(py::init<>())
        .def_readwrite("vetor_clientes", &Recomendador::vetor_clientes)
        .def_readwrite("vetor_produtos", &Recomendador::vetor_produtos)
        .def_readwrite("mapa_clientes", &Recomendador::mapa_clientes)
        .def_readwrite("mapa_produtos", &Recomendador::mapa_produtos)
        .def_readwrite("compras_clientes", &Recomendador::compras_clientes)
        .def_readwrite("matriz_densa", &Recomendador::matriz_densa)
        .def_readwrite("matriz_intersecao", &Recomendador::matriz_intersecao)
        .def_readwrite("matriz_similaridade", &Recomendador::matriz_similaridade);

    py::class_<ProdutoRanqueado>(r, "ProdutoRanqueado")
        .def(py::init<>())
        .def_readwrite("id_produto", &ProdutoRanqueado::id_produto)
        .def_readwrite("score_ranqueamento", &ProdutoRanqueado::score_ranqueamento);
    // ----------------------------------------------------------------------

    r.def(
        "gerar_recomendacoes",
        &gerar_recomendacoes,
        "Recebe a struct Recomendador, o código do cliente e a quantidade k, retornando os produtos mais recomendados"
    );

    r.def(
        "computar_similaridade_jaccard",
        &computar_similaridade_jaccard,
        "Calcula a matriz de similaridade entre os clientes, recebendo a struct e um booleano para o modo otimizado"
    );

    r.def(
        "criar_matriz_densa",
        &criar_matriz_densa,
        "Recebe a struct Recomendador preenchida e constrói a matriz densa de compras"
    );
}