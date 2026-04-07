import p2_p4
import p3 # Importa a biblioteca C++ compilada [cite: 97, 125]

def carregar_base(caminho_arquivo):
    vetor_clientes = []
    mapa_clientes = {}
    vetor_produtos = []
    mapa_produtos = {}
    compras_temp = []

    with open(caminho_arquivo, 'r') as f:
        # Pula o cabeçalho
        next(f)
        for linha in f:
            partes = linha.strip().split()
            if len(partes) < 4:
                continue
            
            # Extrai os dados
            cod_cliente = partes[1]
            cod_produto = partes[2]
            nome_produto = " ".join(partes[3:])

            # Mapeamento de Clientes
            if cod_cliente not in mapa_clientes:
                mapa_clientes[cod_cliente] = len(vetor_clientes)
                vetor_clientes.append(cod_cliente)

            # Mapeamento de Produtos
            if cod_produto not in mapa_produtos:
                mapa_produtos[cod_produto] = len(vetor_produtos)
                vetor_produtos.append(nome_produto)

            id_cliente = mapa_clientes[cod_cliente]
            id_produto = mapa_produtos[cod_produto]
            compras_temp.append((id_cliente, id_produto))

    # Constrói a Matriz Densa preenchida com Zeros
    total_clientes = len(vetor_clientes)
    total_produtos = len(vetor_produtos)
    matriz_densa = [[0 for _ in range(total_produtos)] for _ in range(total_clientes)]

    # Preenche a matriz densa com as compras (1)
    for c, p in compras_temp:
        matriz_densa[c][p] = 1

    return vetor_clientes, vetor_produtos, mapa_clientes, matriz_densa, total_clientes, total_produtos

# ==========================================
# EXECUÇÃO PRINCIPAL
# ==========================================
print("Carregando base de dados em Python...")
vetor_clientes, vetor_produtos, mapa_clientes, matriz_densa, total_c, total_p = carregar_base('dados_clientes.txt')

print("Calculando Similaridade usando módulo C++...")
# Chama a função em C++ passando a lista do Python [cite: 139]
matriz_similaridade = p2_p4.calcular_similaridade(matriz_densa)

# Testador exigido para 3 clientes [cite: 222]
clientes_teste = ["CLI-001", "CLI-102", "CLI-999"]
k = 5

print("\n=== GERANDO RECOMENDAÇÕES (Via C++) ===")
for cod in clientes_teste:
    print(f"\nCliente alvo: {cod}")
    if cod not in mapa_clientes:
        print("  -> Cliente não encontrado.")
        continue
    
    id_alvo = mapa_clientes[cod]
    
    # Chama a função C++. Ela retorna uma lista de tuplas (id_produto, score) [cite: 219]
    recomendacoes = p3.recomendar_produtos(
        c=id_alvo, 
        k=k, 
        matriz_densa=matriz_densa, 
        matriz_similaridade=matriz_similaridade,
        total_produtos=total_p,
        total_clientes=total_c
    )

    if not recomendacoes:
        print("  -> Nenhuma recomendação gerada.")
    else:
        for i, (id_prod, score) in enumerate(recomendacoes):
            nome = vetor_produtos[id_prod]
            print(f"  {i+1}º Lugar: {nome} (Score: {score:.4f})")