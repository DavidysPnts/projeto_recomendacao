#include "projeto.h"

using namespace std;

void carregar_base(Recomendador &rec, const char* nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char data[20], cod_cliente[20], cod_produto[20], nome_produto[100], cabecalho[200];

    fgets(cabecalho, sizeof(cabecalho), arquivo);

    // 1° passagem: Mapear os IDs
    while (fscanf(arquivo, " %[^,],%[^,],%[^,],%[^\n]", data, cod_cliente, cod_produto, nome_produto) == 4) {

        string str_cliente(cod_cliente);
        string str_codproduto(cod_produto);
        string str_nome_produto(nome_produto);

        if (rec.mapa_clientes.find(str_cliente) == rec.mapa_clientes.end()) {
            rec.mapa_clientes[str_cliente] = rec.vetor_clientes.size();
            rec.vetor_clientes.push_back(str_cliente);
        }
        if (rec.mapa_produtos.find(str_codproduto) == rec.mapa_produtos.end()) {
            rec.mapa_produtos[str_codproduto] = rec.vetor_produtos.size();
            rec.vetor_produtos.push_back(str_nome_produto);
        }
    }

    rec.compras_clientes.resize(rec.vetor_clientes.size());

    // 2° passagem: Preencher listas
    rewind(arquivo);
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    while (fscanf(arquivo, " %[^,],%[^,],%[^,],%[^\n]", data, cod_cliente, cod_produto, nome_produto) == 4) {
        int id_cliente = rec.mapa_clientes[string(cod_cliente)];
        int id_produto = rec.mapa_produtos[string(cod_produto)];
        rec.compras_clientes[id_cliente].push_back(id_produto);
    }

    fclose(arquivo);
    cout << "Base de dados carregada: " << rec.vetor_clientes.size() << " clientes." << endl;
}

// Testador
void exibir_compras_cliente(Recomendador &rec, string cod_cliente) {
    if (rec.mapa_clientes.find(cod_cliente) == rec.mapa_clientes.end()) {
        cout << "Cliente " << cod_cliente << " nao encontrado.\n";
        return; 
    }

    int id_cliente = rec.mapa_clientes[cod_cliente];
    cout << "Produtos de " << cod_cliente << ": ";

    for (int id : rec.compras_clientes[id_cliente]) {
        cout << rec.vetor_produtos[id] << " | ";
    }
    cout << endl;
}