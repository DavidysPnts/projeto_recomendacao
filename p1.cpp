#include <iostream>
#include <cstdio>
#include "projeto.h"

using namespace std;

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

    char data[20], cod_cliente[20], cod_produto[20], nome_produto[100];
    char cabecalho[200];

    fgets(cabecalho, sizeof(cabecalho), arquivo);

    // 1° passagem: Mapear os IDs
    while (fscanf(arquivo, " %[^,],%[^,],%[^,],%[^\n]", data, cod_cliente, cod_produto, nome_produto) == 4) {

        string str_cliente(cod_cliente);
        string str_produto(cod_produto);
        string str_nome_produto(nome_produto);

        if (mapa_clientes.find(str_cliente) == mapa_clientes.end()) {
            mapa_clientes[str_cliente] = vetor_clientes.size();
            vetor_clientes.push_back(str_cliente);
        }
        if (mapa_produtos.find(str_produto) == mapa_produtos.end()) {
            mapa_produtos[str_produto] = vetor_produtos.size();
            vetor_produtos.push_back(str_nome_produto);
        }
    }

    compras_clientes.resize(vetor_clientes.size());

    // 2° passagem: Preencher listas
    rewind(arquivo);
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    while (fscanf(arquivo, " %[^,],%[^,],%[^,],%[^\n]", data, cod_cliente, cod_produto, nome_produto) == 4) {
        int id_cliente = mapa_clientes[string(cod_cliente)];
        int id_produto = mapa_produtos[string(cod_produto)];
        compras_clientes[id_cliente].push_back(id_produto);
    }

    fclose(arquivo);
    cout << "Base de dados carregada: " << vetor_clientes.size() << " clientes." << endl;
}

// Testador
void exibir_compras_cliente(string cod_cliente) {
    if (mapa_clientes.find(cod_cliente) == mapa_clientes.end()) {
        cout << "Cliente " << cod_cliente << " nao encontrado.\n";
        return; 
    }

    int id_cliente = mapa_clientes[cod_cliente];
    cout << "Produtos de " << cod_cliente << ": ";

    for (int id : compras_clientes[id_cliente]) {
        cout << vetor_produtos[id] << " | ";
    }
    cout << endl;
}