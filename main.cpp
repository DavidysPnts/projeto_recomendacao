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
    char data[9], cod_cliente[15], cod_produto[15], nome_produto[100];
    char cabecalho[200];

    // 1. Pula a primeira linha (cabeçalho)
    fscanf(arquivo, "%[^\n]\n", cabecalho);

    // 2. Loop lendo linha a linha
    // Lê as 3 primeiras colunas até o espaço, e o nome do produto até o final da linha (\n)
    while (fscanf(arquivo, "%8s %14s %14s %[^\n]\n", data, cod_cliente, cod_produto, nome_produto) == 4) {
        
        // Convertendo de char array (C) para string (C++) para usar no map/vector
        string str_cliente(cod_cliente);
        string str_produto(cod_produto);
        string str_nome_produto(nome_produto);

        // ==========================================
        // FASE 1: CADASTRO DE CLIENTES
        // ==========================================
        if (mapa_clientes.find(str_cliente) == mapa_clientes.end()) {
            // Cliente não existe. Qual será o índice dele? O tamanho atual do vetor!
            int novo_indice_cliente = vetor_clientes.size();
            
            // Salva no vetor e no mapa
            vetor_clientes.push_back(str_cliente);
            mapa_clientes[str_cliente] = novo_indice_cliente;
            
            // Cria uma lista vazia no vetor de compras para este novo cliente
            list<int> lista_vazia;
            compras_clientes.push_back(lista_vazia);
            
            // Print de debug (opcional, bom para ver se está funcionando)
            cout << "Novo cliente cadastrado: " << str_cliente << " no indice " << novo_indice_cliente << endl;
        }

        // ==========================================
        // FASE 1: CADASTRO DE PRODUTOS
        // ==========================================
        if (mapa_produtos.find(str_produto) == mapa_produtos.end()) {
            // Produto não existe. Mesma lógica do cliente.
            int novo_indice_produto = vetor_produtos.size();
            
            vetor_produtos.push_back(str_nome_produto); // O vetor guarda o NOME
            mapa_produtos[str_produto] = novo_indice_produto; // O mapa liga o CODIGO ao índice
            
            cout << "Novo produto cadastrado: " << str_nome_produto << " no indice " << novo_indice_produto << endl;
        }

        // A FASE 2 (registrar a compra na lista) 
        int id_cliente = mapa_clientes[str_cliente];
        int id_produto = mapa_produtos[str_produto];

        // 2. Acessamos a lista do cliente específico e inserimos o produto
        compras_clientes[id_cliente].push_back(id_produto);
    }

    fclose(arquivo);
}

void exibir_compras_cliente(string cod_cliente) {
    cout << "\n--------------------------------------------------\n";
    cout << "Buscando compras do cliente: " << cod_cliente << "\n";

    // 1. Verifica se o cliente existe no mapa
    if (mapa_clientes.find(cod_cliente) == mapa_clientes.end()) {
        cout << "-> Cliente nao encontrado na base de dados.\n";
        return; // Sai da função se não achar
    }

    // 2. Descobre o índice interno (inteiro) do cliente
    int id_cliente = mapa_clientes[cod_cliente];

    // 3. Acessa a lista encadeada de IDs dos produtos que ele comprou
    list<int> produtos_comprados = compras_clientes[id_cliente];

    cout << "-> Total de produtos comprados: " << produtos_comprados.size() << "\n";
    cout << "-> Lista de Produtos:\n";

    // 4. Percorre a lista. Para cada id_produto, busca o nome no vetor_produtos
    for (int id_produto : produtos_comprados) {
        cout << "   - " << vetor_produtos[id_produto] << "\n";
    }
}

int main() {
    // 1. Carrega os dados do arquivo CSV/TXT para a memória
    // Lembre-se de colocar o nome do arquivo que você criou aí na sua pasta
    carregar_base("dados_venda_cluster_0.csv"); 

    cout << "\n=== TESTADOR DO MODULO LISTA DE COMPRAS ===\n";

    // 2. Exibe as compras de pelo menos 3 clientes (Requisito da entrega)
    exibir_compras_cliente("99IE1A01"); // Cliente que comprou 2 smartphones J4 no seu exemplo
    exibir_compras_cliente("9OFA7P01"); // Cliente que comprou o LG K9
    exibir_compras_cliente("99DL9N01"); // Cliente que comprou o Suporte Univ. Bedin

    // Um teste extra para ver o que acontece se o cliente não existir
    exibir_compras_cliente("CLIENTE_FALSO");

    return 0;
}