#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <cstdio>

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
        string str_cliente(cod_cliente);
        string str_produto(cod_produto);
        
        // Pega o índice interno mapeado
        int id_cliente = mapa_clientes[str_cliente];
        int id_produto = mapa_produtos[str_produto];
        compras_clientes[id_cliente].push_back(id_produto); // Adiciona a compra na lista do cliente específico
    }

    fclose(arquivo);
}

// ==========================================
// MÓDULO TESTADOR (Entregável da Atividade)
// ==========================================
void exibir_compras_cliente(string cod_cliente) {
    cout << "\n--------------------------------------------------\n";
    cout << "Buscando compras do cliente: " << cod_cliente << "\n";

    // 1. Verifica se o cliente existe no mapa
    if (mapa_clientes.find(cod_cliente) == mapa_clientes.end()) {
        cout << "-> Cliente nao encontrado na base de dados.\n";
        return; 
    }

    // 2. Descobre o índice interno (inteiro) do cliente
    int id_cliente = mapa_clientes[cod_cliente];

    // 3. Acessa a lista encadeada de IDs dos produtos que ele comprou
    list<int> produtos_comprados = compras_clientes[id_cliente];

    cout << "-> Total de produtos comprados: " << produtos_comprados.size() << "\n";
    cout << "-> Lista de Produtos:\n";

    // 4. Percorre a lista. Para cada id_produto, busca o nome no vetor_produtos
    for (const int id_produto : produtos_comprados) {
        cout << "   - " << vetor_produtos[id_produto] << "\n";
    }
}

// ==========================================
// FUNÇÃO PRINCIPAL
// ==========================================
int main() {
    // 1. Carrega os dados do arquivo CSV/TXT para a memória
    carregar_base("dados_venda_cluster_0.csv"); 

    cout << "\n=== TESTADOR DO MODULO LISTA DE COMPRAS ===\n";

    // 2. Exibe as compras de pelo menos 3 clientes (Requisito da entrega)
    exibir_compras_cliente("99IE1A01"); 
    exibir_compras_cliente("9OFA7P01"); 
    exibir_compras_cliente("99DL9N01"); 

    // Um teste extra 
    exibir_compras_cliente("CLIENTE_FALSO");

    return 0;
}