<!doctype html>
<html lang="pt-BR">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width,initial-scale=1" />
  <title>Trabalho — Tema e Programação Dinâmica</title>
  <style>
    body{font-family:system-ui,-apple-system,Segoe UI,Roboto,"Helvetica Neue",Arial;margin:36px;color:#111}
    header{border-left:6px solid #286090;padding:12px 18px;background:#f6f9fc}
    h1{margin:0 0 8px;font-size:28px}
    h2{margin-top:22px;color:#286090}
    p{line-height:1.5;margin:10px 0}
    code{background:#f1f3f5;padding:2px 6px;border-radius:4px;font-family:monospace}
    .note{font-size:0.95rem;color:#444;background:#fffbe6;padding:10px;border-left:4px solid #ffd24d;border-radius:4px}
  </style>
</head>
<body>
  <header>
    <h1>Tema do Trabalho e Tratamento por Programação Dinâmica</h1>
    <p>Resumo conciso do problema e de como a solução explora conceitos de Programação Dinâmica (PD).</p>
  </header>

  <section>
    <h2>Tema do Trabalho</h2>
    <p>
      O trabalho propõe a construção de um algoritmo que encontra o <strong>melhor percurso</strong> em mapas
      (duas versões: presente e passado) para que uma tripulação chegue a um inimigo final com a maior
      quantidade de força possível. O mapa contém células transponíveis, blocos intransponíveis, inimigos
      (custo em força), zonas de descanso (recuperação de força) e <em>âncoras temporais</em> que permitem
      trocar entre os mapas sem ganho ou perda de força. O movimento deve sempre avançar para a direita
      (com possibilidade de subir/descer), iniciando em qualquer célula da coluna esquerda e saindo em qualquer
      célula da coluna direita.
    </p>
  </section>

  <section>
    <h2>Como o problema é tratado por Programação Dinâmica</h2>
    <p>
      A solução exige otimização global sobre um espaço de estados discretos e, por isso, é natural modelar
      o problema com Programação Dinâmica. A abordagem identifica subproblemas sobrepostos e explora
      estrutura ótima por partes para construir a solução ótima a partir de soluções ótimas de subpassos.
    </p>

    <h3>Modelagem de estados</h3>
    <p>
      Cada estado pode ser representado por uma tripla <code>(linha, coluna, tempo)</code>, onde
      <code>tempo</code> indica se estamos no mapa do presente ou do passado. A cada estado associamos a melhor
      quantidade de força possível ao chegar nele (ou o custo mínimo acumulado). Opcionalmente, pode-se incluir
      a força remanescente no estado se usar uma formulação de maximização direta.
    </p>

    <h3>Transições</h3>
    <p>
      De um estado <code>(i, j, t)</code> as transições válidas são para <code>(i, j+1, t)</code>,
      <code>(i-1, j+1, t)</code> e <code>(i+1, j+1, t)</code> — avançando para a próxima coluna mantendo ou
      trocando a linha. Se a célula for uma âncora, existe também a transição para <code>(i, j, 1-t)</code>
      sem alteração na força. Cada transição incorpora o efeito da célula de destino: perda de força por
      inimigo, ganho por descanso, ou impossibilidade em células intransponíveis.
    </p>

    <h3>Recorrência e estrutura ótima</h3>
    <p>
      A relação recursiva define o melhor valor em <code>(i,j,t)</code> como o máximo (ou mínimo custo) entre
      os valores dos estados predecessores após aplicar o efeito da célula. Isso satisfaz a propriedade de
      <em>subestrutura ótima</em>, porque o melhor caminho até um estado passa por melhores caminhos até seus
      predecessores.
    </p>

    <h3>Implementação prática (memoização/tabulação)</h3>
    <p>
      Na prática a PD pode ser implementada por tabulação iterativa (preenchendo colunas da esquerda para a direita)
      ou por memoização recursiva com cache. A tabulação é geralmente preferível aqui por permitir
      iteração explícita sobre colunas e fácil reconstrução do caminho ótimo guardando ponteiros de predecessor.
    </p>

    <h3>Reconstrução do caminho e critérios de parada</h3>
    <p>
      Para imprimir o trajeto é suficiente guardar, para cada estado, o predecessor que originou o melhor valor.
      Ao final, entre as células da última coluna escolhe-se a com maior força remanescente; a partir dela
      reconstrói-se o caminho até a coluna inicial.
    </p>

    <h3>Complexidade e cuidados</h3>
    <p>
      O espaço de estados é proporcional a <code>O(H × W × 2)</code> (duas camadas temporais). Cada estado considera
      no máximo 3 transições para a coluna seguinte além da possível troca por âncora, logo o tempo é
      <code>O(H × W)</code> multiplicado por custo constante. É importante tratar corretamente células intransponíveis
      e verificar se a força chega a zero (caso em que o caminho torna-se inválido).
    </p>
  </section>

  <footer class="note">
    Observação: esta explicação foca exclusivamente no tema do trabalho e no tratamento por Programação Dinâmica,
    conforme solicitado.
  </footer>
</body>
</html>
