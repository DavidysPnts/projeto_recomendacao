import csv
import time
import Recomendador

def carregar_base(nome_arquivo):
    """
    Traduz a funcionalidade de carregar_base do C++ para Python.
    Realiza o mapeamento de IDs de clientes e produtos e preenche as listas de compras.
    """
    vetor_clientes = []
    mapa_clientes = {}
    vetor_produtos = []
    mapa_produtos = {}
    compras_clientes = []

    try:
        with open(nome_arquivo, mode='r', encoding='utf-8') as arquivo:
            # O leitor de CSV lida automaticamente com a separação por vírgulas
            leitor = csv.reader(arquivo)
            
            # Pula o cabeçalho (equivalente ao primeiro fgets no C++)
            cabecalho = next(leitor)

            # Para simular as "duas passagens" do C++ sem fechar o arquivo, 
            # armazenamos os dados em uma lista temporária
            linhas = list(leitor)

            # 1ª Passagem: Mapear os IDs (Clientes e Produtos)
            for linha in linhas:
                if len(linha) < 4:
                    continue
                
                # Desempacota os dados da linha
                data, cod_cliente, cod_produto, nome_produto = linha[0], linha[1], linha[2], linha[3]

                # Mapeamento de Clientes
                if cod_cliente not in mapa_clientes:
                    mapa_clientes[cod_cliente] = len(vetor_clientes)
                    vetor_clientes.append(cod_cliente)

                # Mapeamento de Produtos
                if cod_produto not in mapa_produtos:
                    mapa_produtos[cod_produto] = len(vetor_produtos)
                    vetor_produtos.append(nome_produto)

            # Inicializa a lista de listas de compras (equivalente ao resize no C++)
            compras_clientes = [[] for _ in range(len(vetor_clientes))]

            # 2ª Passagem: Preencher as listas de compras com IDs
            for linha in linhas:
                if len(linha) < 4:
                    continue
                
                cod_cliente = linha[1]
                cod_produto = linha[2]
                
                id_cliente = mapa_clientes[cod_cliente]
                id_produto = mapa_produtos[cod_produto]
                
                compras_clientes[id_cliente].append(id_produto)

        print(f"Base de dados carregada: {len(vetor_clientes)} clientes.")
        return vetor_clientes, vetor_produtos, mapa_clientes, mapa_produtos, compras_clientes

    except FileNotFoundError:
        print(f"Erro ao abrir o arquivo: {nome_arquivo}")
        return [], [], {}, {}, []

def exibir_compras_cliente(rec_obj, cod_cliente):
    """
    Traduz a função exibir_compras_cliente.
    Assume que rec_obj é o objeto da struct Recomendador (via pybind11) 
    ou possui os mesmos atributos mapeados.
    """
    if cod_cliente not in rec_obj.mapa_clientes:
        print(f"Cliente {cod_cliente} nao encontrado.")
        return

    # No Python, acessamos o dicionário (mapa) para pegar o ID
    id_cliente = rec_obj.mapa_clientes[cod_cliente]
    print(f"Produtos de {cod_cliente}: ", end="")

    # Percorre os IDs de produtos na lista do cliente
    for id_prod in rec_obj.compras_clientes[id_cliente]:
        # Busca o nome no vetor de produtos
        print(f"{rec_obj.vetor_produtos[id_prod]} | ", end="")
    print() # Nova linha


# =====================================================================
# O EQUIVALENTE AO int main() DO SEU ARQUIVO C++
# =====================================================================
def main():
    print("Sistema de Recomendacao:\n")

    # 1. Carrega os dados usando a função em Python
    vetor_clientes, vetor_produtos, mapa_clientes, mapa_produtos, compras_clientes = carregar_base('dados_venda_cluster_0.csv')

    # 2. Instancia a Struct do C++ no Python e preenche os dados
    rec = Recomendador.Recomendador()
    rec.vetor_clientes = vetor_clientes
    rec.vetor_produtos = vetor_produtos
    rec.mapa_clientes = mapa_clientes
    rec.compras_clientes = compras_clientes
    rec.mapa_produtos = mapa_produtos

    # 3. Chama as funções C++ para a Matriz Densa
    Recomendador.criar_matriz_densa(rec)

    # --- Teste do padrão ---
    t1 = time.perf_counter()
    Recomendador.computar_similaridade_jaccard(rec, False)
    t2 = time.perf_counter()
    tempo_padrao = t2 - t1

    # --- Teste do otimizado ---
    t3 = time.perf_counter()
    Recomendador.computar_similaridade_jaccard(rec, True)
    t4 = time.perf_counter()
    tempo_otimizado = t4 - t3

    # Comparativo de Performance
    print("\n--- Comparativo de Performance ---")
    print(f"Tempo Padrao: {tempo_padrao:.6f} segundos")
    print(f"Tempo Otimizado: {tempo_otimizado:.6f} segundos")

    # Verificação de Dados (Em Python)
    print("\nVerificacao de Dados:")
    exibir_compras_cliente(rec, "99DL9N01")
    exibir_compras_cliente(rec, "77602301")
    exibir_compras_cliente(rec, "99E35501")
    
    # A matriz_similaridade em C++ vira uma lista de listas no Python
    print(f"\nDistancia Jaccard entre Cliente 0 e Cliente 1: {rec.matriz_similaridade[0][1]}")

    print("\nRecomendacoes:")

    clientes_teste = ["99DL9N01", "77602301", "99E35501"]
    k = 5

    # Laço de Recomendações
    for cod in clientes_teste:
        print(f"\nRecomendacoes para o cliente: {cod}")

        # Chama a função em C++
        recomendacoes = Recomendador.gerar_recomendacoes(rec, cod, k)

        if not recomendacoes: # Equivalente ao recomendacoes.size() == 0
            print("Nenhuma recomendacao encontrada para este cliente.")
        else:
            for j, prod in enumerate(recomendacoes):
                # Extrai os dados do objeto ProdutoRanqueado
                id_prod = prod.id_produto
                nome = rec.vetor_produtos[id_prod]
                score = prod.score_ranqueamento

                print(f"  {j + 1}. {nome} (Score: {score:.4f})")

if __name__ == "__main__":
    main()