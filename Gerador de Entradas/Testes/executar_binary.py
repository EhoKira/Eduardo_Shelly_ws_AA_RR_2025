import subprocess
import glob
import os

# Caminho para o executável
EXECUTAVEL = "./busca_binaria"  # troque para o nome correto se necessário

# Pasta com as entradas
PASTA_ENTRADAS = "entradas/"

# Arquivo de resultados
ARQ_SAIDA = "resultados_binaria.txt"

# Busca todos os arquivos de entrada
entradas = sorted(glob.glob(os.path.join(PASTA_ENTRADAS, "*.txt")))

with open(ARQ_SAIDA, "w") as fsaida:
    for arquivo in entradas:
        # Descobre o tamanho da entrada (quantidade de linhas)
        with open(arquivo) as fin:
            tamanho = sum(1 for _ in fin)
        chave = tamanho // 2  # você pode mudar esse critério

        # Executa o programa C: ./busca_binaria entradas/entrada_XXXX.txt 500
        resultado = subprocess.run(
            [EXECUTAVEL, arquivo, str(chave)],
            capture_output=True, text=True
        )
        # Salva o nome do arquivo, tamanho, chave e a saída do seu programa
        fsaida.write(f"{os.path.basename(arquivo)},{tamanho},{chave},{resultado.stdout.strip()}\n")
        print(f"Rodou {arquivo}")
