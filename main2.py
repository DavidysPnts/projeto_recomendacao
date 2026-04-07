import time
import Recomendador

def main():
    print("Sistema de Recomendacao:\n")

    # Instancia a Struct do C++
    rec = Recomendador.Recomendador()

    # 1. Carrega os dados usando a função C++ (ERRO 1 corrigido)
    # Isso preenche automaticamente rec.vetor_clientes, mapa_clientes, etc.
    Recomendador.carregar_base(rec, 'dados_venda_cluster_2.csv')

    # 2. Chama as funções C++ para a Matriz Densa
    Recomendador.criar_matriz_densa(rec)

    # --- Teste do padrão ---
    t1 = time.perf_counter()
    Recomendador.computar_similaridade_jaccard(rec, False)
    t2 = time.perf_counter() # <--- AQUI ESTÁ O T2
    tempo_padrao = t2 - t1

    # --- Teste do otimizado ---
    t3 = time.perf_counter()
    Recomendador.computar_similaridade_jaccard(rec, True)
    t4 = time.perf_counter() # <--- AQUI ESTÁ O T4
    tempo_otimizado = t4 - t3

    print("\n--- Comparativo de Performance ---")
    print(f"Tempo Padrao: {tempo_padrao:.6f} segundos")
    print(f"Tempo Otimizado: {tempo_otimizado:.6f} segundos")

    # 3. Verificação de Dados usando a função C++ (ERRO 1 corrigido)
    print("\nVerificacao de Dados:")
    Recomendador.exibir_compras_cliente(rec, "99DL9N01")
    Recomendador.exibir_compras_cliente(rec, "77602301")
    Recomendador.exibir_compras_cliente(rec, "99E35501")
    
    print(f"\nDistancia Jaccard entre Cliente 0 e Cliente 1: {rec.matriz_similaridade[0][1]}")

    print("\nRecomendacoes:")
    clientes_teste = ["99DL9N01", "77602301", "99E35501"]
    k = 5

    for cod in clientes_teste:
        print(f"\nRecomendacoes para o cliente: {cod}")
        recomendacoes = Recomendador.gerar_recomendacoes(rec, cod, k)

        if not recomendacoes:
            print("Nenhuma recomendacao encontrada para este cliente.")
        else:
            for j, prod in enumerate(recomendacoes):
                id_prod = prod.id_produto
                nome = rec.vetor_produtos[id_prod]
                score = prod.score_ranqueamento
                print(f"  {j + 1}. {nome} (Score: {score:.4f})")

if __name__ == "__main__":
    main()