#include <iostream>
#include <cstdio>
#include "projeto.h"

using namespace std;

// Nossas estruturas principais
vector<string> vetor_clientes;
map<string, int> mapa_clientes;

vector<string> vetor_produtos;
map<string, int> mapa_produtos;

vector<list<int>> compras_clientes;

void carregar_base(const char* caminho_arquivo) {
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Variáveis temporárias para o fscanf
    char data[20], cod_cliente[20], cod_produto[20], nome_produto[100];
    char cabecalho[200]; // colocar elas em um struct?

    // Pula cabeçalho
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    // 1° passagem: Mapear os IDs
    // O fscanf usa espaço e %[^,] para ler até a vírgula ignorando espaços no CSV
    while (fscanf(arquivo, " %[^,],%[^,],%[^,],%[^\n]", data, cod_cliente, cod_produto, nome_produto) == 4) {

        string str_cliente(cod_cliente);
        string str_produto(cod_produto);
        string str_nome_produto(nome_produto);

        // Se o cliente for novo, cadastra no map e no vetor
        if (mapa_clientes.find(str_cliente) == mapa_clientes.end()) {
            mapa_clientes[str_cliente] = vetor_clientes.size();
            vetor_clientes.push_back(str_cliente);
        }
        if (mapa_produtos.find(str_produto) == mapa_produtos.end()) {
            mapa_produtos[str_produto] = vetor_produtos.size();
            vetor_produtos.push_back(str_nome_produto);
        }
    }

    //Inicializa o vetor de listas com o tamanho final de clientes
    compras_clientes.resize(vetor_clientes.size());

    // 2° passagem: Preencher listas
    rewind(arquivo); // Volta para o início do arquivo
    fgets(cabecalho, sizeof(cabecalho), arquivo); // Pula cabeçalho de novo

    while (fscanf(arquivo, " %[^,],%[^,],%[^,],%[^\n]", data, cod_cliente, cod_produto, nome_produto) == 4) {        
        // Pega o índice interno mapeado
        int id_cliente = mapa_clientes[string(cod_cliente)];
        int id_produto = mapa_produtos[string(cod_produto)];
        compras_clientes[id_cliente].push_back(id_produto); // Adiciona a compra na lista do cliente específico
    }

    fclose(arquivo);
    cout << "Base de dados carregada: " << vetor_clientes.size() << " clientes." << endl;
}

// MÓDULO TESTADOR (Entregável da Atividade)
void exibir_compras_cliente(string cod_cliente) {
    // 1. Verifica se o cliente existe no mapa
    if (mapa_clientes.find(cod_cliente) == mapa_clientes.end()) {
        cout << "Cliente " << cod_cliente << " nao encontrado.\n";
        return; 
    }

    // 2. Descobre o índice interno (inteiro) do cliente
    int id_cliente = mapa_clientes[cod_cliente];
    cout << "Produtos de " << cod_cliente << ": ";
    // Percorre a lista. Para cada id_produto, busca o nome no vetor_produtos
    for (int id : compras_clientes[id_cliente]) {
        cout << vetor_produtos[id] << " | ";
    }
    cout << endl;
}