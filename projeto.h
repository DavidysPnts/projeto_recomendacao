#ifndef PROJETO
#define PROJETO

#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std;

// --- DADOS DA ATIVIDADE 1 ---
// O 'extern' avisa que essas variáveis foram criadas no arquivo da Atividade 1
extern vector<string> vetor_clientes;
extern map<string, int> mapa_clientes;
extern vector<string> vetor_produtos;
extern map<string, int> mapa_produtos;
extern vector<list<int>> compras_clientes;

// --- DADOS DA ATIVIDADE 2 ---
extern vector<vector<int>> matriz_densa;
extern vector<vector<float>> matriz_similaridade;

// --- PROTÓTIPOS DAS FUNÇÕES ---
void carregar_base(const char* caminho_arquivo);
void exibir_compras_cliente(string cod_cliente);
void criar_matriz_densa();
void computar_similaridade_jaccard();

#endif