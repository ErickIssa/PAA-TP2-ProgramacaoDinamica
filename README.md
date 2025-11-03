<h2>🧩 Tema do Trabalho</h2>

<p>
O trabalho tem como objetivo desenvolver um <strong>algoritmo baseado em Programação Dinâmica (PD)</strong> 
para determinar o melhor caminho possível em um mapa bidimensional que representa o planeta fictício <em>Amphoreus</em>. 
Nesse cenário, uma tripulação precisa atravessar diferentes regiões — divididas entre o <strong>presente</strong> e o <strong>passado</strong> — 
enfrentando inimigos, descansando em áreas seguras e utilizando <strong>âncoras temporais</strong> que permitem alternar entre os dois tempos.
</p>

<p>
O desafio é calcular o <strong>trajeto ótimo</strong> que leva a tripulação até o inimigo final, <em>Nikador</em>, com o <strong>menor desgaste de força</strong> 
possível. Cada movimento tem um custo (quando há inimigos) ou um ganho (em áreas de descanso), e o algoritmo deve garantir 
que a força final da tripulação seja a máxima possível ao término da jornada.
</p>

<h2>🧠 Programação Dinâmica no Problema</h2>

<p>
A <strong>programação dinâmica</strong> é utilizada para resolver o problema de forma eficiente, evitando recomputações 
e aproveitando subestruturas ótimas. Cada estado do problema é definido por uma combinação de:
</p>

<ul>
  <li><strong>posição atual</strong> no mapa (linha e coluna);</li>
  <li><strong>tempo</strong> em que o jogador se encontra (presente ou passado);</li>
  <li><strong>força restante</strong> da tripulação.</li>
</ul>

<p>
A solução utiliza uma <strong>tabela de memorização</strong> (ou estrutura semelhante) para armazenar o melhor valor de força 
obtido até cada posição, considerando todos os caminhos possíveis. Assim, o algoritmo evita explorar trajetos redundantes 
e encontra a rota que maximiza a força final.  
</p>

<p>
Essa abordagem ilustra perfeitamente os princípios de PD, em especial:
</p>

<ul>
  <li><strong>Subproblemas sobrepostos</strong> – cada posição e tempo pode ser alcançada por múltiplos caminhos, mas seu resultado é reutilizado;</li>
  <li><strong>Propriedade da subestrutura ótima</strong> – o melhor caminho global é composto pelos melhores caminhos parciais já calculados.</li>
</ul>

<p>
Dessa forma, o trabalho não apenas explora um cenário criativo, mas também demonstra de maneira prática a aplicação da 
programação dinâmica na <strong>otimização de trajetos com múltiplas dimensões de estado</strong>.
</p>
