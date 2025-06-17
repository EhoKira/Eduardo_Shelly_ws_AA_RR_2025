import matplotlib.pyplot as plt
import csv

def ler_log(log_file):
    tamanhos = []
    comparacoes_binaria = []
    comparacoes_interpolacao = []

    with open(log_file, "r") as file:
        reader = csv.reader(file)
        next(reader)
        for linha in reader:
            algoritmo, arquivo, tamanho, chave, indice, comparacoes = linha
            tamanhos.append(int(tamanho))
            if algoritmo == 'binary_recursive':
                comparacoes_binaria.append(int(comparacoes))
            elif algoritmo == 'interpolation_search':
                comparacoes_interpolacao.append(int(comparacoes))

    return tamanhos, comparacoes_binaria, comparacoes_interpolacao

# Função para plotar o gráfico
def plotar_grafico(tamanhos, comparacoes_binaria, comparacoes_interpolacao):
    plt.figure(figsize=(10, 6))

    # Plotando as comparações da busca binária
    plt.plot(tamanhos, comparacoes_binaria, label='Busca Binária', marker='o')

    # Plotando as comparações da busca por interpolação
    plt.plot(tamanhos, comparacoes_interpolacao, label='Busca por Interpolação', marker='o')

    # Configurações do gráfico
    plt.title('Número de Comparações vs Tamanho do Array')
    plt.xlabel('Tamanho do Array')
    plt.ylabel('Número de Comparações')
    plt.xscale('log')  # Usando escala logaritmica no eixo x
    plt.yscale('log')  # Usando escala logaritmica no eixo y
    plt.legend()
    plt.grid(True, which="both", ls="--")
    plt.show()

if __name__ == "__main__":
    log_file_binaria = "../Resultados/test_binary_uniform.csv"
    log_file_interpolacao = "../Resultados/test_interpolation_uniform.csv"
    tamanhos_binaria, comparacoes_binaria, _ = ler_log(log_file_binaria)
    _, _, comparacoes_interpolacao = ler_log(log_file_interpolacao)

    plotar_grafico(tamanhos_binaria, comparacoes_binaria, comparacoes_interpolacao)