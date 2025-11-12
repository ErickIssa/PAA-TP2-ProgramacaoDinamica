import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Lê o CSV
df = pd.read_csv("resultados.csv")

# Assume que a primeira coluna é o tamanho (n²) e a segunda é o tempo
tamanho = df.iloc[:, 0]
tempo = df.iloc[:, 1]

# Converte o tamanho em n (ex: 4 → 2, 9 → 3, 16 → 4)
n = np.sqrt(tamanho)

# Ordena por n
df["n"] = n
df = df.sort_values(by="n").reset_index(drop=True)
n = df["n"]
tempo = df.iloc[:, 1]

# Define o número de grupos
num_grupos = 50
tamanho_grupo = len(df) // num_grupos

# Calcula médias por grupo
medias_tempo = []
intervalos = []

for i in range(num_grupos):
    inicio = i * tamanho_grupo
    fim = (i + 1) * tamanho_grupo
    n_inicio = int(n.iloc[inicio])
    n_fim = int(n.iloc[fim - 1])
    media = tempo.iloc[inicio:fim].mean()
    medias_tempo.append(media)
    intervalos.append(f"{n_inicio}x{n_inicio}–{n_fim}x{n_fim}")

# Plota o gráfico
plt.figure(figsize=(12, 6))
plt.plot(intervalos, medias_tempo, marker='o', linestyle='-', color='b')
plt.xticks(rotation=45, ha='right')
plt.xlabel("Intervalos de tamanhos do mapa (nxn)")
plt.ylabel("Tempo médio de execução (s)")
plt.title("Tempo médio de execução por intervalo de tamanho do mapa")
plt.grid(True, linestyle='--', alpha=0.6)
plt.tight_layout()
plt.show()
