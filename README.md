# **Análise de Desempenho de Algoritmos de Busca** 🚀

## **Descrição** 📝

Este projeto compara o desempenho de dois algoritmos de busca em arrays: **Busca Binária** 🔍 e **Busca por Interpolação** 📊. O desempenho é avaliado em termos de **número de comparações** realizadas por cada algoritmo para diferentes tipos de entradas, como **entradas ordenadas** 📈 e **entradas uniformes** 🔢.

### **Algoritmos Implementados**:
1. **Busca Binária** 🔎: Algoritmo de busca eficiente com complexidade **O(log n)**.
2. **Busca por Interpolação** 📏: Algoritmo que usa a interpolação para estimar a posição do valor no array com complexidade média **O(log log n)**.

## **Objetivos do Projeto** 🎯

- **Comparar os algoritmos** de busca binária e interpolação em termos de **número de comparações**.
- **Testar os algoritmos em diferentes entradas**: entradas **ordenadas** 📈 e **uniformemente distribuídas** 🔢.
- **Gerar gráficos** 📊 para visualizar a comparação do desempenho dos algoritmos.
- **Medir o tempo de execução** ⏱️ de cada algoritmo, porém esse dado **não foi levado tanto em conta** na análise principal, pois o foco foi nas **comparações** realizadas pelos algoritmos.

## **Estrutura do Projeto** 🗂️

```plaintext
├── Algoritmos/
│   ├── binary_search_recursive.c  # Implementação da busca binária recursiva
│   ├── interpolation_search.c    # Implementação da busca por interpolação
│   └── binary_search.h           # Cabeçalho para a busca binária
├── Entradas/
│   ├── entrada_1000_sorted.txt  # Exemplo de entradas ordenadas
│   ├── entrada_1000_uniform.txt # Exemplo de entradas uniformes
│   └── ...                      # Outras entradas de diferentes tamanhos
├── Gerador_entradas/
│   ├── gerar_entradas.c         # Código para gerar as entradas automaticamente
├── Gráficos/
│   ├── plotar_grafico.py        # Código para plotar os gráficos comparativos
├── Medir_performance/
│   ├── medir_performance.c      # Código para medir o desempenho dos algoritmos
├── Resultados/
│   ├── test_binary.csv          # Resultados da busca binária
│   ├── test_interpolation.csv   # Resultados da busca por interpolação
├── LICENSE                      # Licença do projeto
├── README.md                    # Este arquivo
```

## **Como Usar** ⚙️

### **1. Preparação do Ambiente** 🖥️

Para rodar este projeto, é necessário ter o Python 🐍 e o compilador C instalados. Você pode instalar o **matplotlib** para gerar os gráficos:

```bash
pip install matplotlib
```

### 2. Gerar Entradas 🔄

O código ```gerar_entradas.c``` na pasta ```Gerador_entradas/``` é responsável por gerar os arquivos de entrada com diferentes tamanhos. Basta compilar e executar:

```bash
gcc gerar_entradas.c -o gerar_entradas
./gerar_entradas
```

### 3. Medir Performance 🏃‍♂️
O código ```medir_performance.c``` na pasta ```Medir_performance/``` é responsável por medir o desempenho dos algoritmos de busca. Ele grava os resultados em dois arquivos CSV: ```test_binary.csv``` e ```test_interpolation.csv```.

Compile e execute o código:

```bash
gcc medir_performance.c ../Algoritmos/binary_search_recursive.c ../Algoritmos/interpolation_search.c -o medir_performance
./medir_performance
```

### 4. Plotar Gráficos 📊

Depois de gerar os arquivos CSV, você pode usar o código Python ```plotar_grafico.py``` na ```pasta Gráficos/``` para gerar gráficos comparativos:

```bash
python plotar_grafico.py
```
Isso irá gerar gráficos comparando o número de comparações feitas pela busca binária e pela busca por interpolação.

### Gráficos Comparativos:

**1. Entradas Ordenadas** 📈

O gráfico abaixo mostra o número de comparações realizadas pela busca binária e pela busca por interpolação para entradas ordenadas.



**2. Entradas Uniformes** 🔢

O gráfico abaixo mostra o número de comparações realizadas pela busca binária e pela busca por interpolação para entradas uniformes.



### **Resultados Esperados** 🎯

Os gráficos gerados irão mostrar como o **número de comparações** cresce com o **tamanho do array** para ambos os algoritmos. Além disso, os arquivos CSV gravados contêm os seguintes dados:

- **Algoritmo**: Tipo de algoritmo (Busca Binária ou Busca por Interpolação).
- **Arquivo**: Nome do arquivo de entrada utilizado.
- **Tamanho**: Tamanho do array.
- **Chave**: Valor procurado.
- **Índice**: Índice do valor encontrado (se encontrado).
- **Comparações**: Número de comparações realizadas.
- **Tempo**: Tempo de execução (opcional).
